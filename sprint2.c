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

/*
 * Name: validpress
 * Purpose: Checks the button of the corresponding page and make sure the press is within the bound of the buttons
 * Parameters: point , page , int
 */
int validpress(Point release, Page currentPage, int * buttonPressed) {

	int j;

	printf("Press: %d %d \n ", release.x, release.y);
	//iterate through the buttons of the page
	for (j = 0; j < currentPage.numButtons; j++) {
		Button bttn = currentPage.buttons[j];
		if ((release.x >= bttn.x1) && (release.x <= bttn.x2)) {
			if ((release.y >= bttn.y1) && (release.y <= bttn.y2)) {
				*buttonPressed = 1;
				return j;
			}
		}
	}
	*buttonPressed = -1;
	return -1;
}

/*
 * Name: validkeypress
 * Purpose: Checks the keys of the corresponding page and make sure the press is within the bound of the keys
 * Parameters: point , page , int
 */
int validkeypress(Point release, Page currentPage, int * keyPressed) {
	int j;
	//make sure the page has keyboard
	if (currentPage.hasKeyboard == 1) {
		int k = NUM_SIZE;

		if (currentPage.keyboard.isNum == 0) {
			k = ALPHA_SIZE;
		}
		//iterate through the keys
		for (j = 0; j < k; j++) {

			Key *k = &(currentPage.keyboard.currentKeyset[j]);
			if ((release.x >= k->x1) && (release.x <= k->x2)) {
				if ((release.y >= k->y1) && (release.y <= k->y2)) {
					*keyPressed = 1;
					return j;
				}
			}
		}
	}

	*keyPressed = -1;
	return -1;
}
/*
 * Name: validinputboxpress
 * Purpose: Checks the inputboxes of the corresponding page and make sure the press is within the bound of the box
 * Parameters: point , page , int
 */
int validinputboxpress(Point release, Page currentPage, int * inputBoxPressed) {
	int j;
	int k = currentPage.numInputBoxes;
	//iterate through the inputboxes
	for (j = 0; j < k; j++) {
		InputBox ib = currentPage.inputBoxes[j];
		if ((release.x >= ib.x1) && (release.x <= ib.x2)) {
			if ((release.y >= ib.y1) && (release.y <= ib.y2)) {
				*inputBoxPressed = 1;
				return j;
			}
		}
	}
	*inputBoxPressed = -1;
	return -1;
}
/*
 * Name: validsdboxpress
 * Purpose: Checks the sdbox of the corresponding page and make sure the press is within the bound of the sdboxes
 * Parameters: point , page , int
 */
int validsdboxpress(Point release, Page currentPage, int * sdBoxPressed) {
	int j;
	int k = currentPage.numSDBoxes;
	//iterates through the SDBoxes
	for (j = 0; j < k; j++) {
		SDBox sdb = currentPage.sdBoxes[j];
		if ((release.x >= sdb.x1) && (release.x <= sdb.x2)) {
			if ((release.y >= sdb.y1) && (release.y <= sdb.y2)) {
				*sdBoxPressed = 1;
				return j;
			}
		}
	}
	*sdBoxPressed = -1;
	return -1;
}

/**
 * Name : checkChoice
 * Purpose:Evaluates which area was pressed and returns the value
 * 			of the key, inputbox, button, or sdbox pressed.
 * Parameters: point , page , button , sdbox;
 *
 */
int checkChoice(Point p, Page * globalCurrentPage, int *keyPressed,
		int *inputBoxPressed, int *buttonPressed, int * sdBoxPressed) {
	int choice = -1;
	int check1;
	int check2;

	int checkButtonPressed = -1;
	int checkInputBoxPressed = -1;
	int checkSDBoxPressed = -1;

	if (globalCurrentPage->hasKeyboard) {

		check1 = validkeypress(p, *globalCurrentPage, keyPressed);
		check2 = validpress(p, *globalCurrentPage, buttonPressed);

		if (*keyPressed == 1) {
			choice = check1;
		}
		if (*buttonPressed == 1) {
			choice = check2;
		}
	} else {

		checkButtonPressed = validpress(p, *globalCurrentPage, buttonPressed);
		checkInputBoxPressed = validinputboxpress(p, *globalCurrentPage,
				inputBoxPressed);
		checkSDBoxPressed = validsdboxpress(p, *globalCurrentPage,
				sdBoxPressed);

		if (*sdBoxPressed == 1) {
			choice = checkSDBoxPressed;
		}
		if (*buttonPressed == 1) {
			choice = checkButtonPressed;
		}
		if (*inputBoxPressed == 1) {
			choice = checkInputBoxPressed;
		}
	}
	return choice;

}
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
