#pragma once

#include<iostream>
#include<map>
#include"globalValue.h"

using namespace std;

class Player;
class Card{
private:
	string name;
	cardType type;
	int cost;
	int value;
	int score;
	map<string, int> cardMap;
public:
	void setCard(string _name);
	string getName();
	bool isAction();
	cardType getType();
	void initCardMap();
	int cardStringToNumber(string cardName);
	int cardAction(Player player, string cardName);
	int actionAdventure(Player player);
	int actionBureaucrat(Player player);
	int actionCellar(Player player);
	int actionChancellor(Player player);
	int actionChapel(Player player);
	int actionCouncilroom(Player player);
	int actionFeast(Player player);
	int actionFestival(Player player);
	int actionLaboratory(Player player);
	int actionLibrary(Player player);
	int actionMarket(Player player);
	int actionMilitia(Player player);
	int actionMine(Player player);
	int actionMoat(Player player);
	int actionMoneylender(Player player);
	int actionRemodel(Player player);
	int actionSmithy(Player player);
	int actionSpy(Player player);
	int actionThief(Player player);
	int actionThroneroom(Player player);
	int actionViliage(Player player);
	int actionWitch(Player player);
	int actionWoodcutter(Player player);
	int actionWorkshop(Player player);
	void printCard();
};