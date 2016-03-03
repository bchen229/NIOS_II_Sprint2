#include "Structures.h"
#include "BuildPages.h"
#include "BuildFactory.h"
#include "SD_BOX.h"
#include "InputBox.h"
#include "SD_CARD.h"
#include "Colours.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

void buildHomePage(Page *home) {

	// Allocate memory for home screen buttons
	home->buttons = malloc(sizeof(Button) * 6);
	home->objects = malloc(sizeof(Object) * 3);
	home->numButtons = 6;
	home->numObjects = 3;
	home->numInputBoxes = 0;
	home->numSDBoxes = 0;
	home->backColour = WHITE;

	// Destination button
	buildButton(400, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIME_GREEN, BLACK,
			"Destination", &(home->buttons[0]), strlen("Destination"),
			destination);

	// "Where am I?" button
	buildButton(600, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, GOLD, BLACK,
			"Where am I?", &(home->buttons[1]), strlen("Where am I?"), self);

	//Password
	buildButton(200, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, GOLD, BLACK,
			"Set Password", &(home->buttons[2]), strlen("Set Password"),
			passwordSetup);

	//map
	buildButton(266, 250, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIME_GREEN, BLACK,
			"Map", &(home->buttons[3]), strlen("Map"), map);

	//loggingSettings
	buildButton(533, 250, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIME_GREEN, BLACK,
			"Log Settings", &(home->buttons[4]), strlen("Log Settings"),
			loggingSettings);

	//addresses
	buildButton(400, 150, 300, 50, BLACK, GOLD, BLACK, "Addresses",
			&(home->buttons[5]), strlen("Addresses"), addresses);

	// Title Object
	buildObject(100, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"SPRINT2 GROUP 3", &(home->objects[0]), strlen("SPRINT2 GROUP 3"));

	// Course Title Object
	buildObject(700, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"CPEN391", &(home->objects[1]), strlen("CPEN391"));

	// Time Object
	buildObject(770, 20, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
			"     ", &(home->objects[2]), strlen("00:00"));

}

