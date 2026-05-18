//　一本道のRPG
//　攻撃する順番はランダム
//　1で進む　2で持ち物（薬草が3つ）



/*------ 自分の詳細 ------- */
//　HP 200　MP 40
//　戦闘コマンド　1攻撃　2防御　3魔法　4持ち物
//　魔法コマンド　
//　1メラ 　    ：攻撃魔法20～30ダメージ　 3MP
//　2ポイズン　	：3ターンの間、毒の10～20の持続ダメージ  4MP
//　3ラクカジャ ：3ターンの間、敵から受けるダメージを2/3にする　4MP
//　攻撃コマンドは10～20ダメージ
//　防御コマンドはダメージ半減
//　持ち物コマンドは1使う　2戻る
//　薬草は使うとHP70回復


/*------ 敵1、2の詳細 ------- */
//　HP 100
//　攻撃コマンドは10～20ダメージ


/*------ ラスボスの詳細 ------- */
//　HP 300
//　攻撃コマンドは15～25


#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void Story1(void);
void Story2(void);
void Move(struct player *p, struct enemy *e);
void UseHerb(struct player *p);
void Battle(struct player *p, struct enemy *e);
void EAttack(struct player* p, struct enemy* e,int i);
void Magic(struct player* p, struct enemy* e,int magicSel);

struct player{
	int hp;
	int mp;
	int magic[3]; //上の通りの番号で
	int move;
	int herb;
	int defUpTurn;
	int defUpNext;
};

struct enemy{
	int hp;
	int poisonTurn;
	int lastBoss;
};

struct player InItP(){
	struct player p = { 200, 40, {14,2,3},0 ,3, 0 ,0};
	return p;
}

struct enemy InItE() {
	struct enemy e = {100 , 0, 0};
	return e;
}

void Story1(void) {
	printf("魔王ニヨッテ姫ガサラワレタ\n");
	Sleep(2500);
	printf("姫ヲトリモドセ!!\n");
	Sleep(1000);
	printf("  .  \n");
	Sleep(750);
	printf("  .  \n");
	Sleep(750);
	printf("  .  \n");
	Sleep(1000);
	printf("魔王城ニツイタ!\n\n\n");
	Sleep(500);
}

void Story2(void) {
	Sleep(2500);
	printf("魔王ヲ倒シ姫ヲ取リ戻シタ!\n");
	Sleep(2500);
	printf("世界ニ再ビ平和ガ戻リ\n");
	Sleep(2500);
	printf("アナタハ静カニ暮ラシマシタ\n");
	Sleep(2500);
	printf("The END...");
}

void Move(struct player *p,struct enemy *e) {
	int i,k;

	while (1)
	{
		printf("ドウスル?\n");
		printf("HP：%d\tMP：%d\n", p->hp, p->mp);
		printf("1：進ム\t2：持チ物カクニン\t--->");

		scanf_s("%d", &i);
		if (i == 1) {		//進む
			p->move += 1;
			printf("進ンダ\n\n\n");
			Sleep(500);

			if (p->move == 2 || p->move == 5) {
				printf("敵ノ気配ガスル...\n\n\n");
			}

			if (p->move == 3 || p->move == 6) {
				printf("敵ガ現レタ!\n\n\n");
				e->hp = 100;
				Battle(p,e);  //敵と戦う時の関数
			}

			if (p->move == 9) {
				printf("魔王ノ気配ガスル...\n\n\n");
			}

			if (p->move == 10) {
				printf("魔王ガ現レタ!!\n");
				Sleep(1000);
				e->hp = 300;
				printf("最後ノ戦イダ!!\n\n\n");
				e->lastBoss = 1;
				Battle(p, e);
				break;
			}

		}else if (i == 2) {		//持ち物確認
			printf("\n\nモッテイル薬草ノ数：%d\n", p->herb);
			Sleep(500);
			printf("ツカウ?\n");

			printf("1：Yes\t2：No\t--->");
			scanf_s("%d", &k);
			if (k == 1) {	//Yesのとき
				UseHerb(p);		//薬草を使うときの関数
				Sleep(500);
			}else if (k == 2) {	//Noのとき
				printf("ツカワナカッタ\n\n\n");
				Sleep(500);
				continue;
			}
		}
	}
}

