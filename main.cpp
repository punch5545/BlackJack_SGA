#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

struct Player {
	char* playerName;
	int money;
	int cardNum[10];
	int cardSym[10];
	int score;
	int win;
	int lose;
};
struct Card {
	int cardNumber;
	int cardSymbol;
};

Card cardVal[52], temp;
Player player = {
	(char*)"Player", 1000000,0,0,0,0,0
};
Player com = {
	(char*)"Computer", 1000000,0,0,0,0,0
};

void cardSym(int i);
void MoveCursor(short x, short y, const char* str);
void printCard(int card);
void saveProfile();
void loadProfile();
void suffleCard();
void help();
int cardSum(Player player, int cardNum);
void mainPage();

bool moreCard = true;
bool dealerCard = true;
int betMoney;
int dealerSum;
int playerSum;
int skey;

int main() {
	loadProfile();
	srand(time(0));
	int count = 0;

	while (true)
	{
		mainPage();
		suffleCard();
		int n = 0, m = 0;

		printf("베팅할 금액 설정> ");
		scanf("%d", &betMoney);
		player.money -= betMoney;

		while (moreCard) {
			player.cardNum[n] = cardVal[count].cardNumber;
			player.cardSym[n] = cardVal[count].cardSymbol;
			count++;
			playerSum = cardSum(player, n);
			printCard(n);
			if (playerSum > 21) {
				printf("합계: %d\n", playerSum);
				printf("Burst\n");
				moreCard = false;
			}
			else if (playerSum == 21 && n == 1) {
				printf("Black Jack! \n");
				player.money += betMoney * 1.5;
				moreCard = false;
			}
			else if (n > 0)
			{
				scanf("%d", &skey);
				if (skey == 1) {
					n++;
				}
				else {
					moreCard = false;
				}
			}
			else {
				n++;
			}
			int vc = 0;
		}
		while (cardSum(com, m) < 16) {
			com.cardNum[m] = cardVal[count + 25].cardNumber;
			com.cardSym[m] = cardVal[count + 25].cardSymbol;
			m++;
			count++;
			int vc = 0;
		}
		dealerSum = cardSum(com, m);

		if (dealerSum > 21 && playerSum < 22) {
			printf("합계: %d\t 딜러 합계: %d\n", playerSum, dealerSum);
			printf("Burst승리\n");
			player.money += (betMoney * 2);
			printf("보유 금액: %d\n", player.money);
		}
		else if (playerSum < 22 && playerSum > dealerSum) {
			printf("합계: %d\t 딜러 합계: %d\n", playerSum, dealerSum);
			printf("승리\n");
			player.money += (betMoney * 2);
			printf("보유 금액: %d\n", player.money);
		}
		else if(dealerSum < 22 && dealerSum > playerSum) {
			printf("합계: %d\t 딜러 합계: %d\n", playerSum, dealerSum);
			printf("패배\n");
			printf("보유 금액: %d\n", player.money);
		}
		else if(dealerSum > 21 && playerSum > 21) {
			printf("합계: %d\t 딜러 합계: %d\n", playerSum, dealerSum);
			printf("무승부\n");
			player.money += betMoney;
			printf("보유 금액: %d\n", player.money);
		}
		else if (dealerSum < 21 && playerSum > 21) {
		}
		else {
			printf("합계: %d\t 딜러 합계: %d\n", playerSum, dealerSum);
			printf("무승부\n");
			player.money += betMoney;
			printf("보유 금액: %d\n", player.money);
		}
		betMoney = 0;
		dealerCard = false; moreCard = false;
		saveProfile();

		int c = 0;
		saveProfile();
		printf("\t\t\tPress Any Key to Continue\n");
		printf("\t\t\t    Press Q to Quit\n");
		char key = getch();
		_getch();
		switch (key) {
		case 'q':return 0;
		case 'Q':return 0;
		default:dealerCard = true; moreCard = true; mainPage(); playerSum = 0; break;
		}
	}
	return 0;
}

