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
#include"card.h"
#include"player.h"
#include"shop.h"

using namespace std;

void Card::initCardMap(){
	cardMap["Cellar"] = CELLAR;
	cardMap["Chapel"] = CHAPEL;
	cardMap["Moat"] = MOAT;
	cardMap["Chancellor"] = CHANCELLOR;
	cardMap["Viliage"] = VILIAGE;
	cardMap["Woodcutter"] = WOODCUTTER;
	cardMap["Workshop"] = WORKSHOP;
	cardMap["Bureaucrat"] = BUREAUCRAT;
	cardMap["Feast"] = FEAST;
	cardMap["Gardens"] = GARDENS;
	cardMap["Militia"] = MILITIA;
	cardMap["Moneylender"] = MONEYLENDER;
	cardMap["Remodel"] = REMODEL;
	cardMap["Smithy"] = SMITHY;
	cardMap["Spy"] = SPY;
	cardMap["Thief"] = THIEF;
	cardMap["Throneroom"] = THRONEROOM;
	cardMap["Councilroom"] = COUNCILROOM;
	cardMap["Festival"] = FESTIVAL;
	cardMap["Laboratory"] = LABORATORY;
	cardMap["Library"] = LIBRARY;
	cardMap["Market"] = MARKET;
	cardMap["Mine"] = MINE;
	cardMap["Witch"] = WITCH;
	cardMap["Adventure"] = ADVENTURE;
};

int Card::cardStringToNumber(string cardName){
	return cardMap[cardName];
}

void Card::setCard(string _name){
	initCardMap();
	cout << _name << endl;
	int r = (rand() % TOTALACTION) + 1;
	if(_name == "Copper"){
		name = "Copper";
		type = TREASURE;
		cost = 0;
		value = 1;
	}
	else if(_name == "Silver"){
		name = "Silver";
		type = TREASURE;
		cost = 3;
		value = 2;
	}
	else if(_name == "Gold"){
		name = "Gold";
		type = TREASURE;
		cost = 6;
		value = 3;
	}
	else if(_name == "Estate"){
		name = "Estate";
		type = VICTORY;
		cost = 2;
		score = 1;
	}
	else if(_name == "Duchy"){
		name = "Duchy";
		type = VICTORY;
		cost = 5;
		score = 3;
	}
	else if(_name == "Province"){
		name = "Province";
		type = VICTORY;
		cost = 8;
		score = 6;
	}
	else if(_name == "Curse"){
		name = "Curse";
		type = CURSE;
		cost = 0;
		score = -1;
	}
	else if(_name == "RAND"){
flagSetCard:
		switch(r){
			case CELLAR:
				name = "Cellar";
				type = ACTION;
				cost = 2;
				break;
			case CHAPEL:
				name = "Chapel";
				type = ACTION;
				cost = 2;
				break;
			case MOAT:
				name = "Moat";
				type = ACTION;
				cost = 2;
				break;
			case CHANCELLOR:
				name = "Chancellor";
				type = ACTION;
				cost = 3;
				break;
			case VILIAGE:
				name = "Viliage";
				type = ACTION;
				cost = 3;
				break;
			case WOODCUTTER:
				name = "Woodcutter";
				type = ACTION;
				cost = 3;
				break;
			case WORKSHOP:
				name = "Workshop";
				type = ACTION;
				cost = 4;
				break;
			case BUREAUCRAT:
				name = "Bureaucrat";
				type = ACTION;
				cost = 4;
				break;
			case FEAST:
				name = "Feast";
				type = ACTION;
				cost = 4;
				break;
			case GARDENS:
				name = "Garden";
				type = VICTORY;
				cost = 4;
				break;
			case MILITIA:
				name = "Militia";
				type = ACTION;
				cost = 4;
				break;
			case MONEYLENDER:
				name = "Moneylender";
				type = ACTION;
				cost = 4;
				break;
			case REMODEL:
				name = "Remodel";
				type = ACTION;
				cost = 4;
				break;
			case SMITHY:
				name = "Smithy";
				type = ACTION;
				cost = 4;
				break;
			case SPY:
				name = "Spy";
				type = ACTION;
				cost = 4;
				break;
			case THIEF:
				name = "Thief";
				type = ACTION;
				cost = 4;
				break;
			case THRONEROOM:
				name = "Throneroom";
				type = ACTION;
				cost = 4;
				break;
			case COUNCILROOM:
				name = "CouncilRoom";
				type = ACTION;
				cost = 5;
				break;
			case FESTIVAL:
				name = "Festival";
				type = ACTION;
				cost = 5;
				break;
			case LABORATORY:
				name = "Laboratory";
				type = ACTION;
				cost = 5;
				break;
			case LIBRARY:
				name = "Library";
				type = ACTION;
				cost = 5;
				break;
			case MARKET:
				name = "Market";
				type = ACTION;
				cost = 5;
				break;
			case MINE:
				name = "Mine";
				type = ACTION;
				cost = 5;
				break;
			case WITCH:
				name = "Witch";
				type = ACTION;
				cost = 5;
				break;
			case ADVENTURE:
				name = "Adventure";
				type = ACTION;
				cost = 6;
				break;
		}
	}
	else{
		r = cardStringToNumber(_name);
		goto flagSetCard;
	}
}
string Card::getName(){
	return name;
}

