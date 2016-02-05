#include "altera_up_avalon_character_lcd.h"
#include "Hardware.h"

//Global Variables
char seven_seg_decode_table[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
		0x07, 0x7F, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
char hex_segments[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

/* Set up the Register for 9600 baud , 8 bit data  , no parity  and 1 stop*/
void Init_GPS(void) {

	GPS_Baud = 0x05;
	GPS_Control = 0x15;
	//delay(5000);

}
/* This Function reads the GPS data from the serial port*/
char GetData(void) {

	while ((GPS_Status & 0x01) != 0x01)
		;
	return GPS_RxData;

}
/*This functoin sends commands to the GPS  */
void putcharGPS(int c) {

	while ((GPS_Status & 0x02) != 0x02)
		;
	GPS_TxData = c;

}
/* This function goes through the command string and send the string charater by character */
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
	//	sleep(5);
}

void ClearLogging(void) {
	char *buff = "$PMTK184,1";
	putString(buff);
}

void StartLogger(void) {
	char *buff = "$PMTK186,1";
	putString(buff);

}

// these two functions take a 4 byte IEEE-754 format float
// (passed as a 4 byte int representing latitude and longitude values)
// in big endian format and converts it to an ASCII decimal string
// which it returns with decimal point in the string.
char *FloatToLatitudeConversion(int x) //output format is xx.yyyy
{
	static char buff[100];
	float *ptr = (float *) (&x); // cast int to float
	float f = *ptr; // get the float
	sprintf(buff, "%2.4f", f); // write in string to an array
	return buff;
}
char *FloatToLongitudeConversion(int x) // output format is (-)xxx.yyyy
{
	static char buff[100];
	float *ptr = (float *) (&x);
	float f = *ptr;
	sprintf(buff, "%3.4f", f);
	return buff;
}

// takes a 4 byte float in string form (8 chars) and converts to 4 byte form
// (still stored in an int but in float form)
// and swaps the bytes order the reason for this is the GPS outputs the
// longitude and latitude LOG data in 4 byte float form but as little endian
// NIOS however uses big endian
int swapEndian(char *s) {
	register int val;
	val = strtoul(s, NULL, 16); // convert to 4 byte int form in base 16
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	val = (val << 16) | ((val >> 16) & 0xFFFF);
	return val;
}
// This Function search for the GPGGA data format from the GPS and send 1 if the command is in GPGGA format
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
	//printf("firat command is : %s\n", inputCheck);
	if (strcmp(inputCheck, check1) == 0) {
		//printf("YES");
		return 1;

	}

	return 0;
}
// Thif Function parse the GPGGA command and print the UTC time on the LCD and the Console
void printTime(int hour, int minute, int seconds, char buff[256],
		char* secondBuff, char* minuteBuff, char* timeBuff) {
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
	char maskingBuffer[10];
	char *ptrtime;
	char *ptrMinute;
	char *ptrSeconds;

	ptrtime = timeBuff;
	ptrMinute = minuteBuff;
	ptrSeconds = secondBuff;

	int i;
	for (i = 0; i < 2; i++) {
		*ptrtime++ = buff[hour + i];

	}
	*ptrtime = '\0';
	int maskingHour = timeBuff[0] & 0x0f;
	int maskingHour2 = timeBuff[1] & 0x0f;
	maskingHour = (maskingHour << 4) + maskingHour2;
	*(HEX67_ptr) = maskingHour;
	*ptrtime++ = ':';
	*ptrtime = '\0';

	for (i = 0; i < 2; i++) {

		*ptrMinute++ = buff[minute + i];
	}
	*ptrMinute = '\0';
	int maskingMinute = minuteBuff[0] & 0x0f;
	int maskingMinute2 = minuteBuff[1] & 0x0f;
	maskingMinute = (maskingMinute << 4) + maskingMinute2;
	*(HEX45_ptr) = maskingMinute;
	*ptrMinute++ = ':';
	*ptrMinute = '\0';

	for (i = 0; i < 2; i++) {
		*ptrSeconds++ = buff[seconds + i];
	}

	*ptrSeconds = '\0';
	int masking = secondBuff[0] & 0x0f;
	int masking2 = secondBuff[1] & 0x0f;
	masking = (masking << 4) + masking2;
	*(HEX01_ptr) = masking;
	alt_up_character_lcd_string(char_lcd_dev, timeBuff);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 3, 0);
	alt_up_character_lcd_string(char_lcd_dev, minuteBuff);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 6, 0);
	alt_up_character_lcd_string(char_lcd_dev, secondBuff);
}

// This function parse the Lantitude and longitude
void printCoordinates(int latStart, int longStart, char buff[256]) {
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev("/dev/character_lcd_0");
	if (char_lcd_dev == NULL)
		alt_printf("Error: could not open character LCD device\n");
	else
		alt_printf("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init(char_lcd_dev);
	char latBuff[12];
	char longBuff[12];
	char *ptrlat;
	char *ptrlong;

	ptrlat = latBuff;
	ptrlong = longBuff;

	int i;
	printf("\n%s\n", buff);
	printf("print coordinates function \n");
	for (i = 0; i < 11; i++) {
		*ptrlat++ = buff[latStart + i];
	}
	*ptrlat = '\0';
	alt_up_character_lcd_string(char_lcd_dev, latBuff);
	for (i = 0; i < 12; i++) {

		*ptrlong++ = buff[longStart + i];
	}

	*ptrlong = '\0';

	printf(latBuff, longBuff);

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, longBuff);
	usleep(500);

}

void Wait1ms(void) {

	int i;
	for (i = 0; i < 3000; i++)
		;
}

void Wait3ms(void) {

	int i;
	for (i = 0; i < 3; i++) {
		Wait1ms();
	}

}
void Wait1sec(void) {

	int i;
	for (i = 0; i < 1000; i++) {
		Wait1ms();
	}
}
