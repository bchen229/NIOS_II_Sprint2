#include "altera_up_avalon_character_lcd.h"
#include "Hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Structures.h"
#include "Colours.h"
#include "SD_CARD.h"

#define pi 3.14159265358979323846

//DE2 Display variables
char seven_seg_decode_table[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
		0x07, 0x7F, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
char hex_segments[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void Init_GPS(void) {

	GPS_Baud = 0x05;
	GPS_Control = 0x15;

}

char GetData(void) {

	while ((GPS_Status & 0x01) != 0x01)
		;
	return GPS_RxData;

}

void putcharGPS(int c) {

	while ((GPS_Status & 0x02) != 0x02)
		;
	GPS_TxData = c;

}

void putString(char *s) {
	char i;
	while ((i = *s) != 0) {

		putcharGPS(i);
		s++;

	}
}

void StopLogging(void) {
	char *buff = "$PMTK185,1";
	putString(buff);

}

void ClearLogging(void) {
	char *buff = "$PMTK184,1";
	putString(buff);
}

void StartLogger(void) {
	char *buff = "$PMTK186,1";
	putString(buff);

}

char *FloatToLatitudeConversion(int x)
{
	static char buff[100];
	float *ptr = (float *) (&x); // cast int to float
	float f = *ptr; // get the float
	sprintf(buff, "%2.4f", f); // write in string to an array
	return buff;
}
char *FloatToLongitudeConversion(int x)
{
	static char buff[100];
	float *ptr = (float *) (&x);
	float f = *ptr;
	sprintf(buff, "%3.4f", f);
	return buff;
}

int swapEndian(char *s) {
	register int val;
	val = strtoul(s, NULL, 16); // convert to 4 byte int form in base 16
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	val = (val << 16) | ((val >> 16) & 0xFFFF);
	return val;
}

int checkBuff(char *buff) {

	char *check1 = "GPGGA";
	char *tempBuff;
	char inputCheck[4];
	tempBuff = inputCheck;
	int i;
	for (i = 0; i < 5; i++) {
		*tempBuff++ = buff[i];
	}
	*tempBuff = '\0';
	if (strcmp(inputCheck, check1) == 0) {
		return 1;
	}
	return 0;
}

void printTime(int hour, int minute, int seconds, char buff[256],
		char* secondBuff, char* minuteBuff, char* timeBuff) {
	//Defining the pointer for the HEX displays
	volatile int * HEX01_ptr = (int *) HEX01;
	volatile int * HEX23_ptr = (int *) HEX23;
	volatile int * HEX45_ptr = (int *) HEX45;
	volatile int * HEX67_ptr = (int *) HEX67;
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev("/dev/character_lcd_0");
	if (char_lcd_dev == NULL)
		alt_printf("Error: could not open character LCD device\n");
	else
		alt_printf("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init(char_lcd_dev);
	char *ptrtime;
	char *ptrMinute;
	char *ptrSeconds;

	ptrtime = timeBuff;
	ptrMinute = minuteBuff;
	ptrSeconds = secondBuff;
	//parse hour from the data
	int i;
	for (i = 0; i < 2; i++) {
		*ptrtime++ = buff[hour + i];

	}
	*ptrtime = '\0';
	int maskingHour = timeBuff[0] & 0x0f;
	int maskingHour2 = timeBuff[1] & 0x0f;
	maskingHour = (maskingHour << 4) + maskingHour2;
	//writes it to the hex
	*(HEX67_ptr) = maskingHour;
	*ptrtime++ = ':';
	*ptrtime = '\0';
	//parse the minute
	for (i = 0; i < 2; i++) {

		*ptrMinute++ = buff[minute + i];
	}
	*ptrMinute = '\0';
	int maskingMinute = minuteBuff[0] & 0x0f;
	int maskingMinute2 = minuteBuff[1] & 0x0f;
	maskingMinute = (maskingMinute << 4) + maskingMinute2;
	//writes it to the hex
	*(HEX45_ptr) = maskingMinute;
	*ptrMinute++ = ':';
	*ptrMinute = '\0';
	//parse the second from the GPS data
	for (i = 0; i < 2; i++) {
		*ptrSeconds++ = buff[seconds + i];
	}

	*ptrSeconds = '\0';
	int masking = secondBuff[0] & 0x0f;
	int masking2 = secondBuff[1] & 0x0f;
	masking = (masking << 4) + masking2;
	//writes it to the hex
	*(HEX01_ptr) = masking;
	//writes it to altera LCD
	alt_up_character_lcd_string(char_lcd_dev, timeBuff);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 3, 0);
	alt_up_character_lcd_string(char_lcd_dev, minuteBuff);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 6, 0);
	alt_up_character_lcd_string(char_lcd_dev, secondBuff);
}

void printCoordinates(int latStart, int longStart, char buff[256],
		char* latitude, char* longitude) {
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev("/dev/character_lcd_0");
	if (char_lcd_dev == NULL)
		alt_printf("Error: could not open character LCD device\n");
	else
		alt_printf("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init(char_lcd_dev);

	char latHi[3];
	char lonHi[4];
	char latLo[8];
	char lonLo[8];
	char latdir[2];
	char londir[2];

	latdir[0] = buff[27];
	latdir[1] = '\0';
	londir[0] = buff[40];
	londir[1] = '\0';

	// extract hi and low bits
	memcpy(latHi, &buff[17], 2);
	latHi[2] = '\0';
	memcpy(latLo, &buff[19], 7);
	latLo[7] = '\0';
	memcpy(lonHi, &buff[29], 3);
	lonHi[3] = '\0';
	memcpy(lonLo, &buff[32], 7);
	lonLo[7] = '\0';

	// convert lattitude to decimal
	double latHiDouble;
	double latLoDouble;
	double latDecimal;

	latHiDouble = atof(latHi);
	latLoDouble = atof(latLo);

	latDecimal = (latHiDouble + (latLoDouble / 60.0));
	//printf("THE LATITUDE IN DOUBLE IS: %f\n", latDecimal);

	// convert longitude to double
	double lonHiDouble;
	double lonLoDouble;
	double lonDecimal;

	// char to double
	lonHiDouble = atof((const char*) lonHi);
	lonLoDouble = atof((const char*) lonLo);

	lonDecimal = (lonHiDouble + (lonLoDouble / 60.0));
	//printf("THE LONGITUDE IN DOUBLE IS: %f\n", lonDecimal);

	sprintf(latitude, "%f,", latDecimal);
	sprintf(longitude, "%f,", lonDecimal);
	// copy the decimal latitude and longitude and add direct flags

	strcat(latitude, latdir);
	strcat(longitude, londir);

	// return the decimal values
	curLat = latDecimal;
	curLong = lonDecimal;

	alt_up_character_lcd_string(char_lcd_dev, latitude);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, longitude);

}

//This code was adapted from https://www.geodatasource.com/developers/c
//It takes in two sets of latitude and longitude coordinates, and returns the distance between the two
//in the specified unit, M for metres, K for kilometres

double deg2rad(double deg) {
	return (deg * pi / 180);
}

double rad2deg(double rad) {
	return (rad * 180 / pi);
}

double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
	double theta, dist;
	printf("Lat 1: %.6f, Lon 1 %.6f, Lat 2 %.6f, Lon 2 %.6f \n", lat1, lon1,
			lat2, lon2);

	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2))
			+ cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);

	dist = rad2deg(dist);

	dist = dist * 60 * 1.1515;

	switch (unit) {
	case 'M':
		dist = dist * 1.609344 * 1000;
		break;
	case 'K':
		dist = dist * 1.609344;
		break;
	}

	return (dist);
}

