#pragma once
#include "Scene.h"
#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "../Entity/Object.h"
#include<random>
#include "../Util/Common.h"
#include "ResultScene.h"
#include "TitleScene.h"

// プレイ中のシーン
class GameScene : public Scene
{
public:
	GameScene(SceneManager& sceneManager_, InputManager& inputManager_);
	void update()override;
	void draw()const override;
private:
	Player player;
	// 敵、弾などのオブジェクトをまとめたもの
	// これを enemy や player に渡して弾を追加する
	Object obj;
	// ゲームシーンに移ってからの経過時間
	double timer = 0;

	// 乱数
	std::random_device rd;

	// 敵を出現させる関数
	void spawnEnemy();
	// 敵の出現タイマー
	double norSpawnTimer=0;
	double holSpawnTimer=0;
	double cirSpawnTimer=0;
	double bossSpawnTimer=29;
	// 敵の出現間隔
	double norSpawnItval = 7;
	double holSpawnItval = 6;
	double cirSpawnItval = 15;
	double bossSpawnItval = 30;
};

