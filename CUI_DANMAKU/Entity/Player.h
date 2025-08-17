#pragma once
#include "../Util/Common.h"
#include "../Manager/InputManager.h"
#include "Object.h"
#include <memory>

class Player
{
public:
	Player(Point pos_, Object& obj, InputManager& inputManager);
	~Player() = default;
	
	void update();
	void draw()const;
	// 射線を描画する
	void drawUI()const;
	void attack();
	// 当たり判定を返す
	bool intersects(Point point) {
		return ((pos.x == point.x) && (pos.y == point.y));
	}
	// 死亡したか
	bool isDead = false;
private:
	// 弾を発射するために持っておく
	Object& obj;
	Point pos;
	// キー入力を取得できるクラス
	InputManager& inputManager;
	// 攻撃間隔タイマー
	double attackTimer = 0;
	// 攻撃間隔
	double attackInterval=0.5;
	// 攻撃可能か
	bool canAttack=true;
};
