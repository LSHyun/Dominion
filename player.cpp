#include<iostream>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>
#include<netdb.h>
#include"serverClient.h"
#include"player.h"
//============================================================================
// Name        : InitTurn()
// Author      : LSH
// Version     : 1.1
// Param       : aaction, abuy, acoin
// Return      : NULL
// Deprecated  : Using
// See         : Simulation.cpp/SubRun
// Todo        : Initialize player status
// Bug         : No bug
//============================================================================

void Player::InitTurn(){
	aaction = 1;
	abuy = 1;
	acoin = 0;
	discardHand();
	RevealDeck(ANY,5,HAND,DISCARD);
}
//============================================================================
// Name        : InitDeck()
// Author      : LSH
// Version     : 1.1
// Param       : adeck
// Return      : NULL
// Deprecated  : Using
// See         : Simulation.cpp/MainRun
// Todo        : Initialize player deck and shuffle
// Bug         : No bug
//============================================================================
void Player::InitDeck(){
	int temp[10];
	Card tempCard;
	for(int i=0;i<10;i++){
		temp[i] = rand() % 65536;
	}
	adeck.resize(10);
	for(int i=0;i<7;i++){
		adeck[i].SetCard("Copper");
	}
	for(int i=7;i<10;i++){
		adeck[i].SetCard("Estate");
	}
	for(int i=0;i<9;i++){
		for(int k=1;k<10;k++){
			if(temp[i] < temp[k]){
				int t = temp[i];
				temp[i] = temp[k];
				temp[k] = t;
				tempCard = adeck[i];
				adeck[i] = adeck[k];
				adeck[k] = tempCard;
			}
		}
	}
};
//============================================================================
// Name        : RevealDeck()
// Author      : LSH
// Version     : 1.1
// Param       : adeck, ahand
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp/ActionAdventure , player.cpp/InitTurn, DrawCard
// Todo        : Card revealed in deck and using somewhere
// Bug         : No bug But, not yet comletely using
//============================================================================
void Player::RevealDeck(int type, int count, place dest, place other){
	for(int i=0;i<count;i++){
		if(adeck.size() == 0){
			Shuffle();
		}
		if(adeck.size() == 0){
			break;
		}
		Card card = adeck.front();
		if(type != ANY && type != card.GetType()){
			if(other == DISCARD){
				adiscard.push_back(card);
		
			}
			else if(other == TRASH){
			}
	
		}
		else{
			if(dest == HAND){
				ahand.push_back(card);
			}
		}
		adeck.pop_front();
	}
};
//============================================================================
// Name        : GainCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, adeck, adiscard
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp/ActionBureaucrat
// Todo        : Gain card some card
// Bug         : No bug
//============================================================================
void Player::GainCard(string name, int count, place dest){
	for(int i=0;i<count;i++){
		Card *c = new Card;
		c->SetCard(name);
		cout << c->GetName() << ", " << c->GetCost() << endl;
		if(dest ==DISCARD){
			adiscard.push_back(*c);
		}
		else if(dest == HAND){
			ahand.push_back(*c);
		}
		else if(dest == DECK){
			adeck.push_front(*c);
		}
		cout << "name : " << c->GetName() << endl;
	}
};
//============================================================================
// Name        : gainCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, adeck, adiscard
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp/ActionBureaucrat
// Todo        : Gain card some card
// Bug         : No bug
//============================================================================
void Player::gainCard(Card c, int count, place dest) {
	for(int i=0;i<count;i++){
		cout << c.GetName() << ", " << c.GetCost() << endl;
		if(dest ==DISCARD){
			adiscard.push_back(c);
		}
		else if(dest == HAND){
			ahand.push_back(c);
		}
		else if(dest == DECK){
			adeck.push_front(c);
		}
		cout << "name : " << c.GetName() << endl;
	}
};