void UseHerb(struct player *p) {
	if (p->herb > 0) {
		p->herb -= 1;
		p->hp += 70;
		if (p->hp > 200) {
			p->hp = 200;
		}
		printf("HPガ%dニナッタ!\n\n\n", p->hp);
	}else{
		p->herb = 0;
		printf("薬草ヲ使イキッテシマッタ!\n\n\n");
	}
}

void Battle(struct player *p,struct enemy *e) {
	int i,attack,eDamage,pDamage;

	while (1){
		attack = rand() % 2 + 1;

		printf("ドウスル?\n");
		printf("HP：%d\tMP：%d\n", p->hp, p->mp);
		printf("1：コウゲキ\t2：ボウギョ\t3：マホウ\t4：持チ物\t--->");
		scanf_s("%d", &i);
		printf("\n\n\n");

		if (i == 1) { //攻撃を選んだ場合
			if (attack == 1) { //自分→敵の順番で攻撃
				printf("敵ヲコウゲキ!\n");
				Sleep(1000);
				eDamage = rand() % 10 + 11;
				e->hp -= eDamage; //敵に10～20ダメージ
				printf("%dノダメージヲ与エタ!\n\n\n", eDamage);
				Sleep(1500);

				if (e->hp <= 0) {
					printf("敵ヲ倒シタ!\n\n\n");
					break;
				}

				EAttack(p, e, i); //敵が攻撃するときの関数
			}
			else { //敵→自分への攻撃
				EAttack(p, e, i); //敵が攻撃するときの関数

				printf("敵ヲコウゲキ!\n");
				Sleep(1000);
				eDamage = rand() % 10 + 11;
				e->hp -= eDamage; //敵に10～20ダメージ
				printf("%dノダメージヲ与エタ!\n\n\n", eDamage);
				Sleep(1500);

				if (e->hp <= 0) {
					printf("敵ヲ倒シタ!\n\n\n");
					break;
				}
			}			
		}
		else if (i == 2) { //防御を選んだ場合
			printf("守リノ姿勢ニハイッタ\n");
			Sleep(1000);
			EAttack(p, e, i);
		}
		else if(i == 3) { //魔法を使用
			int magicSel;

			if (attack == 1) {
				printf("ドレヲ使ウ?\n");
				printf("1：メラ   2：ポイズン   3：ラクカジャ\t--->");
				scanf_s("%d", &magicSel);
				printf("\n\n\n");

				if ((magicSel == 1 && p->mp >= 3) || (magicSel == 2 && p->mp >= 4) || (magicSel == 3 && p->mp >= 4)) {
					Magic(p, e, magicSel);
				}else {
					printf("敵ヲコウゲキ!\n");
					Sleep(1000);
					printf("  .  \n");
					Sleep(750);
					printf("  .  \n");
					Sleep(750);
					printf("  .  \n");
					Sleep(750);
					printf("MPガ足リナイ!\n\n\n");
					Sleep(1000);
				}
				

				if (e->hp <= 0) {
					printf("敵ヲ倒シタ!\n\n\n");
					break;
				}

				EAttack(p, e, i);
			}
			else if (attack == 2) {
				printf("ドレヲ使ウ?\n");
				printf("1：メラ   2：ポイズン   3：ラクカジャ\t--->");
				scanf_s("%d", &magicSel);
				printf("\n\n\n");

				EAttack(p, e, i);
				if ((magicSel == 1 && p->mp >= 3) || (magicSel == 2 && p->mp >= 4) || (magicSel == 3 && p->mp >= 4)) {
					Magic(p, e, magicSel);
				}
				else {
					printf("敵ヲコウゲキ!\n");
					Sleep(1000);
					printf("  .  \n");
					Sleep(750);
					printf("  .  \n");
					Sleep(750);
					printf("  .  \n");
					Sleep(750);
					printf("MPガ足リナイ!\n\n\n");
					Sleep(1000);
				}

				if (e->hp <= 0) {
					printf("敵ヲ倒シタ!\n\n\n");
					break;
				}
			}
		}
		else if (i == 4) {
			printf("薬草ヲ使ウ\n");
			Sleep(1000);
			UseHerb(p);
			Sleep(1000);
			EAttack(p, e, i);
		}

		//毒をくらってる時のやつ
		if (e->poisonTurn > 0) {
			int poisonDamage = rand() % 11 + 10; //10～20ダメージ
			e->hp -= poisonDamage;

			printf("毒デ%dノダメージ!\n\n\n", poisonDamage);
			Sleep(1500);
			e->poisonTurn--;

			if (e->hp <= 0) {
				printf("敵ヲ倒シタ!\n\n\n");
				break;
			}

			if (e->poisonTurn == 0) {
				printf("毒ガキレタ!\n\n\n");
				Sleep(1500);
			}
		}

		//防御力アップのやつ
		if (p->defUpNext > 0) {
			p->defUpTurn = p->defUpNext;
			p->defUpNext = 0;
		}

		if (p->defUpTurn > 0) {
			p->defUpTurn--;

			if (p->defUpTurn == 0) {
				printf("ボウギョ力ガ元ニ戻ッタ!\n\n\n");
				Sleep(1500);
			}
		}

	}
}

