#include <DxLib.h>

using namespace std;

int Player, Enemy, Shot;
int PlayerX = 288, PlayerY = 450;							//Player�����ʒu

int EnemySpeed = 5;
int EnemyMove = 40;
int EnemyX = 288;
int EnemyY = 0;

int ShotX, ShotY;

bool ShotShooting = false;

int Score = 0;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h
	DxLib_Init();	//DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK);	//�_�u���o�b�t�@�����O�̎��s�B��ʂ̂������h��

	Player = LoadGraph("img/Player.png");	//�������ɉ摜��ۑ����A�Ăяo����������
	Enemy = LoadGraph("img/Enemy.png");
	Shot = LoadGraph("img/Shot.png");


	while (!ProcessMessage()) {		//windows�̃��b�Z�[�W���[�v�������B������s��Ȃ���windows�̏������d���Ȃ�B�i�炵��
		ClearDrawScreen();			//����ʂ̈ȑO�̉摜����������


		//Player����

		if (CheckHitKey(KEY_INPUT_A)) {
			PlayerX -= 3;
			if (PlayerX < 0) PlayerX = 0;
		}

		if (CheckHitKey(KEY_INPUT_D)) {
			PlayerX += 3;
			if (PlayerX > 640 - 64) PlayerX = 640 - 64;
		}


		//Enemy����


		EnemyX += EnemySpeed;
		if (EnemyX <= 0 || EnemyX >= 640 - 77) {
			EnemySpeed = -EnemySpeed;
			EnemyY += EnemyMove;
		}

		//�O���t�B�b�N����

		if (ShotShooting) DrawGraph(ShotX, ShotY, Shot, true);	//�e�����˂���Atrue�̊Ԃ̂ݒe�摜��`��

		DrawGraph(PlayerX, PlayerY, Player, true);//TRUE�ɂ��邱�ƂŁA�摜�̓��߂�L���ɂ���
		DrawGraph(EnemyX, EnemyY, Enemy, true);

		DrawFormatString(0, 0, GetColor(255, 255, 255), "SCORE : %d ���j", Score);

		ScreenFlip();



		//Shot����
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (!ShotShooting) {
				ShotShooting = true;
				ShotX = PlayerX + 10;
				ShotY = PlayerY;
			}
		}

		//�ȉ��A�����蔻��L�q

		if (ShotShooting) {
			ShotY -= 10;
			if (ShotY < 0) ShotShooting = false;
		}

		if (ShotShooting) {
			if (
				ShotX + 15 > EnemyX &&
				ShotX < EnemyX + 77 &&
				ShotY + 16 > EnemyY &&
				ShotY < EnemyY + 56
				) {

				ShotShooting = false;
				EnemyX = 288;
				EnemyY = 0;
				EnemySpeed = 5;
				Score += 1;
			}


			//�ȏ�A�����蔻��L�q

		}
	}

	DxLib_End();
	return 0;
}