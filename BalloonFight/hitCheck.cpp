#include "DxLib.h"
#include "hitCheck.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

void HitCheckMapVsCharaLR(CHARA_DATA* c)
{
	int bl;	// ��ۯ��̍�(X���W)
	int br; // ��ۯ��̉E(X���W)
	int bu; // ��ۯ��̏�(Y���W)
	int bd; // ��ۯ��̉�(Y���W)

	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 32; x++) {
			if (mapData[y][x] >= 0) {
				bl = x * 16;		// ��
				br = x * 16 + 16;	// �E
				bu = y * 16;		// ��
				bd = y * 16 + 16;	// ��

				//�ړ�����
				//����
				if (c->pos.y < 0 + PLAYER_SIZE_Y / 2) {
					c->pos.y = 0 + PLAYER_SIZE_Y / 2;
					c->tmp.y += 16;		// �������ɔ���
					c->mov.y = 2;		// �ړ��������t�ɁE�E�E
				}
				// ------ �㉺�ǔ���
				if (((c->pos.x - 16) < br) && ((c->pos.x + 16) > bl)) {

					// ------ �n�ʔ���
					if (((c->pos.y + 24) <= bu) && ((c->tmp.y + 24) > bu)) {
						c->tmp.y = bu - 24;		// ��ۯ��̏�ɗ�������
						c->wing = 0;			// ���ł��Ȃ����Ƃɂ���
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

					// ----- ������
					if (((c->pos.y - 24) >= bd) && ((c->tmp.y - 24) < bd)) {
						c->tmp.y += 16;		// �������ɔ���
						c->mov.y = 2;		// �ړ��������t�ɁE�E�E
					}
				}

				// ----- ���E�ǔ���
				if (((c->pos.y - 24) < bd) && ((c->pos.y + 24) > bu)) {
					// ��׸���̉E���ǂ̍��ɏՓ�
					if (((c->pos.x + 16) < bl) && ((c->tmp.x + 16) >= bl)) {
						c->tmp.x -= 10;
					}
					// ��׸���̍����ǂ̉E�ɏՓ�
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
				bl = x * 16;		//��
				br = x * 16 + 16;	//�E
				bu = y * 16;		//��
				bd = y * 16 + 16;	//��

				//�㉺����
				if (((c->pos.x - 16) < br) && ((c->pos.x + 16) > bl)) {
					//�n�ʔ���
					if (((c->pos.y + 24) <= bu) && ((c->tmp.y + 24) > bu)) {
						c->tmp.y = bu - 24;	//�u���b�N�̏�ɗ�������
						c->wing = 0;	//���ł��Ȃ����Ƃɂ���
					}

					//������
					if (((c->pos.y - 24) >= bd) && ((c->tmp.y - 24) < bd)) {
						c->tmp.y += 16;	//�������ɔ���
						c->mov.y = 2;	//�ړ��������t��
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

				//��ʏ�
				if (e->pos.y < 0 + ENEMY_SIZE_Y / 2) {
					e->pos.y = 0 + ENEMY_SIZE_Y / 2;
					e->tmp.y += 16;		// �������ɔ���
					e->mov.y = 2;		// �ړ��������t��
				}

				//�㉺�ǔ���
				if (((e->pos.x - 16) < br) && ((e->pos.x + 16) > bl))
				{
					//�n�ʔ���
					if (((e->pos.y + 24) <= bu) && ((e->tmp.y + 24) > bu))
					{
						e->tmp.y = bu - 24;	//�u���b�N�̏�ɗ���
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

					//������
					if (((e->pos.y - 24) >= bd) && ((e->tmp.y - 24) < bd))
					{
						e->tmp.y += 16;
						e->mov.y = 2;
					}
				}

				//���E�ǔ���
				if (((e->pos.y - 24) < bd) && ((e->pos.y + 24) > bu))
				{
					//�G�̉E�ƕǂ̍�
					if (((e->pos.x + 16) < bl) && ((e->tmp.x + 16) >= bl))
					{
						e->tmp.x -= 10;
					}
					//�G�̍��ƕǂ̉E
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
