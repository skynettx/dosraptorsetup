//
// Configure controllers
//
#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "main.h"

void Pos(item_t* item)
{
	gotoxy(item->x + 1, item->y + 1);
}

void Clear(item_t* item)
{
	int i;

	Pos(item);
	for (i = 0; i < item->w; i++)
		cprintf(" ");
	gotoxy(1, 25);
}

//
//	Get keyboard scan code
//
int GetScanCode(void)
{
	volatile unsigned short rval;

	while (kbhit())
		getch();

	SaveScreen();
	DrawPup(&askpres);

	DrawHelpLabel(0, " ");
	DrawHelpLabel(1, " ");
	DrawHelpLabel(2, " ");
	DrawHelpLabel(3, " ");
	DrawHelpLabel(4, " ");
	DrawHelpLabel(5, " ");
	DrawHelpLabel(6, " ");

	while (1)
	{
		rval = _bios_keybrd(_KEYBRD_SHIFTSTATUS);

		if (rval & 0x0004)
		{
			rval = SC_CTRL;
			break;
		}
		else if (rval & 0x0008)
		{
			rval = SC_ALT;
			break;
		}
		else if ((rval & 0x0001) || (rval & 0x0002))
		{
			rval = SC_RIGHT_SHIFT;
			break;
		}
		else
		{
			rval = _bios_keybrd(_KEYBRD_READY);
			rval = rval >> 8;

			if (rval == SC_ENTER)
				rval = 0;

			if (rval == SC_BACKSPACE)
				rval = 0;

			if (rval)
				break;
		}
	}

	RestoreScreen();
	while (kbhit())
		getch();

	return (rval);
}

enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FIRE,
	CHSPECIAL,
	MEGABOMB,
	MAXKEYS
};
item_t idkeyselitems[] =
{
	{UP, 42, 7, 9, -1, -1},
	{DOWN, 42, 8, 9, -1, -1},
	{LEFT, 42, 9, 9, -1, -1},
	{RIGHT, 42, 10, 9, -1, -1},

	{FIRE, 42, 14, 9, -1, -1},
	{CHSPECIAL, 42, 15, 9, -1, -1},
	{MEGABOMB, 42, 16, 9, -1, -1},
};
menu_t idkeyselmenu =
{
	&idkeyselitems[0],
	UP,
	MAXKEYS,
	0x7f };

void IDConfigKeyboard(void)
{
	short field;
	short key;
	CONTS turk;
	int rval;

	SaveScreen();
	DrawPup(&idkeysel);

	turk = curk;

	textbackground(1);
	textcolor(11);

	Clear(&idkeyselitems[UP]);
	Pos(&idkeyselitems[UP]);
	//cprintf("%s", keydesc[turk.up]);
	cprintf("UP");
	Clear(&idkeyselitems[DOWN]);
	Pos(&idkeyselitems[DOWN]);
	//cprintf("%s", keydesc[turk.down]);
	cprintf("DOWN");
	Clear(&idkeyselitems[LEFT]);
	Pos(&idkeyselitems[LEFT]);
	//cprintf("%s", keydesc[turk.left]);
	cprintf("LEFT");
	Clear(&idkeyselitems[RIGHT]);
	Pos(&idkeyselitems[RIGHT]);
	//cprintf("%s", keydesc[turk.right]);
	cprintf("RIGHT");
	Clear(&idkeyselitems[FIRE]);
	Pos(&idkeyselitems[FIRE]);
	//cprintf("%s", keydesc[turk.fire]);
	cprintf("CTRL");
	Clear(&idkeyselitems[CHSPECIAL]);
	Pos(&idkeyselitems[CHSPECIAL]);
	//cprintf("%s", keydesc[turk.use]);
	cprintf("ALT");
	Clear(&idkeyselitems[MEGABOMB]);
	Pos(&idkeyselitems[MEGABOMB]);
	//cprintf("%s", keydesc[turk.key1]);
	cprintf("SPACE");

	gotoxy(1, 25);

	ResetHelpLabel();
	hlfkeyconfig = 1;

	idkeyselmenu.startitem = UP;

	while (1)
	{
		SetupMenu(&idkeyselmenu);
		field = GetMenuInput();
		key = menukey;

		switch (key)
		{
		case KEY_ESC:
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_F10:
			curk = turk;
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_ENTER:
			switch (field)
			{
			case UP:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.up = rval;
					Clear(&idkeyselitems[UP]);
					Pos(&idkeyselitems[UP]);
					cprintf("%s", keydesc[turk.up]);
				}
				break;

			case DOWN:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.down = rval;
					Clear(&idkeyselitems[DOWN]);
					Pos(&idkeyselitems[DOWN]);
					cprintf("%s", keydesc[turk.down]);
				}
				break;

			case LEFT:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.left = rval;
					Clear(&idkeyselitems[LEFT]);
					Pos(&idkeyselitems[LEFT]);
					cprintf("%s", keydesc[turk.left]);
				}
				break;

			case RIGHT:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.right = rval;
					Clear(&idkeyselitems[RIGHT]);
					Pos(&idkeyselitems[RIGHT]);
					cprintf("%s", keydesc[turk.right]);
				}
				break;

			case FIRE:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.fire = rval;
					Clear(&idkeyselitems[FIRE]);
					Pos(&idkeyselitems[FIRE]);
					cprintf("%s", keydesc[turk.fire]);
				}
				break;

			case CHSPECIAL:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.use = rval;
					Clear(&idkeyselitems[CHSPECIAL]);
					Pos(&idkeyselitems[CHSPECIAL]);
					cprintf("%s", keydesc[turk.use]);
				}
				break;

			case MEGABOMB:
				rval = GetScanCode();
				if (rval)
				{
					textbackground(1);
					textcolor(11);
					turk.key2 = rval;
					Clear(&idkeyselitems[MEGABOMB]);
					Pos(&idkeyselitems[MEGABOMB]);
					cprintf("%s", keydesc[turk.key2]);
				}
				break;
			}
			gotoxy(1, 25);
			break;
		}
	}

