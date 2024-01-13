#include <stdio.h>
#include <conio.h>
#include <mem.h>
#include <dos.h>

#include "main.h"

item_t* current;
menu_t* currentmenu;
int curitem;	  // current item #
char inv_attrib;  // inversion attribute
char buffer[160]; // save the entire screen line!
short menukey;	  // globally set after GetMenuInput()
int hlfmain = 0, hlfmusic = 0, hlfmusicmidiport = 0, hlfsbport = 0;
int hlfsound = 0, hlfsbirq = 0, hlfsbdma = 0, hlfnumdig = 0;
int hlfcontrol = 0, hlfconconfig = 0, hlfkeyconfig = 0, hlfmouconfig = 0;
int hlfjoyconfig = 0;

//
// Make a sound!
//
void Sound(int freq, int dly)
{
	sound(freq);
	delay(dly);
	nosound();
}

//
//	Draw a dot if "value" is > 0 at item->x - 3
//
void SetMark(item_t* item, int value)
{
	char far* screen;

	screen = MK_FP(0xb800, item->y * 160 + (item->x - 3) * 2);
	*screen = ' ';
	if (value)
		*screen = 7;
}

//
// Invert the menu item
//
void Invert(item_t* item)
{
	char far* screen;
	int i;

	movedata(0xb800, item->y * 160, FP_SEG(&buffer), FP_OFF(&buffer), 160);
	screen = MK_FP(0xb800, item->y * 160 + item->x * 2);

	for (i = 0; i < item->w; i++)
	{
		*(screen + 1) = 0x70;
		screen += 2;
	}

	SetHelpLabel();
}

//
//	Restore the screen line (uninvert)
//
void UnInvert(item_t* item)
{
	movedata(FP_SEG(&buffer), FP_OFF(&buffer), 0xb800, item->y * 160, 160);
}

//
//	Set "current" to first menu item
//
void SetupMenu(menu_t* menu)
{
	currentmenu = menu;
	current = menu->items;
	current += menu->startitem;
	curitem = menu->startitem;

	inv_attrib = menu->invert;
	Invert(current);
}

//
//	Get menu input for current menu
// Exit:	-1 = ESC was pressed, xx = item id
//
int GetMenuInput(void)
{
	char c;
	while (1)
	{
		c = getch();
		//		gotoxy(1,2);
		//		printf("char:%x  ",c);
		switch (c)
		{
		case 0x48: // UP
			if (!curitem)
				break;
			UnInvert(current);
			if (current->up)
			{
				curitem = current->up;
				current = currentmenu->items + curitem;
			}
			else
			{
				curitem--;
				current--;
			}
			Invert(current);
			//Sound(50, 10);
			break;

		case 0x50: // DOWN
			if (curitem == currentmenu->maxitems - 1)
				break;
			UnInvert(current);
			if (current->down)
			{
				curitem = current->down;
				current = currentmenu->items + curitem;
			}
			else
			{
				curitem++;
				current++;
			}
			Invert(current);
			//Sound(50, 10);
			break;

		case 0x4b: // LEFT
			if (current->left != -1)
			{
				UnInvert(current);
				curitem = current->left;
				current = currentmenu->items + curitem;
				Invert(current);
				//Sound(50, 10);
			}
			break;

		case 0x4d: // RIGHT
			if (current->right != -1)
			{
				UnInvert(current);
				curitem = current->right;
				current = currentmenu->items + curitem;
				Invert(current);
				//Sound(50, 10);
			}
			break;

		case 0x44: // F10
		case 0x3b: // F1
		case 0x3c: // F2
			UnInvert(current);
			menukey = c;
			currentmenu->startitem = curitem;
			//Sound(50, 10);
			return current->id;

		case 0x0d: // ENTER
			UnInvert(current);
			menukey = c;
			currentmenu->startitem = curitem;
			//Sound(2000, 10);
			return current->id;

		case 0x1b: // ESC
			UnInvert(current);
			menukey = c;
			//Sound(3000, 10);
			return -1;
		}
	}
}

void ResetHelpLabel(void)
{
	hlfmain = 0;
	hlfmusic = 0;
	hlfmusicmidiport = 0;
	hlfsbport = 0;
	hlfsound = 0;
	hlfsbirq = 0;
	hlfsbdma = 0;
	hlfnumdig = 0;
	hlfcontrol = 0;
	hlfconconfig = 0;
	hlfkeyconfig = 0;
	hlfmouconfig = 0;
	hlfjoyconfig = 0;
}

