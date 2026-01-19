#include "inscription.h"
#include "UE.h"
#include "semestre.h"
#include "gestion_liste.h"

#include <iostream>
#include <iomanip> // pour setw et setfill
#include <sstream>

using namespace std;

int Inscription::compteurID = 0;

static int extraireNumeroIDInscription(const string& id)
{
    if (id.size() <= 3) return 0;
    return stoi(id.substr(3));
}

Inscription::Inscription(int nb, UE* u, Semestre* s, string id)
{
    // Gestion de l'identifiant

    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "INS" << setw(3) << setfill('0') << compteurID;
        Id_inscription = oss.str();
    }
    else
    {
        Id_inscription = id;
        int num = extraireNumeroIDInscription(id);
        if (num > compteurID)
            compteurID = num;
    }

    nb_inscrit = nb;
    ue = u;
    semestre = s;

    u->ajouterInscription(this);
    s->ajouterInscription(this);

    ListeInscription.push_back(this);
}





//Setteurs
void Inscription::setNbInscrit(int nb_i){
    nb_inscrit = nb_i;
}

//Getteurs
string Inscription::getId_inscription()const
{
    return Id_inscription;
}

int Inscription::getNbInscrit()const
{
    return nb_inscrit;
}

UE* Inscription::getUE() const
{
    return ue;
}

Semestre* Inscription::getSemestre() const
{
    return semestre;
}

//Afficher les informations d'une inscription
void Inscription::AfficherInscription()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" INSCRIPTION " + Id_inscription) << "\n";
    cout << bleu("----------------------------------") << "\n";

    cout << jaune(" Nombre d'inscrits :") << " " << nb_inscrit << "\n";

    cout << jaune(" UE :") << " " << ue->getNomUE() << "\n";

    cout << jaune(" Semestre :") << " " << semestre->getNom_semestre() << "\n";

    cout << "\n";
}

void afficherInscriptions()
{
    if (ListeInscription.empty())
    {
        cout << "\nAucune inscription enregistree.\n\n";
        return;
    }

    list<Inscription*>::iterator it;        
    for (it = ListeInscription.begin(); it != ListeInscription.end(); ++it)
    {
        (*it)->AfficherInscription();
    }
}