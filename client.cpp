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
	string aname;
	char asendBuffer[BUFSIZE];
	char arecvBuffer[BUFSIZE];
	int aserver;
	int anumber;
	int aturn;
	struct sockaddr_in aserver_addr;
	socklen_t asize;
	char aip[20];
public:
	void Run();
	void Init();
	void PrintPlayerList();
	void PrintShopList();
	void PlayGame();
	void PrintHandList();
	void PrintCommand();
	void DoSpecialAction(int value);
};

void Client::Init(){
	cout << "Choose your name : ";
	cin >> aname;
};

void Client::Run(){
	struct clientInfo cInfo;
	aserver = socket(AF_INET, SOCK_STREAM, 0);
	strcpy(aip,"127.0.0.1");
	
	if(aserver < 0){
		cout << "Error creating socket." << endl;
		exit(1);
	}

	cout << "Client Socket created..." << endl;

	aserver_addr.sin_family = AF_INET;
	aserver_addr.sin_addr.s_addr = inet_addr(aip);
	aserver_addr.sin_port = htons(MAINPORT);

	if(connect(aserver, (struct sockaddr*)&aserver_addr, sizeof(aserver_addr)) == 0){
		cout << "Connecting to Server..." << endl;
	}
	strcpy(asendBuffer,aname.c_str());
	//recv(server, &number, sizeof(int), 0);
	recv(aserver, arecvBuffer, BUFSIZE, 0);
	anumber = atoi(arecvBuffer);
	send(aserver, asendBuffer, BUFSIZE, 0);
	//cInfo.number = number;
	//cInfo.name = name;
	cout << "Welcome " << aname << endl;
	cout << "You entered Dominion Server!" << endl;
	cout << "1 : show player list" << endl;
	cout << "2 : Ready!" << endl;
	cout << "3 : Leave Dominion Server" << endl;
	
	int command;
	do{
		cin >> command;
		send(aserver, &command,sizeof(int),0);
		if(command == 1){
			
			recv(aserver, arecvBuffer,BUFSIZE,0);
			cout << arecvBuffer;
		}
		else if(command == 2){
			//send(server, &command,sizeof(int),0);
			recv(aserver, arecvBuffer,BUFSIZE,0);
			/* recvBuffer must be "Game Start" */
			cout << arecvBuffer << endl;
			int t;
			recv(aserver,&t,sizeof(int),0);
			anumber = t;
			
			PlayGame();
		}
		else if(command == 3){
			//send(server, &command,sizeof(int),0);
		}
		else{
		}
	}
	while(command != 3);
	
	close(aserver);
	
};

void Client::PrintPlayerList(){
	int count;
	system("clear");
	cout << "Player list :" << endl;
	recv(aserver, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(aserver,arecvBuffer,BUFSIZE,0);
		cout << arecvBuffer;
	}
};

void Client::PrintShopList(){
	int count;
	cout << "Shop list :" << endl;
	recv(aserver, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(aserver,arecvBuffer,BUFSIZE,0);
		cout << arecvBuffer;
	}
};

void Client::PrintHandList(){
	int count;
	cout << "------------------------" << endl;
	recv(aserver, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(aserver, arecvBuffer,BUFSIZE,0);
		cout << i << ") " << arecvBuffer << endl;
	}
	cout << "------------------------" << endl;
}

void Client::PlayGame(){
	while(1){
		recv(aserver,&aturn,sizeof(int),0);
		recv(aserver, arecvBuffer,BUFSIZE,0);
		//cout << turn << ", " << number << ", " << recvBuffer << endl;
		PrintPlayerList();
		PrintShopList();
		PrintHandList();
		if(aturn == anumber){
			PrintCommand();
		}
		else{
			cout << "Wait until other's turn end..." << endl;
			recv(aserver,&aturn,sizeof(int),0);
		}
		
	}
}

void Client::PrintCommand(){
	int state;
	//cout << "in printCommand" << endl;
	recv(aserver,&state,sizeof(int),0);
	//cout << "in printCommand after recv" << endl;
	if(state == ACTIONSTATE){
		//cout << "in printCommand ACTIONSTATE" << endl;
		int action, result;
		action = 1;
		do{
			do{
				int funcValue;
				PrintHandList();
				cout << "You can use " << action << " action Card!" << endl;
				cout << "Type number what you want to use" << endl;
				cin >> result;
				send(aserver,&result,sizeof(int),0);
				recv(aserver,&funcValue,sizeof(int),0); // -1 : fail, 0 : normal, else : special
				if(funcValue > 0){
					DoSpecialAction(funcValue);
				}
				recv(aserver,&result,sizeof(int),0);
			}
			while(result == -1);
			recv(aserver,&action,sizeof(int),0);
		}
		while(action > 0);
		state = BUYSTATE;
	}
	if(state == BUYSTATE){
		int money, buyCount, choose, result;
		do{
			recv(aserver,&money,sizeof(int),0);
			recv(aserver,&buyCount,sizeof(int),0);
			cout << "Your Money : " << money << endl;
			cout << "You can buy " << buyCount << " times!" << endl;
			cout << "0 : End, 1~17 : Card Number" << endl;
			cin >> choose;
			send(aserver,&choose,sizeof(int),0);
			if(choose == 0){
				break;
			}
			else{
				recv(aserver,&result,sizeof(int),0);
				if(result == 1){
					--buyCount;
				}
			}
		}
		while(buyCount > 0);
		cout << "Turn end" << endl;
	}
}

void Client::DoSpecialAction(int value){
	switch(value){
		case CELLAR:
		{	
			int count;
			cout << "Discard Card! How many? ";
			cin >> count;
			send(aserver,&count,sizeof(int),0);
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
			send(aserver,&choice,sizeof(char),0);
			break;
		}
		case CHAPEL:
		{
			int count;
			cout << "Trash Card! How many?(0~4) ";
			cin >> count;
			send(aserver,&count,sizeof(int),0);
			for(int i=0;i<count;i++){
				int temp;
				PrintHandList();
				cout << "Choose Card Number : ";
				cin >> temp;
				send(aserver,&temp,sizeof(int),0);
			}
			break;
		}
		case REMODEL:
		{
			int temp;
			PrintHandList();
			cout << "Trash Card! Choose Card Number : ";
			cin >> temp;
			send(aserver,&temp,sizeof(int),0);
			recv(aserver,&temp,sizeof(int),0);
			cout << "You can get card under " << temp << "coin" << endl;
			cout << "Choose card number : ";
			cin >> temp;
			send(aserver,&temp,sizeof(int),0);
			break;
		}

		case MINE:
		{
			int result;
			PrintHandList();
			cout << "Trash treasure card! number? ";
			cin >> result;
			send(aserver,&result,sizeof(int),0);
			break;
		}
		default:
		{
		}
	}

}
int main(){
	Client client;
	client.Init();
	client.Run();
	return 0;
};
