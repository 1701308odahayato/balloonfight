#pragma once

typedef enum
{
	_1UP,
	_1DOWN,
	_1RIGHT,
	_1LEFT,
	_1A,
	_1B,
	_1X,
	_1Y,
	_1L,
	_1R,
	_1SELECT,
	_1START,	// 12
	KEY_MAX
}KEY_CODE;

// ---------- •Ï”‚ÌéŒ¾
extern int trgKey[KEY_MAX];	// ÄØ¶Ş·°
extern int newKey[KEY_MAX];	// ¡‰ñÙ°Ìß‚Ì“ü—Íó‘Ô
extern int oldKey[KEY_MAX];	// ‘O‰ñÙ°Ìß‚Ì“ü—Íó‘Ô
extern int upKey[KEY_MAX];	// ·°±¯Ìß‚µ‚½·°‚ÌÁª¯¸



// ---------- ŠÖ”ÌßÛÄÀ²ÌßéŒ¾
void CheckKey();