#include<vector>
// #include "morpion.h"

// Structure coordonnée (x, y)
struct Coordonnee {
    int x;
    int y;
};

std::vector<Coordonnee> listeCoordonneesS;
int tour = 1;

bool logiqueD(char **tab, int& x, int& y, int size, int nbPion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == ' ') {
                tab[i][j] = 'O'; // On place théoriquement un pion
                if (victoire_morpion(tab, size, nbPion, 'O')) { // On vérifie s'il y a une victoire en alignant nbPion pions
                    if (nbPion == 5) {
                        tab[i][j] = ' '; // On annule le placement théorique
                        x = listeCoordonneesS[0].x;
                        y = listeCoordonneesS[0].y;
                        for (const Coordonnee& coord : listeCoordonneesS) {
                            tab[coord.x][coord.y] = ' ';
                            listeCoordonneesS.pop_back();
                        }
                        return true;
                    } else {
                        listeCoordonneesS.push_back({i, j});
                        if (logiqueD(tab, x, y, size, nbPion + 1)) {
                            return true;
                        }
                        listeCoordonneesS.pop_back();  // Retirer les coordonnées si l'appel récursif ne gagne pas
                    }
                }
                tab[i][j] = ' '; // On annule le placement théorique
            }
        }
    }
    return false;
}

void Troie(char **tab, int& x, int& y, int size){
	if(estLibre_morpion(tab,size,10,13)) {x=10; y=13;}
    else if(estLibre_morpion(tab,size,10,10)) {x=10; y=10;}
    else if(estLibre_morpion(tab,size,10,12)) {x=10; y=12;}
    else if(estLibre_morpion(tab,size,10,11)) {x=10; y=11;}
    else if(estLibre_morpion(tab,size,10,9)) {x=10; y=9;}
    else if(estLibre_morpion(tab,size,10,14)) {x=10; y=14;}
    else if(estLibre_morpion(tab,size,13,13)) {x=13; y=13;}
    else if(estLibre_morpion(tab,size,12,13)) {x=12; y=13;}
    else if(estLibre_morpion(tab,size,11,13)) {x=11; y=13;}
    else if(estLibre_morpion(tab,size,14,13)) {x=14; y=13;}
    else if(estLibre_morpion(tab,size,9,13)) {x=9; y=13;}
    else if(estLibre_morpion(tab,size,12,12)) {x=12; y=12;}
    else if(estLibre_morpion(tab,size,11,11)) {x=11; y=11;}
    else if(estLibre_morpion(tab,size,9,9)) {x=9; y=9;}
    else if(estLibre_morpion(tab,size,14,14)) {x=14; y=14;}
    else if(estLibre_morpion(tab,size,15,15)) {x=15; y=15;}
    else {
		for(int nbPionVirt = 5; nbPionVirt >= 2; nbPionVirt--) {
            if(logiqueD(tab, x, y, size, nbPionVirt)) {return;}
        }
	}
}

void appat(char **tab, int& x, int& y, int size, int nbPion, int &tour){
    if(tour==1) {x=5; y=5;}
    else if(tour==2){
	    if(estLibre_morpion(tab,size,5,6)) {x=5; y=6;}
        else {x=5; y=4;}
    }else if(tour==3){
		if(estLibre_morpion(tab,size,6,5)) {x=6; y=5;}
        else if(estLibre_morpion(tab,size,4,5)) {x=4; y=5;}
        else if(estLibre_morpion(tab,size,5,4)) {x=5; y=4;}
	} else {
		if(logiqueD(tab, x, y, size, 4)) {Troie(tab,x,y,size);}
        else {
			for(int nbPionVirt = 5; nbPionVirt >= 2; nbPionVirt--) {
            	if(logiqueD(tab, x, y, size, nbPionVirt)) {return;}
        	}
		}
	}
	tour++; 
    return;
}

bool checkWin(char** tab, int& x, int& y, int size, int nbPion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == ' ') {
                tab[i][j] = 'O'; // On place théoriquement un pion
                if (victoire_morpion(tab, size, nbPion, 'O')) { // On vérifie s'il y a une victoire en alignant 5 pions
                    tab[i][j] = ' '; // On annule le placement théorique
                    x=i; y=j;
                    return true;
                }
                tab[i][j] = ' '; // On annule le placement théorique
            }
        }
    }
    return false;
}

void jouerRond(char** tab, int& x, int& y, int size = 15, int nbPion = 5) {
    if(checkWin(tab, x, y, size, nbPion)) {return;}

    int nbPionInGrid = 0;
    for(int i=0; i<size; ++i) {
        for(int j=0; j<size; ++j) {
            if(tab[i][j] == 'O' || tab[i][j] == 'X') {nbPionInGrid++;}
        }
    }
    appat(tab, x, y, size, nbPion, tour);
}