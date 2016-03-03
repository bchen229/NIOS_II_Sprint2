// graphics registers all address begin with '8' so as to by pass data cache on NIOS
#include "Colours.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Hardware.h"

void WriteAPixel(int x, int y, int Colour) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command

	GraphicsX1Reg = x; // write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = PutAPixel; // give graphics "write pixel" command
}

int ReadAPixel(int x, int y) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command

	GraphicsX1Reg = x; // write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel; // give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS; // is graphics done reading pixel
	return (int) (GraphicsColourReg); // return the palette number (colour)
}

void ProgramPalette(int PaletteNumber, int RGB) {
	WAIT_FOR_GRAPHICS;
	GraphicsColourReg = PaletteNumber;
	GraphicsX1Reg = RGB >> 16; // program red value in ls.8 bit of X1 reg
	GraphicsY1Reg = RGB; // program green and blue into ls 16 bit of Y1 reg
	GraphicsCommandReg = ProgramPaletteColour; // issue command
}

void HLine(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command

	GraphicsX1Reg = x1; // write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x1 + length;
	GraphicsY2Reg = y1;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = DrawHLine; // give graphics "DrawHLine" command
}

void VLine(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command

	GraphicsX1Reg = x1; // write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x1;
	GraphicsY2Reg = y1 + length;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = DrawVLine; // give graphics "DrawVLine" command
}

void Line(int x1, int y1, int x2, int y2, int Colour) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command

	GraphicsX1Reg = x1; // write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = DrawLine; // give graphics "DrawLine" command
}

void DrawRectangleFill(int x1, int x2, int y1, int y2, int borderColour,
		int fillColour) {
	int j;
	int h_length = x2 - x1;
	int v_length = y2 - y1;

	WAIT_FOR_GRAPHICS;

	for (j = y1; j < y2; j++) {
		HLine(x1, j, h_length, fillColour);
	}
	HLine(x1, y1, h_length, borderColour);
	HLine(x1, y2, h_length, borderColour);
	VLine(x1, y1, v_length, borderColour);
	VLine(x2, y1, v_length + 1, borderColour);
}

void DrawRectangle(int x1, int x2, int y1, int y2, int borderColour) {
	//int j;
	int h_length = x2 - x1;
	int v_length = y2 - y1;

	WAIT_FOR_GRAPHICS;

	HLine(x1, y1, h_length, borderColour);
	HLine(x1, y2, h_length, borderColour);
	VLine(x1, y1, v_length, borderColour);
	VLine(x2, y1, v_length + 1, borderColour);
}

void DrawTriangles(int x1, int y1, int x2, int y2, int x3, int y3,
		int borderColour) {

	WAIT_FOR_GRAPHICS;

	Line(x1, y1, x2, y2, borderColour);
	Line(x2, y2, x3, y3, borderColour);
	Line(x3, y3, x1, y1, borderColour);
}

void DrawCircle(int x0, int y0, int radius, int COLOUR) {
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

	WAIT_FOR_GRAPHICS;

	while (y <= x) {

		WriteAPixel(x + x0, y + y0, COLOUR); // Octant 1
		WriteAPixel(y + x0, x + y0, COLOUR); // Octant 2
		WriteAPixel(-x + x0, y + y0, COLOUR); // Octant 4
		WriteAPixel(-y + x0, x + y0, COLOUR); // Octant 3
		WriteAPixel(-x + x0, -y + y0, COLOUR); // Octant 5
		WriteAPixel(-y + x0, -x + y0, COLOUR); // Octant 6
		WriteAPixel(x + x0, -y + y0, COLOUR); // Octant 7
		WriteAPixel(y + x0, -x + y0, COLOUR); // Octant 8
		y++;
		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
		} else {
			x--;
			decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
		}
	}
}

void DrawCircleFill(int x0, int y0, int radius, int COLOUR) {
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

	WAIT_FOR_GRAPHICS;

	while (y <= x) {

		Line(x0, y0, x + x0, y + y0, COLOUR); // Octant 1
		Line(x0, y0, y + x0, x + y0, COLOUR); // Octant 2
		Line(x0, y0, -x + x0, y + y0, COLOUR); // Octant 4
		Line(x0, y0, -y + x0, x + y0, COLOUR); // Octant 3
		Line(x0, y0, -x + x0, -y + y0, COLOUR); // Octant 5
		Line(x0, y0, -y + x0, -x + y0, COLOUR); // Octant 6
		Line(x0, y0, x + x0, -y + y0, COLOUR); // Octant 7
		Line(x0, y0, y + x0, -x + y0, COLOUR); // Octant 8
		y++;
		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
		} else {
			x--;
			decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
		}
	}
}
