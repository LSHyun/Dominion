#include"shop.h"
#include"simulation.h"

using namespace std;

void Shop::InitShop(int _count){
	aplayerCount = _count;
	/* This is for original dominion */
	acard[0].SetCard("Copper");
	acard[1].SetCard("Silver");
	acard[2].SetCard("Gold");
	acard[3].SetCard("Estate");
	acard[4].SetCard("Duchy");
	acard[5].SetCard("Province");
	acard[6].SetCard("Curse");
	for(int i=7;i<CARDCOUNT;i++){
		acard[i].SetCard("RAND");
		if(acard[i].GetType() == VICTORY){
			aremainCard[i] = 12;
		}
		else{
			aremainCard[i] = 10;
		}
	}
	aremainCard[0] = aplayerCount * 10;
	aremainCard[1] = aplayerCount * 10;
	aremainCard[2] = aplayerCount * 10;
	aremainCard[3] = 12;
	aremainCard[4] = 12;
	aremainCard[5] = 10;
	aremainCard[6] = aplayerCount * 10;
}

void Shop::PrintShop(){
	for(int i=0;i<CARDCOUNT;i++){
		cout << acard[i].GetName() << ", " << aremainCard[i] << endl;
	}
};

string Shop::GetCardName(int pos){
	return acard[pos].GetName();
};

int Shop::GetCardRemain(int pos){
	return aremainCard[pos];
};
int Shop::GetCardCost(int pos){
	return acard[pos].GetCost();
};
void Shop::UpdateCardRemain(int pos, int value){
	aremainCard[pos] += value;
};

Card Shop::GetCard(int pos){
	return acard[pos];
};
