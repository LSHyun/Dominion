#include<cstdlib>

#include"player.h"

void Player::initDeck(){
	int temp[10];
	Card tempCard;
	for(int i=0;i<10;i++){
		temp[i] = rand() % 65536;
	}
	deck.resize(10);
	for(int i=0;i<7;i++){
		deck[i].setCard("Copper");
	}
	for(int i=7;i<10;i++){
		deck[i].setCard("Estate");
	}
	for(int i=0;i<9;i++){
		for(int k=1;k<10;k++){
			if(temp[i] < temp[k]){
				int t = temp[i];
				temp[i] = temp[k];
				temp[k] = t;
				tempCard = deck[i];
				deck[i] = deck[k];
				deck[k] = tempCard;
			}
		}
	}
};

void Player::revealDeck(int type, int count, place dest, place other){
	for(int i=0;i<count;i++){
		Card card = deck.front();
		if(type != ANY && type != card.getType()){
			if(other == DISCARD){
				discard.push_back(card);
			
			}
			else if(other == TRASH){
			}
		
		}
		else{
			if(dest == HAND){
				hand.push_back(card);
			}
		}
		deck.pop_front();
	}
};

void Player::gainCard(string name, int count, place dest){
};

void Player::gainCard(cardType type, int count, int price, place dest) {
};

int Player::discardCard(int count){
	return 0;
};
void Player::setName(string _name){
	name = _name;
};

string Player::getName(){
	return name;
};

void Player::addAction(int count){

};

void Player::drawCard(int count){
};

void Player::addCoin(int count){
};

void Player::discardDeck(int count){
};

int Player::trashCard(cardType type, int count){

};

int Player::trashCard(string name, int count){
}; 

void Player::addBuy(int count){
};

Card* Player::getDeckFront(){
};

int Player::getCardCount(){
};

void Player::gainCardChoose(int count, int cost, place to){
};

void Player::printHand(){
	for(int i=0;i<hand.size();i++){
		hand[i].printCard();
	}
};

void Player::getHandSize(){
	return hand.size();
};
