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
	int server, number;
	struct sockaddr_in server_addr;
	socklen_t size;
	char ip[20];
public:
	void run();
	void init();
	void printPlayerList();
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
			printPlayerList();
			//recv(server, recvBuffer,BUFSIZE,0);
			//cout << recvBuffer;
			//recv(server,simulation,sizeof(Simulation),0);
			//simulation->clientRun(number);
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
	cout << "Player list :" << endl;
	recv(server, &count,sizeof(int),0);
	for(int i=0;i<count;i++){
		recv(server,recvBuffer,BUFSIZE,0);
		cout << recvBuffer;
	}
};
int main(){
	Client client;
	client.init();
	client.run();
	return 0;
};
