#pragma once
#include "Scene.h"
#include "../Util/Common.h"
#include "GameScene.h"

// タイトルシーン
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& sceneManager_, InputManager& inputManager_);
	void update()override;
	void draw()const override;
	// アニメーション用タイマー
	double timer = 0.0;
	// ゲームシーンに移るときのアニメーションを開始ためのフラグ
	bool isSceneChangeStarted=false;
};

