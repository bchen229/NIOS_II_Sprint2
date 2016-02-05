struct Page;
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

	//FONT RELATED STUFF HERE
	struct Page *targetPage;

} Button;

typedef struct Keys {

	//this may get combined with buttons and some point

	int fontColour;
	int keyOutlineColour;
	int keyFillColour;
	int x1;
	int x2;
	int y1;
	int y2;

} Keys;

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

//FONT RELATED STUFF HERE

} Object;

typedef struct Page {

	char *menuName;

	int backColour;
	int outlineColour;

	int numButtons;
	int numObjects;

	Button *buttons;
	Object *objects;
	Keys *keyboard;
} Page;

typedef struct {
	int x, y;
} Point;
