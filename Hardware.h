/**
 * Bluetooth hardware defines
 */
#define Bluetooth_Control (*(volatile unsigned char *)(0x84000220))
#define Bluetooth_Status (*(volatile unsigned char *)(0x84000220))
#define Bluetooth_TxData (*(volatile unsigned char *)(0x84000222))
#define Bluetooth_RxData (*(volatile unsigned char *)(0x84000222))
#define Bluetooth_Baud (*(volatile unsigned char *)(0x84000224))

/**
 * Graphics hardware defines
 */
#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   			(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   			(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   			(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg   			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0x84000010))

/************************************************************************************************
 ** This macro pauses until the graphics chip status register indicates that it is idle
 ***********************************************************************************************/

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

//Here are some software routines to drive some simple graphics functions

// #defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "Colours.h" contains constants for all 256 colours
// while the course file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into the palette

//#define	BLACK			0
//#define	WHITE			1
//#define	RED				2
//#define	LIME			3
//#define	BLUE			4
//#define	YELLOW			5
//#define	CYAN			6
//#define	MAGENTA			7

/**
 * GPS hardware defines
 */
#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

// HEX Display and Slider addresses
#define SLIDER_SWITCH_BASE 0x00001050
#define HEX01  0x00001110
#define HEX23  0x00001100
#define HEX45  0x000010b0
#define HEX67  0x000010a0

// LEDS from DE2
#define redLEDS (*(volatile unsigned char *)(0x80001040))
#define greenLEDS (*(volatile unsigned char *)(0x80001030))

// function declarations

/*******************************************************************************************
 * This function writes a single pixel to the x,y coords specified using the specified colour
 * Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
 ********************************************************************************************/
void WriteAPixel(int x, int y, int Colour);

/*********************************************************************************************
 * This function read a single pixel from the x,y coords specified and returns its colour
 * Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
 *********************************************************************************************/
int ReadAPixel(int x, int y);

/**********************************************************************************
 ** subroutine to program a hardware (graphics chip) palette number with an RGB value
 ** e.g. ProgramPalette(RED, 0x00FF0000) ;
 ************************************************************************************/
void ProgramPalette(int PaletteNumber, int RGB);

/*********************************************************************************************
 This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
 *********************************************************************************************/
void HLine(int x1, int y1, int length, int Colour);

/*********************************************************************************************
 This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
 *********************************************************************************************/
void VLine(int x1, int y1, int length, int Colour);

/*******************************************************************************
 ** Implementation of Bresenhams line drawing algorithm
 *******************************************************************************/
void Line(int x1, int y1, int x2, int y2, int Colour);

/*******************************************************************************
 ** Draw Filled Rectangles w/ Boarder
 *******************************************************************************/
void DrawRectangleFill(int x1, int x2, int y1, int y2, int borderColour,
		int fillColour);

/*******************************************************************************
 ** Draw Filled Rectangles w/ Boarder
 *******************************************************************************/
void DrawRectangle(int x1, int x2, int y1, int y2, int borderColour);

/*******************************************************************************
 ** Draw Triangle
 *******************************************************************************/
void DrawTriangles(int x1, int y1, int x2, int y2, int x3, int y3,
		int borderColour);

/*******************************************************************************
 ** Draw Circle implementation
 ** IMPLEMENTATION OF THE MIDPOINT CIRCLE ALGORITHM FOUND ONLINE
 ** SOURCE: https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *******************************************************************************/
void DrawCircle(int x0, int y0, int radius, int COLOUR);

/*******************************************************************************
 ** Draw Circle Fill implementation
 ** IMPLEMENTATION OF THE MIDPOINT CIRCLE ALGORITHM FOUND ONLINE
 ** SOURCE: https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *******************************************************************************/
void DrawCircleFill(int x0, int y0, int radius, int COLOUR);


