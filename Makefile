COMP = g++
SRC = src/*.cpp


all: zork

zork:
	$(COMP) $(SRC) -o zork

clean:
	rm zork
