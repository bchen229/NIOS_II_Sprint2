#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sys/alt_alarm.h"
#include "Structures.h"
#include "sys/alt_timestamp.h"
#include "Hardware.h"
#include "TouchScreen.h"
#include "SD_CARD.h"
#include "Colours.h"
#include "GPS.h"
#include "BuildFactory.h"
#include "WriteCaption.h"

void Init_Touch(void) {
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command
	Touch_Control = 0x15;
	Touch_Baud = 0x05;
	usleep(4000); // sleep for 4 milliseconds
	// enable touch
	putcharTouch(0x55);
	putcharTouch(0x01);
	putcharTouch(0x12);
	usleep(4000);
}

int ScreenTouched(void) {
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	return (Touch_Recieve == 0x80);
}

void WaitForTouch() {
	alt_timestamp_start();

	while (!ScreenTouched()) {
		if (alt_timestamp() > ALARM_INTERVAL * alt_timestamp_freq()) {
			timerISR();
		}
	}
}

void GetPress(Point *p1) {
	int buf[4];
	int i;
	int yOffset = 125;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	// pick up reponse packets
	for (i = 0; i < 4; i++) {
		buf[i] = getcharTouch();
	}
	// parse x and y coordinates
	p1->x = (buf[1] << 7) | buf[0];
	p1->y = (buf[3] << 7) | buf[2];
	// compute screen coordinates
	p1->x = p1->x * 799 / 4095;
	p1->y = (p1->y - yOffset) * 479 / (4095 - yOffset);
}

void GetRelease(Point *p1) {
	int buf[4];
	int i;
	int yOffset = 150;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	// pick up reponse packets
	for (i = 0; i < 4; i++) {
		buf[i] = getcharTouch();
	}
	// parse x and y coordinates
	p1->x = (buf[1] << 7) | buf[0];
	p1->y = (buf[3] << 7) | buf[2];
	// compute screen coordinates
	p1->x = p1->x * 799 / 4095;
	p1->y = (p1->y - yOffset) * 479 / (4095 - yOffset);
}

int putcharTouch(int c) {
// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
	while ((Touch_Status & 0x02) != 0x02)
		;
	Touch_Transmit = c & 0xFF;
	return Touch_Transmit; // return c
}

int getcharTouch(void) {
	int rx;
	// poll Rx bit in 6850 status register. Wait for it to become '1'
	// read received character from 6850 RxData register.
	while ((Touch_Status & 0x01) != 0x01)
		;
	rx = Touch_Recieve;
	return rx;
}

void updateTime() {
	Object *timeObject = &(home->objects[2]);
	char c;
	char *ptr;
	char buff[256];
	ptr = buff;
	if (globalCurrentPage != home) {
		return;
	}
	while (GetData() != '$') {

	}
	while ((c = GetData()) != '*') {
		*ptr++ = c;
	}
	*ptr = '\0';
	if (checkBuff(buff) == 1) {

		char minuteBuff[10];
		char timeBuff[10];
		char concatTime[8];

		// grab the time values concatenate them
		printTime(6, 8, 10, buff, "", minuteBuff, timeBuff);
		strcpy(concatTime, timeBuff);
		strcat(concatTime, minuteBuff);
		concatTime[strlen(concatTime) - 1] = '\0';
		printf("%s\n", concatTime);

		// draw the time onto the screen
		strcpy(timeObject->objectText, concatTime);
		drawObject(timeObject);
		printf("%s ", timeObject->objectText);
		writeCaptionObject(timeObject, BLACK, PINK);
	}
}

void updateCoord() {

	Object *gpsLat = &(self->objects[5]);
	Object *gpsLong = &(self->objects[6]);
	char c;
	char *ptr;
	char buff[256];
	ptr = buff;
	if (globalCurrentPage != self) {
		return;
	}
	//Wait for the valid data
	while (GetData() != '$') {

	}
	//save the date
	while ((c = GetData()) != '*') {

		*ptr++ = c;
	}
	*ptr = '\0';

	if (checkBuff(buff) == 1) {

		char lat[12];
		char longitude[13];

		printCoordinates(17, 29, buff, lat, longitude);

		//Draw Lat on to the object in the self page
		strcpy(gpsLat->objectText, lat);
		drawObject(gpsLat);
		writeCaptionObject(gpsLat, BLACK, PINK);
		//Draw Long
		strcpy(gpsLong->objectText, longitude);
		drawObject(gpsLong);
		writeCaptionObject(gpsLong, BLACK, PINK);
	}
}

void updateCoordNoPrint() {

	char c;
	char *ptr;
	char buff[256];
	ptr = buff;
	//wait for valid data
	while (GetData() != '$') {

	}
	while ((c = GetData()) != '*') {

		*ptr++ = c;
	}
	*ptr = '\0';
	if (checkBuff(buff) == 1) {

		char lat[12];
		char longitude[13];

		printCoordinates(17, 29, buff, lat, longitude);

	}
}

void timerISR() {

	updateTime();
	updateCoord();
	updateCoordNoPrint();
	char *buf = "y";
	readFromSD(buf, "logf.txt", 1);
	//Reset the LEDS
	redLEDS = 0x0;
	greenLEDS = 0x0;
	//read the flag for logging
	if (strcmp(buf, "y") == 0) {
		checkDistance();
	}
	alt_timestamp_start();

}
