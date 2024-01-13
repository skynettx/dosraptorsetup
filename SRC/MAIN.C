//
// MAIN.C - Handles StartUp and the MainMenu
//
#include <process.h>
#include <io.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>
#include <bios.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "scguess.h"
#include "prefapi.h"

char keydesc[256][10];
unsigned char ASCIINames[] = // Unshifted ASCII for scan codes
{
	//       0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,		// 0
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 0, 0, 'A', 'S', // 1
	'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', 0, '`', 0, 92, 'Z', 'X', 'C', 'V',	// 2
	'B', 'N', 'M', ',', '.', '/', 0, '*', 0, 0, 0, 0, 0, 0, 0, 0,				// 3
	0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',			// 4
	'2', '3', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,						// 5
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,								// 6
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0								// 7
};

char cards[M_LAST][22] = {
	"None",
	"PC Speaker",
	"Adlib",
	"Gravis Ultra Sound",
	"Pro Audio Spectrum",
	"Sound Blaster",
	"WaveBlaster",
	"Roland Sound Canvas",
	"General Midi",
	"Sound Blaster AWE 32"
};

char controls[C_LAST][20] = {
	S_CON1,
	S_CON2,
	S_CON3 };

CONTS curk;

DMXINFO lastc;
DMXINFO newc;

void* swindow;
BOOL savemusic = FALSE;
BOOL savefx = FALSE;

#define KEYBOARDINT 0x9

int mousepresent = 0;

char* n1 = "%s\\setup.ini";
char* pogpath = "APOGEECD";
char    cdpath[33];

BOOL cdflag = FALSE;

char* InitLoadSave(void)
{
	char* var1;

	var1 = getenv(pogpath);

	memset(cdpath, 0, 33);

	strncpy(cdpath, var1, 32);

	if (access(cdpath, 0) == 0)
		cdflag = TRUE;
	else
		cdflag = FALSE;

	if (cdflag)
		printf("Data Path = %s\n", cdpath);

	return (cdpath);

}

enum
{
	MAIN_CMUSIC,
	MAIN_CSFX,
	MAIN_TYPE,
	MAIN_CONFIG,
	MAIN_SAVE,
	MAIN_MAX
};

item_t mainitems[] =
{
	{MAIN_CMUSIC, 26, 13, 27, -1, -1},
	{MAIN_CSFX, 26, 14, 27, -1, -1},
	{MAIN_TYPE, 26, 15, 27, -1, -1},
	{MAIN_CONFIG, 26, 16, 27, -1, -1},
	{MAIN_SAVE, 26, 17, 27, -1, -1},
};

menu_t mainmenu =
{
	&mainitems[0],
	MAIN_CMUSIC,
	MAIN_MAX,
	0x7f };

//
//	Draw a PUP and get a keypress
//
void IrqError(pup_t far* pup)
{
	SaveScreen();
	DrawPup(pup);
	while (kbhit())
		getch();
	while (!kbhit());
	RestoreScreen();
	while (kbhit())
		getch();
}

void MouseError(pup_t far* pup)
{
	SaveScreen();
	DrawPup(pup);

	DrawHelpLabel(1, " ");

	while (kbhit())
		getch();
	while (getch() != 0x1b)
		;
	RestoreScreen();
	while (kbhit())
		getch();
}

void ErrorWindow(pup_t far* pup)
{
	SaveScreen();
	DrawPup(pup);
	while (kbhit())
		getch();
	while (getch() != 0x1b)
		;
	RestoreScreen();
	while (kbhit())
		getch();
	sound(3000);
	delay(10);
	nosound();
}

