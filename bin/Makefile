all: program

program: ../Links/canvas.o ../Links/coordinate.o ../Links/vector.o ../Links/color.o ../Links/intensity.o ../Links/light.o ../Links/shapes.o ../Links/material.o ../Links/object.o ../Links/scene.o ../Links/space3D.o ../Links/main.o 
	g++ ../Links/main.o ../Links/space3D.o ../Links/scene.o ../Links/object.o ../Links/material.o ../Links/shapes.o ../Links/reflect.o ../Links/light.o ../Links/intensity.o ../Links/color.o ../Links/vector.o ../Links/coordinate.o ../Links/canvas.o -o program

../Links/canvas.o: ../Canvas_/Canvas.cpp ../Canvas_/Canvas.h
	g++ -o ../Links/canvas.o ../Canvas_/Canvas.cpp -c

../Links/coordinate.o: ../DataStructures/Coordinate.cpp ../DataStructures/Coordinate.h
	g++ -o ../Links/coordinate.o ../DataStructures/Coordinate.cpp -c

../Links/vector.o: ../DataStructures/Vector.cpp ../DataStructures/Vector.h ../DataStructures/DataConsts.h
	g++ -o ../Links/vector.o ../DataStructures/Vector.cpp -c

../Links/color.o: ../Ilumination/Color.cpp ../Ilumination/Color.h
	g++ -o ../Links/color.o ../Ilumination/Color.cpp -c

../Links/intensity.o: ../Ilumination/Intensity.cpp ../Ilumination/Intensity.h ../DataStructures/DataConsts.h
	g++ -o ../Links/intensity.o ../Ilumination/Intensity.cpp -c

../Links/light.o: ../Ilumination/Light.cpp ../Ilumination/Light.h ../DataStructures/Coordinate.h ../DataStructures/DataConsts.h
	g++ -o ../Links/light.o ../Ilumination/Light.cpp -c

../Links/reflect.o: ../Ilumination/Reflect.cpp ../Ilumination/Reflect.h
	g++ -o ../Links/reflect.o ../Ilumination/Reflect.cpp -c

../Links/shapes.o: ../Object_/Shapes.cpp ../Object_/Shapes.h
	g++ -o ../Links/shapes.o ../Object_/Shapes.cpp -c

../Links/material.o: ../Object_/Material.cpp ../Object_/Material.h
	g++ -o ../Links/material.o ../Object_/Material.cpp -c

../Links/object.o: ../Object_/Object.cpp ../Object_/Object.h
	g++ -o ../Links/object.o ../Object_/Object.cpp -c

../Links/scene.o: ../World/Scene.cpp ../World/Scene.h ../Ilumination/Light.h ../Object_/Shapes.h ../DataStructures/DataConsts.h
	g++ -o ../Links/scene.o ../World/Scene.cpp -c

../Links/space3D.o: ../World/Space3D.cpp ../World/Space3D.h ../DataStructures/Coordinate.h
	g++ -o ../Links/space3D.o ../World/Space3D.cpp -c

../Links/main.o: ../Main/main.cpp ../Canvas_/Canvas.h ../DataStructures/Coordinate.h ../DataStructures/DataConsts.h ../DataStructures/Matrix.h ../DataStructures/Vector.h ../Ilumination/Color.h ../Ilumination/Intensity.h ../Ilumination/Light.h ../Ilumination/Reflect.h ../Object_/Object.h ../Object_/Shapes.h ../World/Scene.h ../World/Space3D.h
	g++ -o ../Links/main.o ../Main/main.cpp -c
