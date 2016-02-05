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

#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud (*(volatile unsigned char *)(0x84000204))

#define MENU_SIZE 1
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define OBJECT_WIDTH 150
#define OBJECT_HEIGHT 50
#define TEXT_SIZE 6

void Init_RS232(void) {

	RS232_Baud = 0x01; //Program Baud rate for 115K
	RS232_Control = 0x15; // x16 clock , 8 data , no parity , 1 stop , no interrupt

}

/*
 * poll Tx bit in 6850 status register. Wait for it to become '1'
 * write 'c' to the 6850 TxData register to output the character
 */
int putcharRS232(int c) {

	while ((RS232_Status & 0x02) != 0x02)
		;
	RS232_TxData = c & 0xFF;
	return RS232_TxData; // return c
}

/*
 * poll Rx bit in 6850 status register. Wait for it to become '1'
 * read received character from 6850 RxData register.read read
 */
int getcharRS232(void) {
	int rx;

	while ((RS232_Status & 0x01) != 0x01)
		;

	rx = RS232_RxData;

	return rx;
}

// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int RS232TestForReceivedData(void) {

	if (RS232_RxData && 0x01 == 0x01) {
		return 1;
	} else
		return 0;
}

/**
 * Writes font on the
 */
void writeCaptionButton(Button * button, int fontColor, int backgroundColor) {

	int xCenter = button->x1 + BUTTON_WIDTH / 2;
	int yCenter = button->y1 + BUTTON_HEIGHT / 2 - 4;
	int x_start = xCenter - (button->captionLength * 10 / 2);
	int len = button->captionLength;
	int i;

	for (i = 0; i < len; i++) {
		OutGraphicsCharFont2a(x_start + i * 10, yCenter, fontColor,
				backgroundColor, button->buttonText[i], 0);

	}

}

void writeCaptionObject(Object * object, int fontColor, int backgroundColor) {

	int xCenter = object->x1 + OBJECT_WIDTH / 2;
	int yCenter = object->y1 + OBJECT_HEIGHT / 2 - 4;
	int x_start = xCenter - (object->captionLength * 10 / 2);
	int len = object->captionLength;
	int i;

	for (i = 0; i < len; i++) {

		OutGraphicsCharFont2a(x_start + i * 11, yCenter, fontColor,
				backgroundColor, object->objectText[i], 0);

	}

}

void drawButton(Button *b) {
	DrawRectangleFill(b->x1, b->x2, b->y1, b->y2, b->outlineColour,
			b->fillColour);
	//DRAW CAPTION

}

void drawObject(Object *o) {
	DrawRectangleFill(o->x1, o->x2, o->y1, o->y2, o->outlineColour,
			o->fillColour);
	//DRAW CAPTION

}

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

