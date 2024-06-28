#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

#include <stdint.h>

#define BATTLE_SCENE_ON  0
#define BATTLE_SCENE_OFF 1

#define BATTLE_STYLE_SHIFT 0
#define BATTLE_STYLE_SET   1

#define SOUND_MONO   0
#define SOUND_STEREO 1

#define TEXT_SPEED_SLOW 5
#define TEXT_SPEED_MID  3
#define TEXT_SPEED_FAST 1

#define FRAME_TYPE1 0
#define FRAME_TYPE2 1
#define FRAME_TYPE3 2
#define FRAME_TYPE4 3
#define FRAME_TYPE5 4
#define FRAME_TYPE6 5
#define FRAME_TYPE7 6
#define FRAME_TYPE8 7

#define PRINT_DARKEST  0x7f
#define PRINT_DARKER   0x60
#define PRINT_NORMAL   0x40
#define PRINT_LIGHTER  0x20
#define PRINT_LIGHTEST 0x0

#define MENU_ACCOUNT_ON  1
#define MENU_ACCOUNT_OFF 0

typedef struct gameOptions {
	struct {
		uint8_t battleScene : 1;
		uint8_t battleStyle : 1;
		uint8_t sound       : 1;
		uint8_t zero        : 2;
		uint8_t textSpeed   : 3;
	};
	uint8_t unk01;
	uint8_t frame;
	uint8_t unk03;
	uint8_t print;
	uint8_t menuAccount;
	uint8_t unk06;
	uint8_t unk07;
} gameOptions_t;

#endif