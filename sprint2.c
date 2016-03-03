/*
 *	CPEN 391
 *	Module 3 - Alzheimer GPS Tracker
 *	Authors: Brian Chen , Henry Li , Kimia Nikazm , David Powall
 *	Purpose: This product helps people who are suffering from the Alzheimer disease
 *			 to remind them where they are going and where they are by integrating GPS and SD card and a touch screen.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Structures.h"
#include "Hardware.h"
#include "ExecutePage.h"
#include "TouchScreen.h"
#include "GPS.h"
#include "Draw.h"

/**********************************************************************************
 * ************************** main Function ***************************************
 * ********************************************************************************
 ***********************************************************************************/
int main(void) {

	drawMenu();
	redLEDS = 0x00;
	greenLEDS = 0x00;

	// initialize GPS
	Init_GPS();
	StopLogging();
	usleep(500);
	ClearLogging();
	usleep(500);
	StartLogger();
	usleep(500);

	// initialize touch screen
	Init_Touch();

	while (1) {
		//keep looping and calling mainmenu
		MainMenu();
	}

	return 0;
}
