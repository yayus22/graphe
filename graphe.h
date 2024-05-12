/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://ericbeaudry.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <assert.h>
#include <queue>
#include <set>
#include <limits>

using namespace std;


// Le type S est le symbole pour identifier un sommet
template <class S>
class Graphe{
  public:
    // Interface public pour créer le graphe.
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2, int val, string rue);
    void ajouterAreteNonOrientee(const S& s1, const S& s2, int val, string rue);

    // Interface public pour les requêtes de base.
    // Amélioration possible : retourner le résultat au lieu de faire l'affichage à l'interne.
    void parcoursRechercheProfondeur(const S& s);
    void parcoursRechercheLargueur(const S& s);
    void extraireComposantesConnexes() const;
    void afficherVoisins(const S& sommet) const;
    void primJarnik();
    template <class T>
    friend std::ostream& operator <<(std::ostream& os, const Graphe<T>& graphe);
    friend void tp3(istream& entree);

  private:
    struct Sommet{
        // À compléter.
        std::set<S> voisins; // ensemble des sommets accessibles via les arêtes sortantes du sommet.
                        // Cela est légèrement différent de la page 128 des notes de cours.
                        // C'est voulu, car ici les arêtes ne sont pas étiquetées par un poids (ex: distance).
                        // Pour attacher une étiquette, il suffirait de modifier pour : map<S, A> sortants;
        bool visited;        // Flag to mark if the vertex has been visited
        std::map<S, int> couts;
        std::map<S, string> noRue;
        Sommet() : visited(false) {} // Constructor to initialize visited flag
    };
    std::map<S, Sommet> sommets; // identification --> sommet
};

template <class S>
void Graphe<S>::ajouterSommet(const S& s){
    this->sommets[s];
}

template <class S>
void Graphe<S>::ajouterAreteNonOrientee(const S& s1, const S& s2, int val, string rue){
    // À compléter.
    // Doit ajouter les 2 arêtes orientées : s1->s2 et s2->s1;
    this->ajouterAreteOrientee(s1, s2, val, rue);
    this->ajouterAreteOrientee(s2, s1, val, rue);
}

template <class S>
void Graphe<S>::ajouterAreteOrientee(const S& s1, const S& s2, int val, string rue){
    // À compléter.
    // Doit uniquement ajouter s1->s2.
    auto it_s1 = this->sommets.find(s1);
    auto it_s2 = this->sommets.find(s2);

    if (it_s1 != this->sommets.end() && it_s2 != this->sommets.end()) {
        this->sommets[s1].voisins.insert(s2);
        this->sommets[s1].couts[s2] = val;
        this->sommets[s1].noRue[s2] = rue;
    }
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur(const S& s){
    // À compléter.
    // Vous devrez implémenter des marqueurs «visité» sur les sommets.
    assert(this->sommets.contains(s));
    this->sommets[s].visited = true;
    std::cout << s << " ";
    for(const S &voisin : this->sommets[s].voisins){
        if(!this->sommets[voisin].visited)
            this->parcoursRechercheProfondeur(voisin);
    }
}

template <class S>
void Graphe<S>::parcoursRechercheLargueur(const S& s) {
    std::queue<S> q;
    std::set<S> visited;
    q.push(s);
    visited.insert(s);

    while (!q.empty()) {
        S current = q.front();
        q.pop();
        std::cout << current << " ";
        
        for (const S& voisin : this->sommets[current].voisins) {
            if (!visited.contains(voisin)) {
                visited.insert(voisin);
                q.push(voisin);
            }
        }
    }
}

template <class S>
void Graphe<S>::extraireComposantesConnexes() const{
    // Marquer tous les sommets comme non visités
    std::map<S, Sommet> sommetsNonVisites = sommets;
    for(auto& pair : sommetsNonVisites){
        pair.second.visited = false;
    }
    
    // Parcourir tous les sommets non visités pour extraire les composantes connexes
    for(auto& pair : sommetsNonVisites){
        const S& sommet = pair.first;
        if(!sommetsNonVisites[sommet].visited){
            std::cout << "Composante connexe :";
            parcoursRechercheProfondeur(sommet);
            std::cout << std::endl;
        }
    }
}

template <class S>
std::ostream& operator<<(std::ostream& os, const Graphe<S>& graphe) {
    for (const auto& [cle, sommet] : graphe.sommets) {
        os << cle << std::endl;
    }
    return os;
}

template <class S>
void Graphe<S>::afficherVoisins(const S& sommet) const {
    auto it = sommets.find(sommet);

    if (it != sommets.end()) {
        for (const auto& voisin : it->second.voisins) {
            cout << it->second.noRue.at(voisin) << " " << sommet << " ";
            cout << voisin << " " << it->second.couts.at(voisin) << "; " << endl;
        }
    }
}

/**
 * Applique l'algorithme de Prim-Jarník pour trouver l'arbre couvrant de poids minimum
 * dans le graphe.
 * 
 * @tparam S Le type des sommets dans le graphe.
 */

template <class S>
void Graphe<S>::primJarnik() {
    int coutTotal = 0;

    for (auto& paire : sommets) {
        paire.second.visited = false;
    }
    std::set<S> visites;

    if (sommets.empty()) {
        return;
    }
    const S& debut = sommets.begin()->first;
    visites.insert(debut);

    while (visites.size() < sommets.size()) {
        int distMin = std::numeric_limits<int>::max();
        S sommetMin;
        S sommetCourant;
        string nomRue;

        for (const S& sommet : visites) {
            for (const auto& voisin : sommets.at(sommet).voisins) {
                if (visites.find(voisin) == visites.end()) {
                    int distance = sommets.at(sommet).couts.at(voisin);
                    if (distance < distMin) {
                        sommetCourant = sommet;
                        nomRue = sommets.at(sommet).noRue.at(voisin);
                        distMin = distance;
                        sommetMin = voisin;
                    }
                }
            }
        }
        visites.insert(sommetMin);
        cout << nomRue << "\t" << sommetCourant << "\t" << sommetMin << "\t" << distMin << endl;
        coutTotal += distMin;
    }
    cout << "----------------------------------" << endl;
    cout << coutTotal << endl;
}




#endif
