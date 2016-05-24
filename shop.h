#pragma once

#include"card.h"

class Shop{
private:
	Card acard[CARDCOUNT];
	int aremainCard[CARDCOUNT];
	int aplayerCount;
public:
	void InitShop(int _count);
	void PrintShop();
	string GetCardName(int pos);
	int GetCardRemain(int pos);
	int GetCardCost(int pos);
	void UpdateCardRemain(int pos, int value);
	Card GetCard(int pos);
	bool IsFinished();
};
