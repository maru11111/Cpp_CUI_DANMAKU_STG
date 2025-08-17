#pragma once
#include<chrono>

// 前のフレームからの経過時間(s)を取得するため
// (時間を測るため)のクラス
// シングルトン
class Time {
public:
    // インスタンスを返す。
    // インスタンスが生成されてなければ生成する
    static Time* getInstance() {
        if (instance == nullptr) {
            instance = new Time();
        }
        return instance;
    }

    // メインループで動かして現在時刻を取得するための関数
    void update() {
        prev = now;
        now = std::chrono::system_clock::now();
    }

    // 前のフレームからの経過時間(s)を返す
    double deltaTime() {
        return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count() / 1000000.0);
    }

private:
    Time() {
        now = std::chrono::system_clock::now();
        prev = now;
    }

    //時間計測用
    std::chrono::system_clock::time_point prev, now;

    // インスタンス
    static Time* instance;
};
