#include <string.h>
#include "Structures.h"
#include "InputBox.h"
#include "Hardware.h"
#include "Font_alg.h"

void buildInputBox(InputBox *ib, int x_centre, int y_centre, int box_width,
		int box_height, int fillColour, int fontColour, int outlineColour){
	ib->x1 = x_centre - (box_width / 2);
	ib->x2 = x_centre + (box_width / 2);
	ib->y1 = y_centre - (box_height / 2);
	ib->y2 = y_centre + (box_height / 2);
	ib->inputBuf[0] = '\0';
	ib->fillColour = fillColour;
	ib->fontColour = fontColour;
	ib->outlineColour = outlineColour;
}

void drawInputBox(InputBox *ib){
	DrawRectangleFill(ib->x1, ib->x2 + 30, ib->y1, ib->y2, ib->outlineColour,
				ib->fillColour);
}

void updateInputBox(InputBox *ib){
	int yCenter = ib->y1 + (ib->y2 - ib->y1) / 2 - 4;
	int i;

	for (i = 0; i < strlen(ib->inputBuf); i++) {

		OutGraphicsCharFont2a(ib->x1 + 2 + i * 11, yCenter - 2, ib->fontColour,
				0, ib->inputBuf[i], 0);

	}
}
