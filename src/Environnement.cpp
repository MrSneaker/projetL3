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
	initNodes();
}

Environnement::~Environnement()
{
}

void Environnement::initNodes()
{
	getMap();
	for (int x = 0; x < DimWindowX / tailleCase; x++)
	{
		for (int y = 0; y < DimWindowY / tailleCase; y++)
		{
			nodes.push_back(new Node());
		}
	}
	for (int x = 0; x < DimWindowX / tailleCase; x++)
	{
		for (int y = 0; y < DimWindowY / tailleCase; y++)
		{
			nodes[x + y * DimWindowX / tailleCase]->setNodepos(Vec2(x, y));
			nodes[x + y * DimWindowX / tailleCase]->setisVisited(false);
			nodes[x + y * DimWindowX / tailleCase]->setFcost(0);
			nodes[x + y * DimWindowX / tailleCase]->setGcost(0);
			nodes[x + y * DimWindowX / tailleCase]->setHcost(0);
			nodes[x + y * DimWindowX / tailleCase]->setParent(nullptr);
			nodes[x + y * DimWindowX / tailleCase]->open = false;
			nodes[x + y * DimWindowX / tailleCase]->indice = x + y * DimWindowX / tailleCase;

			if (map[y][x] == '1')
				nodes[x + y * DimWindowX / tailleCase]->setisObstacle(true);
			else
				nodes[x + y * DimWindowX / tailleCase]->setisObstacle(false);
		}
	}
}

void Environnement::resetNodes()
{
	for (int x = 0; x < DimWindowX / tailleCase; x++)
	{
		for (int y = 0; y < DimWindowY / tailleCase; y++)
		{
			nodes[x + y * DimWindowX / tailleCase]->setisVisited(false);

			nodes[x + y * DimWindowX / tailleCase]->open = false;
			nodes[x + y * DimWindowX / tailleCase]->setParent(nullptr);
			nodes[x + y * DimWindowX / tailleCase]->setFcost(0);
			nodes[x + y * DimWindowX / tailleCase]->setGcost(0);
			nodes[x + y * DimWindowX / tailleCase]->setHcost(0);
			// obstacle
			// nodes[x + y * DimWindowX / tailleCase]->setisObstacle(false);
		}
	}
	cout << "reset" << endl;
	pathTab.clear();
	openList.clear();
	endNodeReached = false;
}

void Environnement::setNodes(unsigned int startInd, unsigned int endInd)
{
	resetNodes();
	startNode = nodes[startInd];
	currentNode = startNode;
	endNode = nodes[endInd];
	// ajoute le current node a la liste ouverte
	openList.push_back(currentNode);

	// on set les coût
	for (int x = 0; x < DimWindowX / tailleCase; x++)
	{
		for (int y = 0; y < DimWindowY / tailleCase; y++)
		{

			getCost(nodes[x + y * DimWindowX / tailleCase]);
			if (map[y][x] == '1')
			{
				nodes[x + y * DimWindowX / tailleCase]->setisObstacle(true);
				nodes[x + y * DimWindowX / tailleCase]->setFcost(99999);
			}
			else
				nodes[x + y * DimWindowX / tailleCase]->setisObstacle(false);
		}
	}
}

void Environnement::getCost(Node *node)
{
	// Gcost
	unsigned int xDist = abs(node->getNodepos().x - startNode->getNodepos().x);
	unsigned int yDist = abs(node->getNodepos().y - startNode->getNodepos().y);
	node->setGcost(xDist + yDist);

	// Hcost
	xDist = abs(node->getNodepos().x - endNode->getNodepos().x);
	yDist = abs(node->getNodepos().y - endNode->getNodepos().y);
	node->setHcost(xDist + yDist);

	// Fcost
	node->setFcost(node->getGcost() + node->getHcost());
}

