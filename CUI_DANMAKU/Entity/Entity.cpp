#include "Entity.h"

Entity::Entity(Point pos_)
	: pos{ pos_ }
{}


bool Entity::isDead() {
	if (isDeadFlg) return true;
	if (pos.x < WINDOW_ORIGIN.x) return true;
	if (pos.y < WINDOW_ORIGIN.y) return true;
	if (WINDOW_SIZE.x < pos.x) return true;
	if (WINDOW_SIZE.y < pos.y) return true;
	return false;
}

// ゲームシーンで当たり判定を取るときに使う
// もっといいやり方がありそうだが思いつかなかった
void Entity::setIsDeadFlg(bool isDeadFlg_) {
	isDeadFlg = isDeadFlg_;
}

bool Entity::intersects(Point vec2) {
	return ((pos.x == vec2.x) && (pos.y == vec2.y));
}