all:
	#g++ src/main.cpp -o exec
	g++ src/room.cpp src/item.cpp src/container.cpp src/creature.cpp src/main.cpp -o exec