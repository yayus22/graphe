/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include "carte.h"
#include "graphe.h"


using namespace std;

// Surcharge de l'opérateur >> pour la classe Carte
istream& operator>>(istream& is, Carte& carte) {
    // Lecture des sites

    return is;
}

// Surcharge de l'opérateur << pour la classe Carte
ostream& operator<<(ostream& os, const Carte& carte) {
    // Affichage des sites
    os << carte.sommet;

    return os;
}


