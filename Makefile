all: compileLinux

compileLinux: main.o p_vector.o Particle.o Triangle.o Raindrop.o Flame.o Fire.o Wall.o Player.o Level.o
	g++ -pg -Wall vector.o main.o Particle.o Triangle.o Raindrop.o Flame.o Fire.o Wall.o Player.o Level.o -o particle -lSDL -lGL -lGLU

main.o:
	g++ -pg -Wall -c main.cpp

p_vector.o:
	g++ -pg -Wall -c vector.cpp

Particle.o:
	g++ -pg -Wall -c Particle.cpp

Traingle.o:
	g++ -pg -Wall -c Triangle.cpp

Raindrop.o:
	g++ -pg -Wall -c Raindrop.cpp

Flame.o:
	g++ -pg -Wall -c Flame.cpp

Fire.o:
	g++ -pg -Wall -c Fire.cpp

Wall.o:
	g++ -pg -Wall -c Wall.cpp

Player.o:
	g++ -pg -Wall -c Player.cpp

Level.o:
	g++ -pg -Wall -c Level.cpp

clean:
	rm particle main.o vector.o Particle.o Triangle.o Raindrop.o Flame.o Fire.o Wall.o Player.o Level.o

