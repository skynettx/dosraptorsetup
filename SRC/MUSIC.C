#include "main.h"
#include "keys.h"

//
// Choose MIDI port
//
enum
{
	MIDI_220,
	MIDI_230,
	MIDI_240,
	MIDI_250,
	MIDI_300,
	MIDI_320,
	MIDI_330,
	MIDI_332,
	MIDI_334,
	MIDI_336,
	MIDI_340,
	MIDI_360,
	MIDI_MAX
};

item_t midiportitems[] =
{
	{MIDI_220, 26, 6, 27, -1, -1},
	{MIDI_230, 26, 7, 27, -1, -1},
	{MIDI_240, 26, 8, 27, -1, -1},
	{MIDI_250, 26, 9, 27, -1, -1},
	{MIDI_300, 26, 10, 27, -1, -1},
	{MIDI_320, 26, 11, 27, -1, -1},
	{MIDI_330, 26, 12, 27, -1, -1},
	{MIDI_332, 26, 13, 27, -1, -1},
	{MIDI_334, 26, 14, 27, -1, -1},
	{MIDI_336, 26, 15, 27, -1, -1},
	{MIDI_340, 26, 16, 27, -1, -1},
	{MIDI_360, 26, 17, 27, -1, -1} };

menu_t midiportmenu =
{
	&midiportitems[0],
	MIDI_330,
	MIDI_MAX,
	0x7f };

int ChooseMidiPort(DMXCARD* card)
{
	short field;
	short key;
	int rval = 0;

	SaveScreen();
	DrawPup(&midiport);

	ResetHelpLabel();
	hlfmusicmidiport = 1;

	// DEFAULT FIELD ========================================

	switch (card->midiport)
	{
	default:
	case 0x220:
		field = MIDI_220;
		break;

	case 0x230:
		field = MIDI_230;
		break;

	case 0x240:
		field = MIDI_240;
		break;

	case 0x250:
		field = MIDI_250;
		break;

	case 0x300:
		field = MIDI_300;
		break;

	case 0x320:
		field = MIDI_320;
		break;

	case 0x330:
		field = MIDI_330;
		break;

	case 0x332:
		field = MIDI_332;
		break;

	case 0x334:
		field = MIDI_334;
		break;

	case 0x336:
		field = MIDI_336;
		break;

	case 0x340:
		field = MIDI_340;
		break;

	case 0x360:
		field = MIDI_360;
		break;
	}

	while (1)
	{
		SetupMenu(&midiportmenu);
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
			case MIDI_220:
				card->midiport = 0x220;
				goto func_exit;

			case MIDI_230:
				card->midiport = 0x230;
				goto func_exit;

			case MIDI_240:
				card->midiport = 0x240;
				goto func_exit;

			case MIDI_250:
				card->midiport = 0x250;
				goto func_exit;

			case MIDI_300:
				card->midiport = 0x300;
				goto func_exit;

			case MIDI_320:
				card->midiport = 0x320;
				goto func_exit;

			case MIDI_330:
				card->midiport = 0x330;
				goto func_exit;

			case MIDI_332:
				card->midiport = 0x332;
				goto func_exit;

			case MIDI_334:
				card->midiport = 0x334;
				goto func_exit;

			case MIDI_336:
				card->midiport = 0x336;
				goto func_exit;

			case MIDI_340:
				card->midiport = 0x340;
				goto func_exit;

			case MIDI_360:
				card->midiport = 0x360;
				goto func_exit;

			default:
				break;
			}
			break;
		}
	}

func_exit:

	RestoreScreen();
	return (rval);
}

//
// Menu for choosing Music Card
//
enum
{
	MCARD_GMIDI,
	MCARD_CANVAS,
	MCARD_WAVE,
	MCARD_AWE,
	MCARD_SB,
	MCARD_PAS,
	MCARD_GUS,
	MCARD_ADLIB,
	MCARD_NONE,
	MCARD_MAX
};

item_t mcarditems[] =
{
	{MCARD_GMIDI, 26, 8, 28, -1, -1},
	{MCARD_CANVAS, 26, 9, 28, -1, -1},
	{MCARD_WAVE, 26, 10, 28, -1, -1},
	{MCARD_AWE, 26, 11, 28, -1, -1},
	{MCARD_SB, 26, 12, 28, -1, -1},
	{MCARD_PAS, 26, 13, 28, -1, -1},
	{MCARD_GUS, 26, 14, 28, -1, -1},
	{MCARD_ADLIB, 26, 15, 28, -1, -1},
	{MCARD_NONE, 26, 16, 28, -1, -1} };

menu_t mcardmenu =
{
	&mcarditems[0],
	MCARD_NONE,
	MCARD_MAX,
	0x7f };

