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
	
	send(client[pos],buffer[pos],BUFSIZE,0);
	while(state == 1);
	send(client[pos],&pos,sizeof(int),0);
	//sendPlayerList(pos);
	//sendShopList(pos);
	while(state == 2);
	player[pos].initTurn();
	while(1){
		if(turn == pos){
			int temp = turn;
			strcpy(buffer[pos],"Your Turn!");
			//cout << "case1 : " << temp << ", " << pos << ", " << buffer[pos] << endl;
			//cout << "------------" << endl;
			//player[pos].printHand();
			//cout << "------------" << endl;
			send(client[pos],&temp,sizeof(int),0);
			send(client[pos],buffer[pos],BUFSIZE,0);
			sendPlayerList(pos);
			sendShopList(pos);
			sendHandList(pos);
			int state = player[pos].getState();
			//cout << "after assign state" << endl;
			
			if(state == ACTIONSTATE){
				send(client[pos],&state,sizeof(int),0);
			}
			if(state == BUYSTATE){
				send(client[pos],&state,sizeof(int),0);
				int money = player[pos].getMoney();
				int buyCount = player[pos].getBuy();
				int choose, result;
				while(buyCount > 0){
					send(client[pos],&money,sizeof(int),0);
					send(client[pos],&buyCount,sizeof(int),0);
					recv(client[pos],&choose,sizeof(int),0);
					if(choose == 0){ // turn end
						break;
					}
					else{
						choose--;
						if(money >= shop.getCardCost(choose) && shop.getCardRemain(choose) > 0){
							player[pos].gainCard(shop.getCardName(choose), 1, DISCARD);
							money -= shop.getCardCost(choose);
							buyCount -= 1;
							shop.updateCardRemain(choose,-1);
							result = 1;
						}
						else{
							result = 0;
						}
						send(client[pos],&result,sizeof(int),0);
					}
				}
				cout << "Turn end" << endl;
				turn = (turn + 1) % number;
			}
			player[pos].initTurn();
		}
		else{
			int len = sprintf(buffer[pos],"%s's Turn!",player[turn].getName().c_str());
			int temp = turn;
			//cout << "case2 : " << temp << ", " << pos << ", " << buffer[pos] << endl;
			send(client[pos],&temp,sizeof(int),0);
			send(client[pos],buffer[pos],BUFSIZE,0);
			sendPlayerList(pos);
			sendShopList(pos);
			sendHandList(pos);
			while(turn != pos);
			//cout << "AFTER WHILE" << endl;
			send(client[pos],&turn,sizeof(int),0);
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
		int len = sprintf(buffer[pos],"%d) %s, cost : %d, remain : %d\n",i+1,shop.getCardName(i).c_str(), shop.getCardCost(i), shop.getCardRemain(i));
		send(client[pos],buffer[pos],BUFSIZE,0);
	}
}

void Simulation::sendHandList(int pos){
	int temp = player[pos].getHandSize();
	send(client[pos],&temp,sizeof(int),0);
	for(int i=0;i<temp;i++){
		strcpy(buffer[pos],player[pos].getHandName(i).c_str());
		send(client[pos],buffer[pos],BUFSIZE,0);
	}
}
