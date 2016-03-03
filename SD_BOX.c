#include "Structures.h"
#include "SD_BOX.h"
#include "Hardware.h"
#include "Font_alg.h"
#include <string.h>

void buildSDBox(int x_centre, int y_centre, int button_width, int button_height,
		int outlineColour, int fillColour, int fontColor, char *text,
		SDBox *sdb, int numChar) {

	sdb->SDBoxText = text;
	sdb->x1 = x_centre - (button_width / 2);
	sdb->x2 = x_centre + (button_width / 2);
	sdb->y1 = y_centre - (button_height / 2);
	sdb->y2 = y_centre + (button_height / 2);
	sdb->outlineColour = outlineColour;
	sdb->fillColour = fillColour;
	sdb->fontColour = fontColor;
	sdb->captionLength = numChar;
}

void drawSDBox(SDBox *sdb) {
	DrawRectangleFill(sdb->x1, sdb->x2, sdb->y1, sdb->y2, sdb->outlineColour,
			sdb->fillColour);
}

void writeCaptionSDBox(SDBox * sdb, int fontColor, int backgroundColor) {

	int xCenter = sdb->x1 + BOX_WIDTH / 2;
	int yCenter = sdb->y1 + BOX_HEIGHT / 2 - 4;
	int x_start = xCenter - (sdb->captionLength * 10 / 2);
	int len = sdb->captionLength;
	int i;

	for (i = 0; i < len; i++) {
		OutGraphicsCharFont2a(x_start + i * 10, yCenter, fontColor,
				backgroundColor, sdb->SDBoxText[i], 0);
	}

}
