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

//============================================================================
// Name        : InitCardMap()
// Author      : SWH
// Version     : 1.1
// Param       : acardmap
// Return      : NULL
// Deprecated  : using
// See         : card.cpp
// Todo        : Initialize card default setting
// Bug         :
//===========================================================================
void Card::InitCardMap(){
	acardMap["Cellar"] = CELLAR;
	acardMap["Chapel"] = CHAPEL;
	acardMap["Moat"] = MOAT;
	acardMap["Chancellor"] = CHANCELLOR;
	acardMap["Viliage"] = VILIAGE;
	acardMap["Woodcutter"] = WOODCUTTER;
	acardMap["Workshop"] = WORKSHOP;
	acardMap["Bureaucrat"] = BUREAUCRAT;
	acardMap["Feast"] = FEAST;
	acardMap["Gardens"] = GARDENS;
	acardMap["Militia"] = MILITIA;
	acardMap["Moneylender"] = MONEYLENDER;
	acardMap["Remodel"] = REMODEL;
	acardMap["Smithy"] = SMITHY;
	acardMap["Spy"] = SPY;
	acardMap["Thief"] = THIEF;
	acardMap["Throneroom"] = THRONEROOM;
	acardMap["Councilroom"] = COUNCILROOM;
	acardMap["Festival"] = FESTIVAL;
	acardMap["Laboratory"] = LABORATORY;
	acardMap["Library"] = LIBRARY;
	acardMap["Market"] = MARKET;
	acardMap["Mine"] = MINE;
	acardMap["Witch"] = WITCH;
	acardMap["Adventure"] = ADVENTURE;
};

//============================================================================
// Name        : CardStringToNumber()
// Author      : SWH
// Version     : 1.1
// Param       : acardmap
// Return      : card default
// Deprecated  : using
// See         : card.cpp
// Todo        : card name to card default number
// Bug         :
//===========================================================================
int Card::CardStringToNumber(string cardName){
	return acardMap[cardName];
}

//============================================================================
// Name        : SetCard()
// Author      : SWH
// Version     : 1.1
// Param       : acardmap, aname, atype, acost, avalue,
// Return      : NULL
// Deprecated  : using
// See         : card.cpp, player.cpp, shop.cpp
// Todo        : initialize or some card set.
// Bug         :
//===========================================================================
void Card::SetCard(string _name){
	InitCardMap();
	cout << _name << endl;
	int r = (rand() % TOTALACTION) + 1;
	if(_name == "Copper"){
		aname = "Copper";
		atype = TREASURE;
		acost = 0;
		avalue = 1;
	}
	else if(_name == "Silver"){
		aname = "Silver";
		atype = TREASURE;
		acost = 3;
		avalue = 2;
	}
	else if(_name == "Gold"){
		aname = "Gold";
		atype = TREASURE;
		acost = 6;
		avalue = 3;
	}
	else if(_name == "Estate"){
		aname = "Estate";
		atype = VICTORY;
		acost = 2;
		ascore = 1;
	}
	else if(_name == "Duchy"){
		aname = "Duchy";
		atype = VICTORY;
		acost = 5;
		ascore = 3;
	}
	else if(_name == "Province"){
		aname = "Province";
		atype = VICTORY;
		acost = 8;
		ascore = 6;
	}
	else if(_name == "Curse"){
		aname = "Curse";
		atype = CURSE;
		acost = 0;
		ascore = -1;
	}
	else if(_name == "RAND"){
flagSetCard:
		switch(r){
			case CELLAR:
				aname = "Cellar";
				atype = ACTION;
				acost = 2;
				break;
			case CHAPEL:
				aname = "Chapel";
				atype = ACTION;
				acost = 2;
				break;
			case MOAT:
				aname = "Moat";
				atype = ACTION;
				acost = 2;
				break;
			case CHANCELLOR:
				aname = "Chancellor";
				atype = ACTION;
				acost = 3;
				break;
			case VILIAGE:
				aname = "Viliage";
				atype = ACTION;
				acost = 3;
				break;
			case WOODCUTTER:
				aname = "Woodcutter";
				atype = ACTION;
				acost = 3;
				break;
			case WORKSHOP:
				aname = "Workshop";
				atype = ACTION;
				acost = 4;
				break;
			case BUREAUCRAT:
				aname = "Bureaucrat";
				atype = ACTION;
				acost = 4;
				break;
			case FEAST:
				aname = "Feast";
				atype = ACTION;
				acost = 4;
				break;
			case GARDENS:
				aname = "Garden";
				atype = VICTORY;
				acost = 4;
				break;
			case MILITIA:
				aname = "Militia";
				atype = ACTION;
				acost = 4;
				break;
			case MONEYLENDER:
				aname = "Moneylender";
				atype = ACTION;
				acost = 4;
				break;
			case REMODEL:
				aname = "Remodel";
				atype = ACTION;
				acost = 4;
				break;
			case SMITHY:
				aname = "Smithy";
				atype = ACTION;
				acost = 4;
				break;
			case SPY:
				aname = "Spy";
				atype = ACTION;
				acost = 4;
				break;
			case THIEF:
				aname = "Thief";
				atype = ACTION;
				acost = 4;
				break;
			case THRONEROOM:
				aname = "Throneroom";
				atype = ACTION;
				acost = 4;
				break;
			case COUNCILROOM:
				aname = "CouncilRoom";
				atype = ACTION;
				acost = 5;
				break;
			case FESTIVAL:
				aname = "Festival";
				atype = ACTION;
				acost = 5;
				break;
			case LABORATORY:
				aname = "Laboratory";
				atype = ACTION;
				acost = 5;
				break;
			case LIBRARY:
				aname = "Library";
				atype = ACTION;
				acost = 5;
				break;
			case MARKET:
				aname = "Market";
				atype = ACTION;
				acost = 5;
				break;
			case MINE:
				aname = "Mine";
				atype = ACTION;
				acost = 5;
				break;
			case WITCH:
				aname = "Witch";
				atype = ACTION;
				acost = 5;
				break;
			case ADVENTURE:
				aname = "Adventure";
				atype = ACTION;
				acost = 6;
				break;
		}
	}
	else{
		r = CardStringToNumber(_name);
		goto flagSetCard;
	}
}