bool Card::isAction(){
	if(type == ACTION){
		return true;
	}
	else{
		return false;
	}
}

cardType Card::getType(){
	return type;
}

/* Input << player */
/* Output >> -1: wrong action, 0: done, else: special case */
int Card::cardAction(Player *player, string cardName, Shop *shop){
	int r = cardStringToNumber(cardName);
	cout << "cardaction in : " << cardName << ", out : " << r << endl;
	switch(r){
		case CELLAR:
			return actionCellar(player);
		case CHAPEL:
			return actionChapel(player);
		case MOAT:
			return actionMoat(player);
		case CHANCELLOR:
			return actionChancellor(player);
		case VILIAGE:
			return actionViliage(player);
		case WOODCUTTER:
			return actionWoodcutter(player);
		case WORKSHOP:
			return actionWorkshop(player);
		case BUREAUCRAT:
			return actionBureaucrat(player);
		case FEAST:
			return actionFeast(player);
		case GARDENS:
			return -1;
		case MILITIA:
			return actionMilitia(player);
		case MONEYLENDER:
			return actionMoneylender(player);
		case REMODEL:
			return actionRemodel(player, shop);
		case SMITHY:
			return actionSmithy(player);
		case SPY:
			return actionSpy(player);
		case THIEF:
			return actionThief(player);
		case THRONEROOM:
			return actionThroneroom(player);
		case COUNCILROOM:
			return actionCouncilroom(player);
		case FESTIVAL:
			return actionFestival(player);
		case LABORATORY:
			return actionLaboratory(player);
		case LIBRARY:
			return actionLibrary(player);
		case MARKET:
			return actionMarket(player);
		case MINE:
			return actionMine(player);
		case WITCH:
			return actionWitch(player);
		case ADVENTURE:
			return actionAdventure(player);
		default:
			return -1;
	}
}
int Card::actionAdventure(Player *player){
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->revealDeck(TREASURE,2,HAND,DISCARD);
	return 0;
};

int Card::actionBureaucrat(Player *player){
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->gainCard("Silver", 1, DECK);
	return BUREAUCRAT;
};

