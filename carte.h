/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */
 
#if !defined(_CARTE__H_)
#define _CARTE__H_
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "graphe.h"

using namespace std;

// Classe représentant une carte
class Carte {
private:
    Graphe<string> sommet;

public:

    // Méthode pour obtenir les rues de la carte

  friend istream& operator >> (istream& is, Carte& carte);
  friend ostream& operator <<(ostream& os, const Carte& carte);
  friend void tp3(istream& entree);
};

#endif

