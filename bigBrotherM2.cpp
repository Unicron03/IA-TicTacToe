#include<vector>
// #include "morpion.h"

// Structure pour représenter une coordonnée (x, y)
struct CoordonneeB {
    int x;
    int y;
};

std::vector<CoordonneeB> listeCoordonneesB;

//vérifier que sa marche comme ça
bool logiqueDB(char **tab, int& x, int& y, int size, int nbPion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == ' ') {
                tab[i][j] = 'O'; // On place théoriquement un pion
                if (victoire_morpion(tab, size, nbPion, 'O')) { // On vérifie s'il y a une victoire en alignant nbPion pions
                    if (nbPion == 5) {
                        tab[i][j] = ' '; // On annule le placement théorique
                        x = listeCoordonneesB[0].x;
                        y = listeCoordonneesB[0].y;
                        for (const CoordonneeB& coord : listeCoordonneesB) {
                            tab[coord.x][coord.y] = ' ';
                            listeCoordonneesB.pop_back();
                        }
                        return true;
                    } else {
                        listeCoordonneesB.push_back({i, j});
                        if (logiqueDB(tab, x, y, size, nbPion + 1)) {
                            return true;  // Ajouter cette condition
                        }
                        listeCoordonneesB.pop_back();  // Retirer les coordonnées si l'appel récursif ne gagne pas
                    }
                }
                tab[i][j] = ' '; // On annule le placement théorique
            }
        }
    }
    return false;
}

bool checkWinB(char** tab, int& x, int& y, int size, int nbPion) {
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

void jouerCroix(char** tab, int &x, int &y, int size = 15, int nbPion = 5) {
	if(checkWinB(tab, x, y, size, nbPion)) {return;}

	for(int nbPionVirt = 5; nbPionVirt >= 1; nbPionVirt--) {
		if(logiqueDB(tab, x, y, size, nbPionVirt)) {return;}
	}
}