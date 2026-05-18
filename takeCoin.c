/*
問題3
Tsurunaga Saku
2026.05.
*/

//ダンジョン探索ゲーム
//Gに行ってEnterキーを押すと別のフロアに行ける
//@はコインのマーク。これを全部取らないとクリアにならない

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 11		//マップの大きさ
#define WIDTH 35
#define HEIGHT 11
#define ENEMY_COUNT 5 //敵の数
#define COIN_COUNT 3

//座標構造体
typedef struct {
	int x;
	int y;
}POS;

//グローバル変数
char map1[HEIGHT][WIDTH] = {
	"##########G#######################",
	"#......#.........................#",
	"#......#....................######",
	"#......#.........................#",
	"#......########...........#......#",
	"#.........................#......#",
	"#....##..............#....#......G",
	"#..........####......#...##...#..#",
	"#....................#........#..#",
	"#....................#...........#",
	"##################################"
};

int game_running = 1;	//ゲームの実行フラグ
POS player;				//砲台の位置
POS enemy[ENEMY_COUNT];	//敵の数と位置
POS coin[COIN_COUNT];
int coinAlive[COIN_COUNT]; //コインがマップに残っているかを表す。1:まだある　2:取った

//関数プロトタイプ
void initialize(void);
void update_map(void);
void draw_map(void);
void handle_input(void);
int check_hit(void);

//初期化処理
void initialize(void) {
	srand((unsigned)time(NULL));

	//マップの生成
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

		}
	}

	//敵の初期化
	for (int i = 0; i < ENEMY_COUNT; i++) {

		do {
			enemy[i].x = rand() % (WIDTH - 2) + 1;
			enemy[i].y = rand() % (HEIGHT - 2) + 1;

		} while (map1[enemy[i].y][enemy[i].x] == '#');
	}

	//プレイヤーの初期化
	player.x = 2;
	player.y = 9;

	//コインの初期化
	for (int i = 0; i < COIN_COUNT; i++) {
		do {
			coin[i].x = rand() % (WIDTH - 2) + 1;
			coin[i].y = rand() % (HEIGHT - 2) + 1;
		} while (map1[coin[i].y][coin[i].x] == '#');

		coinAlive[i] = 1;
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

			int enemyHere = 0;
			for (int i = 0; i < ENEMY_COUNT; i++) {
				if (x == enemy[i].x && y == enemy[i].y) {
					enemyHere = 1;
				}
			}

			int coinHere = 0;
			for (int i = 0; i < COIN_COUNT; i++) {
				if (x == coin[i].x && y == coin[i].y) {
					coinHere = 1;
				}
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
				printf("%c", map1[y][x]);
			}

		}
		printf("\n");
	}
}

//入力処理
void handle_input(void) {
	int key = _getch();	//これでどのキーが押されたのかを記録

	if (key == 'd') {
		if (map1[player.y][player.x + 1] != '#') {  //[player.x + 1]←これはプレイヤーの右隣を参照してるから+1をしてる（右隣が壁なら進まない）
			player.x++;
		}
	}
	else if (key == 'a') {
		if (map1[player.y][player.x - 1] != '#') {
			player.x--;
		}
	}
	else if (key == 'w') {
		if (map1[player.y - 1][player.x] != '#') {
			player.y--;
		}
	}
	else if (key == 's') {
		if (map1[player.y + 1][player.x] != '#') {
			player.y++;
		}
	}
	else if (key == '0') {
		game_running = 0;
	}
	else {}

	//敵の移動(ランダム)
	for (int i = 0; i < ENEMY_COUNT; i++) {
		int move = rand() % 4;
		//横移動
		if (move == 0 && enemy[i].x < WIDTH - 2 && map1[enemy[i].y][enemy[i].x + 1] != '#') {
			enemy[i].x++;
		}
		else if (move == 1 && enemy[i].x > 1 && map1[enemy[i].y][enemy[i].x - 1] != '#') {
			enemy[i].x--;
		}

		//縦移動
		else if (move == 2 && enemy[i].y > 0 && map1[enemy[i].y - 1][enemy[i].x] != '#') {
			enemy[i].y--;//上に移動
		}
		else if (move == 3 && enemy[i].y < HEIGHT - 2 && map1[enemy[i].y + 1][enemy[i].x] != '#') {
			enemy[i].y++; //下に移動
		}
	}
}


//ヒット判定
int check_hit(void) {
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

	printf("ゲーム終了\n");
	return 0;
}