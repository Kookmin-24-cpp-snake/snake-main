CC = g++
CCFLAGS = -g

Snake: src/main.o src/Map.o src/Coord.o src/Snake.o src/Item.o src/ItemManager.o src/GameProcess.o src/UIManager.o src/StageManager.o src/Stage.o src/Gate.o src/GateManager.o
	$(CC) $(CCFLAGS) -o Snake main.o Map.o Coord.o Snake.o Item.o ItemManager.o GameProcess.o UIManager.o StageManager.o Stage.o Gate.o GateManager.o -lncurses

Test:
	g++ src/main.cpp src/Map.cpp src/Coord.cpp src/Snake.cpp src/Item.cpp src/ItemManager.cpp src/GameProcess.cpp src/UIManager.cpp src/StageManager.cpp src/Stage.cpp src/Gate.cpp src/GateManager.cpp -lncurses -o /tmp/a.out && /tmp/a.out

MapTest: src/MapTest.o src/Map.o
	$(CC) $(CCFLAGS) -o MapTest MapTest.o Map.o -lncurses


clean:
	rm -f *.o

%.o : %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $<

% : %.cpp
	$(CC) $(CCFLAGS) -o $@ $<