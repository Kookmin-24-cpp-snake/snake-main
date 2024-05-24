MainTest:
	g++ src/MainTest.cpp src/Map.cpp src/Pos.cpp src/Snake.cpp src/Item.cpp src/ItemManager.cpp src/GameProcess.cpp src/UIManager.cpp src/StageManager.cpp src/Stage.cpp -lncurses -o /tmp/a.out && /tmp/a.out

SMITest:
	g++ src/SMITest.cpp src/Map.cpp src/Pos.cpp src/Snake.cpp src/Item.cpp src/ItemManager.cpp -lncurses -o /tmp/a.out && /tmp/a.out

MapTest:
	g++ src/MapTest.cpp src/Map.cpp -lncurses -o /tmp/a.out && /tmp/a.out