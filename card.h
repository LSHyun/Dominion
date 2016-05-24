#pragma once

#include<iostream>
#include<map>
#include"globalValue.h"

using namespace std;

class Shop;
class Player;
class Card{
private:
	string aname;
	cardType atype;
	int acost;
	int avalue;
	int ascore;
	map<string, int> acardMap;
public:
	void SetCard(string _name);
	string GetName();
	bool IsAction();
	cardType GetType();
	void InitCardMap();
	int CardStringToNumber(string cardName);
	int CardAction(Player *player, string cardName, Shop *shop);
	int ActionAdventure(Player *player);
	int ActionBureaucrat(Player *player);
	int ActionCellar(Player *player);
	int ActionChancellor(Player *player);
	int ActionChapel(Player *player);
	int ActionCouncilroom(Player *player);
	int ActionFeast(Player *player);
	int ActionFestival(Player *player);
	int ActionLaboratory(Player *player);
	int ActionLibrary(Player *player);
	int ActionMarket(Player *player);
	int ActionMilitia(Player *player);
	int ActionMine(Player *player);
	int ActionMoat(Player *player);
	int ActionMoneylender(Player *player);
	int ActionRemodel(Player *player, Shop *shop);
	int ActionSmithy(Player *player);
	int ActionSpy(Player *player);
	int ActionThief(Player *player);
	int ActionThroneroom(Player *player);
	int ActionViliage(Player *player);
	int ActionWitch(Player *player);
	int ActionWoodcutter(Player *player);
	int ActionWorkshop(Player *player);
	void PrintCard();
	int GetValue();
	int GetCost();
};
