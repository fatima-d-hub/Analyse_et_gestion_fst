#include "UE.h"
#include "departement.h"
#include "enseignant.h"
#include "Inscription.h"
#include "couleur.h"
#include "gestion_liste.h"

using namespace std;

#include <iostream>
#include <iomanip> 

int UE::compteurID = 0;

static int extraireNumeroIDUE(const string& id)
{
    return stoi(id.substr(2));
}

UE::UE(
    string nom,
    string description,
    int nbHc, int nbHtd, int nbHtp,
    int nbGc, int nbGtd, int nbGtp,
    Departement* dep,
    Enseignant* ens,
    string id
)
{
    

    // Gestion de l'identifiant
    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "UE" << setw(3) << setfill('0') << compteurID;
        id_UE = oss.str();
    }
    else
    {
        id_UE = id;
        int num = extraireNumeroIDUE(id);
        if (num > compteurID)
            compteurID = num;
    }

    // Données de l'UE
    nom_UE = nom;
    description_UE = description;

    nbH_cours = nbHc;
    nbH_td    = nbHtd;
    nbH_tp    = nbHtp;

    nbG_cours = nbGc;
    nbG_td    = nbGtd;
    nbG_tp    = nbGtp;

    // Relations
    departement = dep;
    departement->ajouterUE(this);

    responsable = ens;
    responsable->ajouterUEResponsable(this);

    // Enregistrement global
    ListeUE.push_back(this);
}


//Setteurs
void UE::setNomUE(string nom)
{
    nom_UE = nom;
}

void UE::setDescriptionUE(string description)
{
    description_UE = description;
}

void UE::setNbHCours(int nbHc)
{
    nbH_cours = nbHc;
}

void UE::setNbHTd(int nbHtd)
{
    nbH_td = nbHtd;
}

void UE::setNbHTp(int nbHtp)
{
    nbH_tp = nbHtp;
}

void UE::setNbGCours(int nbGc)
{
    nbG_cours = nbGc;
}

void UE::setNbGTd(int nbGtd)
{
    nbG_td = nbGtd;
}

void UE::setNbGtp(int nbGtp)
{
    nbG_tp = nbGtp;
}

void UE::setResponsable(Enseignant* e)
{
    responsable = e;
    e->ajouterUEResponsable(this);
}



//Getteurs
string UE::getIdUE()const
{
    return id_UE;
}

string UE::getNomUE()const
{
    return nom_UE;
}

string UE::getDescriptionUE()const
{
    return description_UE;
}

int UE::getNbHCours()const
{
    return nbH_cours;
}

int UE::getNbHTd()const
{
    return nbH_td;
}

int UE::getNbHTp()const
{
    return nbH_tp;
}

int UE::getCoefficientCours()const
{
    return coefficient_cours;
}

int UE::getCoefficientTd()const
{
    return coefficient_td;
}

int UE::getCoefficientTp()const
{
    return coefficient_tp;
}

int UE::getNbGCours()const
{
    return nbG_cours;
}

int UE::getNbGTd()const
{
    return nbG_td;
}

int UE::getNbGTp()const
{
    return nbG_tp;
}

Enseignant* UE::getResponsable() const
{
    return responsable;
}

Departement* UE::getDepartement() const
{
    return departement;
}

int UE::heuresCoursAffectees() const
{
    int total = 0;
    for(auto it = interventions.begin(); it != interventions.end(); ++it)
        total += (*it)->getNbH_cours_intr();
    return total;
}

int UE::heuresTdAffectees() const
{
    int total = 0;
    for(auto it = interventions.begin(); it != interventions.end(); ++it)
        total += (*it)->getNbH_td_intr();
    return total;
}

int UE::heuresTpAffectees() const
{
    int total = 0;
    for(auto it = interventions.begin(); it != interventions.end(); ++it)
        total += (*it)->getNbH_tp_intr();
    return total;
}

//Autres fonctions
void UE::ajouterIntervention(Intervention* i)
{
    interventions.push_back(i);
}

void UE::ajouterInscription(Inscription* i)
{
    inscriptions.push_back(i);
}

//Calcul ETD
float UE::calculETD() const
{
    float etd_cours = nbG_cours*nbH_cours*coefficient_cours;
    float etd_td = nbG_td*nbH_td*coefficient_td;
    float etd_tp = nbG_tp*nbH_tp*coefficient_tp;

    return etd_cours + etd_td + etd_tp;
}



//Nombre inscrit UE
int UE::nombre_inscrit()
{
    int nb_ins = 0;

    list<Inscription*>::iterator it;

    for(it = inscriptions.begin(); it != inscriptions.end(); it++)
    {
        nb_ins += (*it)->getNbInscrit();
    }

    return nb_ins;
}


//Affichage d'une UE
void UE::AfficherUE() const
{
        cout << bleu("----------------------------------") << "\n";
        cout << cyan(" UE : " + id_UE + " - " + nom_UE) << "\n";
        cout << bleu("----------------------------------") << "\n";
        cout << jaune("Description de l'UE : ") << " " << description_UE << "\n";
        cout << jaune("Departement :") << " " << departement->getNom_departement() << "\n";
        if (responsable != nullptr)
            cout << jaune("Responsable :") << " " << responsable->getNom() << "\n";
        else
            cout << jaune("Responsable :") << " Non defini\n";

        cout << jaune("Heures :") << " "
             << nbH_cours << "h Cours, " << nbH_td << "h TD, " << nbH_tp << "h TP\n";
        cout << jaune("Groupes :") << " "
             << nbG_cours << " Cours, " << nbG_td << " TD, " << nbG_tp << " TP\n";
        cout << jaune("Cout ETD :") << " " << UE::calculETD() << " h\n\n";
        
}

void AfficherUEs()
{
    if (ListeUE.empty())
    {
        cout << "\nAucune UE enregistre.\n\n";
        return;
    }

    list<UE*>::iterator it;

    for (it = ListeUE.begin(); it != ListeUE.end(); ++it)
    {
        (*it)->AfficherUE();
    }
}