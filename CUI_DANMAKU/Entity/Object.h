#pragma once

#include "Enemy.h"
#include "Bullet.h"
#include "../Util/PoolAllocator.h"

// ゲーム中の敵と弾を管理するための構造体
struct Object {
	// 弾のメモリプール
	// 実測したら一度で最大100個くらい弾が出ていたので, 余裕をもって200個にしておく
	PoolAllocator<Bullet, 200> bulletPoolAllocator;

	// 敵のリスト
	std::vector<std::unique_ptr<Enemy>>enemies;
	// メモリプールで確保した敵弾のアドレスを保管するリスト
	std::vector<Bullet*>enemyBullets;
	// メモリプールで確保したプレイヤー弾のアドレスを保管するリスト
	std::vector<Bullet*>playerBullets;
};
