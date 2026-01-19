#include "semestre.h"
#include "diplome.h"
#include "departement.h"
#include "Inscription.h"  
#include "gestion_liste.h"

#include <iostream>
#include <iomanip> //

using namespace std;

int Semestre::compteurID = 0;

static int extraireNumeroIDSemestre(const string& id)
{
    return stoi(id.substr(3));// "SEM001" -> 1
}

Semestre::Semestre(string nom, Diplome* d, string id)
{
    // Gestion de l'identifiant
    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "SEM" << setw(3) << setfill('0') << compteurID;
        id_semestre = oss.str();
    }
    else
    {
        id_semestre = id;
        int num = extraireNumeroIDSemestre(id);
        if (num > compteurID)
            compteurID = num;
    }

    nom_semestre = nom;
    diplome = d;

    if (diplome)
        diplome->ajouterSemestre(this);

    ListeSemestre.push_back(this);
}


//Getteurs
string Semestre::getId_semestre() const
{ 
    return id_semestre;
}

string Semestre::getNom_semestre()const
{
    return nom_semestre;
}

Diplome* Semestre::getDiplome() const
{
    return diplome;
}


//Autres fonctions
void Semestre::ajouterInscription(Inscription* i)
{
    inscriptions.push_back(i);
}


 //Calcul cout semestre
float Semestre::calculCoutSemestre()
{
    float cout_semestre = 0;

    list<Inscription*>::iterator it;

    for(it = inscriptions.begin(); it != inscriptions.end(); it++)
    {
        UE* ue = (*it)->getUE();

        int nb_inscrit = (*it)->getNbInscrit();

        int nb_inscrit_total = ue->nombre_inscrit();

        cout_semestre += ue->calculETD()*((float)nb_inscrit/nb_inscrit_total);
        
    }

    return cout_semestre;
}

//Afficher les informations d'un semestre
void Semestre::AfficherSemestre()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" SEMESTRE : " + id_semestre) << "\n";
    cout << bleu("----------------------------------") << "\n";

    cout << jaune(" Nom :") << " " << nom_semestre << "\n";

    cout << jaune(" Diplome :") << " " << diplome->getNomDiplome() << "\n";

    if (inscriptions.size() != 0)
    {
        cout << jaune(" Liste des inscriptions :") << "\n";
        list<Inscription*>::iterator it;

        for (it = inscriptions.begin(); it != inscriptions.end(); it++)
        {
            if (*it != nullptr)
            {
                cout << "  - UE : " << (*it)->getUE()->getNomUE()
                     << " (" << (*it)->getNbInscrit() << " inscrits)\n";
            }
        }
    }

    cout << "\n";
}
