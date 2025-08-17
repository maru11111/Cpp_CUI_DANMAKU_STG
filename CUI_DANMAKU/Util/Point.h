#pragma once
#include <stdint.h>

// int型の二次元ベクトル
class Point {
public:
	// 座標が点(1, 1)から始まっていたので 1 で初期化してた.
	// ゲームの原点は点(1, 1)から変更したのでもう 1 である必要はないが, 
	// 下手に変えてバグが出ても嫌なので放置
	Point()
		: x(1), y(1), prevX(1), prevY(1)
	{}

	Point(int32_t x, int32_t y)
		: x(x), y(y), prevX(x), prevY(y)
	{}

	int32_t x;
	int32_t y;

	// 前のフレームの座標
	// 前のフレームの描画を消すために持っておく（更新は各自でやるけど...
	int32_t prevX;
	int32_t prevY;

	// 前のフレームと値が変わっていたかどうか
	bool isUpdated()const {
		return ((prevX != x) || (prevY != y));
	}

	// 必要な演算子を適宜オーバーロード
	Point operator +(const Point& rhs) {
		return { x + rhs.x, y + rhs.y };
	}
	Point& operator =(const Point& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	Point& operator +=(const Point& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
};