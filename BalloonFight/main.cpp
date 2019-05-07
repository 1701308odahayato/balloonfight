
#include "DxLib.h"
#include "main.h"
#include "keyCheck.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "hitCheck.h"

GAME_MODE gameMode;	// ｹﾞｰﾑﾓｰﾄﾞ宣言

int titleImage;
// 関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言(画面遷移用の変数宣言)
void GameSystemInit();
void GameInit();
void GameTitle();
void GameMain();
void GameOver();
void GameClear();

// ---------- ﾒｲﾝ処理
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);	// ｳｲﾝﾄﾞｳﾓｰﾄﾞ
	SetWindowText("1701308_小田隼斗");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	if (DxLib_Init() == -1) return -1;	// 初期化と裏画面化
	SetDrawScreen(DX_SCREEN_BACK);

	GameSystemInit();
	gameMode = GAME_INIT;	// 最初の初期化を行う

	// ---------- ﾒｲﾝﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClsDrawScreen();

		CheckKey();		// ｷｰ状態をﾁｪｯｸする(毎回ﾙｰﾌﾟ)

		switch (gameMode)
		{
		case GAME_INIT:		// ｹﾞｰﾑ初期化(画像の読み込みなど)
			GameInit();
			break;
		case GAME_TITLE:	// ﾀｲﾄﾙ画面
			GameTitle();
			break;
		case GAME_MAIN:		// ｹﾞｰﾑﾒｲﾝ画面
			GameMain();
			break;
		case GAME_OVER:		// ｹﾞｰﾑｵｰﾊﾞｰ画面
			GameOver();
			break;
		case GAME_CLEAR:	// ｹﾞｰﾑｸﾘｱ画面
			GameClear();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();	// DxLibの後始末
	return 0;	// ｿﾌﾄの終了
}

void GameSystemInit()
{
	MapSystemInit();
	PlayerSystemInit();
	EnemySystemInit();
	gameMode = GAME_INIT;
}

void GameInit()
{
	PlayerInit();
	EnemyInit();
	gameMode = GAME_TITLE;
}

// ========== ﾀｲﾄﾙ画面の処理
void GameTitle()
{
	LoadGraphScreen(10, 100, "image/title3.png", true);		//タイトル画像
	DrawFormatString(100, 350, 0xffffff, "Zボタンを押したらゲームスタート。");
	DrawFormatString(100, 400, 0xffffff, "Xボタンを押したらゲーム終了。");
	if (trgKey[_1A]) {
		gameMode = GAME_MAIN;
	}
	if (trgKey[_1B]) {
		gameMode = GAME_END;
	}
}

// ========== ｹﾞｰﾑﾒｲﾝ処理
void GameMain()
{
	PlayerMain();
	EnemyMain();
	MapDraw();
	PlayerDraw();
	EnemyDraw();
}

// ========== ｹﾞｰﾑｵｰﾊﾞｰ処理
void GameOver()
{
	//5DrawFormatString(100, 100, 0xffffff, "GAME OVER");
	DrawFormatString(100, 350, 0xffffff, "Sボタンを押したらタイトル画面に。");
	LoadGraphScreen(50, 100, "image/オーバー.png", true);
	if (trgKey[_1X]) {
		gameMode = GAME_INIT;	// ﾀｲﾄﾙ画面の前にｹﾞｰﾑの初期化
	}
}

// ========== ｹﾞｰﾑｸﾘｱ処理
void GameClear()
{
	DrawFormatString(100, 100, 0xffffff, "ゲームクリア");
	DrawFormatString(100, 350, 0xffffff, "Sボタンを押したらタイトル画面に。");
	LoadGraphScreen(50, 100, "image/クリア.png", true);
	if (trgKey[_1X]) {
		gameMode = GAME_INIT;	// ﾀｲﾄﾙ画面の前にｹﾞｰﾑの初期化
	}
}

