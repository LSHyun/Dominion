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
	int astate;
	int aturn;
	int anumber;
	int *apclient;
	Player *applayer;
	char **appbuffer;
	int *apclientNumber;
	Shop ashop;
public:
	Simulation();
	void MainRun();
	void SubRun(int number);
	void RegistPlayer(int *_client, string name, int cNumber);
	void Broadcast(char* text);
	void ClientRun(int cNumber);
	int CNumberToNumber(int cNumber);
	void SendPlayerList(int pos);
	void SendShopList(int pos);
	void InitPlayerCard(int pos);
	void SendHandList(int pos);
};