func_exit:

	RestoreScreen();
	return;
}

//
//	Configure joystick buttons
//
enum
{
	J_FIRE,
	J_CHSPECIAL,
	J_MEGA,
	J_MAX
};
item_t idjoyselitems[] =
{
	{J_FIRE, 42, 11, 9, -1, -1},
	{J_CHSPECIAL, 42, 12, 9, -1, -1},
	{J_MEGA, 42, 13, 9, -1, -1} };
menu_t idjoyselmenu =
{
	&idjoyselitems[0],
	J_FIRE,
	J_MAX,
	0x7f };

//
//	Get joystick button
//
int GetJoyButton(void)
{
	int rval = -1;
	int num;
	//int catchkey;

	SaveScreen();
	DrawPup(&mousentr);

	DrawHelpLabel(0, " ");
	DrawHelpLabel(1, " ");
	DrawHelpLabel(2, " ");

	while (kbhit())
		getch();

	while (1)
	{
		num = inp(0x201);

		num = num >> 4;

		if (!(num & 1))
		{
			rval = 0;
			break;
		}
		if (!(num & 2))
		{
			rval = 1;
			break;
		}
		if (!(num & 4))
		{
			rval = 2;
			break;
		}
		if (!(num & 8))
		{
			rval = 3;
			break;
		}

		/*if (kbhit())
		{
			catchkey = _bios_keybrd(_KEYBRD_READY) >> 8;
			if (catchkey == SC_ESC)
				break;

			getch();
		}*/
		if ((_bios_keybrd(_KEYBRD_READY) >> 8) == SC_ESC)
			break;

	}

	RestoreScreen();
	while (kbhit())
		getch();

	return (rval);
}

