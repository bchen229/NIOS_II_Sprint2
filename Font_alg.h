/*************************************************************************************************
 ** This function draws a single ASCII character at the coord and colour specified
 ** it optionally ERASES the background colour pixels to the background colour
 ** This means you can use this to erase characters
 **
 ** e.g. writing a space character with Erase set to true will set all pixels in the
 ** character to the background colour
 *************************************************************************************************/
void OutGraphicsCharFont2a(int x, int y, int colour, int backgroundcolour,
		int c, int Erase);

/**************************************************************************************************
 ** This function draws a single ASCII character at the coord specified using the colour specified
 ** OutGraphicsCharFont2(100,100, RED, 'A', TRUE, FALSE, 1, 1) ;	// display upper case 'A' in RED
 ** at coords 100,100, erase background no scroll, scale x,y= 1,1
 **************************************************************************************************/
void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour,
		int c, int Erase);