//============================================================================
// Name        : GetName()
// Author      : SWH
// Version     : 1.1
// Param       : aname
// Return      : card name
// Deprecated  : using
// See         : card.cpp, player.cpp, shop.cpp simulation.cpp
// Todo        : get card name
// Bug         :
//===========================================================================
string Card::GetName(){
	return aname;
}

//============================================================================
// Name        : IsAction()
// Author      : SWH
// Version     : 1.1
// Param       : atype
// Return      : bool
// Deprecated  : using
// See         : card.cpp, player.cpp, simulation.cpp
// Todo        : check this card is action card?
// Bug         :
//===========================================================================
bool Card::IsAction(){
	if(atype == ACTION){
		return true;
	}
	else{
		return false;
	}
}

//============================================================================
// Name        : GetType()
// Author      : SWH
// Version     : 1.1
// Param       : atype
// Return      : bool
// Deprecated  : using
// See         : card.cpp, player.cpp
// Todo        : get card type (action, tresure,victory)
// Bug         :
//===========================================================================
cardType Card::GetType(){
	return atype;
}

//============================================================================
// Name        : CardAction()
// Author      : SWH
// Version     : 1.1
// Param       : cardName
// Return      : card num
// Deprecated  : using
// See         : simulation.cpp
// Todo        : action card execute
// Bug         :
//===========================================================================
/* Input << player */
/* Output >> -1: wrong action, 0: done, else: special case */
int Card::CardAction(Player *player, string cardName, Shop *shop){
	int r = CardStringToNumber(cardName);
	cout << "cardaction in : " << cardName << ", out : " << r << endl;
	switch(r){
		case CELLAR:
			return ActionCellar(player);
		case CHAPEL:
			return ActionChapel(player);
		case MOAT:
			return ActionMoat(player);
		case CHANCELLOR:
			return ActionChancellor(player);
		case VILIAGE:
			return ActionViliage(player);
		case WOODCUTTER:
			return ActionWoodcutter(player);
		case WORKSHOP:
			return ActionWorkshop(player);
		case BUREAUCRAT:
			return ActionBureaucrat(player);
		case FEAST:
			return ActionFeast(player);
		case GARDENS:
			return -1;
		case MILITIA:
			return ActionMilitia(player);
		case MONEYLENDER:
			return ActionMoneylender(player);
		case REMODEL:
			return ActionRemodel(player, shop);
		case SMITHY:
			return ActionSmithy(player);
		case SPY:
			return ActionSpy(player);
		case THIEF:
			return ActionThief(player);
		case THRONEROOM:
			return ActionThroneroom(player);
		case COUNCILROOM:
			return ActionCouncilroom(player);
		case FESTIVAL:
			return ActionFestival(player);
		case LABORATORY:
			return ActionLaboratory(player);
		case LIBRARY:
			return ActionLibrary(player);
		case MARKET:
			return ActionMarket(player);
		case MINE:
			return ActionMine(player);
		case WITCH:
			return ActionWitch(player);
		case ADVENTURE:
			return ActionAdventure(player);
		default:
			return -1;
	}
}