void IDConfigJoy(void)
{
	short key;
	short field;
	int	rval;
	CONTS turk;
	char joybuts[4][20] =
	{
		"BUTTON 1",
		"BUTTON 2",
		"BUTTON 3",
		"BUTTON 4"
	};
	int	fire;
	int	mega;
	int	chspecial;


	SaveScreen();
	DrawPup(&idjoysel);

	turk = curk;

	fire = turk.joy[ID_FIRE];
	mega = turk.joy[ID_MEGA];
	chspecial = turk.joy[ID_CHSPECIAL];

	textbackground(1);
	textcolor(11);
	Clear(&idjoyselitems[J_FIRE]);
	Pos(&idjoyselitems[J_FIRE]);
	if (fire >= 0)
		cprintf("%s", joybuts[fire]);

	Clear(&idjoyselitems[J_CHSPECIAL]);
	Pos(&idjoyselitems[J_CHSPECIAL]);
	if (mega >= 0)
		cprintf("%s", joybuts[mega]);

	Clear(&idjoyselitems[J_MEGA]);
	Pos(&idjoyselitems[J_MEGA]);
	if (chspecial >= 0)
		cprintf("%s", joybuts[chspecial]);

	gotoxy(1, 25);

	ResetHelpLabel();
	hlfjoyconfig = 1;

	idjoyselmenu.startitem = J_FIRE;

	while (1)
	{
		SetupMenu(&idjoyselmenu);
		field = GetMenuInput();
		key = menukey;
		switch (key)
		{
		case KEY_ESC:
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_F10:
			curk = turk;
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_ENTER:
			switch (field)
			{
			case J_FIRE:
				rval = GetJoyButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.joy[ID_FIRE] = rval;
					Clear(&idjoyselitems[J_FIRE]);
					Pos(&idjoyselitems[J_FIRE]);
					cprintf("%s", joybuts[rval]);

					if (turk.joy[ID_MEGA] == rval)
					{
						turk.joy[ID_MEGA] = -1;
						Clear(&idjoyselitems[J_CHSPECIAL]);
					}
					if (turk.joy[ID_CHSPECIAL] == rval)
					{
						turk.joy[ID_CHSPECIAL] = -1;
						Clear(&idjoyselitems[J_MEGA]);
					}
				}
				break;

			case J_CHSPECIAL:
				rval = GetJoyButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.joy[ID_MEGA] = rval;
					Clear(&idjoyselitems[J_CHSPECIAL]);
					Pos(&idjoyselitems[J_CHSPECIAL]);
					cprintf("%s", joybuts[rval]);

					if (turk.joy[ID_FIRE] == rval)
					{
						turk.joy[ID_FIRE] = -1;
						Clear(&idjoyselitems[J_FIRE]);
					}
					if (turk.joy[ID_CHSPECIAL] == rval)
					{
						turk.joy[ID_CHSPECIAL] = -1;
						Clear(&idjoyselitems[J_MEGA]);
					}
				}
				break;

			case J_MEGA:
				rval = GetJoyButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.joy[ID_CHSPECIAL] = rval;
					Clear(&idjoyselitems[J_MEGA]);
					Pos(&idjoyselitems[J_MEGA]);
					cprintf("%s", joybuts[rval]);

					if (turk.joy[ID_MEGA] == rval)
					{
						turk.joy[ID_MEGA] = -1;
						Clear(&idjoyselitems[J_CHSPECIAL]);
					}
					if (turk.joy[ID_FIRE] == rval)
					{
						turk.joy[ID_FIRE] = -1;
						Clear(&idjoyselitems[J_FIRE]);
					}
				}
				break;
			}
			gotoxy(1, 25);
			break;
		}
	}

func_exit:

	RestoreScreen();
	return;
}

//
// Configure mouse buttons
//
enum
{
	M_FIRE,
	M_CHWEAPON,
	M_MEGABOMB,
	M_MAX
};
item_t idmouselitems[] =
{
	{M_FIRE, 41, 9, 14, -1, -1},
	{M_CHWEAPON, 41, 10, 14, -1, -1},
	{M_MEGABOMB, 41, 11, 14, -1, -1} };
menu_t idmouselmenu =
{
	&idmouselitems[0],
	M_FIRE,
	M_MAX,
	0x7f };

//
//	Get mouse button
//
int GetMouseButton(void)
{
	int rval = -1;
	union REGS r;
	//int catchkey;

	SaveScreen();
	DrawPup(&mousentr);

	DrawHelpLabel(0, " ");
	DrawHelpLabel(1, " ");
	DrawHelpLabel(2, " ");

	while (1)
	{
		r.x.ax = 3;
		int86(0x33, &r, &r);

		if (r.x.bx & 1)
			rval = 0;
		else if (r.x.bx & 2)
			rval = 1;
		else if (r.x.bx & 4)
			rval = 2;

		if (rval != -1)
			break;

		/*if (kbhit())
		{
			catchkey = _bios_keybrd(_KEYBRD_READY) >> 8;
			if (catchkey == SC_ESC)
				break;

			getch();
		}*/

		if ((_bios_keybrd(_KEYBRD_READY) >> 8) == SC_ESC)
			break;
	}

	RestoreScreen();
	while (kbhit())
		getch();

	return (rval);
}

