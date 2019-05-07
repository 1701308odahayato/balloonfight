
#include "DxLib.h"
#include "main.h"
#include "keyCheck.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "hitCheck.h"

GAME_MODE gameMode;	// �ް�Ӱ�ސ錾

int titleImage;
// �֐��������ߐ錾(��ʑJ�ڗp�̕ϐ��錾)
void GameSystemInit();
void GameInit();
void GameTitle();
void GameMain();
void GameOver();
void GameClear();

// ---------- Ҳݏ���
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);	// ����޳Ӱ��
	SetWindowText("1701308_���c���l");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	if (DxLib_Init() == -1) return -1;	// �������Ɨ���ʉ�
	SetDrawScreen(DX_SCREEN_BACK);

	GameSystemInit();
	gameMode = GAME_INIT;	// �ŏ��̏��������s��

	// ---------- Ҳ�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClsDrawScreen();

		CheckKey();		// ����Ԃ���������(����ٰ��)

		switch (gameMode)
		{
		case GAME_INIT:		// �ްя�����(�摜�̓ǂݍ��݂Ȃ�)
			GameInit();
			break;
		case GAME_TITLE:	// ���ى��
			GameTitle();
			break;
		case GAME_MAIN:		// �ް�Ҳ݉��
			GameMain();
			break;
		case GAME_OVER:		// �ްѵ��ް���
			GameOver();
			break;
		case GAME_CLEAR:	// �ްѸر���
			GameClear();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();	// DxLib�̌�n��
	return 0;	// ��Ă̏I��
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

// ========== ���ى�ʂ̏���
void GameTitle()
{
	LoadGraphScreen(10, 100, "image/title3.png", true);		//�^�C�g���摜
	DrawFormatString(100, 350, 0xffffff, "Z�{�^������������Q�[���X�^�[�g�B");
	DrawFormatString(100, 400, 0xffffff, "X�{�^������������Q�[���I���B");
	if (trgKey[_1A]) {
		gameMode = GAME_MAIN;
	}
	if (trgKey[_1B]) {
		gameMode = GAME_END;
	}
}

// ========== �ް�Ҳݏ���
void GameMain()
{
	PlayerMain();
	EnemyMain();
	MapDraw();
	PlayerDraw();
	EnemyDraw();
}

// ========== �ްѵ��ް����
void GameOver()
{
	//5DrawFormatString(100, 100, 0xffffff, "GAME OVER");
	DrawFormatString(100, 350, 0xffffff, "S�{�^������������^�C�g����ʂɁB");
	LoadGraphScreen(50, 100, "image/�I�[�o�[.png", true);
	if (trgKey[_1X]) {
		gameMode = GAME_INIT;	// ���ى�ʂ̑O�ɹްт̏�����
	}
}

// ========== �ްѸر����
void GameClear()
{
	DrawFormatString(100, 100, 0xffffff, "�Q�[���N���A");
	DrawFormatString(100, 350, 0xffffff, "S�{�^������������^�C�g����ʂɁB");
	LoadGraphScreen(50, 100, "image/�N���A.png", true);
	if (trgKey[_1X]) {
		gameMode = GAME_INIT;	// ���ى�ʂ̑O�ɹްт̏�����
	}
}

