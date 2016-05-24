# Dominion
Dominion in c++, add networking

make file을 만드는 데 실패하여
server와 client를 따로만들어야 합니다.
g++ -std=c++11 -o server server.cpp simulation.cpp player.cpp shop.cpp card.cpp -lpthread
g++ -std=c++11 -o client client.cpp simulation.cpp player.cpp shop.cpp card.cpp -lpthread
를 통하여 실행파일을 만들어야 합니다.

그 후 server는 가만히 있는 상태에서 client를 접속 시킨 후 접속에 성공한 모든 client가 2ready명령어를 실행할 때, 게임이 시작됩니다.
