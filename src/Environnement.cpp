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
	float price = random(20, 60) / 10;	  // on simule des floats en divisants par 10.
	unsigned int id = conducteurs.size(); // Marche pas si on supprime un utilisateur du tableau et qu'on en rajoute un.
	string name = "Paulo - " + to_string(id);

	// On attribue à l'utilisateur (que l'on crée juste après) un entier initial aléatoire (entre 0 et 5)
	// de visites de chaque parking (on simule ainsi le passé)
	unsigned int nbVisits0 = random(0, 5);
	unsigned int nbVisits1 = random(0, 5);
	unsigned int nbVisits2 = random(0, 5);

	Utilisateur u(price, id, name);
	conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent

void Environnement::initParkings()
{
	// Initialisation des parkings
	// Parametre du constructeur : Vec2 position, int numberOfPlaces, (float minimumPrice, float maximumPrice) a revoir

	// Créer 3 parkings et les ajouter dans le tableau de parkings
	Parking p1(Vec2(1, 1), 189, 0.5, 1.5, 42, 37);

	Parking p2(Vec2(57, 1), 189, 0.5, 1.5, 42, 37);
	Parking p3(Vec2(1, 52), 294, 0.5, 1.5, 98, 27);
	parkings.push_back(p1);
	parkings.push_back(p2);
	parkings.push_back(p3);
}

void Environnement::AddVoiture()
{
	initUser();
	Voiture V(conducteurs[conducteurs.size() - 1]);
	Vec2 pos = {460, 0};
	V.set_position(pos); // TODO : Set la position aléatoire dans le terrain parmis les 3 entrées possibles -> cf :Schema de la map

	//la position de la target est aléatoire entre l'entrée parkings
	unsigned int TargetPosX;
	unsigned int TargetPosY;
	int target = random(0, 3);
	switch (target)
	{
	case 0:
		TargetPosX = parkings[0].getPos().x+parkings[0].getDIMX()/2; //on prend la position de l'entrée du parking
		TargetPosY = parkings[0].getPos().y+parkings[0].getDIMY();
		break;
	case 1:
		TargetPosX = parkings[1].getPos().x; //on prend la position de l'entrée du parking
		TargetPosY = parkings[1].getPos().y+parkings[1].getDIMY()/2;
		break;
	case 2:
		TargetPosX = parkings[2].getPos().x+parkings[2].getDIMX()/2-1; //on prend la position de l'entrée du parking
		TargetPosY = parkings[2].getPos().y;
		break;
	default:
		break;
	}

	Vec2 targetPos = {TargetPosX*10+5, TargetPosY*10+5};
	V.setTargetPosition(targetPos); // TODO : Set la position de la target : soit un parking, soit une sortie.
	voitures.push_back(V);			// Ajout de la voiture dans le tableau de voitures
	for(int i = 0; i<parkings.size(); i++){
		parkings[i].addUsersTab(&conducteurs[conducteurs.size() - 1]);
	}
}

void Environnement::RemoveVoiture(int numVoiture)
{
	voitures.erase(voitures.begin() + numVoiture);
	voitures[numVoiture].~Voiture();
}

void Environnement::updateStateVoiture()
{
	// On parcours le tableau de voitures
	for (int i = 0; i < voitures.size(); i++)
	{
		// On met à jour l'état de la place ou la voiture se trouve -> pour que quand elle passe sur une place et ne reste pas considere comme non libre
		parkings[voitures[i].getParking()].getPlacesTab()[voitures[i].getPlace()].setIsTaken(false);
		bool inParking = false; // booléen qui permet de savoir si la voiture est dans un parking ou non
		bool isInPlace = false; // booléen qui permet de savoir si la voiture est dans une place ou non
		for (int j = 0; j < parkings.size(); j++)
		{

			int VoiturePosX = voitures[i].get_position().x;	  // Position de la voiture en x
			int VoiturePosY = voitures[i].get_position().y;	  // Position de la voiture en y
			int TargetParkPosX = parkings[j].getPos().x * 10; // Position de la parking en x
			int TargetParkPosY = parkings[j].getPos().y * 10; // Position du parking en y

			// Si la voiture est dans l'enceinte du parking
			if (VoiturePosX >= TargetParkPosX && VoiturePosX <= TargetParkPosX + parkings[j].getDIMX() * 10 && VoiturePosY >= TargetParkPosY && VoiturePosY <= TargetParkPosY + parkings[j].getDIMY() * 10)
			{

				// cout << "Voiture " << i << " est dans le parking " << j << endl;
				inParking = true;		   // La voiture est dans un parking
				voitures[i].setParking(j); // on stock le numero du parking
			
				// On parcours le tableau de places du parking
				for (int k = 0; k < parkings[j].getPlacesTab().size(); k++)
				{
					int TargetPlacePosX = parkings[j].getPlacesTab()[k].getPos().x * 10; // Position de la place en x
					int TargetPlacePosY = parkings[j].getPlacesTab()[k].getPos().y * 10; // Position de la place en y

					// Si la voiture est dans l'enceinte de la place
					if (VoiturePosX >= TargetPlacePosX && VoiturePosX <= TargetPlacePosX + 10 && VoiturePosY >= TargetPlacePosY && VoiturePosY <= TargetPlacePosY + 20)
					{
						voitures[i].setPlace(k); // on stock le numero de la place
						parkings[j].getPlacesTab()[k].setIsTaken(true); // on met à jour l'état de la place

						// cout << "Voiture " << i << " est dans la place " << k << " du parking " << j << endl;
						isInPlace = true; // La voiture est dans une place
					}
				}
			}
			else
			{
			}
			// cout << "Voiture " << i << " n'est pas dans le parking " << j << endl;
		}
		if (inParking)
		{
			voitures[i].setIs_in(true);
			if (isInPlace)
				voitures[i].setIs_parked(true);
			else
				voitures[i].setIs_parked(false);
		}
		else
			voitures[i].setIs_in(false);
	}
}
// Boucle de jeu
void Environnement::Environnement_play()
{

	
	for (int i = 0; i < voitures.size(); i++)
	{
		voitures[i].MoveToTargetPosition();
	}
	updateStateVoiture();
}

void Environnement::test_regresion()
{

	// test de regression de la classe Environnement
	Environnement E;

	for (int i = 0; i < 10; i++)
	{
		E.AddVoiture();
	}
	assert(E.voitures.size() == 10);
	E.RemoveVoiture(0);
	assert(E.voitures.size() == 9);

	cout << "Test de regression de des fonction Add/RemoveVoiture (): OK" << endl;

	E.initParkings();
	assert(E.parkings.size() == 3);
	cout << "Test de regression de la fonction initParking() : OK" << endl;
}