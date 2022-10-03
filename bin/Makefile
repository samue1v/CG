all: program

program: ../Links/main.o ../Links/space3D.o ../Links/scene.o ../Links/object.o ../Links/material.o ../Links/shapes.o ../Links/reflect.o ../Links/light.o ../Links/intensity.o ../Links/color.o ../Links/vector.o ../Links/coordinate.o ../Links/canvas.o
	g++ ../Links/main.o ../Links/space3D.o ../Links/scene.o ../Links/object.o ../Links/material.o ../Links/shapes.o ../Links/reflect.o ../Links/light.o ../Links/intensity.o ../Links/color.o ../Links/vector.o ../Links/coordinate.o ../Links/canvas.o -o program

../Links/canvas.o:
	g++ -o ../Links/canvas.o ../Canvas_/Canvas.cpp -c

../Links/coordinate.o:
	g++ -o ../Links/coordinate.o ../DataStructures/Coordinate.cpp -c

../Links/vector.o:
	g++ -o ../Links/vector.o ../DataStructures/Vector.cpp -c

../Links/color.o:
	g++ -o ../Links/color.o ../Ilumination/Color.cpp -c

../Links/intensity.o:
	g++ -o ../Links/intensity.o ../Ilumination/Intensity.cpp -c

../Links/light.o:
	g++ -o ../Links/light.o ../Ilumination/Light.cpp -c

../Links/reflect.o:
	g++ -o ../Links/reflect.o ../Ilumination/Reflect.cpp -c

../Links/shapes.o:
	g++ -o ../Links/shapes.o ../Object_/Shapes.cpp -c

../Links/material.o:
	g++ -o ../Links/material.o ../Object_/Material.cpp -c

../Links/object.o:
	g++ -o ../Links/object.o ../Object_/Object.cpp -c

../Links/scene.o:
	g++ -o ../Links/scene.o ../World/Scene.cpp -c

../Links/space.o:
	g++ -o ../Links/space3D.o ../World/Space3D.cpp -c

../Links/main.o:
	g++ -o ../Links/main.o ../Main/main.cpp -c
