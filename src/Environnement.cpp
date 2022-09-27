#include "Environnement.h"

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

void Environnement::initUser()
{
	float price = random(20, 60) / 10; // on simule des floats en divisants par 10.
	unsigned int id = conducteurs.size(); //Marche pas si on supprime un utilisateur du tableau et qu'on en rajoute un.
	string name = "Paulo - " + to_string(id); 
	Utilisateur u(price, id, name);
	conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent


using namespace std;

Environnement::Environnement()
{
}

Environnement::~Environnement()
{
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


//Boucle de jeu
void Environnement::Environnement_play()
{
	// Boucle de jeu -- test
	while(true)
	{
		time_t now = time(NULL); // temps actuel
		tm *ltm = localtime(&now); // temps local
		int heure = ltm->tm_hour;
		int minute = ltm->tm_min;
		int seconde = ltm->tm_sec;

		// Ajout d'une voiture toutes les 10 secondes
		if(seconde%10 == 0)
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
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	
}


