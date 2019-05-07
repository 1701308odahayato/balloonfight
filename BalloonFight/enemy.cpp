

#include "DxLib.h"
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "hitCheck.h"
#include "map.h"

int imgEnemyBalloon[2][4];	//���D
int imgEnemyAir[6];		//��C����
int imgEnemyFish[4];	//����
CHARA_DATA enemy;	//�G��

void EnemySystemInit()
{
	int tmp = LoadGraph("image/enemyImage.png");

	//��C����
	for (int i = 0; i < 6; i++) {
		imgEnemyAir[i] = DerivationGraph(32 * i, 48, 32, 48, tmp);
	}

	//���D
	imgEnemyBalloon[0][0] = DerivationGraph(0, 0, 32, 48, tmp);
}

void EnemyInit()
{
	//�G��
	enemy.flag = true;
	enemy.pos.x = 13 * 16;		//��13�R�}��
	enemy.pos.y = 8 * 16 + 8;	//�c�W�R�}��
	enemy.counter = 0;			//�J�E���^�[
	enemy.wing = 0;				//���ł��Ȃ�
	enemy.walk = 0;				//�����Ă��Ȃ�
	enemy.LR = -1;				//1:�E�@-1:��
	enemy.UD = 1;
	enemy.air = 1;
	enemy.life = 2;				//�̗�
	enemy.hitFlag = 0;

}

void EnemyMain()
{
	//�v���C���[�̂ق��Ɍ�����ς���
	for (int i = 0; i < 10; i++) {
		if (enemy.pos.x < player.pos.x) {
			enemy.LR = 1;	//�E
		}
		else {
			enemy.LR = -1;	//��
		}
	}

	//��C����I�������㏸���[�h
	if (enemy.counter == 180) {
		enemy.air = 0;
		enemy.wing = 1;
		enemy.mov.y = -0.3f;
		enemy.mov.x = -0.3f;
	}

	//��C���ꃂ�[�h
	if (enemy.air == 1) {
		enemy.mov.x = 0.0f;
		enemy.mov.y = 0.0f;	//�����Ȃ�
	}

	//�ړ����[�h
	if (enemy.wing == 1) {
		if ((enemy.counter % 90) == 0) {//�ړ��̌�����ς���^�C�~���O
			switch (GetRand(2)) {	//0����2�܂ł̗���
			case 0:
				//�@�㏸���~�͂��̂܂܂ō��E�ړ������������]
				enemy.mov.x = -1;
				break;
			case 1:
				//�A���E�ړ��͂��̂܂܂Ńv���C���[�̍����ɍ��킹��
				if (enemy.pos.y > player.pos.y) {
					enemy.pos.y = -0.5;
				}
				else {
					enemy.mov.y = 0.5f;
				}
				break;
			case 2:
				//�B�c���E�����Ƃ��Ƀv���C���[�ɋ߂���
				if (enemy.pos.y > player.pos.y) {
					enemy.mov.y = -0.5;
				}
				else {
					enemy.mov.y = 0.5f;	//�c��
				}
				if (enemy.pos.x > player.pos.x) {
					enemy.mov.x = -0.5;
				}
				else {
					enemy.mov.x = 0.5f;	//����
				}
				break;
			}
		}

		//No�i���̂܂܈ړ��j
		//�@������ς����Ɉړ���������
		//enemy.mov.y = -0.5f;	//�㏸
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
	//�G�S���`��
	for (int i = 0; i < 10; i++) {
		enemy.counter++;
		//��C������
		if (enemy.air == 1) {
			if (enemy.LR == 1) {	//�E����
				DrawGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyAir[enemy.counter / 30 % 6], true);
			}
			else {	//������
				DrawTurnGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyAir[enemy.counter / 30 % 6], true);
			}
		}
		else {
			if (enemy.life == 2) {
				if (enemy.wing == 1) {
					if (enemy.LR == 1) {	//�E����
						DrawGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyBalloon[0][0], true);
					}
					else {	//������
						DrawTurnGraph(enemy.pos.x - 16, enemy.pos.y - 24, imgEnemyBalloon[0][0], true);
					}
				}
			}
		}
	}
	//�E���獶
	if (enemy.pos.x > SCREEN_SIZE_X)
	{
		enemy.pos.x = SCREEN_SIZE_X - SCREEN_SIZE_X;
	}
	//������E
	if (enemy.pos.x < 0)
	{
		enemy.pos.x = SCREEN_SIZE_X;
	}


}






