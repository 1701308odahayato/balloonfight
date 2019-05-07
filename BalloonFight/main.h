#pragma once

constexpr auto SCREEN_SIZE_X = 512;
constexpr auto SCREEN_SIZE_Y = 480;

constexpr auto PLAYER_SIZE_X = 48;
constexpr auto PLAYER_SIZE_Y = 48;
constexpr auto PLAYER_LIFE_DEF = 2;

constexpr auto ENEMY_SIZE_X = 48;
constexpr auto ENEMY_SIZE_Y = 48;

// ---------- 画面遷移を管理する名称を定義(GAME_MODE型として活用)
typedef enum
{
	GAME_INIT,		// ｹﾞｰﾑ開始時の初期化
	GAME_TITLE,		// ｹﾞｰﾑﾀｲﾄﾙ処理
	GAME_MAIN,		// ｹﾞｰﾑﾒｲﾝ処理
	GAME_OVER,		// ｹﾞｰﾑｵｰﾊﾞｰ処理
	GAME_CLEAR,		// ｹﾞｰﾑｸﾘｱ処理
	GAME_END		// ｹﾞｰﾑ終了
}GAME_MODE;

// ---------- 構造体の宣言
typedef struct
{
	float x;
	float y;
}XY;

typedef struct
{
	XY pos;	// 最終的な座標(衝突判定後)
	XY tmp;	// 計算用の座標(衝突判定前)
	XY mov;	// 移動量
	int	LR;	// 1:右、-1:左
	int UD;
	int	counter;
	int air;	//空気入れ
	int	wing, walk;
	bool flag;
	int	life;	//体力
	int hitFlag;
}CHARA_DATA;

// ｸﾞﾛｰﾊﾞﾙ変数としてのextern宣言
extern GAME_MODE gameMode;	// 画面遷移用
