main: main.cpp main.o card.o player.o simulation.o
	g++ -o main main.cpp main.o card.o player.o simulation.o
card.o: card.cpp card.h
	g++ -o card.cpp card.h
player.o: player.cpp player.h
	g++ -o player.cpp player.h
simulation.o: simulation.cpp simulation.h
	g++ -o simulation.cpp simulation.h
clean:
	rm *.o
	rm *.gch
