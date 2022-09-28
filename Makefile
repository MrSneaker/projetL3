SDL2=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
all : bin/test

bin/test : obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o
	g++ -o bin/test obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o  $(SDL2)

obj/maintest.o : src/maintest.cpp src/Voiture.h 
	g++ -c -o obj/maintest.o src/maintest.cpp $(SDL2)

obj/Environnement.o : src/Environnement.cpp src/Environnement.h
	g++ -c -o obj/Environnement.o src/Environnement.cpp 

obj/Parking.o : src/Parking.cpp src/Parking.h
	g++ -c -o obj/Parking.o src/Parking.cpp 

obj/Voiture.o : src/Voiture.cpp src/Voiture.h 
	g++ -c -o obj/Voiture.o src/Voiture.cpp 

obj/Utilisateur.o : src/Utilisateur.cpp src/Utilisateur.h
	g++ -c -o obj/Utilisateur.o src/Utilisateur.cpp 

obj/vec2.o : src/vec2.cpp src/vec2.h
	g++ -c -o obj/vec2.o src/vec2.cpp 

obj/Affichage.o : src/Affichage.cpp src/Affichage.h
	g++ -c -o obj/Affichage.o src/Affichage.cpp $(SDL2)

clean: 
	rm obj/*.o
	rm bin/*
