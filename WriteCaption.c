#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "WriteCaption.h"
#include "Font_alg.h"

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

void writeCaptionObjectLarge(Object * object, int fontColor,
		int backgroundColor) {

	int xCenter = object->x1 + (object->x2 - object->x1) / 2 - 4;
	int yCenter = object->y1 + (object->y2 - object->y1) / 2 - 4;
	int len = object->captionLength;
	int i;

	for (i = 0; i < len; i++) {

		OutGraphicsCharFont2a(object->x1 + 5 + i * 11, yCenter, fontColor,
				backgroundColor, object->objectText[i], 0);
	}

}

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
