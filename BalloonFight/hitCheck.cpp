#include "DxLib.h"
#include "hitCheck.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

void HitCheckMapVsCharaLR(CHARA_DATA* c)
{
	int bl;	// ﾌﾞﾛｯｸの左(X座標)
	int br; // ﾌﾞﾛｯｸの右(X座標)
	int bu; // ﾌﾞﾛｯｸの上(Y座標)
	int bd; // ﾌﾞﾛｯｸの下(Y座標)

	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 32; x++) {
			if (mapData[y][x] >= 0) {
				bl = x * 16;		// 左
				br = x * 16 + 16;	// 右
				bu = y * 16;		// 上
				bd = y * 16 + 16;	// 下

				//移動制限
				//上画面
				if (c->pos.y < 0 + PLAYER_SIZE_Y / 2) {
					c->pos.y = 0 + PLAYER_SIZE_Y / 2;
					c->tmp.y += 16;		// 下方向に反射
					c->mov.y = 2;		// 移動方向を逆に・・・
				}
				// ------ 上下壁判定
				if (((c->pos.x - 16) < br) && ((c->pos.x + 16) > bl)) {

					// ------ 地面判定
					if (((c->pos.y + 24) <= bu) && ((c->tmp.y + 24) > bu)) {
						c->tmp.y = bu - 24;		// ﾌﾞﾛｯｸの上に立たせる
						c->wing = 0;			// 飛んでいないことにする
						if (mapData[y][x] == 8)
						{
							PlayerDeathProc();
						}
						if (mapData[y][x] == 9)
						{
							PlayerDeathProc();
						}
						if (mapData[y][x] == 10)
						{
							PlayerDeathProc();
						}
						if (mapData[y][x] == 11)
						{
							PlayerDeathProc();
						}
					}

					// ----- 頭判定
					if (((c->pos.y - 24) >= bd) && ((c->tmp.y - 24) < bd)) {
						c->tmp.y += 16;		// 下方向に反射
						c->mov.y = 2;		// 移動方向を逆に・・・
					}
				}

				// ----- 左右壁判定
				if (((c->pos.y - 24) < bd) && ((c->pos.y + 24) > bu)) {
					// ｷｬﾗｸﾀｰの右が壁の左に衝突
					if (((c->pos.x + 16) < bl) && ((c->tmp.x + 16) >= bl)) {
						c->tmp.x -= 10;
					}
					// ｷｬﾗｸﾀｰの左が壁の右に衝突
					if (((c->pos.x - 16) > br) && ((c->tmp.x - 16) <= br)) {
						c->tmp.x += 10;
					}
				}
			}
		}
	}
}

void HitCheckMapVsCharaUD(CHARA_DATA* c)
{
	int bl, br, bu, bd;
	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 32; x++) {
			if (mapData[y][x] >= 0) {
				bl = x * 16;		//左
				br = x * 16 + 16;	//右
				bu = y * 16;		//上
				bd = y * 16 + 16;	//下

				//上下判定
				if (((c->pos.x - 16) < br) && ((c->pos.x + 16) > bl)) {
					//地面判定
					if (((c->pos.y + 24) <= bu) && ((c->tmp.y + 24) > bu)) {
						c->tmp.y = bu - 24;	//ブロックの上に立たせる
						c->wing = 0;	//飛んでいないことにする
					}

					//頭判定
					if (((c->pos.y - 24) >= bd) && ((c->tmp.y - 24) < bd)) {
						c->tmp.y += 16;	//下方向に反射
						c->mov.y = 2;	//移動方向を逆に
					}
				}
			}
		}
	}
}

void HitCheckMapVsEnemyLR(CHARA_DATA* e)
{
	int bl, br, bu, bd;
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (mapData[y][x] >= 0)
			{
				bl = x * 16;
				br = x * 16 + 16;
				bu = y * 16;
				bd = y * 16 + 16;

				//画面上
				if (e->pos.y < 0 + ENEMY_SIZE_Y / 2) {
					e->pos.y = 0 + ENEMY_SIZE_Y / 2;
					e->tmp.y += 16;		// 下方向に反射
					e->mov.y = 2;		// 移動方向を逆に
				}

				//上下壁判定
				if (((e->pos.x - 16) < br) && ((e->pos.x + 16) > bl))
				{
					//地面判定
					if (((e->pos.y + 24) <= bu) && ((e->tmp.y + 24) > bu))
					{
						e->tmp.y = bu - 24;	//ブロックの上に立つ
						//e->mov.y = 0;
						if (mapData[y][x] == 8)
						{
							EnemyDeathProc();
						}

						if (mapData[y][x] == 9)
						{
							EnemyDeathProc();
						}
						if (mapData[y][x] == 10)
						{
							EnemyDeathProc();
						}
						if (mapData[y][x] == 11)
						{
							EnemyDeathProc();
						}
					}

					//頭判定
					if (((e->pos.y - 24) >= bd) && ((e->tmp.y - 24) < bd))
					{
						e->tmp.y += 16;
						e->mov.y = 2;
					}
				}

				//左右壁判定
				if (((e->pos.y - 24) < bd) && ((e->pos.y + 24) > bu))
				{
					//敵の右と壁の左
					if (((e->pos.x + 16) < bl) && ((e->tmp.x + 16) >= bl))
					{
						e->tmp.x -= 10;
					}
					//敵の左と壁の右
					if (((e->pos.x - 16) > br) && ((e->tmp.x - 16) <= br))
					{
						e->tmp.x += 10;
					}
				}
			}
		}
	}
}

void HitCheckMapVsEnemyUD(CHARA_DATA* e)
{
	int bl, br, bu, bd;
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (mapData[y][x] >= 0)
			{
				bl = x * 16;
				br = x * 16 + 16;
				bu = y * 16;
				bd = y * 16 + 16;
				if (((e->pos.x - 16) < br) && ((e->pos.x + 16) > bl))
				{
					if (((e->pos.y + 24) <= bu) && ((e->pos.y + 24) > bu))
					{
						e->tmp.y = bu - 24;
						e->mov.y = 2;
					}
					if (((e->pos.y - 24) >= bd) && ((e->tmp.y - 24) < bd))
					{
						e->tmp.y += 16;
						e->mov.y = 2;
					}
				}
			}
		}
	}
}

void HitCheckPlayerVsEnemy(CHARA_DATA* c,CHARA_DATA* e)
{
	if ((c->pos.x - 16 <= e->pos.x + 16)
		&& (c->pos.x + 16 >= e->pos.x - 16)
		&& (c->pos.y - 24 <= e->pos.y + 24)
		&& (c->pos.y + 24 >= e->pos.y - 24))
	{
		EnemyDeathProc();
	}
	if ((e->pos.x - 16 <= c->pos.x + 16)
		&& (e->pos.x + 16 >= c->pos.x - 16)
		&& (e->pos.y - 24 <= c->pos.y + 24)
		&& (e->pos.y + 24 >= c->pos.y - 24))
	{
		EnemyDeathProc();
	}


}