bool Environnement::search()
{
	while (endNodeReached == false)
	{
		int x = currentNode->indice % (DimWindowX / tailleCase);
		int y = currentNode->indice / (DimWindowX / tailleCase);

		currentNode->setisVisited(true);
		// retire le currentnode de openlist
		openList.erase(openList.begin());

		// ajoute les voisins du current node a la liste ouverte
		// ouvre le voisin du haut
		if (y - 1 >= 0)
		{
			// cout<<"voisin du haut : "<<(x + (y-1) * DimWindowX / tailleCase)<<endl;
			OpenNode(nodes[x + (y - 1) * DimWindowX / tailleCase]);
		}
		// ouvre le voisin du bas
		if (y + 1 < DimWindowY / tailleCase)
		{
			// cout<<"voisin du bas : "<<(x + (y+1) * DimWindowX / tailleCase)<<endl;
			OpenNode(nodes[x + (y + 1) * DimWindowX / tailleCase]);
		}
		// ouvre le voisin de gauche
		if (x - 1 >= 0)
		{
			// cout<<"voisin de gauche : "<<((x-1) + y * DimWindowX / tailleCase)<<endl;
			OpenNode(nodes[(x - 1) + y * DimWindowX / tailleCase]);
		}
		// ouvre le voisin de droite
		if (x + 1 < DimWindowX / tailleCase)
		{
			// cout<<"voisin de droite : "<<((x+1) + y * DimWindowX / tailleCase)<<endl;
			OpenNode(nodes[(x + 1) + y * DimWindowX / tailleCase]);
		}

		unsigned int bestNodeInd = 0;
		unsigned int bestNodeFcost = 999;
		// trouve le noeud avec le plus petit Fcost
		for (int i = 0; i < openList.size(); i++)
		{
			// si le fcost du noeud est le meilleur
			if (openList[i]->getFcost() < bestNodeFcost)
			{
				// cout<<"bestNodeFcost = "<<bestNodeFcost<<endl;
				bestNodeInd = i;
				bestNodeFcost = openList[i]->getFcost();
			}
			// si le fcost est le même, on regarde le gcost
			else if (openList[i]->getFcost() == bestNodeFcost)
			{
				// si le gcost est meilleur
				// cout<<"bestNodeFcost = "<<bestNodeFcost<<endl;
				if (openList[i]->getGcost() < openList[bestNodeInd]->getGcost())
				{
					bestNodeInd = i;
				}
			}
		}

		// si il n'y a plus de noeud dans la openlist
		currentNode = openList[bestNodeInd];
		if (openList.size() == 0)
		{
			endNodeReached = true;
		}

		// si le currentnode est le endnode
		if (currentNode == endNode)
		{
			endNodeReached = true;
			trackPath();
		}
	}
	return endNodeReached;
}

void Environnement::trackPath()
{
	Node *current = endNode; // on commence par le endnode car on remonte le chemin
	while (current != startNode)
	{
		pathTab.push_back(current);		// on ajoute le noeud courant au chemin pour le tracer
		current = current->getParent(); // on passe au noeud parent pour continuer le chemin jusqu'au startnode
	}
}

void Environnement::OpenNode(Node *node)
{
	if (node->open == false && node->getisObstacle() == false && node->getisVisited() == false)
	{
		node->open = true;
		node->setParent(currentNode);
		openList.push_back(node);
	}
}

