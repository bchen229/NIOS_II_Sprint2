#include "Structures.h"
#include "Hardware.h"
#include "ColourPallette.h"
#include "Colours.h"
#include "WriteCaption.h"
#include "InputBox.h"
#include "SD_BOX.h"
#include "Draw.h"
#include "BuildPages.h"

void drawButton(Button *b) {
	DrawRectangleFill(b->x1, b->x2, b->y1, b->y2, b->outlineColour,
			b->fillColour);
}

void drawObject(Object *o) {
	DrawRectangleFill(o->x1, o->x2, o->y1, o->y2, o->outlineColour,
			o->fillColour);
}

void drawKey(Key *k) {

	DrawRectangleFill(k->x1, k->x2, k->y1, k->y2, k->keyOutlineColour,
			k->keyFillColour);
	writeCaptionKey(k, k->fontColour, k->keyFillColour);

}

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
		updateInputBox(&(currentScreen->inputBoxes[i]));
	}
	// Iterate through buttons
	for (i = 0; i < currentScreen->numButtons; i++) {
		drawButton(&(currentScreen->buttons[i]));
		writeCaptionButton(&(currentScreen->buttons[i]), BLACK, LIGHT_SKY_BLUE);
	}
	// Iterate through numSDBoxes
	for (i = 0; i < currentScreen->numSDBoxes; i++) {
		drawSDBox(&(currentScreen->sdBoxes[i]));
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

void drawMenu() {

	globalCurrentPage = buildMenu();
	drawPage(globalCurrentPage);

}

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
