all : main

main : main.o Voiture.o 
	g++ -o main main.o Voiture.o 

main.o : src/main.cpp src/Voiture.h 
	g++ -c src/main.cpp

Voiture.o : src/Voiture.cpp src/Voiture.h 
	g++ -c src/Voiture.cpp

clean :
	rm -f *.o main
