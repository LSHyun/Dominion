#pragma once

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

#include"shop.h"
#include"player.h"

using namespace std;

class Simulation{
private:
	int state;
	int number;
	int *client;
	Player *player;
	char **buffer;
	int *clientNumber;
	Shop shop;
public:
	Simulation();
	void mainRun();
	void subRun(int number);
	void registPlayer(int *_client, string name, int cNumber);
	void broadcast(char* text);
	void clientRun(int cNumber);
	int cNumberToNumber(int cNumber);
	void sendPlayerList(int pos);
};
