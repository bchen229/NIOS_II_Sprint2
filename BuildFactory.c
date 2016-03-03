#include "Structures.h"
#include "BuildFactory.h"
#include "Colours.h"
#include <stdlib.h>

void buildButton(int x_centre, int y_centre, int button_width,
		int button_height, int outlineColour, int fillColour, int fontColor,
		char *text, Button * b, int numChar, Page * targetPage) {

	b->buttonText = text;
	b->x1 = x_centre - (button_width / 2);
	b->x2 = x_centre + (button_width / 2);
	b->y1 = y_centre - (button_height / 2);
	b->y2 = y_centre + (button_height / 2);
	b->outlineColour = outlineColour;
	b->fillColour = fillColour;
	b->fontColour = fontColor;
	b->captionLength = numChar;
	b->targetPage = targetPage;
}

void buildKey(int x_centre, int y_centre, int button_width, int button_height,
		int outlineColour, int fillColour, int fontColor, char *text, Key * k,
		int numChar) {

	k->alpha = text;
	k->len = numChar;
	k->x1 = x_centre - (button_width / 2);
	k->x2 = x_centre + (button_width / 2);
	k->y1 = y_centre - (button_height / 2);
	k->y2 = y_centre + (button_height / 2);
	k->keyOutlineColour = outlineColour;
	k->keyFillColour = fillColour;
	k->fontColour = fontColor;

}

