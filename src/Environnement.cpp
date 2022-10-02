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

	// On attribue à l'utilisateur (que l'on crée juste après) un entier initial aléatoire (entre 0 et 5)
	// de visites de chaque parking (on simule ainsi le passé)
	unsigned int nbVisits0 = random(0, 5);
	unsigned int nbVisits1 = random(0, 5);
	unsigned int nbVisits2 = random(0, 5);

	Utilisateur u(price, id, name, nbVisits0, nbVisits1, nbVisits2);
	conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent

void Environnement::initParkings()
{
	//Initialisation des parkings
	//Parametre du constructeur : Vec2 position, int numberOfPlaces, (float minimumPrice, float maximumPrice) a revoir 
	
	//Créer 3 parkings et les ajouter dans le tableau de parkings
	Parking p1(Vec2(1, 1), 180, 0.5, 1.5,40,36);
	
	Parking p2(Vec2(57, 1), 180, 0.5, 1.5,40,36);
	Parking p3(Vec2(1, 53), 288, 0.5, 1.5,96,27);
	parkings.push_back(p1);
	parkings.push_back(p2);
	parkings.push_back(p3);


}




void Environnement::AddVoiture()
{
	initUser();
	Voiture V(conducteurs[conducteurs.size() - 1]);
	Vec2 pos = {460, 0};
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


int Environnement::GetStateVoiture()
{
	for(int i = 0; i < voitures.size(); i++)
	{

		for(int j = 0; j < parkings.size(); j++)
		{
			
			int VoiturePosX = voitures[i].get_position().x;
			int VoiturePosY = voitures[i].get_position().y;
			int TargetPosX = parkings[j].getPos().x*10;
			int TargetPosY = parkings[j].getPos().y*10;

			//Si la voiture est dans l'enceinte du parking
			if (VoiturePosX >= TargetPosX && VoiturePosX <= TargetPosX + parkings[j].getDIMX()*10 
			&& VoiturePosY >= TargetPosY && VoiturePosY <= TargetPosY + parkings[j].getDIMY()*10)
			{
				//Met la valeur Is_in à true
				voitures[i].setIs_in(true);
				if(voitures[i].getIs_in())
				{
					cout<<"Voiture "<<i<<" est dans le parking "<<j<<endl;
				}

			}
			else{
				voitures[i].setIs_in(false);
				if(!voitures[i].getIs_in())
				{
					cout<<"Voiture "<<i<<" n'est pas dans le parking "<<j<<endl;
				}
			}
		}
		
	}
	
}
//Boucle de jeu
void Environnement::Environnement_play()
{
	/*	
	while(true)
	{
		time_t now = time(NULL); // temps actuel
		tm *ltm = localtime(&now); // temps local
		int heure = ltm->tm_hour;
		int minute = ltm->tm_min;
		int seconde = ltm->tm_sec;

		this_thread::sleep_for(chrono::milliseconds(1000));
	}*/

	
	if(!voitures[0].MoveToTargetPosition())
	{
	}
		GetStateVoiture();
	
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