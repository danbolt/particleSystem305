all: compileWin

compileWin: main.o p_vector.o Particle.o Triangle.o Raindrop.o
	g++ -pg -Wall vector.o main.o Particle.o Triangle.o Raindrop.o -o particle -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32

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

clean:
	rm particle.exe main.o vector.o Particle.o Triangle.o Raindrop.o

