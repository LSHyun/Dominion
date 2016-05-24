#pragma once

#include<deque>
#include<iostream>
#include"card.h"

using namespace std;

class Player{ 
private:
	string aname;
	deque<Card> ahand;
	deque<Card> adeck;
	deque<Card> adiscard;
	int aaction;
	int abuy;
	int acoin;
	int aclient;
public:
	void SetClient(int _client);
	int GetClient();
	void RevealDeck(cardType type, int count, place dest, place other);
	void GainCard(string name, int count, place dest);
	void gainCard(Card c, int count, place dest);
	void gainCard(cardType type, int count, int price, place dest);
	int DiscardCard(int count);
	void DiscardHand(int pos);
	void SetName(string _name);
	void AddBuy(int count);
	void AddCoin(int count);
	void AddAction(int count);
	void DrawCard(int count);
	void TrashCard(int pos);
	int GetCardCount();
	void DiscardDeck(int count);
	void GainCardChoose(int count, int cost, place to);
	Card *GetDeckFront();
	string GetName();
	void InitDeck();
	void PrintHand();
	int GetHandSize();
	string GetHandName(int pos);
	int GetState();
	int GetMoney();
	int GetBuy();
	void InitTurn();
	void Shuffle();
	void discardHand();
	Card* GetHand(int pos);
	int GetAction();
	void SetAction(int _action);
	void SendHandList();
	int GetDeckSize();
	void PrintScore(int number);
};
