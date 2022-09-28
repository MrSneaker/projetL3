#include "Environnement.h"

using namespace std;

int Environnement::random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
							 // négatif ou positif en fonction des bornes fournies en paramètres.
{
	int res;
	if (max - min == 0) // pour éviter les erreurs fatales du à un modulo 0.
		return EXIT_FAILURE;
	if (max - min < 0)
	{
		res = -1 * (min + rand() % (max - min));
	}
	else
		res = min + rand() % (max - min);

	return res;
}

Environnement::Environnement()
{
}

Environnement::~Environnement()
{
}

void Environnement::initUser()
{
	float price = random(20, 60) / 10; // on simule des floats en divisants par 10.
	unsigned int id = conducteurs.size(); //Marche pas si on supprime un utilisateur du tableau et qu'on en rajoute un.
	string name = "Paulo - " + to_string(id); 
	Utilisateur u(price, id, name);
	conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent

void Environnement::initParkings()
{
	//Initialisation des parkings
	//Parametre du constructeur : Vec2 position, int numberOfPlaces, (float minimumPrice, float maximumPrice) a revoir 
	
	//Créer 3 parkings et les ajouter dans le tableau de parkings
	Parking p1(Vec2(600, 500), 100, 0.5, 1.5);
	Parking p2(Vec2(0, 0), 80, 0.5, 1.5);
	Parking p3(Vec2(0, 0), 250, 0.5, 1.5);
	parkings.push_back(p1);
	parkings.push_back(p2);
	parkings.push_back(p3);

}




void Environnement::AddVoiture()
{
	initUser();
	Voiture V(conducteurs[conducteurs.size() - 1]);
	Vec2 pos = {0, 0};
	V.set_position(pos); //TODO : Set la position aléatoire dans le terrain parmis les 3 entrées possibles -> cf :Schema de la map
	Vec2 targetPos = { 0, 0 }; 
	V.setTargetPosition(targetPos); //TODO : Set la position de la target : soit un parking, soit une sortie.
	voitures.push_back(V); // Ajout de la voiture dans le tableau de voitures
}

void Environnement::RemoveVoiture(int numVoiture)
{
	voitures.erase(voitures.begin() + numVoiture);
	voitures[numVoiture].~Voiture();
}

//Boucle de jeu
void Environnement::Environnement_play()
{
		for(int i = 0; i < 10; i++)
		{
			AddVoiture();
		}
		
	while(true)
	{
		time_t now = time(NULL); // temps actuel
		tm *ltm = localtime(&now); // temps local
		int heure = ltm->tm_hour;
		int minute = ltm->tm_min;
		int seconde = ltm->tm_sec;

		/*
		// Ajout d'une voiture toutes les 10 secondes
		if(seconde%1== 0)
		{
			cout<<"Faire une action"<<endl;
			AddVoiture();
			
			system("clear"); // clear le terminal
			for(int i = 0; i < voitures.size(); i++)
			{
				voitures[i].UserGetInfos();
				cout<<"----------------------"<<endl;
			}
		}


		cout<<"voiture a enlever : ";
		int numVoiture;
		cin>>numVoiture;
		RemoveVoiture(numVoiture);

		system("clear"); // clear le terminal
		cout<<"voitures.size : "<<voitures.size()<<endl;
		for(int i = 0; i < voitures.size(); i++)
		{
			voitures[i].UserGetInfos();
			cout<<"----------------------"<<endl;
		}
		*/
 
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	
}


void Environnement::test_regresion(){
	
	//test de regression de la classe Environnement
	Environnement E;

	for(int i = 0; i < 10; i++)
	{
		E.AddVoiture();
	}
	assert(E.voitures.size() == 10);
	E.RemoveVoiture(0);
	assert(E.voitures.size() == 9);

	cout<<"Test de regression de des fonction Add/RemoveVoiture (): OK"<<endl;

	E.initParkings();
	assert(E.parkings.size() == 3);
	cout<<"Test de regression de la fonction initParking() : OK"<<endl;


	





}