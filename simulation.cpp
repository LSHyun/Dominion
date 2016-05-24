#include"simulation.h"
//============================================================================
// Name        : Simulation()
// Author      : SWH,LSH
// Version     : 1.1
// Param       : applayer,appbuffer,apclient,apclientNumber,anumber,astate
// Return      : NULL
// Deprecated  : Using
// See         : server.cpp
// Todo        : initialize Simulation
// Bug         : No bug
//============================================================================
Simulation::Simulation(){
	applayer = new Player[MAXPLAYER];
	appbuffer = new char*[MAXPLAYER];
	apclient = new int[MAXPLAYER];
	apclientNumber = new int[MAXPLAYER];
	anumber = 0;
	astate = 0;
}
//============================================================================
// Name        : Simulation()
// Author      : SWH,LSH
// Version     : 1.1
// Param       : applayer,appbuffer,apclient,apclientNumber,anumber,astate,anumber
// Return      : NULL
// Deprecated  : Using
// See         : server.cpp
// Todo        : Some client login, Regist that player
// Bug         : No bug
//============================================================================
void Simulation::RegistPlayer(int *_client, string name, int cNumber){
	if(anumber < MAXPLAYER){
		applayer[anumber].SetName(name);
		appbuffer[anumber] = new char[BUFSIZE];
		apclient[anumber] = *_client;
		apclientNumber[anumber] = cNumber;
		anumber++;
	}
	else{
		cout << "Critical error Occured at Simulation::registerPlayer" << endl;
	}
}
//============================================================================
// Name        : MainRun()
// Author      : SWH
// Version     : 1.1
// Param       : applayer,appbuffer,apclient,apclientNumber,anumber,astate,anumber,ashop,aturn,astate
// Return      : NULL
// Deprecated  : Using
// See         : server.cpp
// Todo        : initialize and print basic interface
// Bug         : No bug
//============================================================================
void Simulation::MainRun(){
	char buf[BUFSIZE] = "Game Start\0";
	for(int i=0;i<anumber;i++){
		applayer[i].InitDeck();
		applayer[i].SetClient(apclient[i]);
		strcpy(appbuffer[i],buf);
	}
	astate = 1;
	ashop.InitShop(anumber);
	ashop.PrintShop();
	astate = 2;
	aturn = 0;
	astate = 3;
	while(1){
	}
	
}
//============================================================================
// Name        : Subrun()
// Author      : SWH
// Version     : 1.1
// Param       : applayer,appbuffer,apclient,apclientNumber,anumber,astate,anumber,ashop,aturn,astate
// Return      : NULL
// Deprecated  : Using
// See         : server.cpp
// Todo        : in the room main flow in game
// Bug         : No bug
//============================================================================
void Simulation::SubRun(int pos){
	while(astate == 0);
	cout << "SubRun start " << pos << endl;
	
	send(apclient[pos],appbuffer[pos],BUFSIZE,0);
	while(astate == 1);
	send(apclient[pos],&pos,sizeof(int),0);
	while(astate == 2);
	applayer[pos].InitTurn();
	while(1){
		if(aturn == pos){
			int temp = aturn;
			strcpy(appbuffer[pos],"Your Turn!");
			send(apclient[pos],&temp,sizeof(int),0);
			send(apclient[pos],appbuffer[pos],BUFSIZE,0);
			SendPlayerList(pos);
			SendShopList(pos);
			SendHandList(pos);
			int state = applayer[pos].GetState();
			//cout << "after assign state" << endl;
			send(apclient[pos],&state,sizeof(int),0);
			if(state == ACTIONSTATE){
				int action = applayer[pos].GetAction();
				while(action > 0){
					int result;
					//send(client[pos],&action,sizeof(int),0);
					do{
						SendHandList(pos);
						recv(apclient[pos],&result,sizeof(int),0);
						Card *c = applayer[pos].GetHand(result);
						if(c == NULL){
							int temp = -1;
							result = -1;
							send(apclient[pos],&temp,sizeof(int),0);
						}
						else if(c->IsAction()){
							int tt = result;
							result = c->CardAction(&applayer[pos],c->GetName(),&ashop);
							applayer[pos].DiscardHand(tt);
							applayer[pos].SetAction(applayer[pos].GetAction()-1);
							action = applayer[pos].GetAction();
						}
						else{
							int temp = -1;
							result = -1;
							send(apclient[pos],&temp,sizeof(int),0);
						}
						send(apclient[pos],&result,sizeof(int),0);
					}
					while(result == -1);
					
					send(apclient[pos],&action,sizeof(int),0);
				}
				state = BUYSTATE;
			}
			if(state == BUYSTATE){
				//send(client[pos],&state,sizeof(int),0);
				int money = applayer[pos].GetMoney();
				int buyCount = applayer[pos].GetBuy();
				cout << money << ", " << buyCount << endl;
				cout << "Hand count : " << applayer[pos].GetHandSize() << endl;
				applayer[pos].PrintHand();
				int choose, result;
				while(buyCount > 0){
					send(apclient[pos],&money,sizeof(int),0);
					send(apclient[pos],&buyCount,sizeof(int),0);
					recv(apclient[pos],&choose,sizeof(int),0);
					if(choose == 0){ // turn end
						break;
					}
					else{
						choose--;
						if(money >= ashop.GetCardCost(choose) && ashop.GetCardRemain(choose) > 0){
							applayer[pos].gainCard(ashop.GetCard(choose), 1, DISCARD);
							money -= ashop.GetCardCost(choose);
							buyCount -= 1;
							ashop.UpdateCardRemain(choose,-1);
							result = 1;
						}
						else{
							result = 0;
						}
						send(apclient[pos],&result,sizeof(int),0);
					}
				}
				cout << "Turn end" << endl;
				aturn = (aturn + 1) % anumber;
			}
			applayer[pos].InitTurn();
		}
		else{
			int len = sprintf(appbuffer[pos],"%s's Turn!",applayer[aturn].GetName().c_str());
			int temp = aturn;
			//cout << "case2 : " << temp << ", " << pos << ", " << buffer[pos] << endl;
			send(apclient[pos],&temp,sizeof(int),0);
			send(apclient[pos],appbuffer[pos],BUFSIZE,0);
			SendPlayerList(pos);
			SendShopList(pos);
			SendHandList(pos);
			while(aturn != pos);
			//cout << "AFTER WHILE" << endl;
			send(apclient[pos],&aturn,sizeof(int),0);
		}
	}
}
//============================================================================
// Name        : CNumberToNumber()
// Author      : SWH
// Version     : 1.1
// Param       : apclient
// Return      : NULL
// Deprecated  : Using
// See         :
// Todo        : client number check
// Bug         : No bug
//============================================================================
int Simulation::CNumberToNumber(int cNumber){
	for(int i=0;i<MAXPLAYER;i++){
		if(apclientNumber[i] == cNumber){
			return i;
		}
	}
	return -1;
}
//============================================================================
// Name        : SendPlayerList()
// Author      : SWH
// Version     : 1.1
// Param       : apclient, anumber
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp/SubRun
// Todo        : send player list to some client
// Bug         : No bug
//============================================================================
void Simulation::SendPlayerList(int pos){
	int temp = anumber;
	send(apclient[pos],&temp,sizeof(int),0);
	for(int i=0;i<anumber;i++){
		int len = sprintf(appbuffer[pos],"Player %d : %s\n",i,applayer[i].GetName().c_str());
		//cout << buffer[pos] << " in number : " << i << endl;
		send(apclient[pos],appbuffer[pos],BUFSIZE,0);
	}
}
//============================================================================
// Name        : SendShopList()
// Author      : SWH
// Version     : 1.1
// Param       : apclient, anumber, ashop
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp/SubRun
// Todo        : send shop list to some client
// Bug         : No bug
//============================================================================
void Simulation::SendShopList(int pos){
	int temp = CARDCOUNT;
	send(apclient[pos],&temp,sizeof(int),0);
	for(int i=0;i<CARDCOUNT;i++){
		int len = sprintf(appbuffer[pos],"%d) %s, cost : %d, remain : %d\n",i+1,ashop.GetCardName(i).c_str(), ashop.GetCardCost(i), ashop.GetCardRemain(i));
		send(apclient[pos],appbuffer[pos],BUFSIZE,0);
	}
}
//============================================================================
// Name        : SendShopList()
// Author      : SWH
// Version     : 1.1
// Param       : apclient, anumber, aplayer
// Return      : NULL
// Deprecated  : Using
// See         : simulation.cpp/SubRun
// Todo        : send hand cards list to some client
// Bug         : No bug
//============================================================================
void Simulation::SendHandList(int pos){
	int temp = applayer[pos].GetHandSize();
	send(apclient[pos],&temp,sizeof(int),0);
	for(int i=0;i<temp;i++){
		strcpy(appbuffer[pos],applayer[pos].GetHandName(i).c_str());
		send(apclient[pos],appbuffer[pos],BUFSIZE,0);
	}
}
