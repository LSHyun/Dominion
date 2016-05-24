#include"shop.h"
#include"simulation.h"

using namespace std;

//============================================================================
// Name        : InitShop()
// Author      : SWH
// Version     : 1.1
// Param       : acard, aremaincard
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : initialize shop card
// Bug         : No bug
//============================================================================
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

//============================================================================
// Name        : PrintShop()
// Author      : SWH
// Version     : 1.1
// Param       : acard, aremaincard
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : print out card name and card remain
// Bug         : No bug
//============================================================================
void Shop::PrintShop(){
	for(int i=0;i<CARDCOUNT;i++){
		cout << acard[i].GetName() << ", " << aremainCard[i] << endl;
	}
};

//============================================================================
// Name        : GetCardName()
// Author      : SWH
// Version     : 1.1
// Param       : acard
// Return      : card.name
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : get card name
// Bug         : No bug
//============================================================================
string Shop::GetCardName(int pos){
	return acard[pos].GetName();
};

//============================================================================
// Name        : GetCardRemain()
// Author      : SWH
// Version     : 1.1
// Param       : aremaincard
// Return      : remaincard
// Deprecated  : Using
// See         : simulation.cpp
// Todo        : get card remain
// Bug         : No bug
//============================================================================
int Shop::GetCardRemain(int pos){
	return aremainCard[pos];
};

//============================================================================
// Name        : GetCardCost()
// Author      : SWH
// Version     : 1.1
// Param       : acard
// Return      : acard
// Deprecated  : Using
// See         : simulation.cpp card.cpp
// Todo        : get card cost
// Bug         : No bug
//============================================================================
int Shop::GetCardCost(int pos){
	return acard[pos].GetCost();
};

//============================================================================
// Name        : UpdateCardRemain()
// Author      : SWH
// Version     : 1.1
// Param       : aremaincard
// Return      : areamincard
// Deprecated  : Using
// See         : simulation.cpp card.cpp
// Todo        : remain card number adjust
// Bug         : No bug
//============================================================================
void Shop::UpdateCardRemain(int pos, int value){
	aremainCard[pos] += value;
};

//============================================================================
// Name        : GetCard()
// Author      : SWH
// Version     : 1.1
// Param       : acard
// Return      : acard
// Deprecated  : Using
// See         : simulation.cpp card.cpp
// Todo        : get that card
// Bug         : No bug
//============================================================================
Card Shop::GetCard(int pos){
	return acard[pos];
};

//============================================================================
// Name        : IsFinished()
// Author      : SWH
// Version     : 1.1
// Param       : aremainCard
// Return      : bool
// Deprecated  : Using
// See         : simulation.cpp card.cpp
// Todo        : check game is finished
// Bug         : No bug
//============================================================================
bool Shop::IsFinished(){
	int count = 0;
	if(aremainCard[5] == 0){
		return true;
	}
	for(int i=0;i<CARDCOUNT;i++){
		if(aremainCard[i] == 0){
			++count;
		}
	}
	if(count > 2){
		return true;
	}
	else{
		return false;
	}
};
			
