#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Character {
	char* symbol;
	short x;
	short y;
	int hp;
	int atk;
	int def;
	int luk;
}Obj;

void DrawObject(Obj obj);
void DrawTable();
void MoveCursor(short x, short y, const char* str);
int battle(Obj player, Obj mob, int mobCount);

Obj player = {
(char*)"♥", 3, 3, 50, 10, 10, 10 };

Obj mob[3] = {
	{(char*)"◆", 9, 5, 50, rand()%10+1, rand()%30+1, rand()%10+1 },
	{(char*)"◆", 10, 3, 30, rand()%10+1, rand()%20+1, rand()%10+1 },
	{(char*)"◆", 3, 8, 20, rand()%20+1, rand()%10+1, rand()%30+1 }
};
int count;

int main() {
	srand(time(0));
	DrawTable();

	while (count<3)
	{
		char key = getch();
		_getch();

		if (key == 'q')
			break;
		switch (key) {
		case 'w': player.y--; break;
		case 'a': player.x--; break;
		case 's': player.y++; break;
		case 'd': player.x++; break;
		default:break;
		}

		system("cls");
		DrawTable();
		DrawObject(player);
		for (int i = 0; i < 3; i++) {
			DrawObject(mob[i]);
			if (player.x == mob[i].x && player.y == mob[i].y && mob[i].hp > 0) {
				//battle(player, mob[i], i);
				if (battle(player, mob[i], i) == i) {
					mob[i].symbol = (char*)"  ";
					count++;
				}
			}
		}
	}
	for (int i = 60; i > 20; i--) {
		system("cls");
		MoveCursor(i,1,"      ::::::::   :::        ::::::::::      :::      ::::::::: \n");
		MoveCursor(i,2,"    :+:    :+:  :+:        :+:           :+: :+:    :+:    :+: \n");
		MoveCursor(i,3,"   +:+         +:+        +:+          +:+   +:+   +:+    +:+  \n");
		MoveCursor(i,4,"  +#+         +#+        +#++:++#    +#++:++#++:  +#++:++#:    \n");
		MoveCursor(i,5," +#+         +#+        +#+         +#+     +#+  +#+    +#+    \n");
		MoveCursor(i,6,"#+#    #+#  #+#        #+#         #+#     #+#  #+#    #+#     \n");
		MoveCursor(i,7,"########   ########## ##########  ###     ###  ###    ###      \n");
		//Sleep(500);
	}


	return 0;
}

void DrawObject(Obj obj)
{
	MoveCursor(obj.x, obj.y, obj.symbol);

}

int battle(Obj player, Obj mob,int mobCount) {
	srand(time(0));
	int turn = 2;
	while (mob.hp > 0 && player.hp > 0) {
		if (turn % 2 == 0) { // player turn
			MoveCursor(2, 27, "Player Turn");
			if (mob.luk >= rand() % 200 + 1) {
				MoveCursor(2, 25, "Miss!                                                                                           ");
			}
			else {
				if (player.luk >= rand() % 50 + 1) { // 치명타, 방어력 무시
					mob.hp -= player.atk;
					MoveCursor(2, 25, "");
					printf("치명타! %d만큼의 대미지를 입혔습니다.   남은 체력: %d                                                  ", player.atk, mob.hp);
				}
				else {
					mob.hp -= player.atk - (player.atk * mob.def / 100); // 방어력% 만큼 공격 대미지 감쇠
					MoveCursor(2, 25, ""); 
					printf("유효타! %d만큼의 대미지를 입혔습니다.   남은 체력: %d                                               ", player.atk - (player.atk * mob.def / 100), mob.hp);
				}
			}
		}
		else { //mob turn
			MoveCursor(2, 27, "Enemy Turn  ");
			if (player.luk >= rand() % 50 + 1) {
				MoveCursor(2, 25, "Miss!                                    ");
			}
			else {
				if (player.luk >= rand() % 50 + 1) { // 치명타, 방어력 무시
					player.hp -= mob.atk;
					MoveCursor(2, 25, "");
					printf("치명타! %d만큼의 대미지를 입었습니다.  남은 체력: %d                                                 ", mob.atk, player.hp);
				}
				else {
					player.hp -= mob.atk - (mob.atk * player.def / 100); // 방어력% 만큼 공격 대미지 감쇠
					MoveCursor(2, 25, "");
					printf("유효타! %d만큼의 대미지를 입었습니다.  남은 체력: %d                                                 ", mob.atk - (mob.atk * player.def / 100), player.hp);
				}
			}
		}
		MoveCursor(0, 20, "Cur HP");
		for (int i = 0; i < player.hp; i++) {
			MoveCursor(i + 8, 20, "");
			printf("|           ");
		}
		MoveCursor(0, 23, "Mob HP");
		for (int i = 0; i < mob.hp; i++) {
			MoveCursor(i + 8, 23, "");
			printf("|           ");
		}
		Sleep(2000);
		turn++;
	}
	if (mob.hp < 1) {
		mob.symbol = (char*)" ";
		MoveCursor(2, 25, "Enemy Slayered!");
	}
	else if(player.hp <= 0) {
		MoveCursor(4, 2, "  ::::::::      :::     ::::    ::::  ::::::::::   ::::::::  :::     ::: :::::::::: :::::::::  ");
		MoveCursor(4, 3, " :+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:         :+:    :+: :+:     :+: :+:        :+:    :+: ");
		MoveCursor(4, 4, " +:+         +:+   +:+  +:+ +:+:+ +:+ +:+         +:+    +:+ +:+     +:+ +:+        +:+    +:+ ");
		MoveCursor(4, 5, " :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#    +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  ");
		MoveCursor(4, 6, " +#+   +#+# +#+     +#+ +#+       +#+ +#+         +#+    +#+  +#+   +#+  +#+        +#+    +#+ ");
		MoveCursor(4, 7, " #+#    #+# #+#     #+# #+#       #+# #+#         #+#    #+#   #+#+#+#   #+#        #+#    #+# ");
		MoveCursor(4, 8, "  ########  ###     ### ###       ### ##########   ########      ###     ########## ###    ### ");
	}
	return mobCount;
}

void DrawTable()
{
	//MoveCursor(2, 20, "HP");
	//for (int i = 0; i < player.hp; i++) {
	//	MoveCursor(i + 5, 20, "|");
	//}
}

void MoveCursor(short x, short y, const char * str)
{
	COORD coord = { x,y }; //Coordnation: 좌표
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
	printf("%s", str);
}


// 과제

// 네모판 안에 플레이어, 몬스터 n마리
// 몬스터와 만나면 전투 시작 (턴제)
// struct 공 방 회피 HP