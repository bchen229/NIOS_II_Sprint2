/**
 * Input boxes are boxes that hold user input.
 */
typedef struct InputBox {

	int x1;
	int x2;
	int y1;
	int y2;
	int fontColour;
	int fillColour;
	int outlineColour;
	char inputBuf[256]; //I set the buffer to 256, but it can be changed to a larger number

} InputBox;

/**
 * SD Boxes are boxes that execute SD Card
 * functions when pressed.
 */
typedef struct SDBox {

	char *SDBoxText;
	int x1;
	int x2;
	int y1;
	int y2;
	int outlineColour;
	int fillColour;
	int fontColour;
	int captionLength;

} SDBox;

/**
 * Buttons are boxes that contain a target
 * page. When buttons are pressed, the current
 * page updates to the target page.
 */
typedef struct Button {

	char *buttonText;
	int x1;
	int x2;
	int y1;
	int y2;
	int outlineColour;
	int fillColour;
	int fontColour;
	int captionLength;
	struct Page *targetPage;

} Button;

/**
 * Keys are the individual components that make
 * up the keyboard.
 */
typedef struct Key {

	int fontColour;
	int keyOutlineColour;
	int keyFillColour;
	int x1;
	int x2;
	int y1;
	int y2;
	char *alpha; //the string that gets printed to the key
	int len;
	char writeChar; //the stored in the buffer upon press

} Key;

/**
 * The keyboard is an object that operates on the keyboard page.
 * User input is added to the buffer and saved into an input box
 * after the "Done" key is pressed.
 */
typedef struct Keyboard {
	char *fieldText;
	char buffer[256];
	int bufCount;
	int backColour;
	int outlineColour;
	int keyset; // flag for which keyset to display
	int isUpper;
	int isNum;
	int curInputBoxIndex;
	int *numKeys;
	Key *keyset_lowercase, *keyset_uppercase, *numberset1;
	Key *spacebar, *numbers, *caps, *backspace, *lower;
	Key *currentKeyset; // you can assign this to each and every one as needed
	struct Page *caller;

} Keyboard;

/**
 * An object is a static object on a page which
 * does not have any special functionality.
 */
typedef struct Object {

	char *objectText;
	int x1;
	int x2;
	int y1;
	int y2;
	int outlineColour;
	int fillColour;
	int fontColour;
	int captionLength;

} Object;

/**
 * A page is a node in the User interface.
 * They contain buttons, objects, inputBoxes,
 * and sdBoxes. A unique keyboard also contains
 * the keyboard.
 */
typedef struct Page {

	int backColour;
	int outlineColour;
	int numInputBoxes;
	int numButtons;
	int numObjects;
	int numSDBoxes;
	int hasKeyboard;
	char *menuName;
	Button *buttons;
	Object *objects;
	Keyboard keyboard;
	InputBox *inputBoxes;
	SDBox *sdBoxes;

} Page;

/**
 * Contains the x and y coordinates
 */
typedef struct {
	int x, y;
} Point;

// filenames for logging
#define LOGFILE "logfile.txt"

//encrypted and non encrypted file names
#define ESELF "eself.txt"
#define EDEST "edest.txt"
#define NSELF "nself.txt"
#define NDEST "ndest.txt"
#define KEYFILE "key.txt"

// text files for addresses
#define AD1 "a1.txt"
#define AD2 "a2.txt"
#define AD3 "a3.txt"

#define MENU_SIZE 1
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define OBJECT_WIDTH 150
#define OBJECT_HEIGHT 60
#define TEXT_SIZE 6

#define KEY_WIDTH 50
#define KEY_HEIGHT 30

#define ALPHA_SIZE 35
#define NUM_SIZE 13

#ifndef NULL
#define NULL   ((void *) 0)
#endif

double curLat; // Most recently read latitude from GPS
double curLong; // Most recently read longitude from GPS

Page *globalCurrentPage; // globalCurrentPage represents the page currently on the screen
Page *home;
Page *destination;
Page *self;
Page *keys;
Page *map;
Page *password;
Page *passwordSetup;
Page *loggingSettings;
Page *panic;
Page *addresses;

// Arrays used to build the keyboard
static const char row1_low[] = "qwertyuiop"; // 10 chars
static const char row2_low[] = "asdfghjkl;'"; // 11 chars
static const char row3_low[] = "zxcvbnm,."; // 9 chars
static const char row1_caps[] = "QWERTYUIOP"; // 10 chars
static const char row2_caps[] = "ASDFGHJKL:\""; // 11 chars
static const char row3_caps[] = "ZXCVBNM!?"; // 9 chars
static const char numbers[] = "1234567890"; // 10 chars

// Signal the current GPS location is out of
// the geofencing range.
int panicFlag;

// variables used for encryption
char key[16];
int encryptedtextlen;
