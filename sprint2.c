/*
 *	CPEN 391
 *	Module 3 - Alzheimer GPS Tracker
 *	Authors: Brian Chen , Henry Li , Kimia Nikazm , David Powall
 *	Purpose: This product helps people who are suffering from the Alzheimer disease
 *			 to remind them where they are going and where they are by integrating GPS and SD card and a touch screen.
 *
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "altera_up_avalon_character_lcd.h"
#include "ColourPallette.h"
#include "Colours.h"
#include <stdio.h>
#include "Structures.h"
#include "Hardware.h"
#include <math.h>

/*
 *
 * Name: WriteCaptionButton
 * Description: This function writes a caption to the centre of button stuct
 * Parameters: Button , font color , backgroundcolor
 *
 */
void writeCaptionButton(Button * button, int fontColor, int backgroundColor) {

	int xCenter = button->x1 + (button->x2 - button->x1) / 2;
	int yCenter = button->y1 + (button->y2 - button->y1) / 2 - 4;
	int x_start = xCenter - (button->captionLength * 10 / 2);
	int len = button->captionLength;
	int i;

	for (i = 0; i < len; i++) {
		OutGraphicsCharFont2a(x_start + i * 10, yCenter, fontColor,
				backgroundColor, button->buttonText[i], 0);

	}
}

/*
 *
 * Name: WriteCaptionObject
 * Description: This function writes a text to the centre of the Object stuct
 * Parameters: Object , font colour , backgroundcolor
 *
 */
void writeCaptionObject(Object * object, int fontColor, int backgroundColor) {

	int xCenter = object->x1 + (object->x2 - object->x1) / 2 - 8;
	int yCenter = object->y1 + (object->y2 - object->y1) / 2 - 4;
	int x_start = xCenter - (object->captionLength * 10 / 2);
	int len = object->captionLength;
	int i;

	for (i = 0; i < len; i++) {

		OutGraphicsCharFont2a(x_start + i * 11, yCenter, fontColor,
				backgroundColor, object->objectText[i], 0);

	}

}
/*
 *
 * Name: WriteCaptionObjectLarge
 * Description: This function writes a text to the centre of the Larger Objects stuct
 * Parameters: Object , font colour , backgroundcolor
 *
 */
void writeCaptionObjectLarge(Object * object, int fontColor,
		int backgroundColor) {

	int xCenter = object->x1 + (object->x2 - object->x1) / 2 - 4;
	int yCenter = object->y1 + (object->y2 - object->y1) / 2 - 4;
	int x_start = xCenter - (object->captionLength * 10 / 2);
	int len = object->captionLength;
	int i;

	for (i = 0; i < len; i++) {

		OutGraphicsCharFont2a(object->x1 + 5 + i * 11, yCenter, fontColor,
				backgroundColor, object->objectText[i], 0);
	}

}

/*
 *
 * Name: drawButton
 * Description: This function draws the rectangular box as a button, using the DrawRectangleFill function implemented
 * Parameters: Button
 *
 */
void drawButton(Button *b) {
	DrawRectangleFill(b->x1, b->x2, b->y1, b->y2, b->outlineColour,
			b->fillColour);

}
/*
 *
 * Name: WriteCaptionKey
 * Description: This function writes a text to the centre of the key stuct
 * Parameters: key , font colour , backgroundcolor
 *
 */
void writeCaptionKey(Key * k, int fontColor, int backgroundColor) {

	int xCenter = k->x1 + (k->x2 - k->x1) / 2 - 4;
	int yCenter = k->y1 + (k->y2 - k->y1) / 2 - 4;
	int x_start = xCenter - (k->len * 10 / 2);
	int len = k->len;
	int i = 0;

	if (len == 1) {

		OutGraphicsCharFont2a(xCenter - 2, yCenter, fontColor, backgroundColor,
				k->alpha, 0);
		return;
	}

	for (i = 0; i < len; i++) {

		OutGraphicsCharFont2a(x_start + i * 11, yCenter, fontColor,
				backgroundColor, k->alpha[i], 0);
	}

}

/*
 *
 * Name: drawObject
 * Description: This function draws the rectangular box as a object, using the DrawRectangleFill function implemented
 * Parameters: Object
 *
 */
void drawObject(Object *o) {
	DrawRectangleFill(o->x1, o->x2, o->y1, o->y2, o->outlineColour,
			o->fillColour);
}
/*
 *
 * Name: drawKey
 * Description: This function draws the rectangular box as a key, using the DrawRectangleFill function implemented
 * Parameters: Key
 *
 */
void drawKey(Key *k) {

	DrawRectangleFill(k->x1, k->x2, k->y1, k->y2, k->keyOutlineColour,
			k->keyFillColour);
	writeCaptionKey(k, k->fontColour, k->keyFillColour);

}

/*
 *
 * Name: drawPage
 * Description: This function draws a page based on the number of boxes,object and buttons of the page
 * Parameters: Page
 *
 */