void help() {
	system("cls");
	printf("\n\t\t\t\t\t     블랙잭 게임 룰\n\n");
	printf(" 1. 최초 카드를 2장 받고 한장을 오픈합니다.\n\n");
	printf(" 2. 플레이어는 선택에 따라 카드를 더 받을 수도, 그만 받을 수도 있습니다.\n\n");
	printf(" 3. 딜러(컴퓨터)는 본인의 숫자가 16 이하인 경우 무조건 다음 장을 받습니다.\n\n");
	printf(" 4. 숫자 카드의 경우 숫자 그대로, 알파벳 카드인 경우 무조건 10으로 계산합니다.\n     - 단, A는 상황에 따라 10 또는 1로 계산이 가능합니다.\n\n");
	printf(" 5. 본인의 손에 들고있는 카드의 합이 21보다 작으면서 상대보다 21에 근접한 경우 승리합니다.\n     - 이 경우 베팅한 금액의 2배를 돌려받습니다.\n\n");
	printf(" 6. 처음 받은 두 카드의 합이 21일 경우 \"블랙 잭\"으로 베팅한 금액의 1.5배를 돌려받습니다.\n\n");
	printf(" 7. 숫자의 합이 21을 넘을 경우 자동으로 Burst패 합니다.\n\n");
	printf("\t\t\t\t\tPress Any Key to Continue\n");
	char key = getch();
	_getch();
	////
}
int set = 0;
int cardSum(Player player, int cardNum)
{
	int temp = 0;
	for (int i = 0;i<=cardNum;i++) {
		if (player.cardNum[i] > 10) {
			temp += 10;
		}
		else if (player.cardNum[i] == 1 && set<1) {
			int key;
			printf("'A' 숫자 선택: 1. 1   2. 11\n");
			scanf("%d", &key);
			switch (key) {
			case '1': temp += 1; break;
			case '2': temp += 11; break;
			}
			set++;
		}
		else {
			temp += player.cardNum[i];
		}
	}
	return temp;
}

void mainPage()
{
	system("cls");
	printf("\n\n");
	printf("          :::::::::   :::           :::        ::::::::   :::    :::    ::::::::::    :::       ::::::::   :::    ::: \n");
	printf("         :+:    :+:  :+:         :+: :+:     :+:    :+:  :+:   :+:         :+:     :+: :+:    :+:    :+:  :+:   :+:   \n");
	printf("        +:+    +:+  +:+         +:+   +:+   +:+         +:+  +:+          +:+    +:+   +:+   +:+         +:+  +:+     \n");
	printf("       +#++:++#+   +#+        +#++:++#++:  +#+         +#++:++           +#+   +#++:++#++:  +#+         +#++:++       \n");
	printf("      +#+    +#+  +#+        +#+     +#+  +#+         +#+  +#+          +#+   +#+     +#+  +#+         +#+  +#+       \n");
	printf("     #+#    #+#  #+#        #+#     #+#  #+#    #+#  #+#   #+#     #+  #+#   #+#     #+#  #+#    #+#  #+#   #+#       \n");
	printf("    #########   ########## ###     ###   ########   ###    ###      ####    ###     ###   ########   ###    ###   \n\n\n");

	printf("\t\t\t\t\t\    Press Any Key to Start\n\n");
	printf("\t\t\t\t\t\    Press 'H' Key to Help\n");
	printf("\t\t\t\t\t\    Press 'Q' Key to Quit\n");


	char key = getch();
	_getch();

	switch (key) {
	case 'q': break;
	case 'Q': break;
	case 'h': help(); break;
	case 'H': help(); break;
	default: break;
	}
}

void saveProfile() {
	//파일 쓰기
	FILE* fp = fopen("player.dat", "wb");
	fwrite(&player, sizeof(Player), 1, fp);
	fclose(fp);
}

void loadProfile() {
	//파일 열기
	
	FILE* fp = fopen("player.dat", "rb");
	if (fp == NULL) {
		FILE* fp2 = fopen("player.dat", "wb");
		fwrite(&player, sizeof(Player), 1, fp2);
		fclose(fp2);
	}
	else {
		fread(&player, sizeof(Player), 1, fp);
	}
	fclose(fp);
	
	
}
void suffleCard() {
	//패 할당
	int i = 0, j = 0, count = 0;
	for (int i = 1; i <= 4; i++) {
		for (j = 1; j <= 13; j++) {
			cardVal[count].cardNumber = j;
			cardVal[count].cardSymbol = i;
			count++;
		}
	}
	//패 섞기
	for (int k = 0; k < 5; k++) {
		for (i = 0; i < 52; i++) {
			j = rand() % 52;
			temp = cardVal[i];
			cardVal[i] = cardVal[j];
			cardVal[j] = temp;
		}
	}
}
void cardSym(int i) {
	switch (player.cardSym[i]) {
	case 1:	printf(" ♠"); break; // 1: ♠, 2: ◆, 3: ♥, 4: ♣
	case 2:	printf(" ◇"); break;
	case 3:	printf(" ♡"); break;
	case 4:	printf(" ♣"); break;
	}
	switch (player.cardNum[i]) {
	case 1:	printf(" A\t"); break;
	case 10:printf("%d\t", player.cardNum[i]); break;
	case 11: printf(" J\t"); break;
	case 12: printf(" Q\t"); break;
	case 13: printf(" K\t"); break;
	default: printf(" %d\t", player.cardNum[i]); break;
	}
}
void printCard(int card){
	system("cls");
	for (int i = 0; i <= card; i++) {
		cardSym(i);
		printf("\n");
	}
	printf("\nCurr Money : $ %d\t\tBet Money : $ %d \n", player.money, betMoney);
	printf("1. One More   2. Stop\n");
}



// 과제

// 네모판 안에 플레이어, 몬스터 n마리
// 몬스터와 만나면 전투 시작 (턴제)
// struct 공 방 회피 HP