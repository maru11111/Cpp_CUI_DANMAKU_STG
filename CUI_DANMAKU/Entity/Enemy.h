#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include "../Util/Common.h"
#include "Entity.h"

struct Object;

// 敵の基底クラス
class Enemy : public Entity
{
public:
	Enemy(Point pos_, Object& obj_);
	virtual ~Enemy() = default;
	// スコアのゲッター
	int getScore() {
		return score;
	}
	// 敵の種類
	enum class EnemyKind {
		Normal,
		HorizontalMove,
		Circle,
		BossCircle,
		LAST
	};
protected:
	// 弾を追加するために持っておく
	Object& obj;
	// 倒されたときに加算するスコア
	int score = 0;
};

// 縦に動く敵
class NormalEnemy
	: public Enemy {
public:
	NormalEnemy(Point pos_, Point moveDir, Object& obj_);

	void update()override;

	void draw()const override;

	Point moveDir = { 0, 0 };
};

// 横に動く敵
class HorizontalMoveEnemy : public NormalEnemy {
public:
	HorizontalMoveEnemy(Point pos_, Point moveDir, Object& obj_);

	void draw()const override;
};

// 円状に弾を出す敵
class CircleEnemy : public Enemy {
public:

	CircleEnemy(Point pos_, Object& obj_);

	void update()override;

	void draw()const override;

	// 攻撃方向
	Vec2 attackDir = { 0, 0 };

	// 弾の発射角度
	double angle=0.0;

	// 1秒間で変わる弾の発射角度(rad)
	double angleSpeed;
};

// ボス（レアな敵のほうがただしいかも
class BossCircleEnemy : public CircleEnemy {
public:
	BossCircleEnemy(Point pos_, Object& obj_);
	void update()override;
	void draw()const override;
};