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

void Player::InitTurn(){
	aaction = 1;
	abuy = 1;
	acoin = 0;
	discardHand();
	RevealDeck(ANY,5,HAND,DISCARD);
}

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


void Player::gainCard(cardType type, int count, int price, place dest) {
};

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
void Player::SetName(string _name){
	aname = _name;
};

string Player::GetName(){
	return aname;
};

void Player::AddAction(int count){
	aaction += count;
};

void Player::DrawCard(int count){
	RevealDeck(ANY,count,HAND,DISCARD);
};

void Player::AddCoin(int count){
	acoin += count;
};

void Player::DiscardDeck(int count){
	for(int i=0;i<count;i++){
		Card c = adeck.front();
		adiscard.push_back(c);
		adeck.pop_front();
	}
};

void Player::TrashCard(int pos){
	deque<Card>::iterator it = ahand.begin();
	it += pos;
	ahand.erase(it);
};

void Player::AddBuy(int count){
	abuy += count;
};

Card* Player::GetDeckFront(){
};

int Player::GetCardCount(){
	return ahand.size();
};

void Player::GainCardChoose(int count, int cost, place to){
};

void Player::PrintHand(){
	for(int i=0;i<ahand.size();i++){
		ahand[i].PrintCard();
	}
};

int Player::GetHandSize(){
	return ahand.size();
};

string Player::GetHandName(int pos){
	return ahand[pos].GetName();
};

int Player::GetState(){
	for(int i=0;i<ahand.size();i++){
		if(ahand[i].IsAction()){
			return ACTIONSTATE;
		}
	}
	return BUYSTATE;
};

int Player::GetMoney(){
	int sum = 0;
	for(int i=0;i<ahand.size();i++){
		sum += ahand[i].GetValue();
	}
	sum += acoin;
	return sum;
};
int Player::GetBuy(){
	return abuy;
};

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

void Player::discardHand(){
	int temp = DiscardCard(ahand.size());
};

Card* Player::GetHand(int pos){
	if(pos < ahand.size()){
		return &ahand[pos];
	}
	else{
		return NULL;
	}
};

int Player::GetAction(){
	return aaction;
};
void Player::SetAction(int _action){
	aaction = _action;
};
void Player::SetClient(int _client){
	aclient = _client;
};
int Player::GetClient(){
	return aclient;
};
void Player::SendHandList(){
	int temp = ahand.size();
	char buffer[BUFSIZE];
	send(aclient,&temp,sizeof(int),0);
	for(int i=0;i<temp;i++){
		strcpy(buffer,GetHandName(i).c_str());
		send(aclient,buffer,BUFSIZE,0);
	}
}
int Player::GetDeckSize(){
	return adeck.size();
};

void Player::DiscardHand(int pos){
	Card card = ahand[pos];
	deque<Card>::iterator it = ahand.begin();
	it += pos;
	adiscard.push_back(card);
	ahand.erase(it);
}

void Player::PrintScore(int number){
	int sum = 0;
	for(int i=0;i<adeck.size();i++){
		sum += adeck[i].GetScore();
	}
	for(int i=0;i<ahand.size();i++){
		sum += ahand[i].GetScore();
	}
	for(int i=0;i<adiscard.size();i++){
		sum += adiscard[i].GetScore();
	}
	cout << "Player " << number << " Score : " << sum << endl;
};
	
