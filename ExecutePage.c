#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Colours.h"
#include "ExecutePage.h"
#include "BuildFactory.h"
#include "Hardware.h"
#include "Cipher.h"
#include "SD_CARD.h"
#include "Draw.h"
#include "WriteCaption.h"
#include "TouchScreen.h"
#include "InputBox.h"

void executePWSetupPress(int choice, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed) {

	if (*sdBoxPressed == 1) {

		if (choice == 0) {
			char newPassword[80];
			strcpy(newPassword, globalCurrentPage->inputBoxes[0].inputBuf);
			// append '$' to signal end of password
			sprintf(newPassword, "%s%s", newPassword, "$");
			keygen(key, newPassword, strlen(newPassword));
			if (writeToSD(key, KEYFILE) == 0) {
				greenLEDS = 0xff;
			} else {
				redLEDS = 0xff;
			}
			writeToSD(newPassword, "password.txt");
			printkey(key);
		}
		if (choice == 1) {
			if (writeToSD("E", "passMode.txt") == 0) {
				greenLEDS = 0xff;
				;
			}
		}
		if (choice == 2) {
			if (writeToSD("D", "passMode.txt") == 0) {
				redLEDS = 0xff;
			}
		}
	}

	if (*inputBoxPressed == 1) {

		printf("input box choice: %d \n", choice);
		keys->keyboard.curInputBoxIndex = choice;
		keys->keyboard.caller = globalCurrentPage;

		strcpy(keys->keyboard.buffer,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->keyboard.bufCount = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		strcpy(keys->objects[0].objectText,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->objects[0].captionLength = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		globalCurrentPage = keys;

	}

	if (*buttonPressed == 1) {

		Button theButton = globalCurrentPage->buttons[choice];
		globalCurrentPage = theButton.targetPage;
	}

}

void executePWLogin(int choice, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed) {

	if (*inputBoxPressed == 1) {
		keys->keyboard.curInputBoxIndex = choice;
		keys->keyboard.caller = globalCurrentPage;

		strcpy(keys->keyboard.buffer,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->keyboard.bufCount = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		strcpy(keys->objects[0].objectText,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->objects[0].captionLength = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		globalCurrentPage = keys;

	}

	if (*buttonPressed == 1) {
		char password[80] = "";
		int i;

		readFromSD(password, "password.txt", 80);

		// end string at '$' which signals end of password
		for (i = 0; i < strlen(password); i++) {
			if (password[i] == '$') {
				password[i] = '\0';
			}
		}

		if (strcmp(globalCurrentPage->inputBoxes[choice].inputBuf, password)
				== 0) {
			globalCurrentPage = home;
		} else {
			globalCurrentPage->objects[0].fillColour = RED;
			globalCurrentPage->objects[0].objectText =
					"Incorrect Password, Please Try Again";
			globalCurrentPage->objects[0].captionLength = strlen(
					"Incorrect Password, Please Try Again");
		}
	}
}

void executeLoggingSettings(int choice, int *inputBoxPressed,
		int *buttonPressed, int * sdBoxPressed) {

	if (*sdBoxPressed == 1) {
		//enables logging
		if (choice == 0) {
			char *flag = "y";
			writeToSD(flag, "logfl.txt");
			printf("Writing %s flag", flag);
		}
		//disables logging
		if (choice == 1) {
			char *flag = "n";
			writeToSD(flag, "logfl.txt");
			printf("Writing %s flag", flag);
		}
		//write metres value to log
		if (choice == 2) {
			char flag[100];
			strcpy(flag, globalCurrentPage->inputBoxes[0].inputBuf);
			sprintf(flag, "%s%s", flag, "$");
			writeToSD(flag, "log.txt");

		}
	}

	if (*inputBoxPressed == 1) {

		printf("input box choice: %d \n", choice);
		keys->keyboard.curInputBoxIndex = choice;
		keys->keyboard.caller = globalCurrentPage;

		strcpy(keys->keyboard.buffer,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->keyboard.bufCount = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		strcpy(keys->objects[0].objectText,
				globalCurrentPage->inputBoxes[choice].inputBuf);
		keys->objects[0].captionLength = strlen(
				globalCurrentPage->inputBoxes[choice].inputBuf);
		globalCurrentPage = keys;

	}

	if (*buttonPressed == 1) {

		Button theButton = globalCurrentPage->buttons[choice];
		globalCurrentPage = theButton.targetPage;
	}
}

void executeMapPress(Button theButton, int choice) {

	if (choice == 1 || choice == 2 || choice == 3) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		Object *o7;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));
		o7 = malloc(sizeof(Object));

		buildObject(560, 70, 301, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: Kaiser Building", o, strlen("Name: Kaiser Building"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);

		buildObject(560, 115, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latitude = 49.2622103", o2, strlen("Latitude = 49.2622103"));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);

		buildObject(560, 155, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude = -123.2501992", o3,
				strlen("Longitude = -123.2501992"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);

		buildObject(560, 200, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"2332 Main Mall V6T 1Z4", o4, strlen("2332 Main Mall V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Faculty of Electrical", o5, strlen("Faculty of Electrical"));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"And Computer Engineering", o6,
				strlen("And Computer Engineering"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);
		buildObject(560, 348, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Offices of the Dean", o7, strlen("Offices of the Dean"));
		drawObject(o7);
		writeCaptionObjectLarge(o7, BLACK, WHITE);
		WaitForTouch();
		free(o);
		free(o2);
		free(o3);
		free(o4);
		free(o5);
		free(o6);

	} else if (choice == 4 || choice == 5 || choice == 6) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));

		buildObject(560, 70, 301, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: MacLeod Building", o, strlen("Name: MacLeod Building"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);
		buildObject(560, 115, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latitude = 49.2617596", o2, strlen("Latitude = 49.2617596"));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);

		buildObject(560, 158, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude = -123.2493528", o3,
				strlen("Longitude = -123.2493528"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);
		buildObject(560, 200, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"2356 Main Mall V6T 1Z4", o4, strlen("2356 Main Mall V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Electrical and Computer", o5,
				strlen("Electrical and Computer"));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Engineering Building", o6, strlen("Engineering Building"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);
		WaitForTouch();
		free(o);
		free(o2);
	} else if (choice == 10) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));

		buildObject(560, 70, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: The Cheeze Factory", o,
				strlen("Name: The Cheeze Factory"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);
		buildObject(560, 115, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latitude =49.26216059", o2, strlen("Latitude =49.26216059"));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);
		buildObject(560, 158, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude = -123.249256100", o3,
				strlen("Longitude = -123.249256100"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);
		buildObject(560, 200, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"2335 Engineering Road V6T 1Z4", o4,
				strlen("2335 Engineering Road V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Dairy Products", o5, strlen("Dairy Products"));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 325, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Manufacturing laboratory", o6,
				strlen("Manufacturing laboratory"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);
		WaitForTouch();
		free(o);
		free(o2);
	} else if (choice == 11 || choice == 12) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		Object *o7;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));
		o7 = malloc(sizeof(Object));
		buildObject(560, 70, 301, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: Brimacombe", o, strlen("Name: Brimacombe"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);
		buildObject(560, 115, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latidude = 49.261883399", o2,
				strlen("Latidude = 49.261883399 "));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);
		buildObject(560, 158, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude =-123.24831760", o3,
				strlen("Longitude =-123.24831760"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);
		buildObject(560, 200, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"2355 East Mall V6T 1Z4", o4, strlen("2355 East Mall V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Advanced Materials ", o5, strlen("Advanced Materials "));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"And Process Engineering", o6,
				strlen("And Process Engineering"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);
		buildObject(560, 348, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Laboratory", o7, strlen("Laboratory"));
		drawObject(o7);
		writeCaptionObjectLarge(o7, BLACK, WHITE);
		WaitForTouch();
		free(o);
		free(o2);
	} else if (choice == 7 || choice == 8 || choice == 9) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));

		buildObject(560, 70, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: CEME", o, strlen("Name: CEME"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);
		buildObject(560, 115, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latitude = 49.2626097", o2, strlen("Latitude = 49.2626097"));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);
		buildObject(560, 158, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude = -123.249115899", o3,
				strlen("Longitude = -123.249256100"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);
		buildObject(560, 200, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"6250 Applied Science Lane V6T 1Z4", o4,
				strlen("6250 Applied Science Lane V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Civil And Mechanical", o5, strlen("Civil And Mechanical"));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 365, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Engineering Building", o6, strlen("Engineering Building"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);

		WaitForTouch();
		free(o);
		free(o2);
		free(o3);
	} else if (choice == 13 || choice == 14) {
		Object *o;
		Object *o2;
		Object *o3;
		Object *o4;
		Object *o5;
		Object *o6;
		Object *o7;
		o = malloc(sizeof(Object));
		o2 = malloc(sizeof(Object));
		o3 = malloc(sizeof(Object));
		o4 = malloc(sizeof(Object));
		o5 = malloc(sizeof(Object));
		o6 = malloc(sizeof(Object));
		o7 = malloc(sizeof(Object));

		buildObject(560, 70, 301, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Name: ICICS", o, strlen("Name: ICICS"));
		drawObject(o);
		writeCaptionObjectLarge(o, BLACK, WHITE);
		buildObject(560, 115, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Latitude = 49.2611776", o2, strlen("Latitude = 49.2611776"));
		drawObject(o2);
		writeCaptionObjectLarge(o2, BLACK, WHITE);
		buildObject(560, 158, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Longitude =-123.24880439", o3,
				strlen("Longitude =-123.24880439"));
		drawObject(o3);
		writeCaptionObjectLarge(o3, BLACK, WHITE);
		buildObject(560, 200, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"2366 Main Mall V6T 1Z4", o4, strlen("2366 Main Mall V6T 1Z4"));
		drawObject(o4);
		writeCaptionObjectLarge(o4, BLACK, WHITE);
		buildObject(560, 246, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Cognative Systems", o5, strlen("Cognative Systems"));
		drawObject(o5);
		writeCaptionObjectLarge(o5, BLACK, WHITE);
		buildObject(560, 295, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"And Computer Science", o6, strlen("And Computer Engineering"));
		drawObject(o6);
		writeCaptionObjectLarge(o6, BLACK, WHITE);
		buildObject(560, 348, 300, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
				"Building", o7, strlen("Building"));
		drawObject(o7);
		writeCaptionObjectLarge(o7, BLACK, WHITE);
		WaitForTouch();
		free(o);
		free(o2);
		free(o3);
	}

	else {

		globalCurrentPage = theButton.targetPage;
	}

}

void executeKeyPress(int choice) {

	if (globalCurrentPage->keyboard.isNum == 0) {

		//Alpha keys
		if (choice <= 30) {

			Key k = globalCurrentPage->keyboard.currentKeyset[choice];
			updateBuffer(k, globalCurrentPage);

		}

		//Delete Key
		if (choice == 31) {

			decrementBuffer(globalCurrentPage);
		}

		//Uppercase/Lowercase Key
		if (choice == 32) {

			if (globalCurrentPage->keyboard.isUpper == 1) {
				globalCurrentPage->keyboard.isUpper = 0;
				globalCurrentPage->keyboard.currentKeyset =
						globalCurrentPage->keyboard.keyset_lowercase;
			} else {
				globalCurrentPage->keyboard.isUpper = 1;
				globalCurrentPage->keyboard.currentKeyset =
						globalCurrentPage->keyboard.keyset_uppercase;

			}
		}

		//Numbers Key
		if (choice == 33) {

			globalCurrentPage->keyboard.isNum = 1;
			globalCurrentPage->keyboard.currentKeyset =
					globalCurrentPage->keyboard.numberset1;
		}

		//Done Key
		if (choice == 34) {

			int k;
			k = globalCurrentPage->keyboard.curInputBoxIndex;

			strcpy(globalCurrentPage->keyboard.caller->inputBoxes[k].inputBuf,
					globalCurrentPage->keyboard.buffer);
			clearBuffer(globalCurrentPage);

			globalCurrentPage = globalCurrentPage->keyboard.caller;
			updateInputBox(&(globalCurrentPage->inputBoxes[k]));

		}

	} else {

		//Number Keys
		if (choice < 10) {

			Key k = globalCurrentPage->keyboard.currentKeyset[choice];
			updateBuffer(k, globalCurrentPage);

		}
		//Delete Key
		if (choice == 10) {

			decrementBuffer(globalCurrentPage);

		}
		//Return to letters key
		if (choice == 11) {

			globalCurrentPage->keyboard.isNum = 0;
			globalCurrentPage->keyboard.currentKeyset =
					globalCurrentPage->keyboard.keyset_lowercase;
		}

		//Done Key
		if (choice == 12) {

			int k;
			k = globalCurrentPage->keyboard.curInputBoxIndex;

			strcpy(globalCurrentPage->keyboard.caller->inputBoxes[k].inputBuf,
					globalCurrentPage->keyboard.buffer);
			clearBuffer(globalCurrentPage);

			globalCurrentPage = globalCurrentPage->keyboard.caller;
			updateInputBox(&(globalCurrentPage->inputBoxes[k]));

		}

	}

}

void MainMenu() {
	int choice;
	int *keyPressed = malloc(sizeof(int));
	int *inputBoxPressed = malloc(sizeof(int));
	int *buttonPressed = malloc(sizeof(int));
	int *sdBoxPressed = malloc(sizeof(int));
	while (1) {

		choice = displayMenu(keyPressed, inputBoxPressed, buttonPressed,
				sdBoxPressed);
		if (choice >= 0) {
			if (*keyPressed == 1) {
				executeKeyPress(choice);
			} else {
				if (globalCurrentPage == map) {
					executeMapPress(globalCurrentPage->buttons[choice], choice);
				} else if (globalCurrentPage == passwordSetup) {
					executePWSetupPress(choice, inputBoxPressed, buttonPressed,
							sdBoxPressed);
				} else if (globalCurrentPage == password) {
					executePWLogin(choice, inputBoxPressed, buttonPressed,
							sdBoxPressed);
				} else if (globalCurrentPage == loggingSettings) {
					executeLoggingSettings(choice, inputBoxPressed,
							buttonPressed, sdBoxPressed);
					// GENERAL PAGE HANDLING (SELF AND DEST PAGES)
				} else {
					if (*sdBoxPressed == 1) {

						char *secureFilename;
						char *plaintextFilename;

						/*
						 * We need to modify the file names depending on the page we are on in the general handler
						 * This is a quicker solution than writing two seperate handlers
						 * */

						if (globalCurrentPage == self) {

							secureFilename = ESELF;
							plaintextFilename = NSELF;

						}
						if (globalCurrentPage == destination) {

							secureFilename = EDEST;
							plaintextFilename = NDEST;
						}

						//if choice = 0 save plaintext
						if (choice == 0) {
							InputBox *tempSD = globalCurrentPage->inputBoxes;
							// write to SD and update SD Box status
							if (formatAndSaveSD(tempSD[0].inputBuf,
									tempSD[1].inputBuf, tempSD[2].inputBuf,
									tempSD[3].inputBuf, plaintextFilename)
									== 0) {
								greenLEDS = 0xff;
								redLEDS = 0x00;
							} else {
								greenLEDS = 0x00;
								redLEDS = 0xff;
							}
						}
						//choice = 1 save encrypted
						if (choice == 1) {

							printf("Saving encrypted \n");
							InputBox *tempSD = globalCurrentPage->inputBoxes;
							// write to SD and update SD Box status
							if (formatAndSaveSDEncrypted(tempSD[0].inputBuf,
									tempSD[1].inputBuf, tempSD[2].inputBuf,
									tempSD[3].inputBuf, secureFilename) == 0) {
								greenLEDS = 0xff;
								redLEDS = 0x00;
							} else {
								greenLEDS = 0x00;
								redLEDS = 0xff;
							}

						}
						//choice = 2 load plaintext
						if (choice == 2) {

							char read[512] = "";
							InputBox *tempSD = globalCurrentPage->inputBoxes;
							if (readFromSD(read, plaintextFilename, 512) == 0) {
								greenLEDS = 0xff;
								redLEDS = 0x00;
							} else {
								greenLEDS = 0x00;
								redLEDS = 0xff;
							}
							loadInfo(tempSD[0].inputBuf, tempSD[1].inputBuf,
									tempSD[2].inputBuf, tempSD[3].inputBuf,
									read);

						}
						//choice 3 = load encrypted
						if (choice == 3) {

							//readFromSD(key, KEYFILE, 16);
							char read[512] = "";
							InputBox *tempSD = globalCurrentPage->inputBoxes;
							if (readFromSDEncrypted(read, secureFilename, 512)
									== 0) {
								greenLEDS = 0xff;
								redLEDS = 0x00;
							} else {
								greenLEDS = 0x00;
								redLEDS = 0xff;
							}
							printf("read: %s, \n", read);

							loadInfo(tempSD[0].inputBuf, tempSD[1].inputBuf,
									tempSD[2].inputBuf, tempSD[3].inputBuf,
									read);
						}

					}

					if (*inputBoxPressed == 1) {

						printf("input box choice: %d \n", choice);
						keys->keyboard.curInputBoxIndex = choice;
						keys->keyboard.caller = globalCurrentPage;

						strcpy(keys->keyboard.buffer,
								globalCurrentPage->inputBoxes[choice].inputBuf);
						keys->keyboard.bufCount = strlen(
								globalCurrentPage->inputBoxes[choice].inputBuf);
						strcpy(keys->objects[0].objectText,
								globalCurrentPage->inputBoxes[choice].inputBuf);
						keys->objects[0].captionLength = strlen(
								globalCurrentPage->inputBoxes[choice].inputBuf);
						globalCurrentPage = keys;

					}

					if (*buttonPressed == 1) {

						Button theButton = globalCurrentPage->buttons[choice];
						printf("button choice: %d \n", choice);

						//if going to the keyboard, then set the caller on the keyboard.
						if (theButton.targetPage == keys) {
							globalCurrentPage->keyboard.caller = home;

						}

						globalCurrentPage = theButton.targetPage;
					}

				}
			}
		}

	}
	free(keyPressed);
	free(buttonPressed);
	free(inputBoxPressed);
	free(sdBoxPressed);

}

int displayMenu(int *keyPressed, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed) {
	int validPress = 0;
	Point p;
	int choice = -1;
	int checkButtonPressed = -1;
	int checkKeyPressed = -1;
	int checkInputBoxPressed = -1;
	int checkSDBoxPressed = -1;

	// if we are outside the area, we will draw the panic page over home page
	if (panicFlag == 1) {
		if (globalCurrentPage == home) {
			globalCurrentPage = panic;
		}
	}
	drawPage(globalCurrentPage);
	while (validPress == 0) {
		//pen down
		GetPress(&p);
		checkButtonPressed = validpress(p, *globalCurrentPage, buttonPressed);
		checkKeyPressed = validkeypress(p, *globalCurrentPage, keyPressed);
		checkInputBoxPressed = validinputboxpress(p, *globalCurrentPage,
				inputBoxPressed);
		checkSDBoxPressed = validsdboxpress(p, *globalCurrentPage,
				sdBoxPressed);

		if (checkButtonPressed != -1 || checkKeyPressed != -1
				|| checkInputBoxPressed != -1 || checkSDBoxPressed != -1) {
			validPress = 1;
		}
		*keyPressed = -1;
		*inputBoxPressed = -1;
		*buttonPressed = -1;
		*sdBoxPressed = -1;
		if (validPress == 1) {
			validPress = 0;
			//pen up
			GetRelease(&p);

			choice = checkChoice(p, globalCurrentPage, keyPressed,
					inputBoxPressed, buttonPressed, sdBoxPressed);

			if (choice != -1 || *keyPressed != -1 || *buttonPressed != -1
					|| *inputBoxPressed != -1 || *sdBoxPressed != -1) {
				validPress = 1;
			}
		}
	}
	return choice;
}

void decrementBuffer(Page *currentScreen) {
	int len = strlen(currentScreen->keyboard.buffer);

	if (len > 0) {
		currentScreen->keyboard.buffer[len - 1] = '\0';
		currentScreen->keyboard.bufCount--;
	}
}

void clearBuffer(Page *currentScreen) {
	memset(currentScreen->keyboard.buffer, 0,
			sizeof(currentScreen->keyboard.buffer));
}

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
