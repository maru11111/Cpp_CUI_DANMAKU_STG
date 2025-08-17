#include "Bullet.h"

Bullet::Bullet(Point pos_, Vec2 dir_, double speed_, int r_, int g_, int b_, char bulletChar_)
	: Entity{ pos_ }
	, dir{dir_}
	, doubleTypePos{ (double)pos_.x, (double)pos_.y }
	, speed{speed_}
	, r{r_}
	, g{g_}
	, b{b_}
	, bulletChar{bulletChar_}
{}

void Bullet::update() {
	// 前回の座標を記録しておく
	pos.prevX = pos.x;
	pos.prevY = pos.y;
	
	// 1秒ごとに speed だけ dir の方向に進む
	doubleTypePos += dir * speed * Time::getInstance()->deltaTime();
	
	// 座標を整数に丸める
	pos = Point((int32_t)doubleTypePos.x, (int32_t)doubleTypePos.y);	
}

void Bullet::draw()const {
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;%d;%d;%dm\x1b[%d;%dH%c\x1b[39m", r, g, b, pos.y, pos.x, bulletChar); // 今の座標に描画
}