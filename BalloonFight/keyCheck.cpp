#include "DxLib.h"
#include "keyCheck.h"

int trgKey[KEY_MAX];	// ﾄﾘｶﾞｷｰ
int newKey[KEY_MAX];	// 今回ﾙｰﾌﾟ時の入力状態
int oldKey[KEY_MAX];	// 前回ﾙｰﾌﾟ時の入力状態
int upKey[KEY_MAX];		// ｷｰｱｯﾌﾟしたｷｰのﾁｪｯｸ

void CheckKey()
{
	struct {
		int kinput;	// ｷｰﾎﾞｰﾄﾞ
		int jinput;	// ﾊﾟｯﾄﾞ
		KEY_CODE type;	// 自作ｷｰｺｰﾄﾞ
	}keyTypes[] = {
		// ｷｰﾎﾞｰﾄﾞ,　　　　 ﾊﾟｯﾄﾞ,　　　　　ｷｰﾁｪｯｸ名
		{ KEY_INPUT_UP,		PAD_INPUT_UP,		_1UP },	//ジャンプ
		{ KEY_INPUT_DOWN,	PAD_INPUT_DOWN,		_1DOWN },	//下がる
		{ KEY_INPUT_RIGHT,	PAD_INPUT_RIGHT,	_1RIGHT },	//右
		{ KEY_INPUT_LEFT,	PAD_INPUT_LEFT,		_1LEFT },	//左
		{ KEY_INPUT_X,		PAD_INPUT_B,		_1B },	//ゲーム終了
		{ KEY_INPUT_Z,		PAD_INPUT_A,		_1A },	//ゲームスタート
		{ KEY_INPUT_S,		PAD_INPUT_C,		_1X },
		{ KEY_INPUT_A,		PAD_INPUT_X,		_1Y },
		{ KEY_INPUT_Q,		PAD_INPUT_Y,		_1L },
		{ KEY_INPUT_W,		PAD_INPUT_Z,		_1R },
		{ KEY_INPUT_V,		PAD_INPUT_L,		_1SELECT },
		{ KEY_INPUT_SPACE,	PAD_INPUT_R,		_1START }, // 12
	};

	// 前回ｷｰ入力作成&ｸﾘｱ
	for (int i = 0; i < KEY_MAX; i++) {
		oldKey[i] = newKey[i];	// 前回ﾌﾚｰﾑ入力作成
		newKey[i] = 0; // 今回入力ｸﾘｱ
	}

	// ｼﾞｮｲﾊﾟｯﾄﾞ入力出来るかﾁｪｯｸ
	int padNum = GetJoypadNum();
	int key[2];
	key[0] = GetJoypadInputState(DX_INPUT_PAD1);
	key[1] = GetJoypadInputState(DX_INPUT_PAD2);

	if (padNum == 0) {
		key[0] = 0;
		key[1] = 0;
	}	// ﾊﾟｯﾄﾞがなかった場合の処理
	if (padNum == 1) {
		key[1] = 0;
	}

	// ｷｰﾁｪｯｸ
	for (int i = 0; i < KEY_MAX; i++) {
		if ((CheckHitKey(keyTypes[i].kinput))
			|| (key[i / 12] & keyTypes[i].jinput)
			) {
			newKey[keyTypes[i].type] |= 1;	// ｷｰかﾊﾟｯﾄﾞのどちらかが入力されていたらﾌﾗｸﾞを1に・・
		}
		trgKey[keyTypes[i].type] = ~oldKey[keyTypes[i].type] & newKey[keyTypes[i].type];	// ﾄﾘｶﾞ
		upKey[keyTypes[i].type] = oldKey[keyTypes[i].type] & ~newKey[keyTypes[i].type];		// ｱｯﾌﾟｷｰ
	}

	// ①普通の入力			-> newKey[ｷｰｺｰﾄﾞ]で入力ﾁｪｯｸ
	// ②ﾄﾘｶﾞ入力			-> trgKey[ｷｰｺｰﾄﾞ]で入力ﾁｪｯｸ
	// ③ｷｰｱｯﾌﾟしたｷｰﾁｪｯｸ	-> upKey[ｷｰｺｰﾄﾞ]で入力ﾁｪｯｸ
}