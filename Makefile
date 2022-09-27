all : bin/main

bin/main : obj/main.o obj/Voiture.o obj/Utilisateur.o
	g++ -o bin/main obj/main.o obj/Voiture.o obj/Utilisateur.o

obj/main.o : src/main.cpp src/Voiture.h 
	g++ -c -o obj/main.o src/main.cpp

obj/Voiture.o : src/Voiture.cpp src/Voiture.h 
	g++ -c -o obj/Voiture.o src/Voiture.cpp

obj/Utilisateur.o : src/Utilisateur.cpp src/Utilisateur.h
	g++ -c -o obj/Utilisateur.o src/Utilisateur.cpp

clean: 
	rm obj/*.o
	rm bin/*
