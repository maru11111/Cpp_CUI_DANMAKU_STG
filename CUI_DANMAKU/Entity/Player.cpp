#include "Player.h"

Player::Player(Point pos_, Object& obj_, InputManager& inputManager_)
	: pos{ pos_ }
	, obj{obj_}
	, inputManager{inputManager_}
{
}

void Player::update() {
	// 前回の座標を記録しておく
	pos.prevX = pos.x;
	pos.prevY = pos.y;
	// 移動
	if (inputManager.isPressed('d')) pos.x += 1;
	if (inputManager.isPressed('a')) pos.x -= 1;
	if (inputManager.isPressed('s')) pos.y += 1;
	if (inputManager.isPressed('w')) pos.y -= 1;


	// 攻撃インターバル
	if (not canAttack) {
		attackTimer += Time::getInstance()->deltaTime();
		if (attackInterval <= attackTimer) {
			attackTimer = 0;
			canAttack = true;
		}
	}
	// 攻撃
	if(inputManager.isPressed(' ')) attack();

	// 画面の外には行かないように
	if (pos.x < WINDOW_ORIGIN.x) pos.x = WINDOW_ORIGIN.x;
	if (pos.y < WINDOW_ORIGIN.y) pos.y = WINDOW_ORIGIN.y;
	if (WINDOW_SIZE.x < pos.x) pos.x = WINDOW_SIZE.x;
	if (WINDOW_SIZE.y < pos.y) pos.y = WINDOW_SIZE.y;
}

void Player::attack() {
	if (canAttack) {
		obj.playerBullets.push_back(obj.bulletPoolAllocator.Alloc(pos, Vec2{ 0, -1 }, 8.0, 67, 88, 255, 'o'));
		canAttack = false;
	}
}

void Player::draw()const {
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) printf("\x1b[%d;%dH ", pos.prevY, pos.prevX); // 前の座標に' '表示
	printf("\x1b[38;2;0;130;255m\x1b[%d;%dH@", pos.y, pos.x); // 今の座標に'@'表示
	printf("\x1b[39m");
}
void Player::drawUI()const {
	// 前回の射線を消す
	// 前回と座標が異なっていれば
	if (pos.isUpdated()) {
		for (int i = WINDOW_ORIGIN.y; i < pos.prevY; i++) {
			printf("\x1b[%d;%dH ", i, pos.prevX);
		}
	}
	// 射線を描画
	int maxColor=50;
	int color;
	for (int i = pos.y-1; WINDOW_ORIGIN.y <= i; i--) {
		color = std::max(0, maxColor - (int)(-(i-(pos.y-1)) * 1.0));
		printf("\x1b[38;2;%d;%d;%dm\x1b[%d;%dH:\x1b[39m", color, color, color, i, pos.x);
	}
}