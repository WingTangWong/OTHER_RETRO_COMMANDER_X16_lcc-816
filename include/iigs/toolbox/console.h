/*
 * GS/OS Console driver stuff
 */

#ifndef __TYPES__
#include <types.h>
#endif

#ifndef __console__
#define __console__

enum {
	scNULL          = 0x00,
	scSaveTextPort  = 0x01,
	scSetPortSize   = 0x02,
	scClearFromBOL  = 0x03,
	scPopTextPort   = 0x04,
	scHorizScroll   = 0x05,
	scSetVertPos    = 0x06,
	scRingBell      = 0x07,
	scBackspace     = 0x08,
	scTab           = 0x09,
	scLineFeed      = 0x0a,
	scClearToEOP    = 0x0b,
	scClearAndHome  = 0x0c,
	scReturn        = 0x0d,
	scSetNormal     = 0x0e,
	scSetInverse    = 0x0f,
	scDLESpaceExp   = 0x10,
	scSet40Columns  = 0x11,
	scSet80Columns  = 0x12,
	scClearFromBOP  = 0x13,
	scSetHorizPos   = 0x14,
	scSetCursorMove = 0x15,
	scScrollDown    = 0x16,
	scScrollUp      = 0x17,
	scDisableMouse  = 0x18,
	scHome          = 0x19,
	scClearLine     = 0x1a,
	scEnableMouse   = 0x1b,
	scCursorRight   = 0x1c,
	scClearEOL      = 0x1d,
	scGotoXY        = 0x1e,
	scCursorUp      = 0x1f
};


// DStatus
/*
#define GetDeviceStatus 0x0000
#define GetConfigParameters 0x0001
#define GetWaitStatus 0x0002
*/

#define GetTextPort 0x8000
#define GetInputPort 0x8001
#define GetTerminators 0x8002
#define SaveTextPort 0x8003
#define GetScreenChar 0x8004
#define GetReadMode 0x8005
#define GetDefaultString 0x8006
#define GetVectors 0x8007

// DControl

#define SetInputPort 0x8000
#define SetTerminators 0x8001
#define RestoreTextPort 0x8002
#define SetReadMode 0x8003
#define SetDefaultString 0x8004
#define AbortInput 0x8005
#define AddTrap 0x8006
#define ResetTrap 0x8007


typedef struct TextPortRec {
	Byte ch;          /* current cursor horizontal */
	Byte cv;          /* current cursor vertical */
	Byte windLeft;    /* boundaries of the current text port */
	Byte windTop;
	Byte windRight;
	Byte windBottom;
	Byte windWidth;
	Byte windLength;
	Byte consWrap;
	Byte consAdvance;
	Byte consLF;
	Byte consScroll;
	Byte consVideo;
	Byte consDLE;
	Byte consMouse;
	Byte consFill;
} TextPortRec, *TextPortRecPtr;


typedef struct InputPortRec {
	Byte fillChar;
	Byte defCursor;
	Byte cursorMode;
	Byte beepFlag;
	Byte entryType;
	Byte exitType;
	Byte lastChar;
	Byte lastMod;
	Byte lastTermChar;
	Byte lastTermMod;
	Byte cursorPos;
	Byte inputLength;
	Byte inputField;
	Byte originH;
	Word originX;
	Byte originV;
} InputPortRec, *InputPortRecPtr;

#endif
