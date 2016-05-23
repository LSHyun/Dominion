#include<iostream>
#include<stdio.h>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>
#include"serverClient.h"

using namespace std;

void *newConnection(void*);
void *simulationMainRun(void *arg);

struct info{
	int *client, *status, *totalPlayerCount, *readyPlayerCount;
	int number;
	Simulation *simulation;
	string *name;
};

class MainServer{
private:
	int server, *client, totalPlayerCount, readyPlayerCount;
	pthread_t ptClient[CLIENTCOUNT];
	int *status;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr[CLIENTCOUNT];
	socklen_t client_size[CLIENTCOUNT];
	string *name;
	Simulation *simulation;
public:
	void run();
	void makeNewRoom();
	void end();
	void init();
	//void *newConnection(void*);
	int getEmptyPlace();
	int getEmptyClientNumber();
};
class SubServer{
	string name;
	int people;
};
void MainServer::makeNewRoom(){
	int number = getEmptyPlace();
};
void MainServer::run(){
	int number = getEmptyClientNumber();
	char buffer[20];
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server < 0){
		cout << "Error establising connection." << endl;
		exit(1);
	}
	cout << "Server Sockect connection created..." << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(MAINPORT);


	if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		cout << "Error binding socket..." << endl;
		exit(1);
	}
	cout << "Looking for clients..." << endl;

	while(1){
		int len = sprintf(buffer,"%d",number);
		struct info *_info = new info;
		listen(server,1);
		client_size[number] = sizeof(client_addr[number]);
		client[number] = accept(server, (struct sockaddr*)&client_addr[number], &client_size[number]);
		status[number] = 1;

		_info->client = client;
		_info->number = number;
		_info->status = status;
		_info->totalPlayerCount = &totalPlayerCount;
		_info->readyPlayerCount = &readyPlayerCount;
		_info->name = name;
		_info->simulation = simulation;
		++totalPlayerCount;
		int temp = pthread_create(&ptClient[number],NULL,newConnection,_info);
		//int temp = pthread_create(&ptClient[number],NULL,newConnection,&client[number]);
		
		number = getEmptyClientNumber();
		while(number == -1){
			sleep(1);
			number = getEmptyClientNumber();
		}
	}
};

/* status = -1 : empty, 0 : wait client, 1 : running */
int MainServer::getEmptyClientNumber(){
	
	for(int i=0;i<CLIENTCOUNT;i++){
		if(status[i] == -1){
			cout << "return value : " << i << endl;
			return i;
		}
	}
	return -1;
}

void MainServer::end(){
};

void MainServer::init(){
	simulation = new Simulation;
	name = new string[CLIENTCOUNT];
	status = new int[CLIENTCOUNT];
	client = new int[CLIENTCOUNT];
	for(int i=0;i<CLIENTCOUNT;i++){
		//status[i] = new int;
		status[i] = -1;
	}
};

int MainServer::getEmptyPlace(){
	return 0;
}
//void* MainServer::newConnection(void *arg){
void* newConnection(void *arg){
	struct info *temp = (struct info*)arg;
	//int client = *temp;
	Simulation *simulation = temp->simulation;
	int *client = temp->client;
	int number = temp->number;
	int *status = temp->status;
	int *readyPlayerCount = temp->readyPlayerCount;
	int *totalPlayerCount = temp->totalPlayerCount;
	int ready = 0;
	int command;
	string *name = temp->name;
	//int *client = (int *)arg;
	char sendBuffer[BUFSIZE], recvBuffer[BUFSIZE];
	cout << client[number] << ", " << number << endl;

	int len = sprintf(sendBuffer,"%d",number);
	send(client[number],sendBuffer,BUFSIZE,0);
	recv(client[number],recvBuffer,BUFSIZE,0);
	//send(,sendBuffer,BUFSIZE,0);
	string temp_name(recvBuffer);
	name[number] = temp_name;
	cout << "Number : " << number << ", Name : " << name[number] << " entered" << endl;
	//strcpy(sendBuffer, "You entered Dominion Server!");
	//send(*client,sendBuffer,BUFSIZE,0);
	//cout << "???" << endl;
	// This is from client (number) 
	//recv(*client,recvBuffer,BUFSIZE,0);

	do{
		recv(client[number],&command,sizeof(int),0);
		if(command == 1){
			int len = 0;
			for(int i=0;i<CLIENTCOUNT;i++){
				if(status[i] == 1){
					len = sprintf(sendBuffer+len,"Number : %d, Name : %s\n",i,name[i].c_str());
				}
			}
			send(client[number],sendBuffer,BUFSIZE,0);
		}
		else if(command == 2){
			ready = 1;
			++*readyPlayerCount;
			simulation->registPlayer(&client[number],name[number],number);
			if(*readyPlayerCount == *totalPlayerCount){
				pthread_t pt;
				int temp = pthread_create(&pt,NULL,simulationMainRun,simulation);
				simulation->subRun(number);
			}
			else{
				while(*readyPlayerCount == *totalPlayerCount);
				simulation->subRun(number);
			}
			
		}
		else if(command == 3){
			cout << "Client " << number << ", Name : " << name[number] << " end" << endl;
			close(client[number]);
			if(ready == 1){
				--*readyPlayerCount;
			}
			--*totalPlayerCount;
			status[number] = -1;
		}
		else{
		}
	}
	while(command != 3);
};

void *simulationMainRun(void *arg){
	cout << "Main run start" << endl;
	Simulation *simulation = (Simulation *)arg;
	simulation->mainRun();
};

int main(){
	MainServer mainServer;
	mainServer.init();
	mainServer.run();
	return 0;
};