void IDConfigMouse(void)
{
	short key;
	short field;
	int rval;
	CONTS turk;
	char mousebuts[3][20] = {
		"LEFT BUTTON",
		"RIGHT BUTTON",
		"MID BUTTON" };
	int fire;
	int mega;
	int chspecial;

	SaveScreen();
	DrawPup(&idmousel);
	turk = curk;

	fire = turk.mouse[ID_FIRE];
	mega = turk.mouse[ID_MEGA];
	chspecial = turk.mouse[ID_CHSPECIAL];

	textbackground(1);
	textcolor(11);
	Clear(&idmouselitems[M_FIRE]);
	Pos(&idmouselitems[M_FIRE]);
	if (fire >= 0)
		cprintf("%s", mousebuts[fire]);

	Clear(&idmouselitems[M_CHWEAPON]);
	Pos(&idmouselitems[M_CHWEAPON]);
	if (mega >= 0)
		cprintf("%s", mousebuts[mega]);

	Clear(&idmouselitems[M_MEGABOMB]);
	Pos(&idmouselitems[M_MEGABOMB]);
	if (chspecial >= 0)
		cprintf("%s", mousebuts[chspecial]);
	gotoxy(1, 25);

	ResetHelpLabel();
	hlfmouconfig = 1;

	idmouselmenu.startitem = M_FIRE;

	while (1)
	{
		SetupMenu(&idmouselmenu);
		field = GetMenuInput();
		key = menukey;
		switch (key)
		{
		case KEY_ESC:
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_F10:
			curk = turk;
			ResetHelpLabel();
			hlfconconfig = 1;
			goto func_exit;

		case KEY_ENTER:
			switch (field)
			{
			case M_FIRE:
				rval = GetMouseButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.mouse[ID_FIRE] = rval;
					Clear(&idmouselitems[M_FIRE]);
					Pos(&idmouselitems[M_FIRE]);
					cprintf("%s", mousebuts[rval]);
					if (turk.mouse[ID_CHSPECIAL] == rval)
					{
						turk.mouse[ID_CHSPECIAL] = -1;
						Clear(&idmouselitems[M_MEGABOMB]);
					}
					if (turk.mouse[ID_MEGA] == rval)
					{
						turk.mouse[ID_MEGA] = -1;
						Clear(&idmouselitems[M_CHWEAPON]);
					}
				}
				break;

			case M_CHWEAPON:
				rval = GetMouseButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.mouse[ID_MEGA] = rval;
					Clear(&idmouselitems[M_CHWEAPON]);
					Pos(&idmouselitems[M_CHWEAPON]);
					cprintf("%s", mousebuts[rval]);

					if (turk.mouse[ID_CHSPECIAL] == rval)
					{
						turk.mouse[ID_CHSPECIAL] = -1;
						Clear(&idmouselitems[M_MEGABOMB]);
					}
					if (turk.mouse[ID_FIRE] == rval)
					{
						turk.mouse[ID_FIRE] = -1;
						Clear(&idmouselitems[M_FIRE]);
					}
				}
				break;

			case M_MEGABOMB:
				rval = GetMouseButton();
				textbackground(1);
				textcolor(11);
				if (rval != -1)
				{
					turk.mouse[ID_CHSPECIAL] = rval;
					Clear(&idmouselitems[M_MEGABOMB]);
					Pos(&idmouselitems[M_MEGABOMB]);
					cprintf("%s", mousebuts[rval]);

					if (turk.mouse[ID_MEGA] == rval)
					{
						turk.mouse[ID_MEGA] = -1;
						Clear(&idmouselitems[M_CHWEAPON]);
					}
					if (turk.mouse[ID_FIRE] == rval)
					{
						turk.mouse[ID_FIRE] = -1;
						Clear(&idmouselitems[M_FIRE]);
					}
				}
				break;
			}
			gotoxy(1, 25);
			break;
		}
	}

func_exit:

	RestoreScreen();
	return;
}

//
// Choose which controller to configure!
//
enum
{
	CFG_KEY,
	CFG_MOUSE,
	CFG_JOY,
	CFG_MAX
};
item_t conselitems[] =
{
	{CFG_KEY, 26, 11, 27, -1, -1},
	{CFG_MOUSE, 26, 12, 27, -1, -1},
	{CFG_JOY, 26, 13, 27, -1, -1}
};
menu_t conselmenu =
{
	&conselitems[0],
	CFG_KEY,
	CFG_MAX,
	0x7f };

void ConfigControl(void)
{
	short key;
	short field;

	SaveScreen();
	DrawPup(&consel);

	ResetHelpLabel();
	hlfconconfig = 1;

	conselmenu.startitem = CFG_KEY;

	while (1)
	{
		SetupMenu(&conselmenu);
		field = GetMenuInput();
		key = menukey;

		if (key == KEY_ESC)
		{
			ResetHelpLabel();
			hlfmain = 1;
			break;
		}

		if (key != KEY_ENTER && key != KEY_F10)
			continue;

		switch (field)
		{
		default:
		case CFG_KEY:
			IDConfigKeyboard();
			break;

		case CFG_MOUSE:
			if (!mousepresent)
			{
				MouseError(&mouspres);
				break;
			}
			IDConfigMouse();
			break;

		case CFG_JOY:
			IDConfigJoy();
			break;
		}
	}

func_exit:

	RestoreScreen();
	return;
}
