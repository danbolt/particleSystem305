all: compileWin

compileWin: main.o p_vector.o Particle.o Triangle.o Raindrop.o
	g++ -g -Wall vector.o main.o Particle.o Triangle.o Raindrop.o -o particle -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32

main.o:
	g++ -g -Wall -c main.cpp

p_vector.o:
	g++ -g -Wall -c vector.cpp

Particle.o:
	g++ -g -Wall -c Particle.cpp

Traingle.o:
	g++ -g -Wall -c Triangle.cpp

Raindrop.o:
	g++ -g -Wall -c Raindrop.cpp

clean:
	rm particle.exe main.o vector.o Particle.o Triangle.o

