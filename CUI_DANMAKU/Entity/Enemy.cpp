#include "Enemy.h"
#include "Object.h" 

Enemy::Enemy(Point pos_, Object& obj_)
	: Entity(pos_)
	, obj(obj_)
{}


NormalEnemy::NormalEnemy(Point pos_, Point moveDir_, Object& obj_)
	: Enemy(pos_, obj_)
	, moveDir{moveDir_}
{
	score = 100;
}

void NormalEnemy::update() {
	// 前回の座標を記録しておく
	pos.prevX = pos.x;
	pos.prevY = pos.y;

	// 移動, 攻撃間隔のタイマー
	moveTimer += Time::getInstance()->deltaTime();
	attackTimer += Time::getInstance()->deltaTime();

	// 一定時間ごとに移動
	if (0.5 < moveTimer) {
		moveTimer -= 0.5;
		pos += moveDir;
	}

	// 一定時間ごとに攻撃
	if (2.5 < attackTimer) {
		attackTimer -= 2.5;
		obj.enemyBullets.push_back(obj.bulletPoolAllocator.Alloc(pos + Point{ 0, 1 }, Vec2{0, 1}, 4.0, 155, 208, 168, '.'));
	}
}

void NormalEnemy::draw()const {
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;178;140;140m\x1b[%d;%dH1\x1b[39m", pos.y, pos.x); // 今の座標に'1'表示
}




HorizontalMoveEnemy::HorizontalMoveEnemy(Point pos_, Point moveDir_, Object& obj_)
	: NormalEnemy(pos_, moveDir_, obj_)
{
	score = 150;
}

void HorizontalMoveEnemy::draw()const {
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;178;110;110m\x1b[%d;%dH2\x1b[39m", pos.y, pos.x); // 今の座標に'2'表示
}




CircleEnemy::CircleEnemy(Point pos_, Object& obj_)
	: Enemy(pos_, obj_)
{
	moveInterval = 0.5;
	attackInterval = 0.20;
	angleSpeed = M_PI * 3;
	score = 200;
}

void CircleEnemy::update() {
	// 前回の座標を記録しておく
	pos.prevX = pos.x;
	pos.prevY = pos.y;

	// 移動, 攻撃間隔のタイマー
	moveTimer += Time::getInstance()->deltaTime();
	attackTimer += Time::getInstance()->deltaTime();

	// 一定時間ごとに移動
	if (moveInterval < moveTimer) {
		moveTimer -= moveInterval;
		pos.y += 1;
	}

	// 発射角度を更新
	angle += angleSpeed * Time::getInstance()->deltaTime();
	attackDir = { std::cos(angle), std::sin(angle) };

	// 一定時間ごとに攻撃
	if (attackInterval < attackTimer) {
		attackTimer -= attackInterval;
		obj.enemyBullets.push_back(obj.bulletPoolAllocator.Alloc(pos+Point{0, 1}, attackDir, 4.0, 105, 180, 181, '.'));
	}

}

void CircleEnemy::draw()const {
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;188;80;80m\x1b[%d;%dH3", pos.y, pos.x); // 今の座標に'@'表示
	printf("\x1b[39m");
}



BossCircleEnemy::BossCircleEnemy(Point pos_, Object& obj_) 
	: CircleEnemy(pos_, obj_)
{
	moveInterval = 0.15;
	attackInterval = 0.1;
	score = 1000;
}

void BossCircleEnemy::update() {
	// 前回の座標を記録しておく
	pos.prevX = pos.x;
	pos.prevY = pos.y;

	// 移動, 攻撃間隔のタイマー
	moveTimer += Time::getInstance()->deltaTime();
	attackTimer += Time::getInstance()->deltaTime();

	// 一定時間ごとに移動
	if (moveInterval < moveTimer) {
		moveTimer -= moveInterval;
		pos.y += 1;
	}

	// 発射角度を更新
	angle += M_PI * angleSpeed * Time::getInstance()->deltaTime();
	attackDir = { std::cos(angle), std::sin(angle) };

	// 一定時間ごとに攻撃
	if (attackInterval < attackTimer) {
		attackTimer -= attackInterval;
		obj.enemyBullets.push_back(obj.bulletPoolAllocator.Alloc(pos + Point{ 0, 1 }, attackDir, 4.0, 255, 110, 66, 'o'));
	}

}

void BossCircleEnemy::draw()const{
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;188;40;40m\x1b[%d;%dH4\x1b[39m", pos.y, pos.x); // 今の座標に'4'表示
}