//
// Make ASCII names/key value lookup
//
void MakeKeyLookup(void)
{
	int loop;

	memset(keydesc, 0, sizeof(keydesc));

	for (loop = 0; loop < 128; loop++)
		keydesc[loop][0] = ASCIINames[loop];

	strcpy(keydesc[SC_CAPS_LOCK], "CAPSLOCK");
	strcpy(keydesc[SC_BACKSPACE], "BACKSP");
	strcpy(keydesc[SC_ENTER], "ENTER");
	strcpy(keydesc[SC_TAB], "TAB");
	strcpy(keydesc[SC_RIGHT_SHIFT], "RSHIFT");
	strcpy(keydesc[SC_SPACE], "SPACE");
	strcpy(keydesc[SC_CTRL], "CTRL");
	strcpy(keydesc[SC_ALT], "ALT");
	strcpy(keydesc[SC_INSERT], "INS");
	strcpy(keydesc[SC_DELETE], "DEL");
	strcpy(keydesc[SC_PAGEUP], "PGUP");
	strcpy(keydesc[SC_PAGEDN], "PGDN");
	strcpy(keydesc[SC_HOME], "HOME");
	strcpy(keydesc[SC_END], "END");
	strcpy(keydesc[SC_UP], "UP");
	strcpy(keydesc[SC_DOWN], "DOWN");
	strcpy(keydesc[SC_LEFT], "LEFT");
	strcpy(keydesc[SC_RIGHT], "RIGHT");
}

//
// Set funky blue color
//
void SetColor(void)
{

	asm	push  ax
		asm	push  dx

		asm	mov   dx, 0x3C8
		asm	mov   ax, 1
		asm	out   dx, al
		asm	inc   dx

		asm	mov   ax, 1
		asm	out   dx, al

		asm	mov   ax, 5
		asm	out   dx, al

		asm	mov   ax, 16
		asm	out   dx, al

		asm	pop   dx
		asm	pop   ax
}

//
// Draw current config info in window
// MAKE SURE NO WINDOWS ARE ON TOP!
//
void DrawCurrentConfig(int control, int mcard, int dcard)
{
	RestoreScreen();
	textcolor(8);
	textbackground(7);

	if (control != -1)
	{
		gotoxy(35, 6);
		cprintf("                    ");
		gotoxy(35, 6);
		cprintf("%s", controls[control]);
	}

	if (mcard != -1)
	{
		gotoxy(35, 7);
		cprintf("                    ");
		gotoxy(35, 7);
		cprintf("%s", cards[mcard]);
	}

	if (dcard != -1)
	{
		gotoxy(35, 8);
		cprintf("                    ");
		gotoxy(35, 8);
		cprintf("%s", cards[dcard]);
		gotoxy(1, 25);
	}

	SaveScreen();
}

void DrawEmptyConfig(void)
{
	RestoreScreen();
	textcolor(8);
	textbackground(7);
	gotoxy(35, 6);
	cprintf("                    ");
	gotoxy(35, 6);
	cprintf("None");
	gotoxy(35, 7);
	cprintf("                    ");
	gotoxy(35, 7);
	cprintf("None");
	gotoxy(35, 8);
	cprintf("                    ");
	gotoxy(35, 8);
	cprintf("None");
	gotoxy(1, 25);
	SaveScreen();
}

