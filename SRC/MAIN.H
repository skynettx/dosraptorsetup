//
// MAIN.H
//
#include "setup.h"
#include "menu.h"
#include "keys.h"

#define S_CON1 "Keyboard"
#define S_CON2 "Mouse"
#define S_CON3 "Joystick"

#define MAXARGS 12

typedef enum
{
	FALSE,
	TRUE
} BOOL;

typedef enum
{
	M_NONE,
	M_PC,
	M_ADLIB,
	M_GUS,
	M_PAS,
	M_SB,
	M_WAVE,
	M_CANVAS,
	M_GMIDI,
	M_AWE,
	M_LAST
} SCARD;

typedef enum
{
	C_KEY,
	C_MOUSE,
	C_JOY,
	C_LAST
} CONTROL;

typedef struct
{
	SCARD card;
	short midiport;
	short irq;
	short dma;
	short port;
} DMXCARD;

typedef struct
{
	CONTROL control;
	DMXCARD m;
	DMXCARD d;
	short numdig;
} DMXINFO;

typedef struct
{
	int up;
	int down;
	int left;
	int right;
	int fire;
	int use;        // ID = USE         CYGNUS = USE SPECIAL WEAPON
	int key1;       // ID = STRAFE ON   CYGNUS = CHANGE SPECIAL WEAPON
	int key2;       // ID = SPEED ON    CYGNUS = MEGA BOMB HOT KEY
	int key3;       // ID = STRAFE LEFT
	int key4;       // ID = STRAFE RIGHT
	int mouse[3];
	int joy[4];
} CONTS;

typedef enum
{
	ID_FIRE,	// def button 1
	ID_MEGA,	// def button 3
	ID_CHSPECIAL    // def button 2
} IDCONTS;

extern char keydesc[256][10];
extern int mousepresent;
extern DMXINFO lastc;
extern DMXINFO newc;
extern BOOL savemusic;
extern BOOL savefx;
extern CONTS curk;


void IrqError(pup_t far* pup);
void MouseError(pup_t far* pup);
void ErrorWindow(pup_t far* pup);
void StartUp(void);
void MainMenu(void);
void DrawCurrentConfig(int control, int mcard, int dcard);

//
// Functions in other modules
//

// MUSIC.C
int SetupMusic(void);
int ChooseMidiPort(DMXCARD* card);
int ChooseSBPort(DMXCARD* card);

// SFX.C
int SetupFX(void);

// CONTROL.C
int ChooseController(void);

// CONFIG.C
void ConfigControl(void);
void Pos(item_t* item);
void Clear(item_t* item);
