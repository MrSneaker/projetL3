SDL2=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
gnuplot=-lboost_iostreams -lboost_system -lboost_filesystem
all : bin/test bin/app

bin/test : obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o obj/Graph.o obj/Menu.o
	g++ -o bin/test obj/maintest.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o obj/Graph.o obj/Menu.o $(SDL2) $(gnuplot)   -pthread -ggdb

bin/app: obj/mainApp.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o obj/Graph.o obj/Menu.o
	g++ -o bin/app obj/mainApp.o obj/Environnement.o obj/Parking.o obj/Voiture.o obj/Utilisateur.o obj/vec2.o obj/Affichage.o obj/Place.o obj/Message.o obj/Image.o obj/Conversation.o obj/Node.o obj/Graph.o obj/Menu.o $(SDL2)  $(gnuplot) -pthread -ggdb
obj/mainApp.o: src/mainApp.cpp
	g++ -c -o obj/mainApp.o src/mainApp.cpp $(SDL2) -ggdb 

obj/maintest.o : src/maintest.cpp 
	g++ -c -o obj/maintest.o src/maintest.cpp $(SDL2) -ggdb 

obj/Environnement.o : src/Environnement.cpp src/vec2.h src/Environnement.h src/Parking.h src/Voiture.h src/Conversation.h src/Graph.h
	g++ -c -g -o obj/Environnement.o src/Environnement.cpp -ggdb 

obj/Parking.o : src/Parking.cpp src/Parking.h src/Place.h
	g++ -c -g -o obj/Parking.o src/Parking.cpp -ggdb 

obj/Voiture.o : src/Voiture.cpp src/Voiture.h src/Utilisateur.h src/Node.h
	g++ -c -g -o obj/Voiture.o src/Voiture.cpp -ggdb 

obj/Utilisateur.o : src/Utilisateur.cpp src/Utilisateur.h
	g++ -c -o obj/Utilisateur.o src/Utilisateur.cpp -ggdb 

obj/Place.o : src/Place.cpp src/Place.h
	g++ -c -o obj/Place.o src/Place.cpp -ggdb 

obj/Message.o : src/Message.cpp src/Message.h
	g++ -c -g -o obj/Message.o src/Message.cpp -ggdb 

obj/vec2.o : src/vec2.cpp src/vec2.h
	g++ -c -o obj/vec2.o src/vec2.cpp -ggdb 

obj/Affichage.o : src/Affichage.cpp src/Affichage.h src/Environnement.h src/Image.h
	g++ -c -o obj/Affichage.o src/Affichage.cpp $(SDL2) -ggdb 

obj/Image.o : src/Image.cpp src/Image.h
	g++ -c -o obj/Image.o src/Image.cpp $(SDL2) -ggdb 

obj/Node.o : src/Node.cpp src/Node.h
	g++ -c -g -o obj/Node.o src/Node.cpp -ggdb 

obj/Conversation.o : src/Conversation.cpp src/Conversation.h src/Message.h
	g++ -c -g -o obj/Conversation.o src/Conversation.cpp -pthread -ggdb 

obj/Graph.o: src/Graph.cpp src/Graph.h
	g++ -c -g -o obj/Graph.o src/Graph.cpp $(gnuplot) -ggdb 

obj/Menu.o: src/Menu.cpp src/Menu.h
	g++ -c -o obj/Menu.o src/Menu.cpp $(SDL2) -ggdb 


clean:
	rm -f obj/*.o
	rm -f bin/*

cleanLogs:
	rm -f data/logs/*.txt