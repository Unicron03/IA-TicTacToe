#include "morpion.h"
#include "tedM3.cpp"
// #include "spike.cpp"
#include "bigBrotherM2.cpp"

int main() {

	char ** tab;
	int size = 15;
	int nbPion = 5;
	
	init_morpion(tab,size);
	
	bool alignement = false;
	bool joueur = false;
	
	int nbPl = 0;
	
	while(!alignement && nbPl < size*size) {
	
		affichage_morpion(tab,size);
	
		char pion;
		(joueur ? pion = 'X' : pion = 'O');
		joueur = not(joueur);
		
		int x = -1; 
		int y = -1;
		
		do {
		// Vos fonctions ici. 
		// Vos fonctions sont nommées jouerRond pour les ronds et jouerCroix pour les croix.
		// les variables x et y sont passées en référence, elles renvoient la position où jouer.
		if(pion == 'O'){
			jouerRond(tab, x, y);
		}
		else {
			jouerCroix(tab, x, y);
			// std::cout<<" : ";
			// std::cin>>x>>y;
		}
			// std::cin >> x >> y;
			std::cout<<std::endl;
			
		} while(!estLibre_morpion(tab,size,x,y));
	
		placer_morpion(tab,size,x,y,pion);
		affichage_morpion(tab,size);
	
	
		if(pion == 'O') alignement = victoire_morpion(tab,size,nbPion,'O');
		nbPl++; 
	}

	delete_morpion(tab,size);
}
