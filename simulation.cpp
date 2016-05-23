#include"simulation.h"
Simulation::Simulation(){
	player = new Player[MAXPLAYER];
	buffer = new char*[MAXPLAYER];
	client = new int[MAXPLAYER];
	clientNumber = new int[MAXPLAYER];
	number = 0;
	state = 0;
}

void Simulation::registPlayer(int *_client, string name, int cNumber){
	if(number < MAXPLAYER){
		player[number].setName(name);
		buffer[number] = new char[BUFSIZE];
		client[number] = *_client;
		clientNumber[number] = cNumber;
		number++;
	}
	else{
		cout << "Critical error Occured at Simulation::registerPlayer" << endl;
	}
}

void Simulation::mainRun(){
	char buf[BUFSIZE] = "Game Start\0";
	for(int i=0;i<number;i++){
		player[i].initDeck();
		strcpy(buffer[i],buf);
	}
	state = 1;
	shop.initShop(number);
	shop.printShop();
	state = 2;
	turn = 0;
	state = 3;
	while(1){
	}
	
}

void Simulation::subRun(int pos){
	while(state == 0);
	cout << "SubRun start " << pos << endl;
	player[pos].revealDeck(ANY,5,HAND,DISCARD);
	send(client[pos],buffer[pos],BUFSIZE,0);
	while(state == 1);
	sendPlayerList(pos);
	sendShopList(pos);
	while(state == 2);
	while(1){
		if(turn == pos){
			strcpy(buffer[pos],"Your Turn!");
			//cout << "------------" << endl;
			//player[pos].printHand();
			//cout << "------------" << endl;
			send(client[pos],buffer[pos],BUFSIZE,0);
		}
		else{
			int len = sprintf(buffer[pos],"%s's Turn!",player[turn].getName().c_str());
			send(client[pos],buffer[pos],BUFSIZE,0);
		}
	}
}

int Simulation::cNumberToNumber(int cNumber){
	for(int i=0;i<MAXPLAYER;i++){
		if(clientNumber[i] == cNumber){
			return i;
		}
	}
	return -1;
}

void Simulation::sendPlayerList(int pos){
	int temp = number;
	send(client[pos],&temp,sizeof(int),0);
	for(int i=0;i<number;i++){
		int len = sprintf(buffer[pos],"Player %d : %s\n",i,player[i].getName().c_str());
		//cout << buffer[pos] << " in number : " << i << endl;
		send(client[pos],buffer[pos],BUFSIZE,0);
	}
}

void Simulation::sendShopList(int pos){
	int temp = CARDCOUNT;
	send(client[pos],&temp,sizeof(int),0);
	for(int i=0;i<CARDCOUNT;i++){
		int len = sprintf(buffer[pos],"%d) %s, remain : %d\n",i+1,shop.getCardName(i).c_str(), shop.getCardRemain(i));
		send(client[pos],buffer[pos],BUFSIZE,0);
	}
}

void Simulation::sendHandList(int pos){
	int temp = player[pos].getHandSize();
	send(client[pos],&temp,sizeof(int),0);
	for(int i=0;i<temp+2;i++){
		int len = sprintf(buffer[pos],"%d) %s, remain : %d\n",i+1,shop.getCardName(i).c_str(), shop.getCardRemain(i));
		send(client[pos],buffer[pos],BUFSIZE,0);
	}
}

