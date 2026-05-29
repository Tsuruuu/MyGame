#include<stdio.h>
#include<stdlib.h>
#include <conio.h>

#define UMI 0	//海
#define RIKU 1	//陸地
#define FUNE 2	//船
#define _X 50	//地図の大きさ
#define _Y 34	//地図の大きさ

#pragma warning(disable : 4996)

typedef struct pos {
	int x;
	int y;
}POS;

POS ship;
POS treasure;
int endflag = 0;	//終了フラグ
int map[_X][_Y] = { 0 };	//世界地図

void init(void);
void move(void);
void makemap(void);
void message(void);
void ending(void);

void init(void)
{
	ship.x = 3;	//船の初期位置
	ship.y = 2; //船の初期位置
	treasure.x = 26 + 10; //宝の場所
	treasure.y = 15 + 10; //宝の場所

}

void makemap(void)  //map.datからマップデータの読み込み
{
	int x, y;
	FILE* fp;

	fp = fopen("map.txt", "r");
	if (fp == NULL) {
		printf("地図ファイルのオープンに失敗しました。\n");
		exit(1);
	}

	//重要。ファイルから読み込むときはforループでY座標を先に指定すること。
	//本当はCSVファイルを読み込むにはこの方法は使わない。
	for (y = 0; y < _Y; y++) {
		for (x = 0; x < _X; x++) {
			fscanf(fp, "%d", &map[x][y]);
			if (x < _X - 1) {
				fscanf(fp, ",");
			}
		}
	}
	fclose(fp);
	map[ship.x][ship.y] = FUNE;	//船を地図に埋め込む
}

void move() //船の移動先を決める
{
	int i;
	int x, y;

	x = ship.x;
	y = ship.y;

	int key = _getch();	//これでどのキーが押されたのかを記録

	if (key == 'd') {
		if (ship.x < 49 && map[ship.x + 1][ship.y] != RIKU) {
			ship.x++;
		}
	}
	else if (key == 'a') {
		if (ship.x > 0 && map[ship.x - 1][ship.y] != RIKU) {
			ship.x--;
		}
	}
	else if (key == 'w') {
		if (ship.y > 0 && map[ship.x][ship.y - 1] != RIKU) {
			ship.y--;
		}
	}
	else if (key == 's') {
		if (ship.y < 33 && map[ship.x][ship.y + 1] != RIKU) {
			ship.y++;
		}
	}
	else if (key == '\r') {
		if (ship.x == 26 && ship.y == 15) {
			printf("南に10　東に10");
			_getch();
		}
		else if ((ship.x == treasure.x) && (ship.y == treasure.y)) {
			endflag = 1;
		}
		else {
			printf("何もない");
			_getch();
		}

	}
}

void message()
{
	system("cls"); //画面クリア
	//マップの表示
	int x, y;
	for (x = 0; x < _X; x++) { printf("--"); }
	printf("\n");
	//重要。表示の時はforループでY座標を先に指定すること。
	for (y = 0; y < _Y; y++) {
		for (x = 0; x < _X; x++) {

			if (x == ship.x && y == ship.y) {
				printf("船");
			}
			else if (map[x][y] == UMI) {
				printf("  ");
			}
			else if (map[x][y] == RIKU) {
				printf("陸");
			}
		}
		printf("\n");
	}
	for (x = 0; x < _X; x++) { printf("--"); }
	printf("\n");
	printf("w,a,s,dで移動。Enterで探索\n");
}

void ending()	//宝を発見したときのメッセージ
{
	printf("宝を見つけた!\n");
}

int main(void)
{
	init();
	while (endflag != 1) {
		makemap();
		message();
		move();
	}
	if (endflag == 1) { ending(); }
	else { printf("残念でした。\n"); }
	return(0);
}