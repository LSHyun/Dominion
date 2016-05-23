#pragma once

#include<deque>
#include<iostream>
#include"card.h"

using namespace std;

class Player{ 
private:
	string name;
	deque<Card> hand;
	deque<Card> deck;
	deque<Card> discard;
	int action;
	int buy;
	int coin;
public:
	void revealDeck(cardType type, int count, place dest, place other);
	void gainCard(string name, int count, place dest);
	void gainCard(cardType type, int count, int price, place dest);
	int discardCard(int count);
	void setName(string _name);
	void addBuy(int count);
	void addCoin(int count);
	void addAction(int count);
	void drawCard(int count);
	int trashCard(cardType type, int count);
	int trashCard(string name, int count);
	int getCardCount();
	void discardDeck(int count);
	void gainCardChoose(int count, int cost, place to);
	Card *getDeckFront();
	string getName();
	void initDeck();
	void printHand();
	void getHandSize();
};