void Environnement::initUser()
{
	float price = random(20, 60) / 10;	  // on simule des floats en divisants par 10.
	unsigned int id = conducteurs.size(); // Marche pas si on supprime un utilisateur du tableau et qu'on en rajoute un.
	string name = "Paulo - " + to_string(id);

	// On attribue à l'utilisateur (que l'on crée juste après) un entier initial aléatoire (entre 0 et 5)
	// de visites de chaque parking (on simule ainsi le passé)
	// avec les changements cela doit être fait avec les procédures dans parkings.. mais à ce moment là uniquement au premiere ajout de l'utilisateur.

	Utilisateur u(price, id, name);
	conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent

void Environnement::initParkings()
{
	// Initialisation des parkings
	// Parametre du constructeur : Vec2 position, int numberOfPlaces, (float minimumPrice, float maximumPrice) a revoir

	// Créer 3 parkings et les ajouter dans le tableau de parkings
	Parking p1(Vec2(1, 1), 189, 0.5, 1.5, 42, 37, 0);

	Parking p2(Vec2(57, 1), 189, 0.5, 1.5, 42, 37, 1);
	Parking p3(Vec2(1, 52), 294, 0.5, 1.5, 98, 27, 2);
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

	// la position de la target est aléatoire entre l'entrée parkings
	float TargetPosX;
	float TargetPosY;
	int target = random(0, 3);
	switch (target)
	{
	case 0:
		TargetPosX = parkings[0].getPos().x + parkings[0].getDIMX() / 2; // on prend la position de l'entrée du parking
		TargetPosY = parkings[0].getPos().y + parkings[0].getDIMY();
		break;
	case 1:
		TargetPosX = parkings[1].getPos().x; // on prend la position de l'entrée du parking
		TargetPosY = parkings[1].getPos().y + parkings[1].getDIMY() / 2;
		break;
	case 2:
		TargetPosX = parkings[2].getPos().x + parkings[2].getDIMX() / 2 - 1; // on prend la position de l'entrée du parking
		TargetPosY = parkings[2].getPos().y;
		break;
	default:
		break;
	}

	Vec2 targetPos = {TargetPosX * 10 + 5, TargetPosY * 10 + 5};
	V.setTargetPosition(targetPos); // TODO : Set la position de la target : soit un parking, soit une sortie.
	voitures.push_back(V);			// Ajout de la voiture dans le tableau de voitures
	for (int i = 0; i < parkings.size(); i++)
	{
		parkings[i].addUsersTab(&conducteurs[conducteurs.size() - 1]);
	}
}

void Environnement::RemoveVoiture(int numVoiture)
{
	voitures.erase(voitures.begin() + numVoiture);
	voitures[numVoiture].~Voiture(); // inutile, vector utilise déjà le destructeur de la classe à l'appel de erase..
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
						voitures[i].setPlace(k);						// on stock le numero de la place
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

void Environnement::getMap()
{
	ifstream MaMap("map.txt", ios::in);
	int i = 0;
	if (MaMap)
	{
		while (getline(MaMap, map[i], '\n'))
		{
			i++;
		}
		MaMap.close();
	}
	//affiche la longueur de la map
	 cout << "Longueur de la map : " << map[0].length() << endl;
	 cout<<"map[][] : "<<map[42][99]<<endl;
	 for(int y =0; y<80; y++){
	 	for(int x =0 ;x<100; x++){
	 		cout<<map[y][x];
	 	}
	 	cout<<endl;
	 }
}

void Environnement::test_regresion()
{

	// test de regression de la classe Environnement
	Environnement E;

	// for (int i = 0; i < 10; i++)
	// {
	// 	E.AddVoiture();
	// }
	// assert(E.voitures.size() == 10);
	// E.RemoveVoiture(0);
	// assert(E.voitures.size() == 9);

	// cout << "Test de regression de des fonction Add/RemoveVoiture (): OK" << endl;

	// E.initParkings();
	// assert(E.parkings.size() == 3);
	// cout << "Test de regression de la fonction initParking() : OK" << endl;

	/*// Affiche les infos du noeud 47
	cout << "Noeud 47 : " << endl;
	cout << "Position : " << E.nodes[47]->getNodepos().x << " " << E.nodes[47]->getNodepos().y << endl;
	cout << "fcost : " << E.nodes[47]->getFcost() << endl;
	cout << "gcost : " << E.nodes[47]->getGcost() << endl;
	cout << "hcost : " << E.nodes[47]->getHcost() << endl;

	// Affiche les infos du noeud 4299
	cout << "Noeud 4299 : " << endl;
	cout << "Position : " << E.nodes[4299]->getNodepos().x << " " << E.nodes[4299]->getNodepos().y << endl;
	cout << "fcost : " << E.nodes[4299]->getFcost() << endl;
	cout << "gcost : " << E.nodes[4299]->getGcost() << endl;
	cout << "hcost : " << E.nodes[4299]->getHcost() << endl;
	*/

	E.setNodes(47, 4298);

	if (E.search() == true)
	{
		cout<<"test regresion de la fonction search() : OK"<<endl;
	}
	else
	{
		cout<<"test regresion de la fonction search() : FAIL"<<endl;
	}

	cout<<"path size : "<<E.pathTab.size()<<endl;

	for(int i=0; i<E.pathTab.size(); i++)
	{
		cout<<"Noeud "<<i<<" : "<<E.pathTab[i]->getNodepos().x<<" "<<E.pathTab[i]->getNodepos().y<<endl;
	}
	E.getMap();
	// test de regression de la fonction OpenNode()
}