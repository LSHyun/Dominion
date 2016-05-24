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
	int client;
public:
	void setClient(int _client);
	int getClient();
	void revealDeck(cardType type, int count, place dest, place other);
	void gainCard(string name, int count, place dest);
	void gainCard(Card c, int count, place dest);
	void gainCard(cardType type, int count, int price, place dest);
	int discardCard(int count);
	void discardHand(int pos);
	void setName(string _name);
	void addBuy(int count);
	void addCoin(int count);
	void addAction(int count);
	void drawCard(int count);
	void trashCard(int pos);
	int getCardCount();
	void discardDeck(int count);
	void gainCardChoose(int count, int cost, place to);
	Card *getDeckFront();
	string getName();
	void initDeck();
	void printHand();
	int getHandSize();
	string getHandName(int pos);
	int getState();
	int getMoney();
	int getBuy();
	void initTurn();
	void shuffle();
	void discardHand();
	Card* getHand(int pos);
	int getAction();
	void setAction(int _action);
	void sendHandList();
	int getDeckSize();
};
