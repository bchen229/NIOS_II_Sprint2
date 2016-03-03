/**
 * Initialize the input box
 */
void buildInputBox(InputBox *ib, int x_centre, int y_centre, int box_width,
		int box_height, int fillColour, int fontColour, int outlineColour);

/**
 * Update the contents in the input box.
 */
void drawInputBox(InputBox *ib);

/**
 * Redraw the input box with new word.
 */
void updateInputBox(InputBox *ib);
