main: main.o Sphere.o Scenery.o Objects.o Vector.o SdlFunctions.o
	g++ SdlFunctions.o Scenery.o Vector.o Objects.o Sphere.o main.o -lSDL2 -o main

main.o: Sphere.h
	g++ -c main.cpp -o main.o

Scenery.o: scenery.h
	g++ -c Scenery.cpp -o Scenery.o

Sphere.o: Sphere.cpp Sphere.h returnType.h
	g++ -c Sphere.cpp -o Sphere.o

Objects.o: Objects.cpp Objects.h returnType.h
	g++ -c Objects.cpp -o Objects.o

Vector.o: Vector.cpp Vector.h
	g++ -c Vector.cpp -o Vector.o 

SdlFunctions.o:
	g++ -c SdlFunctions.cpp -o SdlFunctions.o

clean:
	rm *.o