void SetHelpLabel(void)
{
	if (hlfmain)
	{
		DrawHelpLabel(0, "  Select Sound Card that will play Music");
		DrawHelpLabel(1, "  Select Sound Card that will play Sound FX");
		DrawHelpLabel(2, "  Select Controller Type ( Mouse / Joystick / Keyboard )");
		DrawHelpLabel(3, "  Configure Keyboard / Mouse / Joystick Layout");
		DrawHelpLabel(4, "  Save Current Settings as Defaults");
	}

	if (hlfmusic)
	{
		DrawHelpLabel(0, " MPU-401 General MIDI");
		DrawHelpLabel(1, " Roland Sound Canvas");
		DrawHelpLabel(2, "  WaveBlaster");
		DrawHelpLabel(3, "  AWE 32 Sound Blaster");
		DrawHelpLabel(4, " Sound Blaster, Sound Blaster 16, Sound Blaster AWE32 and Sound Blaster Pro");
		DrawHelpLabel(5, "  Pro Audio Spectrum");
		DrawHelpLabel(6, " Gravis UltraSound");
		DrawHelpLabel(7, " Adlib and 100% compatibles");
		DrawHelpLabel(8, "  Do not use any Sound");
	}

	if (hlfmusicmidiport)
	{
		DrawHelpLabel(0, "  Sets Midi port to 220");
		DrawHelpLabel(1, "  Sets Midi port to 230");
		DrawHelpLabel(2, "  Sets Midi port to 240");
		DrawHelpLabel(3, "  Sets Midi port to 250");
		DrawHelpLabel(4, "  Sets Midi port to 300");
		DrawHelpLabel(5, "  Sets Midi port to 320");
		DrawHelpLabel(6, "  Sets Midi port to 330");
		DrawHelpLabel(7, "  Sets Midi port to 332");
		DrawHelpLabel(8, "  Sets Midi port to 334");
		DrawHelpLabel(9, "  Sets Midi port to 336");
		DrawHelpLabel(10, "  Sets Midi port to 340");
		DrawHelpLabel(11, "  Sets Midi port to 360");
	}

	if (hlfsbport)
	{
		DrawHelpLabel(0, "  Sets PORT address to 210");
		DrawHelpLabel(1, "  Sets PORT address to 220");
		DrawHelpLabel(2, "  Sets PORT address to 230");
		DrawHelpLabel(3, "  Sets PORT address to 240");
		DrawHelpLabel(4, "  Sets PORT address to 250");
		DrawHelpLabel(5, "  Sets PORT address to 260");
		DrawHelpLabel(6, "  Sets PORT address to 280");
	}

	if (hlfsound)
	{
		DrawHelpLabel(0, "  Select for General Midi Sound FX - MPU-401 General Midi");
		DrawHelpLabel(1, "  Select for Roland Sound Canvas Sound FX ( Uses Built in FX on card )");
		DrawHelpLabel(2, "  Digital Sound FX - Sound Blaster, Pro, 16 and AWE32");
		DrawHelpLabel(3, "  Digital Sound FX - Pro Audio Spectrum");
		DrawHelpLabel(4, "  Gravis UltraSound Digital Sound FX");
		DrawHelpLabel(5, "  Sound FX ( Adlib and 100% compatibles )");
		DrawHelpLabel(6, "  PC speaker Sound FX");
		DrawHelpLabel(7, "  Select for No Sound FX");
	}

	if (hlfsbirq)
	{
		DrawHelpLabel(0, "  Sets IRQ to 2");
		DrawHelpLabel(1, "  Sets IRQ to 5");
		DrawHelpLabel(2, "  Sets IRQ to 7");
		DrawHelpLabel(3, "  Sets IRQ to 10");
	}

	if (hlfsbdma)
	{
		DrawHelpLabel(0, "  Sets DMA to 0");
		DrawHelpLabel(1, "  Sets DMA to 1");
		DrawHelpLabel(2, "  Sets DMA to 3");
		DrawHelpLabel(3, "  Sets DMA to 5");
		DrawHelpLabel(4, "  Sets DMA to 6");
		DrawHelpLabel(5, "  Sets DMA to 7");
	}

	if (hlfnumdig)
	{
		DrawHelpLabel(0, "  Will play one Digital sound effects at a time");
		DrawHelpLabel(1, "  Will play two Digital sound effects at a time");
		DrawHelpLabel(2, "  Will play Three Digital sound effects at a time");
		DrawHelpLabel(3, "  Will play four Digital sound effects at a time");
		DrawHelpLabel(4, "  Will play five Digital sound effects at a time");
		DrawHelpLabel(5, "  Will play six Digital sound effects at a time");
		DrawHelpLabel(6, "  Will play seven Digital sound effects at a time");
		DrawHelpLabel(7, "  Will play eight Digital sound effects at a time");
	}

	if (hlfcontrol)
	{
		DrawHelpLabel(0, "  Use Keyboard for All Controls");
		DrawHelpLabel(1, "  Use Mouse for Main control");
		DrawHelpLabel(2, "  Use Joystick for Main control");
	}

	if (hlfconconfig)
	{
		DrawHelpLabel(0, "  Setup New Keyboard Layout");
		DrawHelpLabel(1, "  Configure Mouse Button Layout");
		DrawHelpLabel(2, "  Configure Joystick Button Layout");
	}

	if (hlfkeyconfig)
	{
		DrawHelpLabel(0, " Move ship forward");
		DrawHelpLabel(1, " Move ship backwards");
		DrawHelpLabel(2, " Move ship to the left");
		DrawHelpLabel(3, " Move ship to the right");
		DrawHelpLabel(4, " Fire main weapons");
		DrawHelpLabel(5, " Fire special weapons the you pickup/buy");
		DrawHelpLabel(6, " Change to next avalable special weapon");
	}

	if (hlfmouconfig)
	{
		DrawHelpLabel(0, " Fire main weapons");
		DrawHelpLabel(1, " Change to next available Special weapon");
		DrawHelpLabel(2, " Launch a Mega Bomb");
	}

	if (hlfjoyconfig)
	{
		DrawHelpLabel(0, " Fire main weapons");
		DrawHelpLabel(1, " Change to next available Special weapon");
		DrawHelpLabel(2, " Fires a Mega Bomb");
	}
}

void DrawHelpLabel(int id, const char* label)
{
	if (id == current->id)
	{
		textcolor(8);
		textbackground(7);
		gotoxy(1, 25);
		cprintf("                                                                           ");
		gotoxy(1, 25);
		cprintf("%s", label);
		gotoxy(1, 25);
	}
}
