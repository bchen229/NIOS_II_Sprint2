#define BOX_WIDTH 150
#define BOX_HEIGHT 50

/**
 * Initialize SD Box with parameters provided.
 */
void buildSDBox(int x_centre, int y_centre, int button_width, int button_height,
		int outlineColour, int fillColour, int fontColor, char *text,
		SDBox *sdb, int numChar);

/**
 * Draws the SD Box to the screen.
 */
void drawSDBox(SDBox *sdb);

/**
 * Draws the caption inside the SD Box.
 */
void writeCaptionSDBox(SDBox * sdb, int fontColor, int backgroundColor);