//============================================================================
// Name        : ActionAdventure()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionAdventure
// Bug         :
//===========================================================================
int Card::ActionAdventure(Player *player){
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->RevealDeck(TREASURE,2,HAND,DISCARD);
	return 0;
};

//============================================================================
// Name        : ActionBureaucrat()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionBureaucrat
// Bug         :
//===========================================================================
int Card::ActionBureaucrat(Player *player){
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->GainCard("Silver", 1, DECK);
	return BUREAUCRAT;
};

//============================================================================
// Name        : ActionCellar()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionCellar
// Bug         :
//===========================================================================
int Card::ActionCellar(Player *player){
	int client = player->GetClient();
	int temp = CELLAR;
	send(client,&temp,sizeof(int),0);
	recv(client,&temp,sizeof(int),0);
	player->AddAction(1);
	int count = player->DiscardCard(temp);
	player->DrawCard(count);
	return 0;
};

//============================================================================
// Name        : ActionChancellor()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionChancellor
// Bug         :
//===========================================================================
int Card::ActionChancellor(Player *player){
	int client = player->GetClient();
	int temp = CHANCELLOR;
	char choice;
	send(client,&temp,sizeof(int),0);
	recv(client,&choice,sizeof(char),0);
	if(choice == 'y'){
		player->DiscardDeck(player->GetDeckSize());
	}
	player->AddCoin(2);
	return 0;
}

//============================================================================
// Name        : ActionChapel()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionChapel
// Bug         :
//===========================================================================
int Card::ActionChapel(Player *player){
	int client = player->GetClient();
	int temp = CHAPEL;
	int count;
	send(client,&temp,sizeof(int),0);
	recv(client,&count,sizeof(int),0);
	for(int i=0;i<count;i++){
		player->SendHandList();
		recv(client,&temp,sizeof(int),0);
		player->TrashCard(temp);
	}
	return 0;
};

//============================================================================
// Name        : ActionCouncilroom()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionCouncilroom
// Bug         :
//===========================================================================
int Card::ActionCouncilroom(Player *player){
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(4);
	player->AddBuy(1);
	return COUNCILROOM;
};

//============================================================================
// Name        : ActionFeast()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionFeast
// Bug         :
//===========================================================================
int Card::ActionFeast(Player *player){
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	//player.gainCardChoose(1,5,DISCARD);
	return FEAST;
};

//============================================================================
// Name        : ActionFestival()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionFestival
// Bug         :
//===========================================================================
int Card::ActionFestival(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->AddAction(2);
	player->AddBuy(1);
	player->AddCoin(2);
	return 0;
};

//============================================================================
// Name        : ActionLaboratory()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionLaboratory
// Bug         :
//===========================================================================
int Card::ActionLaboratory(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(2);
	player->AddAction(1);
	return 0;
};

//============================================================================
// Name        : ActionLaboratory()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionLaboratory
// Bug         : can not execute perfectly
//===========================================================================
int Card::ActionLibrary(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	while (player->GetCardCount() < 7) {
		Card *top = player->GetDeckFront();
		if (top->IsAction()) {
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
			player->DiscardDeck(1);
		}
		else {
			player->DrawCard(1);
		}
	}
	return 0;
}

//============================================================================
// Name        : ActionMarket()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionMarket
// Bug         :
//===========================================================================
int Card::ActionMarket(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(1);
	player->AddAction(1);
	player->AddBuy(1);
	player->AddCoin(1);
	return 0;
};

//============================================================================
// Name        : ActionMilitia()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionMilitia
// Bug         :
//==========================================================================
int Card::ActionMilitia(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->AddCoin(1);
	return MILITIA;
};