void EAttack(struct player* p, struct enemy* e, int i) {
	int pDamage = 0;
	printf("敵ノコウゲキ!\n");
	Sleep(1000);

	if (i == 1 || i == 3 || i == 4) { //攻撃を選んだ時
		pDamage = rand() % 10 + 11; //プレイヤーに10～20ダメージ
		if (e->lastBoss == 1) {
			pDamage = rand() % 11 + 15; //魔王が攻撃した場合に15～25ダメージ
		}
	}else if (i == 2) { //防御を選んだ時
		pDamage = rand() % 5 + 6; //プレイヤーに5～10ダメージ
		if (e->lastBoss == 1) {
			pDamage = rand() % 8 + 10; //魔王が攻撃した場合に7～14ダメージ
		}
	}

	if (p->defUpTurn > 0) {//防御力アップの魔法を使っている場合
		pDamage = pDamage * 2 / 3;
	}

	printf("%dノ傷ヲ負ッタ!\n\n\n", pDamage);
	Sleep(1500);
	p->hp -= pDamage;
	if (p->hp <= 0) { //のちのち、死亡関数にしたほうが見やすくなる？
		printf("シンデシマッタ!\n");
		exit(0);
	}
}

void Magic(struct player* p, struct enemy* e, int magicCel) {
	int eDamage;

	if (magicCel == 1) { //メラのとき  攻撃魔法20～30ダメージ　 3MP
		printf("メラ!\n");
		Sleep(1000);
		eDamage = rand() % 11 + 20; //20～30ダメージ
		e->hp -= eDamage;
		p->mp -= 3;
		printf("%dノダメージヲ与エタ!\n\n\n", eDamage);
		Sleep(1500);
	}else if (magicCel == 2) { //3ターンの間、毒の10～20の持続ダメージ  4MP
		printf("ポイズン!\n");
		p->mp -= 4;
		Sleep(1000);
		printf("敵ハ毒ニカカッタ!\n\n\n");
		Sleep(1500);
		e->poisonTurn = 3;
	}else if (magicCel == 3) { //3ターンの間、敵から受けるダメージを2 / 3にする　4MP
		printf("ラクカジャ!\n");
		Sleep(1000);
		p->mp -= 4;
		printf("ボウギョ力ガ上ガッタ!\n\n\n");
		Sleep(1500);
		p->defUpNext = 4;
	}
}

int main(){
	struct player p = InItP();
	struct enemy e = InItE();
	Story1();
	Move(&p,&e);
	Story2();
}