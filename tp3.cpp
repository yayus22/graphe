/*  INF3105 - Structures de données et algorithmes
    UQAM / Département d'informatique, TP3
*/

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "carte.h"

using namespace std;

/**
 * Charge les données d'une carte à partir d'un flux d'entrée et applique l'algorithme de Prim-Jarnik.
 * 
 * @param entree Le flux d'entrée contenant les données de la carte.
 */
void tp3(istream& entree){

    Carte carte;
    string s;
    while (entree >> s && s != "---") {
        carte.sommet.ajouterSommet(s);
    }
    cout << carte ;

    while (entree >> s && s != "---") {
        string rue = s;
        entree >> s;
        string voisin;
        entree >> s >> voisin;
        int val;
        entree >> val;
        carte.sommet.ajouterAreteNonOrientee(s, voisin, val, rue);
        entree >> s;
    }
    cout << "----------------------------------" << endl;
    carte.sommet.primJarnik();
}


int main(int argc, const char** argv)
{
  
    if(argc!=2){
        cout << "Syntaxe: ./tp3 exemple.txt" << endl;
        return 1;
    }

    if(argc>1){
        std::ifstream entree_fichier(argv[1]);
        if(entree_fichier.fail()){
            std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        tp3(entree_fichier);
    }
    return 0;
}
