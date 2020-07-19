
all: dijkstras

dijkstras: dijkstras.cpp
	g++ dijkstras.cpp -o dijkstras

clean:
	rm dijkstras