void checkDistance() {

	//home latitude and longitude, west is negative
	double homeLat = 49.261812;
	double homeLong = -123.250065;
	double currentLatitude = curLat;
	double currentLongitude = (-1)*curLong;
	double distanceCheck = distance(homeLat, homeLong, currentLatitude, currentLongitude, 'M');

	char buf[6] = "";
	int i;

	//9999 metres maximum
	readFromSD(buf,"log.txt", 5);

	for(i = 0 ; i < strlen(buf); i++){
		if(buf[i] == '$'){
			buf[i] = '\0';
			break;
		}
	}

	int storedDistance = atoi(buf);

	int check = (int) distanceCheck - storedDistance;
	//will be positive if over buffer
	if (check >= 0 ) {
		char buff[1] = "";

		//read the logging flag to see if we log
		readFromSD(buff,"logfl.txt", 1);
		// we log if flag is set to 'y'
		// ie. we are outside the defined radius
		if(buff[0] == 'y'){
			redLEDS = 0xff;
			panicFlag = 1;
		} else {
			redLEDS = 0x00;
			panicFlag = 0;
		}
	} else {
		redLEDS = 0x00;
	}
	if (globalCurrentPage == map){

		int xhome;
		int yhome;
		int xcur;
		int ycur;

		computePixel(homeLat, homeLong, &xhome, &yhome);
		computePixel(currentLatitude, currentLongitude, &xcur, &ycur);

		DrawCircle(xhome+40, yhome+60, storedDistance, BLACK);
	}
}