Keyboard buildKeyboard(Keyboard *kb) {

	// Keys start in lower half of the screen ie y > 240
	// assuming each key takes 50x50 px (actual dimensions 40x40 with 5px spacing),
	// there is enough room for 16 keys across the 800 pixel screen space

	int i, j;
	Key *k, *space, *numbutton, *caps, *backspace, *lower, *donebutton;

	// build lower-case keyset
	kb->spacebar = malloc(sizeof(Key));
	kb->keyset_lowercase = malloc(sizeof(Key) * ALPHA_SIZE);
	j = 0; // indexes into keyset_lowercase
	for (i = 0; row1_low[i]; i++) { //qwertyuiop
		k = malloc(sizeof(Key));
		// reserve space of 2 keys for the side keys
		buildKey(80 + 65 * i, 300, 50, 30, BLACK, WHITE, BLACK, row1_low[i], k,
				1);
		k->writeChar = row1_low[i];
		kb->keyset_lowercase[j++] = *k;
	}

	for (i = 0; row2_low[i]; i++) { //asdfghjkl;'
		k = malloc(sizeof(Key));
		// shift keys right half a key
		buildKey(90 + 65 * i, 350, 50, 30, BLACK, WHITE, BLACK, row2_low[i], k,
				1);
		k->writeChar = row2_low[i];
		kb->keyset_lowercase[j++] = *k;

	}

	for (i = 0; row3_low[i]; i++) { //zxcvbnm,.
		k = malloc(sizeof(Key));
		// shift keys right half a key
		buildKey(95 + 65 * i, 400, 50, 30, BLACK, WHITE, BLACK, row3_low[i], k,
				1);
		k->writeChar = row3_low[i];
		kb->keyset_lowercase[j++] = *k;
	}

	// build upper-case keyset
	kb->keyset_uppercase = malloc(sizeof(Key) * ALPHA_SIZE);
	j = 0; // reset counter

	for (i = 0; row1_caps[i]; i++) { //QWERTYUIOP
		k = malloc(sizeof(Key));
		// reserve space of 2 keys for the side keys
		buildKey(80 + 65 * i, 300, 50, 30, BLACK, WHITE, BLACK, row1_caps[i], k,
				1);
		k->writeChar = row1_caps[i];
		kb->keyset_uppercase[j++] = *k;
	}

	for (i = 0; row2_caps[i]; i++) { //ASDFGHJKL:\"
		k = malloc(sizeof(Key));
		// shift keys right half a key
		buildKey(90 + 65 * i, 350, 50, 30, BLACK, WHITE, BLACK, row2_caps[i], k,
				1);
		k->writeChar = row2_caps[i];
		kb->keyset_uppercase[j++] = *k;

	}

	for (i = 0; row3_caps[i]; i++) { //ZXCVBNM!?
		k = malloc(sizeof(Key));
		// shift keys right half a key
		buildKey(95 + 65 * i, 400, 50, 30, BLACK, WHITE, BLACK, row3_caps[i], k,
				1);
		k->writeChar = row3_caps[i];
		kb->keyset_uppercase[j++] = *k;
	}
	kb->numberset1 = malloc(sizeof(Key) * NUM_SIZE);
	j = 0;

	for (i = 0; i < 3; i++) {

		k = malloc(sizeof(Key));
		buildKey(300 + 100 * i, 280, 100, 50, BLACK, WHITE, BLACK, numbers[j],
				k, 1);
		k->writeChar = (char) numbers[j];
		kb->numberset1[j++] = *k;

	}

	for (i = 0; i < 3; i++) {

		k = malloc(sizeof(Key));
		buildKey(300 + 100 * i, 340, 100, 50, BLACK, WHITE, BLACK, numbers[j],
				k, 1);
		k->writeChar = numbers[j];
		kb->numberset1[j++] = *k;

	}

	for (i = 0; i < 3; i++) {

		k = malloc(sizeof(Key));
		buildKey(300 + 100 * i, 400, 100, 50, BLACK, WHITE, BLACK, numbers[j],
				k, 1);
		k->writeChar = numbers[j];
		kb->numberset1[j++] = *k;

	}

	k = malloc(sizeof(Key));
	buildKey(400, 455, 100, 50, BLACK, WHITE, BLACK, numbers[j], k, 1);
	k->writeChar = numbers[j];
	kb->numberset1[j] = *k;

	char *spacetext = "SPACE";
	space = malloc(sizeof(Key));
	buildKey(400, 450, 350, 30, BLACK, WHITE, BLACK, spacetext, space, 5);
	space->writeChar = ' ';
	kb->spacebar = space;

	char *num = "123";
	numbutton = malloc(sizeof(Key));
	buildKey(175, 450, 75, 30, BLACK, WHITE, BLACK, num, numbutton, 3);
	kb->numbers = numbutton;

	char *delete = "Delete";
	backspace = malloc(sizeof(Key));
	buildKey(625, 450, 75, 30, BLACK, WHITE, BLACK, delete, backspace, 6);
	kb->backspace = backspace;

	char *capitals = "ABC";
	caps = malloc(sizeof(Key));
	buildKey(90, 450, 75, 30, BLACK, WHITE, BLACK, capitals, caps, 3);
	kb->caps = caps;

	char *lowercase = "abc";
	lower = malloc(sizeof(Key));
	buildKey(90, 450, 75, 30, BLACK, WHITE, BLACK, lowercase, lower, 3);

	char *done = "Done";
	donebutton = malloc(sizeof(Key));
	buildKey(715, 450, 75, 30, BLACK, WHITE, BLACK, done, donebutton, 4);

	kb->numberset1[10] = *backspace;
	kb->numberset1[11] = *lower;
	kb->numberset1[12] = *donebutton;

	kb->keyset_lowercase[30] = *space;
	kb->keyset_uppercase[30] = *space;

	kb->keyset_lowercase[31] = *backspace;
	kb->keyset_uppercase[31] = *backspace;

	kb->keyset_lowercase[32] = *caps;
	kb->keyset_uppercase[32] = *lower;

	kb->keyset_lowercase[33] = *numbutton;
	kb->keyset_uppercase[33] = *numbutton;

	kb->keyset_lowercase[34] = *donebutton;
	kb->keyset_uppercase[34] = *donebutton;

	kb->curInputBoxIndex = -1;

	return *kb;
}

void buildObject(int x_centre, int y_centre, int object_width,
		int object_height, int outlineColour, int fillColour, int fontColor,
		char *text, Object * o, int numChar) {

	o->objectText = text;
	o->x1 = x_centre - (object_width / 2);
	o->x2 = x_centre + (object_width / 2);
	o->y1 = y_centre - (object_height / 2);
	o->y2 = y_centre + (object_height / 2);
	o->outlineColour = outlineColour;
	o->fillColour = fillColour;
	o->fontColour = fontColor;
	o->captionLength = numChar;
}
