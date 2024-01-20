#include<vector>
// #include "morpion.h"

// Structure coordonnée (x, y)
struct Coordonnee {
    int x;
    int y;
};

std::vector<Coordonnee> listeCoordonnees;

void logiqueT(char **tab, int& x, int& y, int size, int nbPion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == 'O' && i+6<size) {
                //Verif patern deja place donc gagnant
                bool paternGagnant = true;
                for(int ind=i; ind<=i+6; ind=ind+2) {
                    if(tab[ind][j] != 'O') {paternGagnant = false; break;}
                }
                if(tab[i+3][j] == 'X' || tab[i+1][j] == 'X' || tab[i+5][j] == 'X') {paternGagnant = false;}
                if(paternGagnant && tab[i+3][j] == ' ') {x=i+3; y=j; return;}
                //Verif patern base
                bool paternValid = true;
                for(int ind=i; ind<=i+6; ind++) {
                    if(tab[ind][j] == 'X') {paternValid = false; break;}
                }
                if(paternValid == true && i+6 < size) {
                    for(int ind=i; ind<=i+6; ind=ind+2) {
                        if(tab[ind][j] == ' ') {x=ind; y=j; return;}
                    }
                }
            }
        }
    }

    bool emptyGrid = true;
    for(int i=0; i<size; ++i) {
        for(int j=0; j<size; ++j) {
            if(tab[i][j] == 'O' || tab[i][j] == 'X') {emptyGrid = false; break;} //Si plateau full vide
        }
    }
    if(emptyGrid) {x=0; y=size/2;}
    else {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                bool canPlace = true;
                for(int ind=i; ind<=i+6; ind++) {
                    if(tab[ind][j] == 'X' || tab[ind][j] == 'O') {canPlace = false; break;}
                }
                if(canPlace) {x=i; y=j; return;}
            }
        }
    }
}

void logiqueE(char **tab, int& x, int& y, int size, int nbPion) {
    // On parcours le tableau pour trouver une ligne avec des 'O' alignés
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == 'O') {
                bool nothingD = true;
                for(int indLD=j; indLD<=j+(nbPion-1); indLD++) {
                    if(tab[i][indLD] == 'X') {nothingD = false;}
                }
                if(nothingD) {
                    if(tab[i][j+1] == 'O') {
                        if(tab[i][j+3] == ' ') {x=i; y=j+3; return;}
                        else {x=i; y=j+2; return;}
                    } else if(tab[i][j+1] == ' ') {x=i; y=j+1; return;}
                }
            }
        }
    }

    bool emptyGrid = true;
    for(int i=0; i<size; ++i) {
        for(int j=0; j<size; ++j) {
            if(tab[i][j] == 'O' || tab[i][j] == 'X') {emptyGrid = false; break;}
        }
    }
    if(emptyGrid) {x=size/2; y=size/2;}
    else {
        // Si aucune ligne avec 'O' alignés n'est trouvée, on place 'O' dans la première case vide
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                bool canPlace = true;
                if (tab[i][j] == ' ' && j+(nbPion-1) <= size) {
                    for(int ind=j-1; ind<=j+(nbPion-1); ind++) {
                        if(tab[i][ind] != ' ') {canPlace = false;}
                    }
                    if(canPlace) {
                        x = i;
                        y = j;
                        return;
                    }
                }
            }
        }
    }
}

bool logiqueD(char **tab, int& x, int& y, int size, int nbPion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tab[i][j] == ' ') {
                tab[i][j] = 'O'; // On place théoriquement un pion
                if (victoire_morpion(tab, size, nbPion, 'O')) { // On vérifie s'il y a une victoire en alignant nbPion pions
                    if (nbPion == 5) {
                        tab[i][j] = ' '; // On annule le placement théorique
                        x = listeCoordonnees[0].x;
                        y = listeCoordonnees[0].y;
                        for (const Coordonnee& coord : listeCoordonnees) {
                            tab[coord.x][coord.y] = ' ';
                            listeCoordonnees.pop_back();
                        }
                        return true;
                    } else {
                        listeCoordonnees.push_back({i, j});
                        if (logiqueD(tab, x, y, size, nbPion + 1)) {
                            return true;
                        }
                        listeCoordonnees.pop_back();  // Retirer les coordonnées si l'appel récursif ne gagne pas
                    }
                }
                tab[i][j] = ' '; // On annule le placement théorique
            }
        }
    }
    return false;
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
    if(nbPionInGrid<=94) {logiqueT(tab, x, y, size, nbPion);}
    else if(nbPionInGrid<=169) {logiqueE(tab, x, y, size, nbPion);}
    else {
        for(int nbPionVirt = 5; nbPionVirt >= 2; nbPionVirt--) {
            if(logiqueD(tab, x, y, size, nbPionVirt)) {return;}
        }
    }
}