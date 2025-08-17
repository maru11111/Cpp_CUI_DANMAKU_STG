#pragma once
#include <cmath>

// double型の二次元ベクトルを扱えるクラス
class Vec2 {
public:
	// 座標が点(1, 1)から始まっていたので 1 で初期化してた
	// ゲームの原点は点(1, 1)から変更したのでもう 1 である必要はないが, 
	// 下手に変えてバグが出ても嫌なので放置
	Vec2()
		: x(1), y(1)
	{}

	Vec2(double x, double y)
		: x(x), y(y)
	{}

	double x;
	double y;

	// 必要な演算子を適宜オーバーロード
	Vec2 operator +(const Vec2& rhs) {
		return { x + rhs.x, y + rhs.y };
	}
	Vec2 operator *(const double rhs) {
		return { x * rhs, y * rhs };
	}
	Vec2& operator +=(const Vec2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
};