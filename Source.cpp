#include <DxLib.h>

using namespace std;

int Player, Enemy, Shot;
int PlayerX = 288, PlayerY = 450;							//Player初期位置

int EnemySpeed = 5;
int EnemyMove = 40;
int EnemyX = 288;
int EnemyY = 0;

int ShotX, ShotY;

bool ShotShooting = false;

int Score = 0;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(TRUE);	//ウィンドウモード
	DxLib_Init();	//DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK);	//ダブルバッファリングの実行。画面のちらつきを防ぐ

	Player = LoadGraph("img/Player.png");	//メモリに画像を保存し、呼び出しを高速化
	Enemy = LoadGraph("img/Enemy.png");
	Shot = LoadGraph("img/Shot.png");


	while (!ProcessMessage()) {		//windowsのメッセージループを処理。これを行わないとwindowsの処理が重くなる。（らしい
		ClearDrawScreen();			//裏画面の以前の画像を消去する


		//Player処理

		if (CheckHitKey(KEY_INPUT_A)) {
			PlayerX -= 3;
			if (PlayerX < 0) PlayerX = 0;
		}

		if (CheckHitKey(KEY_INPUT_D)) {
			PlayerX += 3;
			if (PlayerX > 640 - 64) PlayerX = 640 - 64;
		}


		//Enemy処理


		EnemyX += EnemySpeed;
		if (EnemyX <= 0 || EnemyX >= 640 - 77) {
			EnemySpeed = -EnemySpeed;
			EnemyY += EnemyMove;
		}

		//グラフィック処理

		if (ShotShooting) DrawGraph(ShotX, ShotY, Shot, true);	//弾が発射され、trueの間のみ弾画像を描写

		DrawGraph(PlayerX, PlayerY, Player, true);//TRUEにすることで、画像の透過を有効にする
		DrawGraph(EnemyX, EnemyY, Enemy, true);

		DrawFormatString(0, 0, GetColor(255, 255, 255), "SCORE : %d 撃破", Score);

		ScreenFlip();



		//Shot処理
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (!ShotShooting) {
				ShotShooting = true;
				ShotX = PlayerX + 10;
				ShotY = PlayerY;
			}
		}

		//以下、当たり判定記述

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


			//以上、当たり判定記述

		}
	}

	DxLib_End();
	return 0;
}