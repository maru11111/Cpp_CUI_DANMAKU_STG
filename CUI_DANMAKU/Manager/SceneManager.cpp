#include "SceneManager.h"
#include "../Scene/Scene.h"

SceneManager::SceneManager() 
{}

// メインループで呼び出す関数
void SceneManager::Update() {
	// 現在のシーンがあれば更新
	if (currentScene) {
		currentScene->update();
		currentScene->draw();
	}

	// changeSceneが呼ばれていれば
	if (shouldChangeScene) {
		shouldChangeScene = false;
		// 次のシーンに移る
		currentScene = std::move(nextScene);
	}
}

// シーン遷移をするための関数
// これが呼ばれた段階ではまだシーン遷移をしない。
// (現在のシーンの描画を行うため)
void SceneManager::changeScene(std::unique_ptr<Scene>nextScene_) {
	// 次に遷移するシーンを受け取る
	nextScene = std::move(nextScene_);
	// シーン遷移フラグを立てる
	shouldChangeScene = true;
}

// 実行するシーンがなくなれば終了
bool SceneManager::isEnded() {
	return (currentScene != nullptr);
}