//
// Start up and initialize SETUP
//
void StartUp(void)
{
	int addr;
	int irq;
	int dma;
	int midi;
	union REGS r;
	char ini[24];

	InitLoadSave();

	r.x.ax = 0;
	int86(0x33, &r, &r);
	if (r.x.ax == 0xffff)
		mousepresent = 1;
	else
		mousepresent = 0;

	r.x.ax = 2;
	int86(0x33, &r, &r);

	SetColor();

	memset(&newc, 0, sizeof(DMXINFO));
	memset(&lastc, 0, sizeof(DMXINFO));

	MakeKeyLookup();
	midi = addr = irq = dma = 0; // WILL BE INITED LATER

	curk.up = SC_UP;
	curk.down = SC_DOWN;
	curk.left = SC_LEFT;
	curk.right = SC_RIGHT;
	curk.fire = SC_CTRL;
	curk.use = SC_ALT;
	curk.key1 = SC_SPACE;
	curk.key2 = SC_RIGHT_SHIFT;
	curk.key3 = SC_COMMA;
	curk.key4 = SC_PERIOD;
	curk.mouse[0] = 0;
	curk.mouse[1] = 1;
	curk.mouse[2] = 2;
	curk.joy[0] = 0;
	curk.joy[1] = 1;
	curk.joy[2] = 2;
	curk.joy[3] = 3;


	newc.m.card = M_NONE;
	newc.m.port = -1;
	newc.m.midiport = -1;
	newc.m.irq = -1;
	newc.m.dma = -1;
	newc.d = newc.m;
	newc.numdig = 4;

	DrawPup(&title);
	DrawPup(&show);

	SaveScreen();


	if (SmellsLikeGUS(&addr, &irq, &dma))
	{
		newc.m.card = M_GUS;
		newc.m.port = addr;
		newc.m.midiport = -1;
		newc.m.irq = irq;
		newc.m.dma = dma;
		newc.d = newc.m;
		//fprintf(stderr, "GUS: addr=%x, irq=%d, dma=%d\n", addr, irq, dma);
	}
	else if (SmellsLikeSB(&addr, &irq, &dma, &midi))
	{
		newc.m.card = M_SB;
		newc.m.port = addr;
		newc.m.midiport = midi;
		newc.m.irq = irq;
		newc.m.dma = dma;
		newc.d = newc.m;
	}

	if (cdflag)
		sprintf(ini, n1, cdpath);
	else
		strcpy(ini, "setup.ini");

	if (INI_InitPreference(ini))
	{
		lastc.control = newc.control = INI_GetPreferenceLong("Setup", "Control", (long)0);
		lastc.m.card = INI_GetPreferenceLong("Music", "CardType", (long)0);
		lastc.m.port = INI_GetPreferenceHex("Music", "BasePort", (long)-1);
		lastc.m.midiport = INI_GetPreferenceHex("Music", "MidiPort", (long)-1);
		lastc.m.irq = INI_GetPreferenceLong("Music", "Irq", (long)-1);
		lastc.m.dma = INI_GetPreferenceLong("Music", "Dma", (long)-1);
		lastc.d.card = INI_GetPreferenceLong("SoundFX", "CardType", (long)0);
		lastc.d.port = INI_GetPreferenceHex("SoundFX", "BasePort", (long)-1);
		lastc.d.midiport = INI_GetPreferenceHex("SoundFX", "MidiPort", (long)-1);
		lastc.d.irq = INI_GetPreferenceLong("SoundFX", "Irq", (long)-1);
		lastc.d.dma = INI_GetPreferenceLong("SoundFX", "Dma", (long)-1);
		newc.numdig = lastc.numdig = INI_GetPreferenceLong("SoundFX", "Channels", 4);
		curk.up = INI_GetPreferenceLong("Keyboard", "MoveUp", (long)SC_UP);
		curk.down = INI_GetPreferenceLong("Keyboard", "MoveDn", (long)SC_DOWN);
		curk.left = INI_GetPreferenceLong("Keyboard", "MoveLeft", (long)SC_LEFT);
		curk.right = INI_GetPreferenceLong("Keyboard", "MoveRight", (long)SC_RIGHT);
		curk.fire = INI_GetPreferenceLong("Keyboard", "Fire", (long)SC_CTRL);
		curk.use = INI_GetPreferenceLong("Keyboard", "FireSp", (long)SC_ALT);
		curk.key1 = INI_GetPreferenceLong("Keyboard", "ChangeSp", (long)SC_SPACE);
		curk.key2 = INI_GetPreferenceLong("Keyboard", "MegaFire", (long)SC_RIGHT_SHIFT);
		curk.mouse[0] = INI_GetPreferenceLong("Mouse", "Fire", (long)0);
		curk.mouse[1] = INI_GetPreferenceLong("Mouse", "FireSp", (long)1);
		curk.mouse[2] = INI_GetPreferenceLong("Mouse", "ChangeSp", (long)2);
		curk.joy[0] = INI_GetPreferenceLong("JoyStick", "Fire", (long)0);
		curk.joy[1] = INI_GetPreferenceLong("JoyStick", "FireSp", (long)1);
		curk.joy[2] = INI_GetPreferenceLong("JoyStick", "ChangeSp", (long)2);
		curk.joy[3] = INI_GetPreferenceLong("JoyStick", "MegaFire", (long)3);

		if (lastc.control != -1)
			DrawCurrentConfig(lastc.control, -1, -1);

		if (lastc.m.card != -1)
			DrawCurrentConfig(-1, lastc.m.card, -1);

		if (lastc.d.card != -1)
			DrawCurrentConfig(-1, -1, lastc.d.card);

		mainmenu.startitem = MAIN_CMUSIC;
	}
	else
	{
		DrawEmptyConfig();

		ChooseController();
		SetupMusic();
		SetupFX();

		mainmenu.startitem = MAIN_SAVE;
	}

	DrawPup(&idmain2);
	SaveScreen();

	//
	// GLOBALS
	//
	MainMenu();
	clrscr();
}

