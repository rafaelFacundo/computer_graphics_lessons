main: main.o Sphere.o Scenery.o Objects.o Vector.o SdlFunctions.o Cylinder.o Cone.o Plan.o
	g++ SdlFunctions.o Scenery.o Plan.o Vector.o Objects.o Cylinder.o Sphere.o Cone.o main.o -lSDL2 -o main

main.o: Sphere.h SdlFunction.h
	g++ -c main.cpp -o main.o

Scenery.o: scenery.h
	g++ -c Scenery.cpp -o Scenery.o

Cone.o: Cone.h
	g++ -c Cone.cpp -o Cone.o

Cylinder.o: Cylinder.h
	g++ -c Cylinder.cpp -o Cylinder.o

Sphere.o: Sphere.cpp Sphere.h returnType.h
	g++ -c Sphere.cpp -o Sphere.o

Plan.o: Plan.cpp Plan.h 
	g++ -c Plan.cpp -o Plan.o

Objects.o: Objects.cpp Objects.h returnType.h
	g++ -c Objects.cpp -o Objects.o

Vector.o: Vector.cpp Vector.h
	g++ -c Vector.cpp -o Vector.o 

SdlFunctions.o: SdlFunction.h
	g++ -c SdlFunctions.cpp -o SdlFunctions.o

clean:
	rm *.o