COMP = g++
SRC = src/main.cpp src/room.cpp src/item.cpp src/container.cpp src/creature.cpp src/triggers.cpp

all: zork

zork:
	$(COMP) $(SRC) -o zork

clean:
	rm zork