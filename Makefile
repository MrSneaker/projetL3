all : bin/test

bin/test : obj/maintest.o obj/Voiture.o obj/Utilisateur.o
	g++ -o bin/test obj/maintest.o obj/Voiture.o obj/Utilisateur.o

obj/maintest.o : src/maintest.cpp src/Voiture.h 
	g++ -c -o obj/maintest.o src/maintest.cpp

obj/Voiture.o : src/Voiture.cpp src/Voiture.h 
	g++ -c -o obj/Voiture.o src/Voiture.cpp

obj/Utilisateur.o : src/Utilisateur.cpp src/Utilisateur.h
	g++ -c -o obj/Utilisateur.o src/Utilisateur.cpp

clean: 
	rm obj/*.o
	rm bin/*