void buildDestPage(Page *destination) {

	// Definitions for Destination Page
	// Memory management
	destination->hasKeyboard = 0;
	destination->buttons = malloc(sizeof(Button) * 1);
	destination->objects = malloc(sizeof(Object) * 4);
	destination->inputBoxes = malloc(sizeof(InputBox) * 4);
	destination->sdBoxes = malloc(sizeof(SDBox) * 4);
	destination->numButtons = 1;
	destination->numObjects = 4;
	destination->backColour = WHITE;
	destination->numInputBoxes = 4;
	destination->numSDBoxes = 4;

	// Home button
	buildButton(160, 330, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(destination->buttons[0]), strlen("Home"), home);

	//Save Plaintext To SD
	buildSDBox(160, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Save Plaintext", &(destination->sdBoxes[0]),
			strlen("Save Plaintext"));
	//Save Encrypted To SD
	buildSDBox(320, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Save Encrypted", &(destination->sdBoxes[1]),
			strlen("Save Encrypted"));
	//Load from SD
	buildSDBox(480, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Load Data", &(destination->sdBoxes[2]), strlen("Load Data"));

	buildSDBox(640, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Load Secure", &(destination->sdBoxes[3]), strlen("Load Secure"));

	// Page contents
	// Headings
	buildObject(150, 100, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
			"Your Destination Is: ", &(destination->objects[0]),
			strlen("Your Destination Is: "));
	buildObject(150, 150, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
			"Home Address: ", &(destination->objects[1]),
			strlen("Home Address: "));
	buildObject(150, 200, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
			"Phone #: ", &(destination->objects[2]), strlen("Phone #: "));
	buildObject(150, 250, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
			"Name: ", &(destination->objects[3]), strlen("Name: "));

	// Text Fields for Input Boxes from top to bottom respectively
	buildInputBox(&(destination->inputBoxes[0]), 450, 100, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(destination->inputBoxes[1]), 450, 150, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(destination->inputBoxes[2]), 450, 200, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(destination->inputBoxes[3]), 450, 250, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);

}

void buildMapPage(Page *Map) {

	Map->buttons = malloc(sizeof(Button) * 15);
	Map->objects = malloc(sizeof(Object) * 5);
	Map->numButtons = 15;
	Map->numObjects = 5;
	Map->backColour = GRAY_REPEAT;
	Map->numInputBoxes = 0;
	Map->numSDBoxes = 0;
	//Kaiser Red
	buildButton(700, 420, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Menu", &(Map->buttons[0]), strlen("Menu"), home);
	buildButton(190, 90, 120, 200, RED, RED, RED, "Kaiser", &(Map->buttons[1]),
			strlen("Kaiser"), NULL);
	buildButton(190, 196, 85, 10, RED, RED, RED, "", &(Map->buttons[2]),
			strlen(""), NULL);
	buildButton(293, 40, 85, 20, RED, RED, RED, "", &(Map->buttons[3]),
			strlen(""), NULL);
	//Mcleod Yellow
	buildButton(190, 276, 35, 150, ORANGE, ORANGE, ORANGE, "",
			&(Map->buttons[4]), strlen(""), NULL);
	buildButton(288, 370, 230, 47, ORANGE, ORANGE, ORANGE, "MacLeod",
			&(Map->buttons[5]), strlen("MacLeod"), NULL);
	buildButton(406, 370, 10, 23, ORANGE, ORANGE, ORANGE, "",
			&(Map->buttons[6]), strlen(""), NULL);
	//CEME
	buildButton(500, 39, 350, 74, INDIGO, INDIGO, INDIGO,
			"Civil and Mechanical", &(Map->buttons[7]),
			strlen("Civil and Mechanical"), NULL);
	buildButton(455, 170, 70, 240, INDIGO, INDIGO, INDIGO, "",
			&(Map->buttons[8]), strlen(""), NULL);
	buildButton(660, 120, 100, 200, INDIGO, INDIGO, INDIGO, "",
			&(Map->buttons[9]), strlen(""), NULL);
	//CHEESE
	buildButton(330, 250, 90, 60, WHITE, WHITE, BLACK, "CHEESE",
			&(Map->buttons[10]), strlen("CHEESE"), NULL);
	//Brimacombe Building
	buildButton(500, 390, 90, 170, ORANGE_RED, ORANGE_RED, ORANGE_RED, "",
			&(Map->buttons[11]), strlen(""), NULL);
	buildButton(630, 340, 190, 50, ORANGE_RED, ORANGE_RED, ORANGE_RED,
			"Brimacomb", &(Map->buttons[12]), strlen("Brimacomb"), NULL);
	//ICICS
	buildButton(230, 450, 180, 80, CORN_FLOWER_BLUE, CORN_FLOWER_BLUE,
			CORN_FLOWER_BLUE, "ICICS", &(Map->buttons[13]), strlen("ICICS"),
			NULL);
	buildButton(135, 445, 10, 30, CORN_FLOWER_BLUE, CORN_FLOWER_BLUE,
			CORN_FLOWER_BLUE, "", &(Map->buttons[14]), strlen(""), NULL);

	//GRASS
	buildObject(50, 120, 70, 200, FOREST_GREEN, FOREST_GREEN, FOREST_GREEN, "",
			&(Map->objects[0]), strlen(""));
	buildObject(50, 340, 70, 200, FOREST_GREEN, FOREST_GREEN, FOREST_GREEN, "",
			&(Map->objects[1]), strlen(""));
	//Main Mall road
	buildObject(95, 230, 156, 15, LIGHT_GRAY, LIGHT_GRAY, LIGHT_GRAY, "",
			&(Map->objects[2]), strlen(""));
	//Engineering Road
	buildObject(435, 385, 15, 189, LIGHT_GRAY, LIGHT_GRAY, LIGHT_GRAY, "",
			&(Map->objects[3]), strlen(""));
	//.road.
	buildObject(100, 200, 20, 600, LIGHT_GRAY, LIGHT_GRAY, LIGHT_GRAY, "",
			&(Map->objects[4]), strlen(""));
}

void buildSelfPage(Page *self) {

	// Definitions for "Where am I?"
	// Memory Management
	self->buttons = malloc(sizeof(Button) * 1);
	self->objects = malloc(sizeof(Object) * 7);
	self->inputBoxes = malloc(sizeof(InputBox) * 4);
	self->sdBoxes = malloc(sizeof(SDBox) * 4);
	self->numButtons = 1;
	self->numObjects = 7;
	self->backColour = WHITE;
	self->numInputBoxes = 4;
	self->numSDBoxes = 4;
	// Buttons
	buildButton(160, 330, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(self->buttons[0]), strlen("Home"), home);

	//Save Plaintext To SD
	buildSDBox(160, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Save Plaintext", &(self->sdBoxes[0]), strlen("Save Plaintext"));
	//Save Encrypted To SD
	buildSDBox(320, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Save Encrypted", &(self->sdBoxes[1]), strlen("Save Encrypted"));
	//Load from SD
	buildSDBox(480, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Load Data", &(self->sdBoxes[2]), strlen("Load Data"));

	buildSDBox(640, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Load Secure", &(self->sdBoxes[3]), strlen("Load Secure"));

	// Info fields
	// Name
	buildObject(150, 50, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Your Name Is: ", &(self->objects[0]), strlen("Your Name Is: "));

	// Address
	buildObject(150, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Home Address: ", &(self->objects[1]), strlen("Home Address: "));

	// Phone
	buildObject(150, 150, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Phone #: ", &(self->objects[2]), strlen("Phone #: "));

	// Emergency Contact
	buildObject(150, 200, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Emergency #: ", &(self->objects[3]), strlen("Emergency #: "));

	// Current Location
	buildObject(150, 250, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Your Location Is: ", &(self->objects[4]),
			strlen("Your Location Is: "));
	// Latitude
	buildObject(450, 250, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, WHITE, WHITE,
			BLACK, "------------", &(self->objects[5]), 12);
	// Longitude
	buildObject(450, 300, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, WHITE, WHITE,
			BLACK, "-------------", &(self->objects[6]), 13);

	// Input boxes on screen from top to bottom respectively
	buildInputBox(&(self->inputBoxes[0]), 450, 50, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(self->inputBoxes[1]), 450, 100, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(self->inputBoxes[2]), 450, 150, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
	buildInputBox(&(self->inputBoxes[3]), 450, 200, OBJECT_WIDTH + 100,
			OBJECT_HEIGHT / 2, WHITE, BLACK, BLACK);
}

void buildKeysPage(Page *keys) {

	keys->objects = malloc(sizeof(Object) * 1);
	keys->backColour = WHITE;
	keys->hasKeyboard = 1; //ONLY THIS PAGE WILL HAVE THIS FLAG HIGH
	keys->numObjects = 1;
	keys->numButtons = 0;
	Keyboard *kb = malloc(sizeof(Keyboard));
	buildKeyboard(kb);
	keys->keyboard = *kb;
	keys->keyboard.isNum = 0;
	keys->keyboard.isUpper = 0;
	keys->keyboard.bufCount = 0;
	keys->keyboard.currentKeyset = keys->keyboard.keyset_lowercase;
	keys->numInputBoxes = 0;
	keys->numSDBoxes = 0;

	buildObject(380, 200, BUTTON_WIDTH * 4, BUTTON_HEIGHT * 2, BLACK, WHITE,
			BLACK, "", &(keys->objects[0]), 0);

}

Page* buildMenu(void) {

	// Build/allocate pages
	home = malloc(sizeof(Page));
	password = malloc(sizeof(Page));
	passwordSetup = malloc(sizeof(Page));
	destination = malloc(sizeof(Page));
	self = malloc(sizeof(Page));
	keys = malloc(sizeof(Page));
	map = malloc(sizeof(Page));
	panic = malloc(sizeof(Page));
	loggingSettings = malloc(sizeof(Page));
	addresses = malloc(sizeof(Page));

	home->hasKeyboard = 0;
	destination->hasKeyboard = 0;
	password->hasKeyboard = 0;
	passwordSetup->hasKeyboard = 0;
	self->hasKeyboard = 0;
	keys->hasKeyboard = 1;
	map->hasKeyboard = 0;
	loggingSettings->hasKeyboard = 0;
	panic->hasKeyboard = 0;
	addresses->hasKeyboard = 0;

	buildHomePage(home);
	buildDestPage(destination);
	buildSelfPage(self);
	buildKeysPage(keys);
	buildMapPage(map);
	buildPWLoginPage(password);
	buildPWSetupPage(passwordSetup);
	buildLoggingSettingsPage(loggingSettings);
	buildPanicPage(panic);
	buildAddressesPage(addresses);

	char buf[2] = "";

	readFromSD(buf, "passMode.txt", 1);
	printf("enable: %s\n", buf);

	if (strcmp(buf, "E") == 0) {
		return password;
	}

	return home;

}

void buildPWLoginPage(Page *password) {

	password->buttons = malloc(sizeof(Button) * 1);
	password->objects = malloc(sizeof(Object) * 1);
	password->inputBoxes = malloc(sizeof(InputBox) * 1);
	password->backColour = WHITE;
	password->numObjects = 1;
	password->numButtons = 1;
	password->numInputBoxes = 1;
	password->numSDBoxes = 0;

	// Enter Button
	buildButton(400, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Enter", &(password->buttons[0]), strlen("Enter"), home);

	// Incorrect Password Message
	buildObject(400, 100, BUTTON_WIDTH * 3, BUTTON_HEIGHT, BLACK, GOLD, BLACK,
			"Please Enter Your Password", &(password->objects[0]),
			strlen("Please Enter Your Password"));

	// Input Box
	buildInputBox(&(password->inputBoxes[0]), 380, 200, BUTTON_WIDTH * 4,
			BUTTON_HEIGHT * 2, GOLD, BLACK, BLACK);

}

void buildPWSetupPage(Page *passwordSetup) {

	passwordSetup->buttons = malloc(sizeof(Button) * 3);
	passwordSetup->inputBoxes = malloc(sizeof(InputBox) * 1);
	passwordSetup->backColour = WHITE;
	passwordSetup->numObjects = 0;
	passwordSetup->numButtons = 1;
	passwordSetup->numInputBoxes = 1;
	passwordSetup->numSDBoxes = 3;

	// Home button
	buildButton(100, 50, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(passwordSetup->buttons[0]), strlen("Home"), home);

	buildSDBox(600, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Change PW", &(passwordSetup->sdBoxes[0]), strlen("Change PW"));

	buildSDBox(200, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Enable", &(passwordSetup->sdBoxes[1]), strlen("Enable"));

	buildSDBox(400, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, RED, BLACK,
			"Disable", &(passwordSetup->sdBoxes[2]), strlen("Disable"));

	buildInputBox(&(passwordSetup->inputBoxes[0]), 380, 200, BUTTON_WIDTH * 4,
			BUTTON_HEIGHT * 2, WHITE, BLACK, BLACK);

}

void buildLoggingSettingsPage(Page * loggingSettings) {

	loggingSettings->buttons = malloc(sizeof(Button) * 1);
	loggingSettings->objects = malloc(sizeof(Object) * 1);
	loggingSettings->inputBoxes = malloc(sizeof(InputBox) * 1);
	loggingSettings->sdBoxes = malloc(sizeof(SDBox) * 3);
	loggingSettings->numButtons = 1;
	loggingSettings->numObjects = 1;
	loggingSettings->backColour = WHITE;
	loggingSettings->numInputBoxes = 1;
	loggingSettings->numSDBoxes = 3;

	buildButton(160, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(loggingSettings->buttons[0]), strlen("Home"), home);

	buildObject(380 + 15, 150, BUTTON_WIDTH * 3 + 30, BUTTON_HEIGHT, BLACK,
			AQUA, BLACK, "Please Set Fence Radius In Metres:",
			&(loggingSettings->objects[0]),
			strlen("Please Set Fence Radius In Metres:"));

	buildInputBox(&(loggingSettings->inputBoxes[0]), 380, 200, BUTTON_WIDTH * 3,
			BUTTON_HEIGHT, WHITE, BLACK, BLACK);

	buildSDBox(320, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Enable Logging", &(loggingSettings->sdBoxes[0]),
			strlen("Enable Logging"));

	buildSDBox(480, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, RED, BLACK,
			"Disable Logging", &(loggingSettings->sdBoxes[1]),
			strlen("Disable Logging"));

	buildSDBox(640, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIME_GREEN, BLACK,
			"Save Distance", &(loggingSettings->sdBoxes[2]),
			strlen("Save Distance"));
}

void buildPanicPage(Page *panicPage) {
	panicPage->buttons = malloc(sizeof(Button) * 4);
	panicPage->objects = malloc(sizeof(Object) * 1);
	panicPage->numButtons = 4;
	panicPage->numObjects = 1;
	panicPage->backColour = BLACK;
	panicPage->numInputBoxes = 0;
	panicPage->numSDBoxes = 0;

	buildButton(700, 420, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Menu", &(panicPage->buttons[0]), strlen("Menu"), home);
	buildButton(200, 300, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Where am I?", &(panicPage->buttons[1]), strlen("Where am I?"),
			map);
	buildButton(600, 300, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Remind Me", &(panicPage->buttons[2]), strlen("Remind Me"), self);
	buildButton(400, 300, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Logging", &(panicPage->buttons[3]), strlen("Logging"),
			loggingSettings);

	buildObject(400, 200, 500, 100, RED, RED, RED, "You Got Out Of The Fence",
			&(panicPage->objects[0]), strlen("You Got Out Of The Fence"));

	// disable logging intially
	writeToSD("n", "logfl.txt");
	// intialize panicFlag
	panicFlag = 0;
}

void buildAddressesPage(Page *addresses) {
	addresses->buttons = malloc(sizeof(Button) * 1);
	addresses->objects = malloc(sizeof(Object) * 4);
	addresses->numButtons = 1;
	addresses->numObjects = 4;
	addresses->backColour = POWDER_BLUE;
	addresses->numInputBoxes = 0;
	addresses->numSDBoxes = 0;

	char read[512] = "";
	char read2[512] = "";
	char read3[512] = "";
	char* ad;
	char* ad2;
	char* ad3;
	int i;

	readFromSD(read, AD1, 512);
	for(i=0;i<512;i++){
		if(read[i]=='$'){
		read[i]='\0';
		break;
		}
	}
	ad = malloc(strlen(read) * sizeof(char));
	strcpy(ad,read);

	readFromSD(read2, AD2, 512);
	for(i=0;i<512;i++){
		if(read2[i]=='$'){
		read2[i]='\0';
		break;
		}
	}
	ad2 = malloc(strlen(read2) * sizeof(char));
	strcpy(ad2,read2);

	readFromSD(read3, AD3, 512);
	for(i=0;i<512;i++){
		if(read3[i]=='$'){
		read3[i]='\0';
		break;
		}
	}
	ad3 = malloc(strlen(read3) * sizeof(char));
	strcpy(ad3,read3);

	buildButton(700, 420, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Menu", &(addresses->buttons[0]), strlen("Menu"), home);

	buildObject(400, 50, 400, 30, CORN_FLOWER_BLUE, CORN_FLOWER_BLUE,
			CORN_FLOWER_BLUE, "List of Addresses", &(addresses->objects[0]),
			strlen("List of Addresses"));
	buildObject(400, 170, 650, 50, WHITE, WHITE, WHITE, ad,
			&(addresses->objects[1]), strlen(ad));
	buildObject(400, 250, 650, 50, WHITE, WHITE, WHITE, ad2,
			&(addresses->objects[2]), strlen(ad2));
	buildObject(400, 345, 650, 50, WHITE, WHITE, WHITE, ad3,
			&(addresses->objects[3]), strlen(ad3));

}
