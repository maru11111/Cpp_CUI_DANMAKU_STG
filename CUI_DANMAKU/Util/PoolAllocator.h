#pragma once

#include<vector>
#include<iostream>

/* === プールアロケータ === */
// 課題で出したものでは引数ありのコンストラクタを呼べなかったため, 可変長引数に変更した。
// O(1)でAlloc, Freeができる

template<class T, size_t MAXSIZE> class PoolAllocator
{
public:
	// コンストラクタ
	PoolAllocator() {
		// 初めはすべてのメモリを使える
		for (int i = 0; i < MAXSIZE; i++) {
			availableList.push_back((T*)(&memories[i]));
		}

		// フラグを初期化
		for (int i = 0; i < MAXSIZE; i++) {
			isUsed[i] = false;
		}
	}

	// デストラクタ
	~PoolAllocator() {
		// まだfreeされてないメモリのデストラクタを呼ぶ
		for (int i = 0; i < MAXSIZE; i++) {
			if (isUsed[i] == true) {
				((T*)(&memories[i]))->~T();
			}
		}
	}

	// 確保できない場合はnullptrを返す事。
	// 引数ありのコンストラクタを呼ぶため、可変長引数に変更した。
	template <class... Args>
	T* Alloc(Args... args) {
		// 確保できない場合
		if (availableList.empty()) {
			// nullptrを返す
			return nullptr;
		}

		// 確保できる場合
		// 次に確保する番地を取得
		T *nextAddr = availableList.back();

		// 次に確保する番地は利用可能リストから除く
		availableList.pop_back();

		// デフォルトコンストラクタで初期化しておく（placement new
		nextAddr = new(nextAddr) T(args...);
		
		// 使用中フラグを立てる
		// (アドレスから何番目の要素か計算）
		isUsed[nextAddr - (T*)memories] = true;

		// 使える番地を渡す
		return nextAddr;
	}

	// Free(nullptr)で誤動作しないようにする事。
	void Free(T* Addr) {
		// nullptrの開放を防ぐ
		if (Addr == nullptr) return;
	
		// 解放した番地を利用可能リストに入れる
		availableList.push_back(Addr);

		// 使用中フラグを下ろす
		isUsed[Addr - (T*)memories] = false;

		// デストラクタを呼ぶ
		Addr->~T();

		return;
	}

private:
	struct Memory {
		char size[sizeof(T)]; // 初期化時にコンストラクタが呼ばれないよう、Tのサイズ分のメモリだけ確保する
	};

	// 管理するメモリ
	Memory memories[MAXSIZE];

	// メモリが解放されているかのフラグ（デストラクタを呼ぶかの判定に使用
	bool isUsed[MAXSIZE];

	// 利用可能リスト
	std::vector<T*> availableList;
};
