#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& sceneManager_, InputManager& inputManager_)
	: Scene{sceneManager_, inputManager_ }
{
	// ゲーム画面の囲い描画
	for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
		for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
			// 上面
			if (k == WINDOW_ORIGIN.y - 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
				printf("\x1b[%d;%dH~", k, i);
			//下面
			if (k == WINDOW_SIZE.y + 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
				printf("\x1b[%d;%dH-", k, i);
			// 左面
			if (i == WINDOW_ORIGIN.x - 1 && (WINDOW_ORIGIN.y - 1 < k && k < WINDOW_SIZE.y + 1))
				printf("\x1b[%d;%dH:", k, i);

			// 右面
			if (i == WINDOW_SIZE.x + 1 && (WINDOW_ORIGIN.x - 1 < k && k < WINDOW_SIZE.y + 1))
				printf("\x1b[%d;%dH:", k, i);
		}
	}
	// 各種パラメータ表示
	//printf("\x1b[%d;%dH     【パラメータ】", 7, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH    ------------------", 4, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH    ・経過時間：%.2lf", 5, WINDOW_SIZE.x + 2 + 1, 0.0);
	printf("\x1b[%d;%dH    ・スコア：%d", 6, WINDOW_SIZE.x + 2 + 1, 0);
	printf("\x1b[%d;%dH    ------------------", 7, WINDOW_SIZE.x + 2 + 1);

	// 敵のスコアを表示
	printf("\x1b[%d;%dH    ---【ターゲット】---", 9, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;178;140;140m         １：100点", 10, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;178;110;110m         ２：150点", 11, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;188;80;80m         ３：200点", 12, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;188;40;40m         ４：1000点", 13, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[39m");
	printf("\x1b[%d;%dH    --------------------", 14, WINDOW_SIZE.x + 2 + 1);

	// ランク
	printf("\x1b[%d;%dH     ---【ランク表】---", 15, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;121;156;190m   0～199", 16, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;121;190;153m 200～499", 17, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;213;132;76m 500～999", 18, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;210;89;93m1000～1899", 19, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;167;121;190m1900～", 20, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[39m");
	printf("\x1b[%d;%dH     ------------------", 21, WINDOW_SIZE.x + 2 + 1);

	// 遊び方
	printf("\x1b[%d;%dH        【遊び方】", 23, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH ・弾に当たるとGAME OVER！", 24, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH ・敵を倒すとスコアが上昇！", 25, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH・スコアに応じて\x1b[38;2;121;156;190m青\x1b[39m～\x1b[38;2;167;121;190m紫\x1b[39mまでの", 26, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH    ランクがつくぞ！", 27, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH・\x1b[38;2;188;60;60m1000点\x1b[39m以上を取ったらクリア！", 28, WINDOW_SIZE.x + 2);

	// 操作方法
	printf("\x1b[%d;%dH      【操作方法】", 30, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH     ・WASDで移動！", 31, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH     ・SPACEで攻撃！", 32, WINDOW_SIZE.x + 2 + 1);
	//printf("\x1b[%d;%dH   ・Qでタイトルへ, 33, WINDOW_SIZE.x + 2 + 1);

	for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
		printf("\x1b[%d;%dH ", 16, i);
		printf("\x1b[%d;%dH ", 17, i);
		printf("\x1b[%d;%dH ", 18, i);
		printf("\x1b[%d;%dH ", 19, i);
		printf("\x1b[%d;%dH ", 20, i);

		printf("\x1b[%d;%dH-", 15, i);
		printf("\x1b[%d;%dH-", 21, i);
	}
	printf("\x1b[%d;%dH【Title】", 15, TERMINAL_WINDOW_SIZE.x / 2 - 4);
	printf("\x1b[%d;%dH「弾幕シューティングゲーム」", 16, TERMINAL_WINDOW_SIZE.x / 2 - 14);
	printf("\x1b[%d;%dH  Spaceキーでスタート！", 18, TERMINAL_WINDOW_SIZE.x / 2 - 12);

	printf("\x1b[%d;%dH(Qキーでゲームを終える)", 20, TERMINAL_WINDOW_SIZE.x -24);
}

void TitleScene::update() {
	// シーン遷移前アニメーションのタイマーを動かす
	if (isSceneChangeStarted) timer += Time::getInstance()->deltaTime(); 
	// スペースキーで開始
	if (inputManager.isPressed(' ')) isSceneChangeStarted = true;
	// qでゲームを終了
	if (inputManager.isPressed('q'))sceneManager.changeScene(nullptr);
}

void TitleScene::draw()const {
	// シーン遷移前のアニメーション
	if (isSceneChangeStarted) {
		for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
			for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
				// 上面
				if (k == WINDOW_ORIGIN.y - 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
					printf("\x1b[%d;%dH~", k, i);
				//下面
				if (k == WINDOW_SIZE.y + 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
					printf("\x1b[%d;%dH-", k, i);
				// 左面
				if (i == WINDOW_ORIGIN.x - 1 && (WINDOW_ORIGIN.y - 1 < k && k < WINDOW_SIZE.y + 1))
					printf("\x1b[%d;%dH:", k, i);

				// 右面
				if (i == WINDOW_SIZE.x + 1 && (WINDOW_ORIGIN.x - 1 < k && k < WINDOW_SIZE.y + 1))
					printf("\x1b[%d;%dH:", k, i);
			}
		}
		if (timer <= 0.075) {
			for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
				printf("\x1b[%d;%dH                        ", 18, TERMINAL_WINDOW_SIZE.x / 2 - 12);
				printf("\x1b[%d;%dH ", 15, i);
				printf("\x1b[%d;%dH ", 21, i);

				if (i < TERMINAL_WINDOW_SIZE.x / 2 - 4 || TERMINAL_WINDOW_SIZE.x / 2 - 4 + 8 < i)
					printf("\x1b[%d;%dH-", 16, i);
				printf("\x1b[%d;%dH-", 20, i);
			}
			printf("\x1b[%d;%dH【Title】", 16, TERMINAL_WINDOW_SIZE.x / 2 - 4);
		}
		else if (timer < 0.075*2) {
			for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
				printf("\x1b[%d;%dH ", 16, i);
				printf("\x1b[%d;%dH ", 20, i);

				if (i < TERMINAL_WINDOW_SIZE.x / 2 - 4 || TERMINAL_WINDOW_SIZE.x / 2 - 4 + 8 < i)
					printf("\x1b[%d;%dH-", 17, i);
				printf("\x1b[%d;%dH-", 19, i);
			}
			printf("\x1b[%d;%dH【Title】", 17, TERMINAL_WINDOW_SIZE.x / 2 - 4);
		}
		else if (timer < 0.075 * 3) {
			for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
				printf("\x1b[%d;%dH ", 17, i);
				printf("\x1b[%d;%dH ", 19, i);

				if(i<TERMINAL_WINDOW_SIZE.x/2-4 || TERMINAL_WINDOW_SIZE.x / 2 - 4 +8<i)
				printf("\x1b[%d;%dH-", 18, i);
			}
			printf("\x1b[%d;%dH【Title】", 18, TERMINAL_WINDOW_SIZE.x / 2 - 4);
		}
		else if (timer < 0.075 * 4) {
			for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
				printf("\x1b[%d;%dH ", 18, i);
			}
		}
		else {
			// アニメーションが再生し終わったら
			// ゲームに映る
			sceneManager.changeScene(std::make_unique<GameScene>(sceneManager, inputManager));
		}
	}
}
