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
	unsigned int id = Conducteur.size();
	string name = "Paulo" + id;
	Utilisateur u(price, id, name);
	Conducteur.push_back(u);
}

using namespace std;

Environnement::Environnement()
{
}

Environnement::~Environnement()
{
}

void InitVoitureInEnvironnement()
{
	// Initialisation des voitures avec un conducteur
}