void drawPage(Page * currentScreen) {
	// Fill background
	int j;
	for (j = 0; j < 481; j++) {
		HLine(0, j, 801, currentScreen->backColour);
	}

	// Iterate through Boxes
	int i = 0;

	for (i = 0; i < currentScreen->numInputBoxes; i++) {
		drawInputBox(&(currentScreen->inputBoxes[i]));
		updateInputBox(&(currentScreen->inputBoxes[i]), BLACK, LIGHT_SKY_BLUE);
	}
	// Iterate through buttons
	for (i = 0; i < currentScreen->numButtons; i++) {
		drawButton(&(currentScreen->buttons[i]));
		writeCaptionButton(&(currentScreen->buttons[i]), BLACK, LIGHT_SKY_BLUE);
	}
	// Iterate through numSDBoxes
	for (i = 0; i < currentScreen->numSDBoxes; i++) {
		drawButton(&(currentScreen->sdBoxes[i]));
		writeCaptionSDBox(&(currentScreen->sdBoxes[i]), BLACK, LIGHT_SKY_BLUE);
	}

	// Iterate through objects
	for (i = 0; i < currentScreen->numObjects; i++) {

		drawObject(&(currentScreen->objects[i]));
		if (currentScreen->hasKeyboard == 1) {

			writeCaptionObjectLarge(&(currentScreen->objects[i]), BLACK, PINK);
		} else {
			writeCaptionObject(&(currentScreen->objects[i]), BLACK, PINK);
		}
	}

	if (currentScreen->hasKeyboard == 1) {
		drawKeyboard(currentScreen);
	}

}
/*
 *
 * Name: updateBuffer
 * Description: This functions updates the buffer corresponding to the keyboard input
 * Parameters: key ,a Page
 *
 */
void updateBuffer(Key k, Page *currentScreen) {

	char input = k.writeChar;
	char *buffer = currentScreen->keyboard.buffer;

	Object *inputBox = &(currentScreen->objects[0]);
	currentScreen->keyboard.bufCount++;
	//Check if the buffer is empty
	if (currentScreen->keyboard.bufCount == 1) {
		strcpy(buffer, "\0");
		strncat(buffer, &input, 1);
	} else {
		strncat(buffer, &input, 1);
	}
	//Check the buffer and draws the buffer to the box
	//Maximum input characters is 55
	if (currentScreen->keyboard.bufCount < 55) {

		buildObject(400, 200, BUTTON_WIDTH * 4, BUTTON_HEIGHT * 2, BLACK, WHITE,
				BLACK, buffer, inputBox, strlen(buffer));
		drawObject(inputBox);
		writeCaptionObjectLarge(inputBox, BLACK, WHITE);

	}
}
/*
 *
 * Name: decrementBuffer
 * Description: This functions updates the buffer upon deletion of characters
 * Parameters: Page
 *
 */
void decrementBuffer(Page *currentScreen) {

	int len = strlen(currentScreen->keyboard.buffer);

	if (len > 0) {

		currentScreen->keyboard.buffer[len - 1] = '\0';
		currentScreen->keyboard.bufCount--;

	}
}
/*
 *
 * Name: clearBuffer
 * Description: This functions empties the buffer
 * Parameters: Page
 *
 */
void clearBuffer(Page *currentScreen) {

	memset(currentScreen->keyboard.buffer, 0,
			sizeof(currentScreen->keyboard.buffer));

}
/*
 *
 * Name: drawKeyboard
 * Description: This function draws the keyboard on the page being passed
 * Parameters: Page
 *
 */
void drawKeyboard(Page * currentScreen) {
	int i;
	int n;
	Key * k = currentScreen->keyboard.currentKeyset;

	n = sizeof(k) / sizeof(k[0]);

	if (currentScreen->keyboard.isNum == 1) {

		for (i = 0; i < NUM_SIZE; i++) {
			drawKey(&(currentScreen->keyboard.currentKeyset[i]));
		}
	} else {
		for (i = 0; i < ALPHA_SIZE; i++) {
			drawKey(&(currentScreen->keyboard.currentKeyset[i]));
		}
	}

}

/*
 *
 * Name: updateTime
 * Description: This function checks the data from the gps and print out the time
 * Parameters: void
 *
 */
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
		//printf("Waiting for start .. \n");
	}
	while ((c = GetData()) != '*') {
		//printf("%c\n", c);
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

/*
 *
 * Name: updateCoord
 * Description: This function checks the data from the gps and print out the coordinates recieved from the GPS
 * Parameters: void
 *
 */
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
/*
 *
 * Name: updateCoordNoPrint
 * Description: This function checks the data from the gps. Used to get the distance for geofencing
 * Parameters: void
 *
 */
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

		printCoordinates(17, 29, buff, lat, longitude, NULL, NULL);

	}
}

/*******************************************************************************
 ** Draw Menus
 *******************************************************************************/
void drawMenu() {

	globalCurrentPage = buildMenu();
	drawPage(globalCurrentPage);

}
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
