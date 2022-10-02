all: program

canvas: 
	g++ -o ../Links/canvas.o -c ../Canvas_/Canvas.cpp

coordinate:
	g++ -o ../Links/coordinate.o -c ../DataStructures/Coordinate.cpp

vector:
	g++ -o ../Links/vector.o -c ../DataStructures/Vector.cpp

color:
	g++ -o ../Links/color.o -c ../Ilumination/Color.cpp

intensity:
	g++ -o ../Links/intensity.o -c ../Ilumination/Intensity.cpp

light:
	g++ -o ../Links/light.o -c ../Ilumination/Light.cpp

reflect:
	g++ -o ../Links/reflect.o -c ../Ilumination/Reflect.cpp

shapes:
	g++ -o ../Links/shapes.o -c ../Object_/Shapes.cpp

material:
	g++ -o ../Links/material.o -c ../Object_/Material.cpp

object:
	g++ -o ../Links/object.o -c ../Object_/Object.cpp

scene:
	g++ -o ../Links/scene.o -c ../World/Scene.cpp

space:
	g++ -o ../Links/space3D.o -c ../World/Space3D.cpp

main:
	g++ -o ../Links/main.o -c ../Main/main.cpp

program: canvas coordinate vector color intensity light reflect shapes material object scene space main
	g++ ../Links/main.o ../Links/space3D.o ../Links/scene.o ../Links/object.o ../Links/material.o ../Links/shapes.o ../Links/reflect.o ../Links/light.o ../Links/intensity.o ../Links/color.o ../Links/vector.o ../Links/coordinate.o ../Links/canvas.o -o program

