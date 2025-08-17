#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneManager& sceneManager_, InputManager& inputManager_)
	: Scene{ sceneManager_, inputManager_ }
	, player(Point((int)(WINDOW_SIZE.x/2), (int)(WINDOW_SIZE.y/2)), obj, inputManager)
{
	//敵が初めに出現する時間をランダムに決める
	std::uniform_int_distribution<int> dist(0, 5);
	norSpawnTimer = dist(rd);
	holSpawnTimer = dist(rd);
	cirSpawnTimer = dist(rd);
}

void GameScene::update() {
	/* === 更新 === */
	// 経過時間計測
	timer += Time::getInstance()->deltaTime();
	// 敵を出現させる
	spawnEnemy();
	// 経過時間によるスコア加算
	sceneManager.score += 1.5 * Time::getInstance()->deltaTime();
	// プレイヤー更新
	player.update();
	// プレイヤー弾更新
	for (auto& bullet : obj.playerBullets) {
		bullet->update();
	}
	// 敵更新
	for (auto& enemy:obj.enemies) {
		enemy->update();
	}
	// 敵弾更新
	for (auto& bullet : obj.enemyBullets) {
		bullet->update();
	}


	/* === 当たり判定 === */
	// プレイヤー vs 敵弾
	for (auto& bullet : obj.enemyBullets) {
		if (player.intersects(bullet->getPos())) {
			bullet->setIsDeadFlg(true);
			player.isDead = true;
		}
	}
	// 敵 vs プレイヤー弾
	for (auto& bullet : obj.playerBullets) {
		for (auto& enemy : obj.enemies) {
			// すり抜け対策で一つ前の座標も調べる
			if (enemy->intersects(bullet->getPos()) || enemy->intersects(Point{ bullet->getPos().prevX, bullet->getPos().prevY })) {
				bullet->setIsDeadFlg(true);
				enemy->setIsDeadFlg(true);
				// スコア加算
				sceneManager.score += enemy->getScore();
			}
		}
	}


	/* === 削除 === */ 
	// 敵の削除
	for (int i = 0; i < obj.enemies.size(); i++) {
		if (obj.enemies[i]->isDead()) {
			printf("\x1b[%d;%dH ", obj.enemies[i]->getPos().prevY, obj.enemies[i]->getPos().prevX); // 前の座標に' '表示
			// メモリアロケータの時はFreeにする			
			obj.enemies.erase(obj.enemies.begin() + i);
			i--;
		}
	}
	// 敵弾の削除
	for (int i = 0; i < obj.enemyBullets.size(); i++) {
		if (obj.enemyBullets[i]->isDead()) {
			printf("\x1b[%d;%dH ", obj.enemyBullets[i]->getPos().prevY, obj.enemyBullets[i]->getPos().prevX); // 前の座標に' '表示
			// メモリプールでFree
			obj.bulletPoolAllocator.Free(obj.enemyBullets[i]);
			// 解放済みのポインタをリストから削除
			obj.enemyBullets.erase(obj.enemyBullets.begin() + i);
			i--;
		}
	}
	// プレイヤー弾の削除
	for (int i = 0; i < obj.playerBullets.size(); i++) {
		if (obj.playerBullets[i]->isDead()) {
			printf("\x1b[%d;%dH ", obj.playerBullets[i]->getPos().prevY, obj.playerBullets[i]->getPos().prevX); // 前の座標に' '表示
			// メモリプールでFree
			obj.bulletPoolAllocator.Free(obj.playerBullets[i]);
			// 解放済みのポインタをリストから削除
			obj.playerBullets.erase(obj.playerBullets.begin() + i);
			i--;
		}
	}

	// タイトルに戻る
	if (inputManager.isPressed('q')) {
		// 画面をクリア
		for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
			for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
				printf("\x1b[%d;%dH ", k, i);
			}
		}
		sceneManager.changeScene(std::make_unique<TitleScene>(sceneManager, inputManager));
	}

	// リザルトに進む
	if (player.isDead || 1000<=sceneManager.score || inputManager.isPressed('R')) {
		sceneManager.changeScene(std::make_unique<ResultScene>(sceneManager, inputManager));
	}
}

