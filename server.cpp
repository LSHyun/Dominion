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
	int aserver;
	int *apclient;
	int atotalPlayerCount;
	int areadyPlayerCount;
	pthread_t aptClient[CLIENTCOUNT];
	int *apstatus;
	struct sockaddr_in aserver_addr;
	struct sockaddr_in aclient_addr[CLIENTCOUNT];
	socklen_t aclient_size[CLIENTCOUNT];
	string *apname;
	Simulation *apsimulation;
public:
	void Run();
	void MakeNewRoom();
	void End();
	void Init();
	//void *newConnection(void*);
	int GetEmptyPlace();
	int GetEmptyClientNumber();
};
class SubServer{
	string name;
	int people;
};
void MainServer::MakeNewRoom(){
	int number = GetEmptyPlace();
};
void MainServer::Run(){
	int number = GetEmptyClientNumber();
	char buffer[20];
	
	aserver = socket(AF_INET, SOCK_STREAM, 0);
	if(aserver < 0){
		cout << "Error establising connection." << endl;
		exit(1);
	}
	cout << "Server Sockect connection created..." << endl;

	aserver_addr.sin_family = AF_INET;
	aserver_addr.sin_addr.s_addr = htons(INADDR_ANY);
	aserver_addr.sin_port = htons(MAINPORT);


	if(bind(aserver, (struct sockaddr*)&aserver_addr, sizeof(aserver_addr)) < 0){
		cout << "Error binding socket..." << endl;
		exit(1);
	}
	cout << "Looking for clients..." << endl;

	while(1){
		int len = sprintf(buffer,"%d",number);
		struct info *_info = new info;
		listen(aserver,1);
		aclient_size[number] = sizeof(aclient_addr[number]);
		apclient[number] = accept(aserver, (struct sockaddr*)&aclient_addr[number], &aclient_size[number]);
		apstatus[number] = 1;

		_info->client = apclient;
		_info->number = number;
		_info->status = apstatus;
		_info->totalPlayerCount = &atotalPlayerCount;
		_info->readyPlayerCount = &areadyPlayerCount;
		_info->name = apname;
		_info->simulation = apsimulation;
		++atotalPlayerCount;
		int temp = pthread_create(&aptClient[number],NULL,newConnection,_info);
		//int temp = pthread_create(&ptClient[number],NULL,newConnection,&client[number]);
		
		number = GetEmptyClientNumber();
		while(number == -1){
			sleep(1);
			number = GetEmptyClientNumber();
		}
	}
};

/* status = -1 : empty, 0 : wait client, 1 : running */
int MainServer::GetEmptyClientNumber(){
	
	for(int i=0;i<CLIENTCOUNT;i++){
		if(apstatus[i] == -1){
			cout << "return value : " << i << endl;
			return i;
		}
	}
	return -1;
}

void MainServer::End(){
};

void MainServer::Init(){
	apsimulation = new Simulation;
	apname = new string[CLIENTCOUNT];
	apstatus = new int[CLIENTCOUNT];
	apclient = new int[CLIENTCOUNT];
	for(int i=0;i<CLIENTCOUNT;i++){
		//status[i] = new int;
		apstatus[i] = -1;
	}
};

int MainServer::GetEmptyPlace(){
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
			simulation->RegistPlayer(&client[number],name[number],number);
			if(*readyPlayerCount == *totalPlayerCount){
				pthread_t pt;
				int temp = pthread_create(&pt,NULL,simulationMainRun,simulation);
				simulation->SubRun(number);
			}
			else{
				while(*readyPlayerCount == *totalPlayerCount);
				simulation->SubRun(number);
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
	simulation->MainRun();
};

int main(){
	MainServer mainServer;
	mainServer.Init();
	mainServer.Run();
	return 0;
};

