
#include "DxLib.h"
#include "KeyCheck.h"
#include "player.h"
#include "hitCheck.h"
#include "enemy.h"

int imgPlayer[2][14];
CHARA_DATA player;
int FlagCnt;

void PlayerSystemInit()
{
	int tmp = LoadGraph("image/playerImage.png");

	// 羽ばたき（風船1個)
	imgPlayer[0][0] = DerivationGraph(0, 0, 32, 48, tmp);	//1
	imgPlayer[0][1] = DerivationGraph(32, 0, 32, 48, tmp);	//2
	imgPlayer[0][2] = DerivationGraph(64, 0, 32, 48, tmp);	//3
	imgPlayer[0][3] = imgPlayer[0][1];	//4(2と同様)

	// 歩き（風船1個）
	imgPlayer[0][4] = DerivationGraph(96 + 32 * 0, 0, 32, 48, tmp);
	imgPlayer[0][5] = DerivationGraph(128 + 32 * 1, 0, 32, 48, tmp);
	imgPlayer[0][6] = DerivationGraph(160 + 32 * 2, 0, 32, 48, tmp);
	imgPlayer[0][7] = DerivationGraph(192 + 32 * 3, 0, 32, 48, tmp);
	imgPlayer[0][8] = DerivationGraph(224 + 32 * 4, 0, 32, 48, tmp);

	// 羽ばたき（風船2個）
	imgPlayer[1][0] = DerivationGraph(0, 48, 32, 48, tmp);
	imgPlayer[1][1] = DerivationGraph(32, 48, 32, 48, tmp);
	imgPlayer[1][2] = DerivationGraph(64, 48, 32, 48, tmp);
	imgPlayer[1][3] = imgPlayer[1][1];

	// 歩き（風船2個）
	imgPlayer[1][4] = DerivationGraph(96, 48, 32, 48, tmp);
	imgPlayer[1][5] = DerivationGraph(96 + 32, 48, 32, 48, tmp);
	imgPlayer[1][6] = DerivationGraph(128 + 32, 48, 32, 48, tmp);
	imgPlayer[1][7] = DerivationGraph(160 + 32, 48, 32, 48, tmp);
}

// --------------------
// ﾌﾟﾚｲﾔｰ初期化処理
// --------------------
void PlayerInit()
{
	player.counter = 0;
	player.pos.x = 3 * 16;
	player.pos.y = 376;
	player.LR = 1;
	player.life = 2;
	player.flag = true;
	player.hitFlag = 0;
}

// --------------------
// ﾒｲﾝ処理
// --------------------
void PlayerMain()
{

	// ----------- ｷｰ入力があった時
	if (newKey[_1UP]) {
		player.wing = 1;
		player.mov.y -= 0.1f;	// 上昇加速（とりあえず0.1ぐらい）
		if (player.mov.y < -2.0f) {
			player.mov.y = -2.0f;
		}
	}
	else {
		player.wing = 1;
		player.mov.y += 0.05f;	// 下降加速（とりあえず0.05ぐらい）
		if (player.mov.y > 1.5f) {
			player.mov.y = 1.5f;
		}
	}
	// 最終的な座標
	player.tmp.y = player.pos.y + player.mov.y;

	player.walk = 0;		// 歩いていないことにする
	if (newKey[_1RIGHT]) {
		player.mov.x += 0.05f;	//0.05f
		if (player.mov.x > 2.0f) player.mov.x = 2.0f;
		player.walk = 1;	// 歩いたことにする
		player.LR = 1;		// 右ﾌﾗｸﾞ
	}
	if (newKey[_1LEFT]) {
		player.mov.x -= 0.05f;		//0.05f
		if (player.mov.x < -2.0f) player.mov.x = -2.0f;
		player.walk = 1;	//歩いたことにする
		player.LR = -1;		//左フラグ
	}

	// 減速
	if (player.walk == 0) {
		// 停止寸前なら誤差を無くして完全停止
		if ((player.mov.x <= 0.05f)
			&& (player.mov.x >= 0.05f)
			) {
			player.mov.x = 0.0f;
		}
		// 地面の減速
		if (player.wing == 0) {
			if (player.mov.x > 0)player.mov.x -= 0.1f;
			if (player.mov.x < 0)player.mov.x += 0.1f;
		}
		else {		// 空中の減速
			if (player.mov.x > 0)player.mov.x -= 0.02f;
			if (player.mov.x < 0)player.mov.x += 0.02f;
		}
	}
	player.tmp.x = player.pos.x + player.mov.x;

	// 背景ｵﾌﾞｼﾞｪｸﾄとの判定
	player.hitFlag = 0;
	HitCheckMapVsCharaLR(&player);
	HitCheckMapVsCharaUD(&player);

	for (int i = 0; i < 10; i++)
	{
		HitCheckPlayerVsEnemy(&player, &enemy);
	}

	// 最終的な座標
	player.pos.x = player.tmp.x;
	player.pos.y = player.tmp.y;
}

void PlayerDeathProc()
{
	FlagCnt = 0;
	player.flag = false;
	player.life--;
	if (player.life <= 0)
	{
		gameMode = GAME_OVER; 

	}
}

void PlayerDraw()
{
	player.counter++;

	//体力2
	if (player.life == 2) {
		// ------ 飛んでいる状態
		if (player.wing == 1) {
			if (player.LR == 1) { // 右向き
				DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][player.counter / 5 % 4], true);
			}
			else {		// 左向き
				DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][player.counter / 5 % 4], true);
			}
		}
		// ---- 飛んでいない状態
		if (player.wing == 0) {

			if (player.walk == 1) {
				// 歩いている状態
				if (player.LR == 1) {	// 右向き
					DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][4 + player.counter / 4 % 4], true);
				}
				else {	// 左向き
					DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][4 + player.counter / 4 % 4], true);
				}
			}
			if (player.walk == 0) {
				// 歩いていない状態
				if (player.LR == 1) {	// 右向き
					DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][4], true);
				}
				else {	// 左向き
					DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[1][4], true);
				}
			}

		}
	}

	//体力1
	if (player.life == 1) {
		// ------ 飛んでいる状態
		if (player.wing == 1) {
			if (player.LR == 1) { // 右向き
				DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][player.counter / 5 % 4], true);
			}
			else {		// 左向き
				DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][player.counter / 5 % 4], true);
			}
		}
		// ---- 飛んでいない状態
		if (player.wing == 0) {

			if (player.walk == 1) {
				// 歩いている状態
				if (player.LR == 1) {	// 右向き
					DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][4 + player.counter / 4 % 4], true);
				}
				else {	// 左向き
					DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][4 + player.counter / 4 % 4], true);
				}
			}
			if (player.walk == 0) {
				// 歩いていない状態
				if (player.LR == 1) {	// 右向き
					DrawGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][4], true);
				}
				else {	// 左向き
					DrawTurnGraph(player.pos.x - 16, player.pos.y - 24, imgPlayer[0][4], true);
				}
			}

		}
	}
	//右から左
	if (player.pos.x > SCREEN_SIZE_X)
	{
		player.pos.x = SCREEN_SIZE_X - SCREEN_SIZE_X;
	}
	//左から右
	if (player.pos.x < 0)
	{
		player.pos.x = SCREEN_SIZE_X;
	}

}