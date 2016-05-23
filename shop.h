#pragma once

#include"card.h"

class Shop{
private:
	Card card[CARDCOUNT];
	int remainCard[CARDCOUNT];
	int playerCount;
public:
	void initShop(int _count);
	void printShop();
	string getCardName(int pos);
	int getCardRemain(int pos);
	int getCardCost(int pos);
	void updateCardRemain(int pos, int value);
};