Page * buildMenu(void) {

	Page *home = malloc(sizeof(Page));
	Page *destination = malloc(sizeof(Page));
	Page *self = malloc(sizeof(Page));
	Page *graphicTest = malloc(sizeof(Page));

	home->buttons = malloc(sizeof(Button) * 3);
	home->objects = malloc(sizeof(Object) * 2);
	home->numButtons = 3;
	home->numObjects = 2;
	home->backColour = WHITE;

	buildButton(400, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIME_GREEN, BLACK,
			"Destination", &(home->buttons[0]), strlen("Destination"),
			destination);

	buildButton(600, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, GOLD, BLACK,
			"Where am I?", &(home->buttons[1]), strlen("Where am I?"), self);

	buildButton(200, 359, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, LIGHT_SKY_BLUE,
			BLACK, "Graphics Test", &(home->buttons[2]),
			strlen("Graphics Test"), graphicTest);

	buildObject(100, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"SPRINT1 GROUP 3", &(home->objects[0]), strlen("SPRINT1 GROUP 3"));

	buildObject(700, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"CPEN391", &(home->objects[1]), strlen("CPEN391"));

	destination->buttons = malloc(sizeof(Button) * 2);
	destination->objects = malloc(sizeof(Object) * 8);
	destination->numButtons = 2;
	destination->numObjects = 8;
	destination->backColour = WHITE;

	buildButton(200, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(destination->buttons[0]), strlen("Home"), home);
	buildButton(600, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Menu Jump", &(destination->buttons[1]), strlen("Menu Jump"), self);



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

	buildObject(450, 100, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
			BLACK, "", &(destination->objects[4]),
			strlen(""));
	buildObject(450, 150, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
			BLACK, "", &(destination->objects[5]),
			strlen(""));
	buildObject(450, 200, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
			BLACK, "", &(destination->objects[6]), strlen(""));
	buildObject(450, 250, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
			BLACK, "", &(destination->objects[7]), strlen(""));



	self->buttons = malloc(sizeof(Button) * 2);
	self->objects = malloc(sizeof(Object) * 10);
	self->numButtons = 2;
	self->numObjects = 10;
	self->backColour = WHITE;
	buildButton(200, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Home", &(self->buttons[0]), strlen("Home"), home);
	buildButton(600, 400, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK, AQUA, BLACK,
			"Menu Jump", &(self->buttons[1]), strlen("Menu Jump"), destination);

	buildObject(150, 50, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Your Name Is: ", &(self->objects[0]), strlen("Your Name Is: "));
	buildObject(450, 50, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
				BLACK, "", &(self->objects[1]), strlen(""));

	buildObject(150, 100, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Home Address: ", &(self->objects[2]), strlen("Home Address: "));
	buildObject(450, 100, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
				BLACK, "", &(self->objects[3]), strlen(""));

	buildObject(150, 150, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Phone #: ", &(self->objects[4]), strlen("Phone #: "));
	buildObject(450, 150, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
				BLACK, "", &(self->objects[5]), strlen(""));

	buildObject(150, 200, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Emergency #: ", &(self->objects[6]), strlen("Emergency #: "));
	buildObject(450, 200, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
				BLACK, "", &(self->objects[7]), strlen(""));

	buildObject(150, 250, OBJECT_WIDTH, OBJECT_HEIGHT, WHITE, WHITE, BLACK,
			"Your Location Is: ", &(self->objects[8]),
			strlen("Your Location Is: "));
	buildObject(450, 250, OBJECT_WIDTH + 100, OBJECT_HEIGHT / 2, BLACK, WHITE,
			BLACK, "", &(self->objects[9]), strlen(""));

	graphicTest->buttons = malloc(sizeof(Button) * 1);

	graphicTest->numButtons = 1;
	graphicTest->numObjects = 0;
	graphicTest->backColour = WHITE;
	buildButton(400, 240, 400, 400, WHITE, WHITE, WHITE, "Graphics",
			&(graphicTest->buttons[0]), strlen("Graphics"), home);

	return home;

}

//void writeCaptionButton(Button button, int fontColor, int backgroundColor) {

void drawPage(Page * currentScreen) {

	int j;
	for (j = 0; j < 481; j++) {

		HLine(0, j, 801, currentScreen->backColour);

	}
	usleep(50);

	int i = 0;
	for (i = 0; i < currentScreen->numButtons; i++) {

		drawButton(&(currentScreen->buttons[i]));
		usleep(50);
		writeCaptionButton(&(currentScreen->buttons[i]), BLACK, LIGHT_SKY_BLUE);
		usleep(50);

	}

	for (i = 0; i < currentScreen->numObjects; i++) {

		drawObject(&(currentScreen->objects[i]));
		usleep(50);
		writeCaptionObject(&(currentScreen->objects[i]), BLACK, PINK);
		usleep(50);

	}

}

/**
 * Updates the time and draws it onto the screen.
 */
updateTime() {
	Object * timeObject;
	int sw_values = 0;
	volatile int * slider_switch_ptr = (int *) SLIDER_SWITCH_BASE;
	char c;
	char *ptr;
	char buff[256];
	ptr = buff;

	while (GetData() != '$') {
		//printf("Waiting for start .. \n");
	}
	while ((c = GetData()) != '*') {
		//printf("%c\n", c);
		*ptr++ = c;
	}
	*ptr = '\0';
	sw_values = *(slider_switch_ptr);
	if (checkBuff(buff) == 1 && sw_values == 0) {

		char secondBuff[10];
		char minuteBuff[10];
		char timeBuff[10];
		char concatTime[30];
		char i;

		// grab the time values concatenate them
		printTime(6, 8, 10, buff, secondBuff, minuteBuff, timeBuff);
		strcpy(concatTime, timeBuff);
		strcat(concatTime, minuteBuff);
		strcat(concatTime, secondBuff);
		printf("%s\n", concatTime);

		// draw the time onto the screen
		buildObject(500, 100, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE, WHITE, BLACK,
				concatTime, timeObject, strlen(concatTime));
		drawObject(timeObject);
		writeCaptionObject(timeObject, BLACK, PINK);
	}
}

/*******************************************************************************
 ** Draw Rectangles
 *******************************************************************************/

int main(void) {
	srand(time(NULL));

	int j;
	Page *currentPage = buildMenu();
	drawPage(currentPage);

	Point *touch = malloc(sizeof(Point));
	Point *release = malloc(sizeof(Point));

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
	int col = 0;

	while (1) {

		printf("x = %d ", release->x);
		printf("y = %d\n", release->y);
		int test;
		int rect;
		int tri;
		int circ;

		// if we are in the graphics menu, draw the shapes
		if (strlen("Graphics")
				== strlen((currentPage->buttons[0]).buttonText)) {
			for (test = 0; test < 1; test++) {
				for (col = 0; col < 2000; col++) {

					int a = rand() % 799;
					int b = rand() % 799;
					int c = rand() % 479;
					int d = rand() % 479;

					Line(a, c, b, d, col%150);
				}

				for (circ = 0; circ < 150; circ++) {

					DrawCircleFill(400, 250, 100, circ);

				}
				for (rect = 0; rect < 150; rect++) {

					DrawRectangleFill(100, 700, 100, 300, BLACK, rect);

				}
				for (tri = 0; tri < 150; tri++) {

					DrawTriangles(100, 100, 200, 200, 300, 300, BLACK, tri);

				}

			}
		}

		if(ScreenTouched()){
			GetPress(touch);
			GetRelease(release);
		}

		for (j = 0; j < currentPage->numButtons; j++) {

			Button bttn = currentPage->buttons[j];
			if ((release->x >= bttn.x1) && (release->x <= bttn.x2)) {
				if ((release->y >= bttn.y1) && (release->y <= bttn.y2)) {
					currentPage = bttn.targetPage;
					drawPage(currentPage);
				}
			}

		}
	}
	free(touch);
	free(release);

	return 0;
}

//	Init_GPS();
//	StopLogging();
//	usleep(500);
//	ClearLogging();
//	usleep(500);
//	StartLogger();
//	usleep(500);
//
//	initBluetooth(); // CURRENT ISSUE IS THAT MY INITIALIZATION COMMANDS ARE NOT SETTING UP THE CORRECT PROPERTIES. MAYBE THERE IS AN ISSUE
//
//	usleep(1000);
//	enterCommandMode();
//	usleep(1000);
//	factoryReset();
//	usleep(1000);
//	getcharBluetooth();
//	setDeviceName();
//	usleep(1000);
//	getcharBluetooth();
//	setBluetoothPassword();
//	getcharBluetooth();
//	usleep(1000);

//	// test draw HLine
//		printf("Hello World!\n");
//		int i, j;
//
////		Fill(0,0, RED, RED );
//
//		for(j = 0; j < 481; j++){
//
//			HLine(0,j,801, WHITE);
//
//		}
//	DrawRectangles(5,50,0,50,AQUA,BLACK); //x1 x2 y1 y2 fill border
//	usleep(50);
//
//	DrawRectangles(5,50,100,150,MEDIUM_PURPLE,BLACK);
//	usleep(50);
//
//	DrawRectangles(5,50,200,250,PLUM,BLACK);
//	usleep(50);
//
//	DrawRectangles(5,50,300,350,ORCHID,BLACK);
//	usleep(50);
//	DrawCircle(400, 200, 20, BLACK);

//	DrawRectangles(0,50,70,100,AQUA,BLACK);
//	DrawRectangles(0,50,70,100,MIDNIGHT_BLUE,BLACK);
//	DrawRectangles(0,50,70,100,INDIGO,BLACK);

//
//		for(j = 0; j < 480; j++){
//			HLine(0, j, 400, BLUE);
//		}
//		for(i = 0; i < 800; i++){
//			VLine(i, 0, 240, RED);
//		}
//		Line(0, 800, 800, 480, GREEN);
//		Line(0,100,800,480,ORANGE);
//		for(i = 0; i < 800; i++){
//			Line(i, 200, 800, 480, PURPLE);
//	}
//		printf("done\n");

//GPS STUFF
//dumpLogger();

//	int sw_values = 0;
//
//	volatile int * slider_switch_ptr = (int *) SLIDER_SWITCH_BASE;
//
//	char c;
//	char buff[256];
//	char *ptr;
//	while (1) {
//
//		ptr = buff;
//
//		while (GetData() != '$') {
//			//printf("Waiting for start .. \n");
//		}
//		while ((c = GetData()) != '*') {
//			//printf("%c\n", c);
//			*ptr++ = c;
//		}
//		*ptr = '\0';
//		//printf("\n%s\n", buff);
//		int example = 0x76543211;
//		sw_values = *(slider_switch_ptr);
//		printf("Switch values : %d\n", sw_values);
//		if (checkBuff(buff) == 1 && sw_values == 0) {
//
//			printTime(6, 8, 10, buff);
//			//Update_HEX_Display (example);
//
//		} else if (checkBuff(buff) == 1 && sw_values == 1) {
//
//			printCoordinates(17, 29, buff);
//
//		}
//
//		//printf("%c", c);
//	}
