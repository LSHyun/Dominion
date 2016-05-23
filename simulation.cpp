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
		strcpy(buffer[i],buf);
	}
	state = 1;
	shop.initShop(number);
	shop.printShop();
	state = 2;
	
}

void Simulation::subRun(int pos){
	while(state == 0);
	cout << "SubRun start " << pos << endl;
	//cout << buffer[number];
	send(client[pos],buffer[pos],BUFSIZE,0);
	while(state == 1);
	sendPlayerList(pos);
	//cout << buffer[number];
	//send(client[number],buffer[number],BUFSIZE,0);
	while(state == 2);
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