//============================================================================
// Name        : ActionMine()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionMine
// Bug         :
//==========================================================================
int Card::ActionMine(Player *player) {
	int client = player->GetClient();
	int temp = MINE;
	send(client,&temp,sizeof(int),0);
	player->SendHandList();
	recv(client,&temp,sizeof(int),0);
	if(temp < 0 || temp >= player->GetHandSize()){
	}
	else if(player->GetHandName(temp) == "Copper"){
		Card c;
		c.SetCard("Silver");
		player->TrashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else if(player->GetHandName(temp) == "Silver"){
		Card c;
		c.SetCard("Gold");
		player->TrashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else if(player->GetHandName(temp) == "Gold"){
		Card c;
		c.SetCard("Gold");
		player->TrashCard(temp);
		player->gainCard(c,1,HAND);
	}
	else{
	}
	return 0;
}

//============================================================================
// Name        : ActionMoat()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionMoat
// Bug         :
//==========================================================================
int Card::ActionMoat(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(2);
	return 0;
}

//============================================================================
// Name        : ActionMoneylender()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionMoneylender
// Bug         :
//==========================================================================
int Card::ActionMoneylender(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	for(int i=0;i<player->GetHandSize();i++){
		if(player->GetHandName(i) == "Copper"){
			player->TrashCard(i);
			player->AddCoin(3);
			break;
		}
	}
	return 0;
}

//============================================================================
// Name        : ActionRemodel()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionRemodel
// Bug         :
//==========================================================================
int Card::ActionRemodel(Player *player, Shop *shop) {
	int client = player->GetClient();
	int temp = REMODEL;
	send(client,&temp,sizeof(int),0);
/*
	int value = player.trashCard(ANY, 1);
	if (value != -1) {
		player.gainCard(ANY, 1, value + 2, DISCARD);
	}
*/
	player->SendHandList();
	recv(client,&temp,sizeof(int),0);
	int value = player->GetHand(temp)->GetCost() + 2;
	int choose;
	player->TrashCard(temp);

	send(client,&value,sizeof(int),0);
	recv(client,&choose,sizeof(int),0);
	if(choose == 0){ // turn end
	}
	else{
		choose--;
		if(value >= shop->GetCardCost(choose) && shop->GetCardRemain(choose) > 0){
			player->gainCard(shop->GetCard(choose), 1, DISCARD);
			shop->UpdateCardRemain(choose,-1);
		}
		else{
		}
	}
	return 0;
}

//============================================================================
// Name        : ActionSmithy()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionSmithy
// Bug         :
//==========================================================================
int Card::ActionSmithy(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(3);
	return 0;
}

//============================================================================
// Name        : ActionSpy()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionSpy
// Bug         : unembodiment
//==========================================================================
int Card::ActionSpy(Player *player){
	int client = player->GetClient();
	int temp = SPY;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(1);
	player->AddAction(1);
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

//============================================================================
// Name        : ActionThief()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionThief
// Bug         : unembodiment
//==========================================================================
int Card::ActionThief(Player *player) {
	int client = player->GetClient();
	int temp = THIEF;
	send(client,&temp,sizeof(int),0);
	return THIEF;
}

//============================================================================
// Name        : ActionThroneroom()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionThroneroom
// Bug         : unembodiment
//==========================================================================
int Card::ActionThroneroom(Player *player) {
	int client = player->GetClient();
	int temp = THRONEROOM;
	send(client,&temp,sizeof(int),0);
	return THRONEROOM;
}

//============================================================================
// Name        : ActionViliage()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionViliage
// Bug         :
//==========================================================================
int Card::ActionViliage(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(1);
	player->AddAction(2);
	return 0;
}

//============================================================================
// Name        : ActionWitch()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionWitch
// Bug         :
//==========================================================================
int Card::ActionWitch(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->DrawCard(2);
	return WITCH;
}

//============================================================================
// Name        : ActionWoodcutter()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionWoodcutter
// Bug         :
//==========================================================================
int Card::ActionWoodcutter(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->AddCoin(2);
	player->AddBuy(1);
	return 0;
}

//============================================================================
// Name        : ActionWorkshop()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : 0
// Deprecated  : using
// See         : card.cpp
// Todo        : execute  ActionWorkshop
// Bug         :
//==========================================================================
int Card::ActionWorkshop(Player *player) {
	int client = player->GetClient();
	int temp = 0;
	send(client,&temp,sizeof(int),0);
	player->gainCard(ANY, 1, 4, DISCARD);
	return 0;
}

//============================================================================
// Name        : PrintCard()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : NULL
// Deprecated  : using
// See         : player.cpp
// Todo        : print card name
// Bug         :
//==========================================================================
void Card::PrintCard(){
	cout << aname << endl;
};

//============================================================================
// Name        : GetValue()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : avalue
// Deprecated  : using
// See         : player.cpp
// Todo        : get card value
// Bug         :
//==========================================================================
int Card::GetValue(){
	return avalue;
};

//============================================================================
// Name        : GetCost()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : acost
// Deprecated  : using
// See         : player.cpp card.cpp shop.cpp
// Todo        : get card cost
// Bug         :
//==========================================================================
int Card::GetCost(){
	return acost;
};
//============================================================================
// Name        : GetScore()
// Author      : SWH
// Version     : 1.1
// Param       : player
// Return      : ascore
// Deprecated  : using
// See         : player.cpp card.cpp shop.cpp
// Todo        : get card score
// Bug         :
//==========================================================================
int Card::GetScore(){
	return ascore;
};
