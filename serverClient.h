#include<string.h>
#include"simulation.h"

using namespace std;

#define SUBSERVERSIZE 1
#define MAINPORT 20000
#define CLIENTCOUNT SUBSERVERSIZE * 4

struct clientInfo{
	string name;
	int number;
};
