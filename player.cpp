#include"player.h"

void Player::revealDeck(int type, int count, place dest, place other){
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
