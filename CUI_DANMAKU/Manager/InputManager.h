#pragma once
#include <conio.h>
#include <vector>
#include <mutex>
#include <thread>

// 入力を受け取れるクラス
// 入力以外の処理と同期して動かせる
class InputManager
{
public:
	InputManager() = default;
	// 入力スレッドを終了させる
	~InputManager() {
		stop();
	}
	
	// 入力受け取りを開始するときに呼び出すメソッド
	void start() {
		// スレッド起動
		inputThread = std::thread(&InputManager::inputKeyThreadFunc, this);
	}

	// 入力受け取りを終了するとき位呼び出すメソッド
	void stop() {
		// スレッドのwhileループを終了
		isEnded = true;
		// スレッドを起動しているか確認
		if (inputThread.joinable()) {
			// スレッドの終了を待つ
			inputThread.join();
		}
	}

	// keyが押されていたか返す
	bool isPressed(char key) {
		std::lock_guard<std::mutex>lock(mtx);
		if (input.empty()) {
			return false;
		}

		for (int i = 0; i < input.size(); i++) {
			if (input[i] == key) {
				input.clear();
				return true;
			}
		}
		
		return false;
	}

private:
	// 同期処理で呼び出す関数
	void inputKeyThreadFunc() {
		// stop()が呼ばれるまで無限ループ
		while (not isEnded) {
			// 入力があれば
			if (_kbhit()) {
				int i = _getch();
				// ロック
				std::lock_guard<std::mutex>lock(mtx);
				// maxInput以上なら古いものを消す
				if (maxInput < input.size()) {
					input.erase(input.begin());
				}
				// 入力を受け取る
				input.push_back((char)i);
			}
		}
	}

	// 保持しておく入力の最大数
	const int maxInput=5;
	// 保持している入力
	std::vector<char> input;
	// キー取得中に入力、またはキー入力中に取得されないようにする
	std::mutex mtx;
	// スレッドを終了させるためのフラグ
	bool isEnded=false;
	// 同期処理のためのスレッドを自身で持っておく
	std::thread inputThread;
};