//============================================================================
// Name        : gainCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, adeck, adiscard
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp/ActionBureaucrat
// Todo        : ?
// Bug         : ?
//============================================================================
void Player::gainCard(cardType type, int count, int price, place dest) {
};
//============================================================================
// Name        : DiscardCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, adiscard
// Return      : result
// Deprecated  : Using
// See         : card.cpp/ActionCellar , player.cpp/discardHand
// Todo        : set name
// Bug         : No bug But, not yet comletely using
//============================================================================
int Player::DiscardCard(int count){
	int result = 0;
	for(int i=0;i<count;i++){
		if(ahand.size() != 0){
			Card card = ahand.front();
			adiscard.push_back(card);
			ahand.pop_front();
			++result;
		}
		else{
			break;
		}
	}
	return result;
};
//============================================================================
// Name        : SetName()
// Author      : LSH
// Version     : 1.1
// Param       : aname
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp/RegistPlayer
// Todo        : set name
// Bug         : No bug
//============================================================================
void Player::SetName(string _name){
	aname = _name;
};
//============================================================================
// Name        : GetName()
// Author      : LSH
// Version     : 1.1
// Param       : aname
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp/SubRun, SendPlayerList
// Todo        : get name
// Bug         : No bug
//============================================================================
string Player::GetName(){
	return aname;
};
//============================================================================
// Name        : AddAction()
// Author      : LSH
// Version     : 1.1
// Param       : aaction
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : additional action function
// Bug         : No bug
//============================================================================
void Player::AddAction(int count){
	aaction += count;
};
//============================================================================
// Name        : DrawCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, discard
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : deck to hand card
// Bug         : No bug
//============================================================================
void Player::DrawCard(int count){
	RevealDeck(ANY,count,HAND,DISCARD);
};
//============================================================================
// Name        : AddCoin()
// Author      : LSH
// Version     : 1.1
// Param       : acoin
// Return      : NULL
// Deprecated  : Using
// See         : simulator.cpp , card.cpp
// Todo        : coin add
// Bug         : No bug
//============================================================================
void Player::AddCoin(int count){
	acoin += count;
};
//============================================================================
// Name        : DiscardDeck()
// Author      : LSH
// Version     : 1.1
// Param       : acoin
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : Deck to Discard card
// Bug         : No bug
//============================================================================
void Player::DiscardDeck(int count){
	for(int i=0;i<count;i++){
		Card c = adeck.front();
		adiscard.push_back(c);
		adeck.pop_front();
	}
};
//============================================================================
// Name        : TrashCard()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : delete some card, card goto Trash
// Bug         : No bug
//============================================================================
void Player::TrashCard(int pos){
	deque<Card>::iterator it = ahand.begin();
	it += pos;
	ahand.erase(it);
};
//============================================================================
// Name        : AddBuy()
// Author      : LSH
// Version     : 1.1
// Param       : abuy
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : buy chance increase
// Bug         : No bug
//============================================================================
void Player::AddBuy(int count){
	abuy += count;
};

Card* Player::GetDeckFront(){
};
//============================================================================
// Name        : GetCardCount()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : ahand.size()
// Deprecated  : Using
// See         : card.cpp
// Todo        : how many cards in your hand?
// Bug         : No bug
//============================================================================
int Player::GetCardCount(){
	return ahand.size();
};

