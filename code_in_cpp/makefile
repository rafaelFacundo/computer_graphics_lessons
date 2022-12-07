main: ./build/main.o ./build/Sphere.o ./build/Scenery.o ./build/Objects.o ./build/Vector.o ./build/SdlFunctions.o ./build/Cylinder.o ./build/Cone.o ./build/Plan.o ./build/Edge.o ./build/Face.o ./build/Point.o ./build/Mesh.o
	g++ ./build/SdlFunctions.o ./build/Scenery.o ./build/Plan.o ./build/Vector.o ./build/Objects.o ./build/Cylinder.o ./build/Sphere.o ./build/Cone.o ./build/Face.o ./build/Edge.o ./build/Point.o ./build/Mesh.o ./build/main.o -lSDL2 -o main

./build/main.o: ./include/Sphere.h ./include/SdlFunction.h
	g++ -c main.cpp -o ./build/main.o

./build/Scenery.o: ./include/scenery.h
	g++ -c ./lib/Scenery.cpp -o ./build/Scenery.o

./build/Cone.o: ./include/Cone.h
	g++ -c ./lib/Cone.cpp -o ./build/Cone.o

./build/Cylinder.o: ./include/Cylinder.h
	g++ -c ./lib/Cylinder.cpp -o ./build/Cylinder.o

./build/Sphere.o: ./include/Sphere.h ./include/returnType.h
	g++ -c ./lib/Sphere.cpp -o ./build/Sphere.o

./build/Plan.o: ./include/Plan.h
	g++ -c ./lib/Plan.cpp -o ./build/Plan.o

./build/Objects.o: ./include/Objects.h ./include/returnType.h
	g++ -c ./lib/Objects.cpp -o ./build/Objects.o

./build/Vector.o: ./include/Vector.h
	g++ -c ./lib/Vector.cpp -o ./build/Vector.o

./build/SdlFunctions.o: ./include/SdlFunction.h
	g++ -c ./lib/SdlFunctions.cpp -o ./build/SdlFunctions.o

./build/Mesh.o: ./include/Mesh.h
	g++ -c ./lib/Mesh.cpp -o ./build/Mesh.o

./build/Face.o: ./include/Face.h
	g++ -c ./lib/Face.cpp -o ./build/Face.o

./build/Edge.o: ./include/Edge.h
	g++ -c ./lib/Edge.cpp -o ./build/Edge.o

./build/Point.o: ./include/Point.h
	g++ -c ./lib/Point.cpp -o ./build/Point.o


clean:
	rm ./build/*.o
