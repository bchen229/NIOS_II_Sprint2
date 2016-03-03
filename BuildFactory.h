// function declarations for BuildFactory

/**
 * Constructor for a button (instantiates and defines all fields)
 */
void buildButton(int x_centre, int y_centre, int button_width,
		int button_height, int outlineColour, int fillColour, int fontColor,
		char *text, Button * b, int numChar, Page * targetPage);

/**
 * Constructor for a key
 */
void buildKey(int x_centre, int y_centre, int button_width, int button_height,
		int outlineColour, int fillColour, int fontColor, char *text, Key *k,
		int numChar);

/**
 * Constructor for a keyboard
 */
Keyboard buildKeyboard(Keyboard *kb);

/*
 * Constructor for an object (instantiates and defines all fields)
 */
void buildObject(int x_centre, int y_centre, int object_width,
		int object_height, int outlineColour, int fillColour, int fontColor,
		char *text, Object *o, int numChar);
