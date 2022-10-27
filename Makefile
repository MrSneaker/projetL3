SDL2=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
all : clean bin/test

bin/test : obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o
	g++ -o bin/test obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o $(SDL2) -pthread -ggdb

obj/maintest.o : src/maintest.cpp src/Voiture.h 
	g++ -c -o obj/maintest.o src/maintest.cpp $(SDL2) -ggdb

obj/Environnement.o : src/Environnement.cpp src/Environnement.h
	g++ -c -g -o obj/Environnement.o src/Environnement.cpp -ggdb

obj/Parking.o : src/Parking.cpp src/Parking.h
	g++ -c -g -o obj/Parking.o src/Parking.cpp -ggdb

obj/Voiture.o : src/Voiture.cpp src/Voiture.h 
	g++ -c -g -o obj/Voiture.o src/Voiture.cpp -ggdb 

obj/Utilisateur.o : src/Utilisateur.cpp src/Utilisateur.h
	g++ -c -o obj/Utilisateur.o src/Utilisateur.cpp -ggdb

obj/Place.o : src/Place.cpp src/Place.h
	g++ -c -o obj/Place.o src/Place.cpp -ggdb

obj/Message.o : src/Message.cpp src/Message.h
	g++ -c -g -o obj/Message.o src/Message.cpp -ggdb

obj/vec2.o : src/vec2.cpp src/vec2.h
	g++ -c -o obj/vec2.o src/vec2.cpp -ggdb

obj/Affichage.o : src/Affichage.cpp src/Affichage.h
	g++ -c -o obj/Affichage.o src/Affichage.cpp $(SDL2) -ggdb

obj/Image.o : src/Image.cpp src/Image.h
	g++ -c -o obj/Image.o src/Image.cpp $(SDL2) -ggdb

obj/Node.o : src/Node.cpp src/Node.h
	g++ -c -g -o obj/Node.o src/Node.cpp -ggdb

obj/Conversation.o : src/Conversation.cpp src/Conversation.h
	g++ -c -g -o obj/Conversation.o src/Conversation.cpp -pthread -ggdb



clean:
	rm -f data/logs/*.txt
	rm -f obj/*.o
	rm -f bin/*