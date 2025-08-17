#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <memory>

#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Scene/ResultScene.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"

/* == ゲームの概要 ====================================== 
【ジャンル】
弾幕シューティングゲーム

【制作期間】
3日 + 後からちょい修正

【制作経緯】
インターンの課題

【実装した機能】
・タイトル、ゲーム、リザルトシーンをステートマシンで管理
→ SceneManager

・多態性を用いたオブジェクト管理
→ Scene, Enemy, Bullet

・自作のPoolアロケータを使用
→ Objectで宣言, PlayerとEnemyでAlloc, GameSceneでFree

・スレッドを用いた並行処理を使用
→ InputManager
======================================================= */ 

int main()
{
	// エスケープシーケンスを有効に
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdOut, &mode);
	SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// カーソルを消す
	printf("\x1b[?25l");

	// コンソールの大きさを変える
	system("mode con: cols=81 lines=35");

	// 入力用クラス
	InputManager inputManager;

	// シーン管理クラス
	SceneManager sceneManager;

	// 初めのシーンをタイトルに設定
	sceneManager.changeScene(std::make_unique<TitleScene>(sceneManager, inputManager));

	// 同期処理で入力を受け取る
	inputManager.start();

	// メインループ
	do {
		// 時間計測
		Time::getInstance()->update();
		// 現在のシーンを更新
		sceneManager.Update();
	} while (sceneManager.isEnded());

	// ゲームが終了したら
	// 入力の受け取りスレッドを終了
	inputManager.stop();

	// カーソルを表示
	printf("\x1b[?25h");
	return EXIT_SUCCESS;
}
