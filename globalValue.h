#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

typedef int cardType;
typedef int place;
typedef int position;

#define TREASURECOUNT 3
#define VICTORYCOUNT 3
#define BASICCARDCOUNT 10
#define EXTRACOUNT 1
#define CARDCOUNT TREASURECOUNT + VICTORYCOUNT + BASICCARDCOUNT + EXTRACOUNT
#define EXPANSION 0
#define ORIGINAL 25
#define TOTALACTION ORIGINAL

#define INF -2
#define ALL -1

#define	CELLAR		1
#define	CHAPEL		2
#define	MOAT		3
#define	CHANCELLOR	4
#define	VILIAGE		5
#define	WOODCUTTER	6
#define	WORKSHOP	7
#define	BUREAUCRAT	8
#define	FEAST		9
#define	GARDENS		10
#define	MILITIA		11
#define	MONEYLENDER	12
#define	REMODEL		13
#define	SMITHY		14
#define	SPY		15
#define	THIEF		16
#define	THRONEROOM	17
#define	COUNCILROOM	18
#define	FESTIVAL	19
#define	LABORATORY	20
#define	LIBRARY		21
#define	MARKET		22
#define	MINE		23
#define	WITCH		24
#define	ADVENTURE	25

#define MAXPLAYER 4
#define BUFSIZE 1024
//#define PLAYERCOUNT 4

#define TREASURE 1
#define ACTION 2
#define VICTORY 4
#define CURSE 8
#define ANY 16

#define HAND 1
#define DECK 2
#define DISCARD 4
#define TRASH 8

#define TOP 1
#define BOTTOM 0
#endif

