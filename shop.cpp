#include"shop.h"
#include"simulation.h"

using namespace std;

void Shop::initShop(int _count){
	playerCount = _count;
	/* This is for original dominion */
	card[0].setCard("Copper");
	card[1].setCard("Silver");
	card[2].setCard("Gold");
	card[3].setCard("Estate");
	card[4].setCard("Duchy");
	card[5].setCard("Province");
	card[6].setCard("Curse");
	for(int i=7;i<CARDCOUNT;i++){
		card[i].setCard("RAND");
		if(card[i].getType() == VICTORY){
			remainCard[i] = 12;
		}
		else{
			remainCard[i] = 10;
		}
	}
	remainCard[0] = playerCount * 10;
	remainCard[1] = playerCount * 10;
	remainCard[2] = playerCount * 10;
	remainCard[3] = 12;
	remainCard[4] = 12;
	remainCard[5] = 10;
	remainCard[6] = playerCount * 10;
}

void Shop::printShop(){
	for(int i=0;i<CARDCOUNT;i++){
		cout << card[i].getName() << ", " << remainCard[i] << endl;
	}
};

string Shop::getCardName(int pos){
	return card[pos].getName();
};

int Shop::getCardRemain(int pos){
	return remainCard[pos];
};
int Shop::getCardCost(int pos){
	return card[pos].getCost();
};
void Shop::updateCardRemain(int pos, int value){
	remainCard[pos] += value;
};
