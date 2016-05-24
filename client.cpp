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

using namespace std;

class Client{
private:
	string name;
	char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
	int server, number, turn;
	struct sockaddr_in server_addr;
	socklen_t size;
	char ip[20];
public:
	void run();
	void init();
	void printPlayerList();
	void printShopList();
	void playGame();
	void printHandList();
	void printCommand();
	void doSpecialAction(int value);
};

void Client::init(){
	cout << "Choose your name : ";
	cin >> name;
};

void Client::run(){
	struct clientInfo cInfo;
	server = socket(AF_INET, SOCK_STREAM, 0);
	strcpy(ip,"127.0.0.1");
	
	if(server < 0){
		cout << "Error creating socket." << endl;
		exit(1);
	}

	cout << "Client Socket created..." << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(MAINPORT);

	if(connect(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0){
		cout << "Connecting to Server..." << endl;
	}
	strcpy(sendBuffer,name.c_str());
	//recv(server, &number, sizeof(int), 0);
	recv(server, recvBuffer, BUFSIZE, 0);
	number = atoi(recvBuffer);
	send(server, sendBuffer, BUFSIZE, 0);
	//cInfo.number = number;
	//cInfo.name = name;
	cout << "Welcome " << name << endl;
	cout << "You entered Dominion Server!" << endl;
	cout << "1 : show player list" << endl;
	cout << "2 : Ready!" << endl;
	cout << "3 : Leave Dominion Server" << endl;
	
	int command;
	do{
		cin >> command;
		send(server, &command,sizeof(int),0);
		if(command == 1){
			
			recv(server, recvBuffer,BUFSIZE,0);
			cout << recvBuffer;
		}
		else if(command == 2){
			//send(server, &command,sizeof(int),0);
			recv(server, recvBuffer,BUFSIZE,0);
			/* recvBuffer must be "Game Start" */
			cout << recvBuffer << endl;
			int t;
			recv(server,&t,sizeof(int),0);
			number = t;
			
			playGame();
		}
		else if(command == 3){
			//send(server, &command,sizeof(int),0);
		}
		else{
		}
	}
	while(command != 3);
	
	close(server);
	
};

void Client::printPlayerList(){
	int count;
	system("clear");
	cout << "Player list :" << endl;
	recv(server, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(server,recvBuffer,BUFSIZE,0);
		cout << recvBuffer;
	}
};

void Client::printShopList(){
	int count;
	cout << "Shop list :" << endl;
	recv(server, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(server,recvBuffer,BUFSIZE,0);
		cout << recvBuffer;
	}
};

void Client::printHandList(){
	int count;
	cout << "------------------------" << endl;
	recv(server, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(server, recvBuffer,BUFSIZE,0);
		cout << i << ") " << recvBuffer << endl;
	}
	cout << "------------------------" << endl;
}

void Client::playGame(){
	while(1){
		recv(server,&turn,sizeof(int),0);
		recv(server, recvBuffer,BUFSIZE,0);
		//cout << turn << ", " << number << ", " << recvBuffer << endl;
		printPlayerList();
		printShopList();
		printHandList();
		if(turn == number){
			printCommand();
		}
		else{
			cout << "Wait until other's turn end..." << endl;
			recv(server,&turn,sizeof(int),0);
		}
		
	}
}

void Client::printCommand(){
	int state;
	//cout << "in printCommand" << endl;
	recv(server,&state,sizeof(int),0);
	//cout << "in printCommand after recv" << endl;
	if(state == ACTIONSTATE){
		//cout << "in printCommand ACTIONSTATE" << endl;
		int action, result;
		action = 1;
		do{
			do{
				int funcValue;
				cout << "You can use " << action << " action Card!" << endl;
				cout << "Type number what you want to use" << endl;
				cin >> result;
				send(server,&result,sizeof(int),0);
				recv(server,&funcValue,sizeof(int),0); // -1 : fail, 0 : normal, else : special
				if(funcValue > 0){
					doSpecialAction(funcValue);
				}
				recv(server,&result,sizeof(int),0);
			}
			while(result == -1);
			recv(server,&action,sizeof(int),0);
		}
		while(action > 0);
		state = BUYSTATE;
	}
	if(state == BUYSTATE){
		int money, buyCount, choose, result;
		do{
			recv(server,&money,sizeof(int),0);
			recv(server,&buyCount,sizeof(int),0);
			cout << "Your Money : " << money << endl;
			cout << "You can buy " << buyCount << " times!" << endl;
			cout << "0 : End, 1~17 : Card Number" << endl;
			cin >> choose;
			send(server,&choose,sizeof(int),0);
			if(choose == 0){
				break;
			}
			else{
				recv(server,&result,sizeof(int),0);
				if(result == 1){
					--buyCount;
				}
			}
		}
		while(buyCount > 0);
		cout << "Turn end" << endl;
	}
}

void Client::doSpecialAction(int value){
	switch(value){
		case CELLAR:
		{	
			int count;
			cout << "Discard Card! How many? ";
			cin >> count;
			send(server,&count,sizeof(int),0);
			break;
		}
		case CHANCELLOR:
		{
			char choice;
flagChancellor:
			cout << "Discard Deck? (Y/N) ";
			cin >> choice;
			if(choice == 'y' || choice == 'Y'){
				choice = 'y';
			}
			else if(choice == 'n' || choice == 'N'){
				choice = 'n';
			}
			else{
				goto flagChancellor;
			}
			send(server,&choice,sizeof(char),0);
			break;
		}
		case CHAPEL:
		{
			int count;
			cout << "Trash Card! How many?(0~4) ";
			cin >> count;
			send(server,&count,sizeof(int),0);
			for(int i=0;i<count;i++){
				int temp;
				printHandList();
				cout << "Choose Card Number : ";
				cin >> temp;
				send(server,&temp,sizeof(int),0);
			}
			break;
		}
		case REMODEL:
		{
			int temp;
			printHandList();
			cout << "Trash Card! Choose Card Number : ";
			cin >> temp;
			send(server,&temp,sizeof(int),0);
			recv(server,&temp,sizeof(int),0);
			cout << "You can get card under " << temp << "coin" << endl;
			cout << "Choose card number : ";
			cin >> temp;
			send(server,&temp,sizeof(int),0);
			break;
		}

		case MINE:
		{
			int result;
			printHandList();
			cout << "Trash treasure card! number? ";
			cin >> result;
			send(server,&result,sizeof(int),0);
			break;
		}
		default:
		{
		}
	}

}
int main(){
	Client client;
	client.init();
	client.run();
	return 0;
};