void GameScene::spawnEnemy() {
	// タイマーを動かす
	norSpawnTimer += Time::getInstance()->deltaTime();
	holSpawnTimer += Time::getInstance()->deltaTime();
	cirSpawnTimer += Time::getInstance()->deltaTime();
	// ボスの出現は 30秒 経ってから
	if(30<=timer) bossSpawnTimer += Time::getInstance()->deltaTime();

	// 縦に動く敵
	if (norSpawnItval <= norSpawnTimer) {
		norSpawnTimer -= norSpawnItval;
		std::uniform_int_distribution<int> distX(WINDOW_ORIGIN.x, WINDOW_SIZE.x);
		obj.enemies.push_back(std::make_unique<NormalEnemy>(Point{ distX(rd), WINDOW_ORIGIN.y }, Point{0, 1}, obj));
	}

	// 横に動く敵
	if (holSpawnItval <= holSpawnTimer) {
		holSpawnTimer -= holSpawnItval;
		std::uniform_int_distribution<int> distLR(0, 1);
		std::uniform_int_distribution<int> distY(WINDOW_ORIGIN.y, WINDOW_ORIGIN.y+3);

		int32_t spawnPosX;
		Point moveDir;
		if (distLR(rd) == 0) { spawnPosX = WINDOW_ORIGIN.x; moveDir = { 1, 0 }; }
		else { spawnPosX = WINDOW_SIZE.x; moveDir = { -1, 0 }; }

		obj.enemies.push_back(std::make_unique<HorizontalMoveEnemy>(Point{ spawnPosX, distY(rd)}, moveDir, obj));
	}

	// 円状に弾を発射する敵
	if (cirSpawnItval <= cirSpawnTimer) {
		cirSpawnTimer -= cirSpawnItval;
		std::uniform_int_distribution<int> distX(WINDOW_ORIGIN.x, WINDOW_SIZE.x);
		obj.enemies.push_back(std::make_unique<CircleEnemy>(Point{ distX(rd), WINDOW_ORIGIN.y }, obj));
	}

	// ボス
	if (bossSpawnItval <= bossSpawnTimer) {
		bossSpawnTimer -= bossSpawnItval;
		std::uniform_int_distribution<int> distX(WINDOW_ORIGIN.x, WINDOW_SIZE.x);
		obj.enemies.push_back(std::make_unique<BossCircleEnemy>(Point{ distX(rd), WINDOW_ORIGIN.y }, obj));
	}

	//// ランダムに出現 
	//std::uniform_int_distribution<int> dist(0, (int)Enemy::EnemyKind::LAST - 1);
	//switch ((Enemy::EnemyKind)dist(rd)) {
	//case Enemy::EnemyKind::Normal:
	//	obj.enemies.push_back(std::make_unique<NormalEnemy>(Point{ (int)(WINDOW_SIZE.x / 2), 4 }, obj));
	//	break;

	//case Enemy::EnemyKind::HorizontalMove:
	//	obj.enemies.push_back(std::make_unique<HorizontalMoveEnemy>(Point{ (int)(WINDOW_SIZE.x / 2), 4 }, Point{ 1, 0 }, obj));
	//	break;

	//case Enemy::EnemyKind::Circle:
	//	obj.enemies.push_back(std::make_unique<CircleEnemy>(Point{ (int)(WINDOW_SIZE.x / 2), 4 }, obj));
	//	break;

	//case Enemy::EnemyKind::BossCircle:
	//	obj.enemies.push_back(std::make_unique<BossCircleEnemy>(Point{ (int)(WINDOW_SIZE.x / 2), 4 }, obj));
	//	break;
	//}	
}

