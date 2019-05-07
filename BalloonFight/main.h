#pragma once

constexpr auto SCREEN_SIZE_X = 512;
constexpr auto SCREEN_SIZE_Y = 480;

constexpr auto PLAYER_SIZE_X = 48;
constexpr auto PLAYER_SIZE_Y = 48;
constexpr auto PLAYER_LIFE_DEF = 2;

constexpr auto ENEMY_SIZE_X = 48;
constexpr auto ENEMY_SIZE_Y = 48;

// ---------- ��ʑJ�ڂ��Ǘ����閼�̂��`(GAME_MODE�^�Ƃ��Ċ��p)
typedef enum
{
	GAME_INIT,		// �ްъJ�n���̏�����
	GAME_TITLE,		// �ް����ُ���
	GAME_MAIN,		// �ް�Ҳݏ���
	GAME_OVER,		// �ްѵ��ް����
	GAME_CLEAR,		// �ްѸر����
	GAME_END		// �ްяI��
}GAME_MODE;

// ---------- �\���̂̐錾
typedef struct
{
	float x;
	float y;
}XY;

typedef struct
{
	XY pos;	// �ŏI�I�ȍ��W(�Փ˔����)
	XY tmp;	// �v�Z�p�̍��W(�Փ˔���O)
	XY mov;	// �ړ���
	int	LR;	// 1:�E�A-1:��
	int UD;
	int	counter;
	int air;	//��C����
	int	wing, walk;
	bool flag;
	int	life;	//�̗�
	int hitFlag;
}CHARA_DATA;

// ��۰��ٕϐ��Ƃ��Ă�extern�錾
extern GAME_MODE gameMode;	// ��ʑJ�ڗp