int Card::actionCellar(Player *player){
	int client = player->getClient();
	int temp = CELLAR;
	send(client,&temp,sizeof(int),0);
	recv(client,&temp,sizeof(int),0);
	player->addAction(1);
	int count = player->discardCard(temp);
	player->drawCard(count);
	return 0;
};
int Card::actionChancellor(Player *player){
	int client = player->getClient();
	int temp = CHANCELLOR;
	char choice;
	send(client,&temp,sizeof(int),0);
	recv(client,&choice,sizeof(char),0);
	if(choice == 'y'){
		player->discardDeck(player->getDeckSize());
	}
	player->addCoin(2);
	return 0;
}
int Card::actionChapel(Player *player){
	int client = player->getClient();
	int temp = CHAPEL;
	int count;
	send(client,&temp,sizeof(int),0);
	recv(client,&count,sizeof(int),0);
	for(int i=0;i<count;i++){
		player->sendHandList();
		recv(client,&temp,sizeof(int),0);
		player->trashCard(temp);
	}
	return 0;
};
int Card::actionCouncilroom(Player *player){
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(4);
	player->addBuy(1);
	return COUNCILROOM;
};
int Card::actionFeast(Player *player){
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	//player.gainCardChoose(1,5,DISCARD);
	return FEAST;
};
int Card::actionFestival(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->addAction(2);
	player->addBuy(1);
	player->addCoin(2);
	return 0;
};
int Card::actionLaboratory(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(2);
	player->addAction(1);
	return 0;
};
int Card::actionLibrary(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	while (player->getCardCount() < 7) {
		Card *top = player->getDeckFront();
		if (top->isAction()) {
/*
			temp = 1;
			send(client,&temp,sizeof(int),0);
			char choice;
			cout << "Card Name : " << top->getName() << endl;
			cout << "Set aside this card?(y/n)";
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				
			}
			else if (choice == 'n' || choice == 'N') {

			}
			else {

			}
*/
			player->discardDeck(1);
		}
		else {
			player->drawCard(1);
		}
	}
	return 0;
}
int Card::actionMarket(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(1);
	player->addAction(1);
	player->addBuy(1);
	player->addCoin(1);
	return 0;
};
int Card::actionMilitia(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->addCoin(1);
	return MILITIA;
};
int Card::actionMine(Player *player) {
	int client = player->getClient();
	int temp = MINE;
	send(client,&temp,sizeof(int),0);
	player->sendHandList();
	recv(client,&temp,sizeof(int),0);
	if(temp < 0 || temp >= player->getHandSize()){
	}
	else if(player->getHandName(temp) == "Copper"){
		Card c;
		c.setCard("Silver");
		player->trashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else if(player->getHandName(temp) == "Silver"){
		Card c;
		c.setCard("Gold");
		player->trashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else if(player->getHandName(temp) == "Gold"){
		Card c;
		c.setCard("Gold");
		player->trashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else{
	}
	return 0;
}
int Card::actionMoat(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(2);
	return 0;
}
int Card::actionMoneylender(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	for(int i=0;i<player->getHandSize();i++){
		if(player->getHandName(i) == "Copper"){
			player->trashCard(i);
			player->addCoin(3);
			break;
		}
	}
	return 0;
}
int Card::actionRemodel(Player *player, Shop *shop) {
	int client = player->getClient();
	int temp = REMODEL;
	send(client,&temp,sizeof(int),0);
/*
	int value = player.trashCard(ANY, 1);
	if (value != -1) {
		player.gainCard(ANY, 1, value + 2, DISCARD);
	}
*/
	player->sendHandList();
	recv(client,&temp,sizeof(int),0);
	int value = player->getHand(temp)->getCost() + 2;
	int choose;
	player->trashCard(temp);

	send(client,&value,sizeof(int),0);
	recv(client,&choose,sizeof(int),0);
	if(choose == 0){ // turn end
	}
	else{
		choose--;
		if(value >= shop->getCardCost(choose) && shop->getCardRemain(choose) > 0){
			player->gainCard(shop->getCard(choose), 1, DISCARD);
			shop->updateCardRemain(choose,-1);
		}
		else{
		}
	}
	return 0;
}
int Card::actionSmithy(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(3);
	return 0;
}
int Card::actionSpy(Player *player){
	int client = player->getClient();
	int temp = SPY;
	send(client,&temp,sizeof(int),0);
	player->drawCard(1);
	player->addAction(1);
/*
	char choice;
	cout << "Reveal your deck : " << top->getName() << endl;
	cout << "Discard or Put back?(d/p)";
	cin >> choice;
	if (choice == 'd' || choice == 'D') {
	}
	else if (choice == 'p' || choice == 'P') {

	}
	else {
	}
*/
	return SPY;
}
int Card::actionThief(Player *player) {
	int client = player->getClient();
	int temp = THIEF;
	send(client,&temp,sizeof(int),0);
	return THIEF;
}
int Card::actionThroneroom(Player *player) {
	int client = player->getClient();
	int temp = THRONEROOM;
	send(client,&temp,sizeof(int),0);
	return THRONEROOM;
}
int Card::actionViliage(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(1);
	player->addAction(2);
	return 0;
}
int Card::actionWitch(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->drawCard(2);
	return WITCH;
}
int Card::actionWoodcutter(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->addCoin(2);
	player->addBuy(1);
	return 0;
}
int Card::actionWorkshop(Player *player) {
	int client = player->getClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->gainCard(ANY, 1, 4, DISCARD);
	return 0;
}
void Card::printCard(){
	cout << name << endl;
};
int Card::getValue(){
	return value;
};
int Card::getCost(){
	return cost;
};