void GameScene::draw()const {
	// カーソルを左上に移動
	std::cout << "\033[H";

	// 描画
	//プレイヤーUI
	player.drawUI();
	// 敵弾
	for (auto& bullet : obj.enemyBullets) {
		bullet->draw();
	}
	// 敵
	for (auto& enemy : obj.enemies) {
		enemy->draw();
	}
	// プレイヤー弾
	for (auto& bullet : obj.playerBullets) {
		bullet->draw();
	}
	// プレイヤー
	player.draw();

	// 移動可能範囲の枠を描画
	for (int i = TERMINAL_WINDOW_ORIGIN.x; i < TERMINAL_WINDOW_SIZE.x; i++) {
		for (int k = TERMINAL_WINDOW_ORIGIN.y; k < TERMINAL_WINDOW_SIZE.y; k++) {
			// 上面
			if (k == WINDOW_ORIGIN.y - 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
				printf("\x1b[%d;%dH~", k, i);
			//下面
			if (k == WINDOW_SIZE.y + 1 && (WINDOW_ORIGIN.x - 1 < i && i < WINDOW_SIZE.x + 1))
				printf("\x1b[%d;%dH-", k, i);
			// 左面
			if (i == WINDOW_ORIGIN.x - 1 && (WINDOW_ORIGIN.y - 1 < k && k < WINDOW_SIZE.y + 1))
				printf("\x1b[%d;%dH:", k, i);

			// 右面
			if (i == WINDOW_SIZE.x + 1 && (WINDOW_ORIGIN.x - 1 < k && k < WINDOW_SIZE.y + 1))
				printf("\x1b[%d;%dH:", k, i);
		}
	}

	// パラメータ表示
	//printf("\x1b[%d;%dH     【パラメータ】", 7, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH    ==================", 4, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH    ・経過時間：%.2lf", 5, WINDOW_SIZE.x + 2 + 1, timer);
	if (sceneManager.score < 200) printf("\x1b[38;2;121;156;190m"); // 青
	else if (sceneManager.score < 500) printf("\x1b[38;2;121;190;153m"); // 緑
	else if (sceneManager.score < 1000) printf("\x1b[38;2;213;132;76m"); // 橙色
	else if (sceneManager.score < 1900) printf("\x1b[38;2;210;89;93m"); // 赤
	else printf("\x1b[38;2;167;121;190m"); // 紫
	printf("\x1b[%d;%dH    ・スコア：%d", 6, WINDOW_SIZE.x + 2 + 1, (int)sceneManager.score);
	printf("\x1b[39m");
	printf("\x1b[%d;%dH    ==================", 7, WINDOW_SIZE.x + 2 + 1);

	// 敵のスコアを表示
	printf("\x1b[%d;%dH    ---【ターゲット】---", 9, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;178;140;140m         １：100点", 10, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;178;110;110m         ２：150点", 11, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;188;80;80m         ３：200点", 12, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;188;40;40m         ４：1000点", 13, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[39m");
	printf("\x1b[%d;%dH    --------------------", 14, WINDOW_SIZE.x + 2 + 1);

	// ランク
	printf("\x1b[%d;%dH     ---【ランク表】---", 15, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH\x1b[38;2;121;156;190m   0～199", 16, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;121;190;153m 200～499", 17, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;213;132;76m 500～999", 18, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;210;89;93m1000～1899", 19, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[%d;%dH\x1b[38;2;167;121;190m1900～", 20, WINDOW_SIZE.x + 2 + 9);
	printf("\x1b[39m");
	printf("\x1b[%d;%dH     ------------------", 21, WINDOW_SIZE.x + 2 + 1);

	// 遊び方
	printf("\x1b[%d;%dH        【遊び方】", 23, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH ・弾に当たるとGAME OVER！", 24, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH ・敵を倒すとスコアが上昇！", 25, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH・スコアに応じて\x1b[38;2;121;156;190m青\x1b[39m～\x1b[38;2;167;121;190m紫\x1b[39mまでの", 26, WINDOW_SIZE.x + 2);
	printf("\x1b[%d;%dH    ランクがつくぞ！", 27, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH・\x1b[38;2;188;60;60m1000点\x1b[39m以上を取ったらクリア！", 28, WINDOW_SIZE.x + 2);

	// 操作方法
	printf("\x1b[%d;%dH      【操作方法】", 30, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH     ・WASDで移動！", 31, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH     ・SPACEで攻撃！", 32, WINDOW_SIZE.x + 2 + 1);
	printf("\x1b[%d;%dH    ・Qでタイトルへ", 33, WINDOW_SIZE.x + 2 + 1);

}