int ChooseMusicCard(void) // RETURN: 0 = OK, -1 == ABORT
{
	short key;
	short field;
	int rval = 0;

	switch (newc.m.card)
	{
	default:
	case M_NONE:
		field = MCARD_NONE;
		break;

	case M_ADLIB:
		field = MCARD_ADLIB;
		break;

	case M_GUS:
		field = MCARD_GUS;
		break;

	case M_PAS:
		field = MCARD_PAS;
		break;

	case M_SB:
		field = MCARD_SB;
		break;

	case M_WAVE:
		field = MCARD_WAVE;
		break;

	case M_AWE:
		field = MCARD_AWE;
		break;

	case M_GMIDI:
		field = MCARD_GMIDI;
		break;

	case M_CANVAS:
		field = MCARD_CANVAS;
		break;
	}

	mcardmenu.startitem = field;
	SaveScreen();
	DrawPup(&mcard);

	while (1)
	{
		SetupMenu(&mcardmenu);
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
			switch (field)
			{
			case MCARD_GMIDI:
				newc.m.card = M_GMIDI;
				newc.m.port = -1;
				newc.m.irq = -1;
				newc.m.dma = -1;
				goto func_exit;

			case MCARD_CANVAS:
				newc.m.card = M_CANVAS;
				newc.m.port = -1;
				newc.m.irq = -1;
				newc.m.dma = -1;
				goto func_exit;

			case MCARD_WAVE:
				newc.m.card = M_WAVE;
				newc.m.port = -1;
				newc.m.irq = -1;
				newc.m.dma = -1;
				goto func_exit;

			case MCARD_AWE:
				newc.m.card = M_AWE;
				goto func_exit;

			case MCARD_SB:
				newc.m.card = M_SB;
				goto func_exit;

			case MCARD_PAS:
				newc.m.card = M_PAS;
				goto func_exit;

			case MCARD_GUS:
				newc.m.card = M_GUS;
				newc.m.midiport = -1;
				goto func_exit;

			case MCARD_ADLIB:
				newc.m.card = M_ADLIB;
				newc.m.port = -1;
				newc.m.midiport = -1;
				newc.m.irq = -1;
				newc.m.dma = -1;
				goto func_exit;

			case MCARD_NONE:
				newc.m.card = M_NONE;
				newc.m.port = -1;
				newc.m.midiport = -1;
				newc.m.irq = -1;
				newc.m.dma = -1;
				goto func_exit;

			default:
				break;
			}
			break;
		}
	}

func_exit:

	ResetHelpLabel();
	hlfmain = 1;

	RestoreScreen();
	return (rval);
}

enum
{
	SB_PORT_210,
	SB_PORT_220,
	SB_PORT_230,
	SB_PORT_240,
	SB_PORT_250,
	SB_PORT_260,
	SB_PORT_280,
	SB_PORT_MAX
};

item_t sbportitemsm[] =
{
	{SB_PORT_210, 26, 9, 27, -1, -1},
	{SB_PORT_220, 26, 10, 27, -1, -1},
	{SB_PORT_230, 26, 11, 27, -1, -1},
	{SB_PORT_240, 26, 12, 27, -1, -1},
	{SB_PORT_250, 26, 13, 27, -1, -1},
	{SB_PORT_260, 26, 14, 27, -1, -1},
	{SB_PORT_280, 26, 15, 27, -1, -1}
};

menu_t sbportmenum =
{
	&sbportitemsm[0],
	SB_PORT_220,
	SB_PORT_MAX,
	0x7f };

int ChooseSBPort(DMXCARD* card)
{
	short field;
	short key;
	int rval = 0;

	SaveScreen();
	DrawPup(&sbport);

	ResetHelpLabel();
	hlfsbport = 1;

	// DEFAULT FIELD ========================================

	switch (card->port)
	{
	default:
	case 0x210:
		field = SB_PORT_210;
		break;

	case 0x220:
		field = SB_PORT_220;
		break;

	case 0x230:
		field = SB_PORT_230;
		break;

	case 0x240:
		field = SB_PORT_240;
		break;

	case 0x250:
		field = SB_PORT_250;
		break;

	case 0x260:
		field = SB_PORT_260;
		break;

	case 0x280:
		field = SB_PORT_280;
		break;
	}

	while (1)
	{
		SetupMenu(&sbportmenum);
		field = GetMenuInput();
		key = menukey;
		switch (key)
		{
		case KEY_ESC:
			ResetHelpLabel();
			hlfmain = 1;
			rval = -1;
			goto func_exit;

		case KEY_ENTER:
		case KEY_F10:
			ResetHelpLabel();
			hlfmain = 1;
			switch (field)
			{
			case SB_PORT_210:
				card->port = 0x210;
				goto func_exit;

			case SB_PORT_220:
				card->port = 0x220;
				goto func_exit;

			case SB_PORT_230:
				card->port = 0x230;
				goto func_exit;

			case SB_PORT_240:
				card->port = 0x240;
				goto func_exit;

			case SB_PORT_250:
				card->port = 0x250;
				goto func_exit;

			case SB_PORT_260:
				card->port = 0x260;
				goto func_exit;

			case SB_PORT_280:
				card->port = 0x280;
				goto func_exit;

			default:
				break;
			}
			break;
		}
	}

func_exit:

	RestoreScreen();
	return (rval);
}

//
// Choose Music Card menu
//
int SetupMusic(void)
{
	ResetHelpLabel();
	hlfmusic = 1;

	if (ChooseMusicCard() == -1)
		return (-1);

	DrawCurrentConfig(-1, newc.m.card, -1);

	switch (newc.m.card)
	{
	default:
		savemusic = FALSE;
		break;

	case M_NONE:
		savemusic = TRUE;
		break;

	case M_ADLIB:
		savemusic = TRUE;
		break;

	case M_PAS:
	case M_GUS:
		savemusic = TRUE;
		break;


	case M_SB:
		if (ChooseSBPort(&newc.m) == -1) return (-1);
		savemusic = TRUE;
		break;

	case M_AWE:
		if (ChooseMidiPort(&newc.m) == -1) return (-1);
		savemusic = TRUE;
		break;

	case M_WAVE:
		if (ChooseMidiPort(&newc.m) == -1) return (-1);
		savemusic = TRUE;
		break;

	case M_CANVAS:
		newc.m.midiport = 0x330;
		if (ChooseMidiPort(&newc.m) == -1) return (-1);
		savemusic = TRUE;
		break;

	case M_GMIDI:
		if (ChooseMidiPort(&newc.m) == -1) return (-1);
		savemusic = TRUE;
		break;
	}
	return 0;
}
