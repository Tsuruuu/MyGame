//ダンジョン探索ゲーム
//$はコインのマーク。これを全部取らないとクリアにならない
//マップのコインを取りきるとドアが開いて次のステージに進める

// ------ マップの詳細 ---------//
/*
P：プレイヤー。上下左右に動ける
E：敵。当たるとゲームオーバーになる。上下左右に動ける
#：これ以上先に進めない壁
.：道。プレイヤーも敵も進める
$：コイン。ランダムに配置される。これを取らないと次のマップに進めない
D：別のマップに行くためのドア
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 11		//マップの大きさ
#define WIDTH 35
#define HEIGHT 11
#define ENEMY_COUNT 5 //敵の数
#define COIN_COUNT 3  //コインの数
#define MAP_NUMBER 2  //マップの数

//座標構造体
typedef struct {
	int x;
	int y;
}POS;

//グローバル変数
char map[MAP_NUMBER][HEIGHT][WIDTH] = {
	"##################################",
	"#......#.........................D",
	"#......#....................######",
	"#......#.........................#",
	"#......########...........#......#",
	"#.........................#......#",
	"#....##..............#....#......#",
	"#..........####......#...##...#..#",
	"#....................#........#..#",
	"#....................#...........#",
	"##################################"
};

int game_running = 1;	//ゲームの実行フラグ
POS player;				//砲台の位置
POS enemy[MAP_NUMBER][ENEMY_COUNT];	//敵の数と位置
POS coin[MAP_NUMBER][COIN_COUNT];
int coinAlive[COIN_COUNT]; //コインがマップに残っているかを表す。1:まだある　0:取った
int currentMap = 0;

//関数プロトタイプ
void initialize(void);
void update_map(void);
void draw_map(void);
void handle_input(void);

//初期化処理
void initialize(void) {
	srand((unsigned)time(NULL));

	//マップの生成
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

		}
	}

	//敵の初期化
	for (int mapNumber = 0; mapNumber < MAP_NUMBER; mapNumber++) {
		for (int i = 0; i < ENEMY_COUNT; i++) {

			do {
				enemy[mapNumber][i].x = rand() % (WIDTH - 2) + 1;
				enemy[mapNumber][i].y = rand() % (HEIGHT - 2) + 1;

			} while (map[mapNumber][enemy[mapNumber][i].y][enemy[mapNumber][i].x] == '#');
		}
	}

	//プレイヤーの初期化
	player.x = 2;
	player.y = 9;

	//コインの初期化
	for (int mapNumber = 0; mapNumber < MAP_NUMBER; mapNumber++) {
		for (int i = 0; i < COIN_COUNT; i++) {
			do {
				coin[mapNumber][i].x = rand() % (WIDTH - 2) + 1;
				coin[mapNumber][i].y = rand() % (HEIGHT - 2) + 1;
			} while (map[mapNumber][coin[mapNumber][i].y][coin[mapNumber][i].x] == '#');

			coinAlive[i] = 1;
		}
	}
}

//マップの更新
void update_map(void) {

}

//マップの描画
void draw_map(void) {
	system("cls");	//画面をいったんクリアにしてくれる

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

			//敵が存在したらenemyHereを1にする×ENEMY_COUNT
			int enemyHere = 0;
			for (int i = 0; i < ENEMY_COUNT; i++) {
				if (x == enemy[currentMap][i].x && y == enemy[currentMap][i].y) {
					enemyHere = 1;
				}
			}

			//コインが存在したらcoinHereを1にする×coinHere
			int coinHere = 0;
			int remainCoin = 0;  //マップに残ってるコインがあるか記憶
			for (int i = 0; i < COIN_COUNT; i++) {
				if (coinAlive[i] && x == coin[currentMap][i].x && y == coin[currentMap][i].y) {
					coinHere = 1;
				}

				if (coinAlive[i] && coin[currentMap][i].x == player.x && coin[currentMap][i].y == player.y) {
					coinAlive[i] = 0;
				}

				if (coinAlive[i]) {
					remainCoin++;
				}
			}

			if (remainCoin == 0) {
				game_running = 0;
			}

			if (x == player.x && y == player.y) {
				printf("P");
			}
			else if (enemyHere) {
				printf("E");
			}
			else if(coinHere){
				printf("$");
			}
			else {
				printf("%c", map[currentMap][y][x]);
			}

		}
		printf("\n");
	}
}

//入力処理
void handle_input(void) {
	int key = _getch();	//これでどのキーが押されたのかを記録

	if (key == 'd') {
		if (map[currentMap][player.y][player.x + 1] != '#') {  //[player.x + 1]←これはプレイヤーの右隣を参照してるから+1をしてる（右隣が壁なら進まない）
			player.x++;
		}
	}
	else if (key == 'a') {
		if (map[currentMap][player.y][player.x - 1] != '#') {
			player.x--;
		}
	}
	else if (key == 'w') {
		if (map[currentMap][player.y - 1][player.x] != '#') {
			player.y--;
		}
	}
	else if (key == 's') {
		if (map[currentMap][player.y + 1][player.x] != '#') {
			player.y++;
		}
	}
	else if (key == '0') {
		game_running = 0;
	}

	//敵の移動(ランダム)
	for (int i = 0; i < ENEMY_COUNT; i++) {
		int move = rand() % 4;
		//横移動
		if (move == 0 && enemy[currentMap][i].x < WIDTH - 2 && map[currentMap][enemy[currentMap][i].y][enemy[currentMap][i].x + 1] != '#') {
			enemy[currentMap][i].x++;
		}
		else if (move == 1 && enemy[currentMap][i].x > 1 && map[currentMap][enemy[currentMap][i].y][enemy[currentMap][i].x - 1] != '#') {
			enemy[currentMap][i].x--;
		}

		//縦移動
		else if (move == 2 && enemy[currentMap][i].y > 0 && map[currentMap][enemy[currentMap][i].y - 1][enemy[currentMap][i].x] != '#') {
			enemy[currentMap][i].y--;//上に移動
		}
		else if (move == 3 && enemy[currentMap][i].y < HEIGHT - 2 && map[currentMap][enemy[currentMap][i].y + 1][enemy[currentMap][i].x] != '#') {
			enemy[currentMap][i].y++; //下に移動
		}

	}
}

//メイン関数
int main(void) {
	initialize();

	update_map();
	draw_map();
	//printf("\n\n0で終了");

	while (game_running) {
		handle_input();
		update_map();
		draw_map();
	}

	printf("CLEAR!\n");
	printf("ゲーム終了\n");
	return 0;
}