#include "ResultScene.h"

ResultScene::ResultScene(SceneManager& sceneManager_, InputManager& inputManager_)
	: Scene{ sceneManager_, inputManager_ }
{}

void ResultScene::update() {
	// アニメーション用時間計測
	timer += Time::getInstance()->deltaTime();

	// タイトルに戻る
	if (inputManager.isPressed('t')) {
		// 画面をクリア
		for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
			for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
				printf("\x1b[%d;%dH ", k, i);
			}
		}
		// スコアをリセットしておく
		sceneManager.score = 0;
		// シーン遷移
		sceneManager.changeScene(std::make_unique<TitleScene>(sceneManager, inputManager));
	}

	// リトライ
	if (inputManager.isPressed('r')) {
		// 画面をクリア
		for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
			for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
				printf("\x1b[%d;%dH ", k, i);
			}
		}
		// スコアをリセットしておく
		sceneManager.score = 0;
		// シーン遷移
		sceneManager.changeScene(std::make_unique<GameScene>(sceneManager, inputManager));
	}

	// ゲームを終了する
	if (inputManager.isPressed('q')) {
		// nullptrを渡すと終了する
		sceneManager.changeScene(nullptr);
		return;
	}

	//DEBUG
	//if (inputManager.isPressed('1')) sceneManager.score = 0;
	//if (inputManager.isPressed('2')) sceneManager.score = 101;
	//if (inputManager.isPressed('3')) sceneManager.score = 251;
	//if (inputManager.isPressed('4')) sceneManager.score = 501;
	//if (inputManager.isPressed('5')) sceneManager.score = 1001;
	//if (sceneManager.score < 100) printf("\x1b[38;2;121;156;190m"); // 青
	//else if (sceneManager.score < 250) printf("\x1b[38;2;121;190;153m"); // 緑
	//else if (sceneManager.score < 500) printf("\x1b[38;2;213;132;76m"); // 橙色
	//else if (sceneManager.score < 1000) printf("\x1b[38;2;210;89;93m"); // 赤
	//else printf("\x1b[38;2;167;121;190m"); // 紫
	//if (sceneManager.score < 100) printf("\x1b[%d;%dH  ヨワヨワ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
	//else if (sceneManager.score < 250) printf("\x1b[%d;%dH  ソレナリ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
	//else if (sceneManager.score < 500) printf("\x1b[%d;%dH  ツヨツヨ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
	//else if (sceneManager.score < 1000) printf("\x1b[%d;%dH   スゴイ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
	//else printf("\x1b[%d;%dH  超スゴイ！", 19, TERMINAL_WINDOW_SIZE.x / 2 - 7);
	//printf("\x1b[%d;%dHスコア：%d", 16, TERMINAL_WINDOW_SIZE.x / 2 - 5, (int)sceneManager.score);
	//printf("\x1b[39m");
}

void ResultScene::draw()const {
	// アニメーションさせながら描画
	if (timer <= 0.075) {
		for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
			printf("\x1b[%d;%dH-", 18, i);
		}
		printf("\x1b[%d;%dH【Result】", 18, TERMINAL_WINDOW_SIZE.x / 2 - 5);
	}
	else if (timer < 0.075*2) {
		for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
			printf("\x1b[%d;%dH ", 18, i);

			if (i < TERMINAL_WINDOW_SIZE.x / 2 - 5 || TERMINAL_WINDOW_SIZE.x / 2 - 5 + 9 < i)
				printf("\x1b[%d;%dH-", 17, i);
			printf("\x1b[%d;%dH-", 19, i);
		}
		printf("\x1b[%d;%dH【Result】", 17, TERMINAL_WINDOW_SIZE.x / 2 - 5);
		printf("\x1b[%d;%dH  『評価』", 18, TERMINAL_WINDOW_SIZE.x/2 -6);
	}
	else if (timer < 0.075 * 3) {
		for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
			printf("\x1b[%d;%dH ", 17, i);
			printf("\x1b[%d;%dH ", 19, i);

			if (i < TERMINAL_WINDOW_SIZE.x / 2 - 5 || TERMINAL_WINDOW_SIZE.x / 2 - 5 + 9 < i)
				printf("\x1b[%d;%dH-", 16, i);
			printf("\x1b[%d;%dH-", 20, i);
		}
		printf("\x1b[%d;%dH【Result】", 16, TERMINAL_WINDOW_SIZE.x / 2 - 5);
		if (sceneManager.score < 200) printf("\x1b[38;2;121;156;190m"); // 青
		else if (sceneManager.score < 500) printf("\x1b[38;2;121;190;153m"); // 緑
		else if (sceneManager.score < 1000) printf("\x1b[38;2;213;132;76m"); // 橙色
		else if (sceneManager.score < 1900) printf("\x1b[38;2;210;89;93m"); // 赤
		else printf("\x1b[38;2;167;121;190m"); // 紫
		if (sceneManager.score < 200) printf("\x1b[%d;%dH  ヨワヨワ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
		else if(sceneManager.score < 500) printf("\x1b[%d;%dH  ソレナリ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
		else if(sceneManager.score < 1000) printf("\x1b[%d;%dH  ツヨツヨ", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
		else if (sceneManager.score < 1900) printf("\x1b[%d;%dH  クリア！", 19, TERMINAL_WINDOW_SIZE.x / 2 - 6);
		else printf("\x1b[%d;%dH   超スゴイ！", 19, TERMINAL_WINDOW_SIZE.x / 2 - 7);
		printf("\x1b[39m");
	}
	else if (timer < 0.075 * 4) {
		for (int i = 0; i < TERMINAL_WINDOW_SIZE.x; i++) {
			printf("\x1b[%d;%dH ", 16, i);
			printf("\x1b[%d;%dH ", 20, i);

			if (i < TERMINAL_WINDOW_SIZE.x / 2 - 5 || TERMINAL_WINDOW_SIZE.x / 2 - 5 + 9 < i)
				printf("\x1b[%d;%dH-", 15, i);
			printf("\x1b[%d;%dH-", 21, i);
		}
		printf("\x1b[%d;%dH【Result】", 15, TERMINAL_WINDOW_SIZE.x / 2 - 5);
		if (sceneManager.score < 200) printf("\x1b[38;2;121;156;190m"); // 青
		else if (sceneManager.score < 500) printf("\x1b[38;2;121;190;153m"); // 緑
		else if (sceneManager.score < 1000) printf("\x1b[38;2;213;132;76m"); // 橙色
		else if (sceneManager.score < 1900) printf("\x1b[38;2;210;89;93m"); // 赤
		else printf("\x1b[38;2;167;121;190m"); // 紫
		printf("\x1b[%d;%dHスコア：%d", 16, TERMINAL_WINDOW_SIZE.x / 2 - 5, (int)sceneManager.score);
		printf("\x1b[39m");
		printf("\x1b[%d;%dH(Tキーでタイトルへ)", 18, TERMINAL_WINDOW_SIZE.x - 20);
		printf("\x1b[%d;%dH(Rキーでリトライ  )", 19, TERMINAL_WINDOW_SIZE.x - 20);
		printf("\x1b[%d;%dH(Qキーで終了      )", 20, TERMINAL_WINDOW_SIZE.x - 20);
	}
}