void Player::GainCardChoose(int count, int cost, place to){
};
//============================================================================
// Name        : PrintHand()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : what cards in your hand?
// Bug         : No bug
//============================================================================
void Player::PrintHand(){
	for(int i=0;i<ahand.size();i++){
		ahand[i].PrintCard();
	}
};
//============================================================================
// Name        : GetHandSize()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : ahand.size()
// Deprecated  : Using
// See         : card.cpp simulation.cpp
// Todo        : how many cards in your hand?
// Bug         : No bug
//============================================================================
int Player::GetHandSize(){
	return ahand.size();
};
//============================================================================
// Name        : GetHandName()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : ahand[pos].GetName()  card.Name()
// Deprecated  : Using
// See         : card.cpp player.cpp simulation.cpp
// Todo        : get some position card name
// Bug         : No bug
//============================================================================
string Player::GetHandName(int pos){
	return ahand[pos].GetName();
};
//============================================================================
// Name        : GetState()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : player state
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : What to do player?
// Bug         : No bug
//============================================================================
int Player::GetState(){
	for(int i=0;i<ahand.size();i++){
		if(ahand[i].IsAction()){
			return ACTIONSTATE;
		}
	}
	return BUYSTATE;
};
//============================================================================
// Name        : GetMoney()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : money
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : How many money you gain?
// Bug         : No bug
//============================================================================
int Player::GetMoney(){
	int sum = 0;
	for(int i=0;i<ahand.size();i++){
		sum += ahand[i].GetValue();
	}
	sum += acoin;
	return sum;
};
//============================================================================
// Name        : GetBuy()
// Author      : LSH
// Version     : 1.1
// Param       : abuy
// Return      : abuy
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : How many times you buy?
// Bug         : No bug
//============================================================================
int Player::GetBuy(){
	return abuy;
};
//============================================================================
// Name        : Shuffle()
// Author      : LSH
// Version     : 1.1
// Param       : adiscard, adeck
// Return      : NULL
// Deprecated  : Using
// See         : player.cpp/RevealDeck
// Todo        : Shuffle discard and go to deck
// Bug         : No bug
//============================================================================
void Player::Shuffle(){
	for(int i=0;i<adiscard.size();i++){
		Card card = adiscard.front();
		adeck.push_back(card);
		adiscard.pop_front();
	}
	int temp[adeck.size()];
	Card tempCard;
	for(int i=0;i<adeck.size();i++){
		temp[i] = rand() % 65536;
	}
	for(int i=0;i<adeck.size()-1;i++){
		for(int k=1;k<adeck.size();k++){
			if(temp[i] < temp[k]){
				int t = temp[i];
				temp[i] = temp[k];
				temp[k] = t;
				tempCard = adeck[i];
				adeck[i] = adeck[k];
				adeck[k] = tempCard;
			}
		}
	}
};
//============================================================================
// Name        : discardHand()
// Author      : LSH
// Version     : 1.1
// Param       : adiscard, ahand
// Return      : NULL
// Deprecated  : Using
// See         : player.cpp/InitTurn
// Todo        : Hand to discard
// Bug         : No bug
//============================================================================
void Player::discardHand(){
	int temp = DiscardCard(ahand.size());
};
//============================================================================
// Name        : GetHand()
// Author      : LSH
// Version     : 1.1
// Param       : ahand
// Return      : Card
// Deprecated  : Using
// See         : card.cpp simulation.cpp
// Todo        : get some position hand card
// Bug         : No bug
//============================================================================
Card* Player::GetHand(int pos){
	if(pos < ahand.size()){
		return &ahand[pos];
	}
	else{
		return NULL;
	}
};
//============================================================================
// Name        : GetAction()
// Author      : LSH
// Version     : 1.1
// Param       : aaction
// Return      : aaction
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : How many times you action?
// Bug         : No bug
//============================================================================
int Player::GetAction(){
	return aaction;
};
//============================================================================
// Name        : SetAction()
// Author      : LSH
// Version     : 1.1
// Param       : aaction
// Return      : aaction
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : set action
// Bug         : No bug
//============================================================================
void Player::SetAction(int _action){
	aaction = _action;
};
//============================================================================
// Name        : SetClient()
// Author      : LSH
// Version     : 1.1
// Param       : aname
// Return      : aaction
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : set client
// Bug         : No bug
//============================================================================
void Player::SetClient(int _client){
	aclient = _client;
};
//============================================================================
// Name        : GetClient()
// Author      : LSH
// Version     : 1.1
// Param       : aclient
// Return      : aclient
// Deprecated  : Using
// See         : card.cpp
// Todo        : get client
// Bug         : No bug
//============================================================================
int Player::GetClient(){
	return aclient;
};
//============================================================================
// Name        : SendHandList()
// Author      : LSH
// Version     : 1.1
// Param       : ahand, aclient, buffer
// Return      : NULL
// Deprecated  : Using
// See         : card.cpp
// Todo        : send hand cards list from server to client
// Bug         : No bug
//============================================================================
void Player::SendHandList(){
	int temp = ahand.size();
	char buffer[BUFSIZE];
	send(aclient,&temp,sizeof(int),0);
	for(int i=0;i<temp;i++){
		strcpy(buffer,GetHandName(i).c_str());
		send(aclient,buffer,BUFSIZE,0);
	}
}
//============================================================================
// Name        : GetDeckSize()
// Author      : LSH
// Version     : 1.1
// Param       : adeck
// Return      : adeck.size()
// Deprecated  : Using
// See         : card.cpp
// Todo        : GetDeckSize
// Bug         : No bug
//============================================================================
int Player::GetDeckSize(){
	return adeck.size();
};
//============================================================================
// Name        : DiscardHand()
// Author      : LSH
// Version     : 1.1
// Param       : adeck,adiscard
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : card go hand to discard
// Bug         : No bug
//============================================================================
void Player::DiscardHand(int pos){
	Card card = ahand[pos];
	deque<Card>::iterator it = ahand.begin();
	it += pos;
	adiscard.push_back(card);
	ahand.erase(it);
}
	
