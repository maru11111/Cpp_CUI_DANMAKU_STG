#pragma once
#include "../Util/Common.h"
#include <iostream>
#include "Entity.h"

class Bullet : public Entity {
public:
	Bullet(Point pos_, Vec2 dir_, double speed, int r, int g, int b, char bulletChar);
	virtual ~Bullet() = default;
	void update()override;
	void draw()const override;
	// 弾の飛ぶ方向
	Vec2 dir;
	// 斜めに弾を飛ばしたいときもあるので, double型の座標も持っておく
	Vec2 doubleTypePos;
	// 弾の色
	int r=0, g=0, b=0;
	// 弾の速度
	double speed = 4.0;
	// 弾のグラフィック
	char bulletChar='a';
};