//
// Main menu
//
void MainMenu(void)
{
	int field;
	short key;

	ResetHelpLabel();
	hlfmain = 1;

	// ASSUME THAT THE MAIN MENU HAS BEEN DRAWN IN STARTUP

	while (1)
	{
		SetupMenu(&mainmenu);
		field = GetMenuInput();
		key = menukey;

		if (key == KEY_ESC)
		{
			RestoreScreen();
			break;
		}

		if (key != KEY_ENTER && key != KEY_F10)
			continue;

		switch (field)
		{
		case MAIN_CMUSIC:
			SetupMusic();
			break;

		case MAIN_CSFX:
			SetupFX();
			break;

		case MAIN_TYPE:
			ChooseController();
			break;

		case MAIN_CONFIG:
			ConfigControl();
			break;

		case MAIN_SAVE:
			INI_PutPreferenceLong("Setup", "Detail", (long)1);

			if (savemusic)
			{
				INI_PutPreferenceLong("Music", "Volume", (long)85);
				INI_PutPreferenceLong("Music", "CardType", (long)newc.m.card);
				INI_PutPreferenceHex("Music", "BasePort", (long)newc.m.port);
				INI_PutPreferenceHex("Music", "MidiPort", (long)newc.m.midiport);
				INI_PutPreferenceLong("Music", "Irq", (long)newc.m.irq);
				INI_PutPreferenceLong("Music", "Dma", (long)newc.m.dma);
			}
			
			if (savefx)
			{
				INI_PutPreferenceLong("SoundFX", "Volume", (long)85);
				INI_PutPreferenceLong("SoundFX", "CardType", (long)newc.d.card);
				INI_PutPreferenceHex("SoundFX", "BasePort", (long)newc.d.port);
				INI_PutPreferenceHex("SoundFX", "MidiPort", (long)newc.d.midiport);
				INI_PutPreferenceLong("SoundFX", "Irq", (long)newc.d.irq);
				INI_PutPreferenceLong("SoundFX", "Dma", (long)newc.d.dma);
				INI_PutPreferenceLong("SoundFX", "Channels", (long)newc.numdig);
			}
			
			INI_PutPreferenceLong("Setup", "Control", (long)newc.control);
			INI_PutPreferenceLong("Keyboard", "MoveUp", (long)curk.up);
			INI_PutPreferenceLong("Keyboard", "MoveDn", (long)curk.down);
			INI_PutPreferenceLong("Keyboard", "MoveLeft", (long)curk.left);
			INI_PutPreferenceLong("Keyboard", "MoveRight", (long)curk.right);
			INI_PutPreferenceLong("Keyboard", "Fire", (long)curk.fire);
			INI_PutPreferenceLong("Keyboard", "FireSp", (long)curk.use);
			INI_PutPreferenceLong("Keyboard", "ChangeSp", (long)curk.key1);
			INI_PutPreferenceLong("Keyboard", "MegaFire", (long)curk.key2);
			INI_PutPreferenceLong("Mouse", "Fire", (long)curk.mouse[0]);
			INI_PutPreferenceLong("Mouse", "FireSp", (long)curk.mouse[1]);
			INI_PutPreferenceLong("Mouse", "ChangeSp", (long)curk.mouse[2]);
			INI_PutPreferenceLong("JoyStick", "Fire", (long)curk.joy[0]);
			INI_PutPreferenceLong("JoyStick", "FireSp", (long)curk.joy[1]);
			INI_PutPreferenceLong("JoyStick", "ChangeSp", (long)curk.joy[2]);
			INI_PutPreferenceLong("JoyStick", "MegaFire", (long)curk.joy[3]);

			textbackground(0);
			textcolor(7);
			clrscr();

			goto func_exit;

		default:
			break;
		}
	}

func_exit:

	textbackground(0);
	textcolor(7);
	clrscr();
	_setcursortype(_NORMALCURSOR);

	return;
}
