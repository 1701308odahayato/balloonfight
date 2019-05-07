

#include "DxLib.h"
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "hitCheck.h"
#include "map.h"

int imgEnemyBalloon[2][4];	//風船
int imgEnemyAir[6];		//空気入れ
int imgEnemyFish[4];	//怪魚
CHARA_DATA enemy;	//雑魚

void EnemySystemInit()
{
	int tmp = LoadGraph("image/enemyImage.png");

	//空気入れ
	for (int i = 0; i < 6; i++) {
		imgEnemyAir[i] = DerivationGraph(32 * i, 48, 32, 48, tmp);
	}

	//風船
	imgEnemyBalloon[0][0] = DerivationGraph(0, 0, 32, 48, tmp);
}

void EnemyInit()
{
	//雑魚
	enemy.flag = true;
	enemy.pos.x = 13 * 16;		//横13コマ目
	enemy.pos.y = 8 * 16 + 8;	//縦８コマ目
	enemy.counter = 0;			//カウンター
	enemy.wing = 0;				//飛んでいない
	enemy.walk = 0;				//歩いていない
	enemy.LR = -1;				//1:右　-1:左
	enemy.UD = 1;
	enemy.air = 1;
	enemy.life = 2;				//体力
	enemy.hitFlag = 0;

}

void EnemyMain()
{
	//プレイヤーのほうに向きを変える
	for (int i = 0; i < 10; i++) {
		if (enemy.pos.x < player.pos.x) {
			enemy.LR = 1;	//右
		}
		else {
			enemy.LR = -1;	//左
		}
	}

	//空気入れ終わったら上昇モード
	if (enemy.counter == 180) {
		enemy.air = 0;
		enemy.wing = 1;
		enemy.mov.y = -0.3f;
		enemy.mov.x = -0.3f;
	}

	//空気入れモード
	if (enemy.air == 1) {
		enemy.mov.x = 0.0f;
		enemy.mov.y = 0.0f;	//動かない
	}

	//移動モード
	if (enemy.wing == 1) {
		if ((enemy.counter % 90) == 0) {//移動の向きを変えるタイミング
			switch (GetRand(2)) {	//0から2までの乱数
			case 0:
				//①上昇下降はそのままで左右移動方向だけ反転
				enemy.mov.x = -1;
				break;
			case 1:
				//②左右移動はそのままでプレイヤーの高さに合わせる
				if (enemy.pos.y > player.pos.y) {
					enemy.pos.y = -0.5;
				}
				else {
					enemy.mov.y = 0.5f;
				}
				break;
			case 2:
				//③縦軸・横軸ともにプレイヤーに近つける
				if (enemy.pos.y > player.pos.y) {
					enemy.mov.y = -0.5;
				}
				else {
					enemy.mov.y = 0.5f;	//縦軸
				}
				if (enemy.pos.x > player.pos.x) {
					enemy.mov.x = -0.5;
				}
				else {
					enemy.mov.x = 0.5f;	//横軸
				}
				break;
			}
		}

		//No（そのまま移動）
		//①方向を変えずに移動し続ける
		//enemy.mov.y = -0.5f;	//上昇
	}

	enemy.tmp.x = enemy.pos.x + enemy.mov.x;
	enemy.tmp.y = enemy.pos.y + enemy.mov.y;

	enemy.hitFlag = 0;
	for (int i = 0; i < 10; i++)
	{
		HitCheckMapVsEnemyLR(&enemy);
		HitCheckMapVsEnemyUD(&enemy);
	}
	enemy.pos.x = enemy.tmp.x;
	enemy.pos.y = enemy.tmp.y;
}

void EnemyDeathProc()
{
	enemy.flag = false;
	enemy.life--;
	if (enemy.life == 0)
	{
		gameMode = GAME_CLEAR;
	}
}

void EnemyDraw()
{
	//敵全員描画
	for (int i = 0; i < 10; i++) {
		enemy.counter++;
		//空気入れ状態
		if (enemy.air == 1) {
			if (enemy.LR == 1) {	//右向き
				DrawGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyAir[enemy.counter / 30 % 6], true);
			}
			else {	//左向き
				DrawTurnGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyAir[enemy.counter / 30 % 6], true);
			}
		}
		else {
			if (enemy.life == 2) {
				if (enemy.wing == 1) {
					if (enemy.LR == 1) {	//右向き
						DrawGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyBalloon[0][0], true);
					}
					else {	//左向き
						DrawTurnGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyBalloon[0][0], true);
					}
				}
			}
		}
	}
	//右から左
	if (enemy.pos.x > SCREEN_SIZE_X)
	{
		enemy.pos.x = SCREEN_SIZE_X - SCREEN_SIZE_X;
	}
	//左から右
	if (enemy.pos.x < 0)
	{
		enemy.pos.x = SCREEN_SIZE_X;
	}


}






