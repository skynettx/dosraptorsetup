//
// Choose which type of controller to use
//
#include "main.h"

enum
{
	CON_KEY,
	CON_MOUSE,
	CON_JOY,
	CON_MAX
};
item_t controlitems[] =
{
	{CON_KEY, 26, 11, 28, -1, -1},
	{CON_MOUSE, 26, 12, 28, -1, -1},
	{CON_JOY, 26, 13, 28, -1, -1} };
menu_t controlmenu =
{
	&controlitems[0],
	CON_MOUSE,
	CON_MAX,
	0x7f };

int ChooseController(void)
{
	short key;
	short field;
	int rval = 0;

	SaveScreen();
	DrawPup(&control);

	// DEFAULT FIELD ========================================

	if (newc.control == C_MOUSE)
		field = CON_MOUSE;
	else if (newc.control == C_JOY)
		field = CON_JOY;
	else
		field = CON_KEY;

	//controlmenu.startitem = field;
	controlmenu.startitem = CON_KEY;

	ResetHelpLabel();
	hlfcontrol = 1;

	while (1)
	{
		SetupMenu(&controlmenu);
		field = GetMenuInput();
		key = menukey;
		switch (key)
		{
		case KEY_ESC:
			rval = -1;
			ResetHelpLabel();
			hlfmain = 1;
			goto func_exit;

		case KEY_ENTER:
		case KEY_F10:
			ResetHelpLabel();
			hlfmain = 1;
			switch (field)
			{
			case CON_KEY:
				newc.control = C_KEY;
				goto func_exit;

			case CON_MOUSE:
				newc.control = C_MOUSE;
				goto func_exit;

			case CON_JOY:
				newc.control = C_JOY;
				goto func_exit;

			default:
				break;
			}
			break;
		}
	}

func_exit:

	RestoreScreen();
	DrawCurrentConfig(newc.control, -1, -1);
	return (rval);
}
