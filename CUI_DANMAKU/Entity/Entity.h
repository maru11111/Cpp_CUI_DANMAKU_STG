#pragma once
#include "../Util/Common.h"

// 敵と弾の基底クラス
// Playerは共通点が少なかったので継承しなかった
// 継承すべきなのかは不明
class Entity
{
public:
	Entity(Point pos_);
	virtual ~Entity() = default;
	virtual void update()=0;
	virtual void draw()const = 0;
	// 削除するかを返す
	bool isDead();
	// 与えられた座標との当たり判定結果を返す
	bool intersects(Point vec2);
	// ゲームシーンでの当たり判定時に削除判定をオンにするためのセッター
	void setIsDeadFlg(bool isDeadFlg_);
	// 座標のゲッター
	Point getPos()const {
		return pos;
	}
protected:
	// 時間依存移動用タイマー
	double moveTimer = 0;
	// 時間依存攻撃用タイマー
	double attackTimer = 0;
	// 移動間隔
	double moveInterval;
	// 攻撃間隔
	double attackInterval = 0;
	// 座標
	Point pos;
	// 削除するかのフラグ
	bool isDeadFlg=false;
};

