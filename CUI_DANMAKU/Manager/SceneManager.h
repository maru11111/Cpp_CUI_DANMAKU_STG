#pragma once

#include "../Scene/Scene.h"
#include <memory>
#include "../Manager/InputManager.h"

class Scene;

// シーンを管理するステートマシン
class SceneManager {
public:
	SceneManager();

	~SceneManager() = default;

	// メインループで呼び出す関数
	// シーンのupdate, draw関数を呼び出す
	void Update();

	// シーン遷移用の関数
	// 次に遷移するシーンを受け取る
	void changeScene(std::unique_ptr<Scene>nextScene);

	// 実行するシーンがあるかどうか
	// main.cppでメインループを終了するかの判定に使う
	bool isEnded();

	// シーン間共通変数
	// スコア
	double score = 0;

private:
	// 現在のシーンを持っておく。
	// これをポリモーフィズムを使って置き換えることで, 
	// Sceneを継承するだけで新たなシーンを作れる
	std::unique_ptr<Scene>currentScene;

	// 次のシーン
	std::unique_ptr<Scene>nextScene;

	// 現在のフレームでシーン遷移を行うかのフラグ
	bool shouldChangeScene = false;
};