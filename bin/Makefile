all: program

program: ../Links/coordinate.o ../Links/vector.o ../Links/color.o ../Links/intensity.o ../Links/light.o ../Links/reflect.o ../Links/shapes.o ../Links/material.o ../Links/object.o ../Links/scene.o ../Links/space3D.o ../Links/meshUtils.o ../Links/mesh.o ../Links/texture.o ../Links/camera.o ../Links/main.o #../Links/canvas.o
	g++ ../Links/main.o ../Links/space3D.o ../Links/scene.o ../Links/object.o ../Links/material.o ../Links/shapes.o ../Links/reflect.o ../Links/light.o ../Links/intensity.o ../Links/color.o ../Links/vector.o ../Links/coordinate.o ../Links/meshUtils.o ../Links/mesh.o ../Links/texture.o ../Links/camera.o -Ofast -lSDL2 -lSDL2_image -o program

#../Links/canvas.o: ../Canvas_/Canvas.cpp ../Canvas_/Canvas.h
#	g++ -o ../Links/canvas.o ../Canvas_/Canvas.cpp -c

../Links/coordinate.o: ../DataStructures/Coordinate.cpp ../DataStructures/Coordinate.h
	g++ -Ofast -o ../Links/coordinate.o ../DataStructures/Coordinate.cpp -c

../Links/camera.o: ../DataStructures/Vector.h ../Camera/Camera.h ../DataStructures/Matrix.h ../DataStructures/Coordinate.h
	g++ -Ofast -o ../Links/camera.o ../Camera/Camera.cpp -c

../Links/vector.o: ../DataStructures/Vector.cpp ../DataStructures/Vector.h ../DataStructures/DataConsts.h
	g++ -Ofast -o ../Links/vector.o ../DataStructures/Vector.cpp -c

../Links/color.o: ../Ilumination/Color.cpp ../Ilumination/Color.h
	g++ -Ofast -o ../Links/color.o ../Ilumination/Color.cpp -c

../Links/intensity.o: ../Ilumination/Intensity.cpp ../Ilumination/Intensity.h ../DataStructures/DataConsts.h
	g++ -Ofast -o ../Links/intensity.o ../Ilumination/Intensity.cpp -c

../Links/light.o: ../Ilumination/Light.cpp ../Ilumination/Light.h ../DataStructures/Coordinate.h ../DataStructures/DataConsts.h
	g++ -Ofast -o ../Links/light.o ../Ilumination/Light.cpp -c

../Links/reflect.o: ../Ilumination/Reflect.cpp ../Ilumination/Reflect.h
	g++ -Ofast -o ../Links/reflect.o ../Ilumination/Reflect.cpp -c

../Links/shapes.o: ../Object_/Shapes.cpp ../Object_/Shapes.h
	g++ -Ofast -o ../Links/shapes.o ../Object_/Shapes.cpp -c

../Links/material.o: ../Object_/Material.cpp ../Object_/Material.h
	g++ -Ofast -o ../Links/material.o ../Object_/Material.cpp -c

../Links/object.o: ../Object_/Object.cpp ../Object_/Object.h ../Object_/Mesh.h ../DataStructures/MeshUtils.h
	g++ -Ofast -o ../Links/object.o ../Object_/Object.cpp -c

../Links/mesh.o: ../Object_/Mesh.cpp ../Object_/Mesh.h ../DataStructures/Triple.h ../DataStructures/Vector.h ../Object_/Transformation.h ../DataStructures/Matrix.h
	g++ -Ofast -o ../Links/mesh.o ../Object_/Mesh.cpp -c

../Links/scene.o: ../World/Scene.cpp ../World/Scene.h ../Ilumination/Light.h ../Object_/Shapes.h ../Object_/Texture.h ../DataStructures/DataConsts.h
	g++ -Ofast -o ../Links/scene.o ../World/Scene.cpp -c

../Links/space3D.o: ../World/Space3D.cpp ../World/Space3D.h ../DataStructures/Coordinate.h
	g++ -Ofast -o ../Links/space3D.o ../World/Space3D.cpp -c

../Links/meshUtils.o: ../DataStructures/MeshUtils.cpp ../DataStructures/MeshUtils.h
	g++ -Ofast -o ../Links/meshUtils.o ../DataStructures/MeshUtils.cpp -c

../Links/texture.o: ../Object_/Texture.cpp ../Object_/Texture.h ../Ilumination/Color.h
	g++ -Ofast -o ../Links/texture.o ../Object_/Texture.cpp -c

../Links/main.o: ../Main/main.cpp ../Canvas_/Canvas.h ../DataStructures/Coordinate.h ../DataStructures/DataConsts.h ../DataStructures/Matrix.h ../DataStructures/Vector.h ../Ilumination/Color.h ../Ilumination/Intensity.h ../Ilumination/Light.h ../Ilumination/Reflect.h ../Object_/Object.h ../Object_/Shapes.h ../World/Scene.h ../World/Space3D.h ../Camera/Camera.h
	g++ -Ofast -o ../Links/main.o ../Main/main.cpp -c

clean:
	cd ../Links && rm *.o