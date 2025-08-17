#pragma once
#include <memory>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

class SceneManager;

// シーンの基底クラス
class Scene {
public:
	Scene(SceneManager& sceneManager_, InputManager& inputManager_)
		: sceneManager{ sceneManager_ }
		, inputManager{inputManager_}
	{}
	virtual ~Scene() {};
	virtual void update()=0;
	virtual void draw()const = 0;
	// 継承したシーンで入力、シーン遷移ができるようにするため持たせる
	InputManager& inputManager;
	SceneManager& sceneManager;
};