#pragma once
#include"Scene.h"
#include "../Util/Common.h"
#include <memory>
#include "TitleScene.h"
#include "GameScene.h"

// 結果を表示するシーン
class ResultScene : public Scene
{
public:
	ResultScene(SceneManager& sceneManager_, InputManager& inputManager_);
	void update()override;
	void draw()const override;
	// アニメーション用タイマー
	double timer=0;
};

