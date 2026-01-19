#include "departement.h"
#include "enseignant.h"
#include "gestion_liste.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Compteur statique
int Departement::compteurID = 0;


static int extraireNumeroIDDep(const string& id)
{

    if (id.size() <= 3)
        return 0;

    return stoi(id.substr(3));
}

// Constructeur
Departement::Departement( string nom, Enseignant* e, string id)
{
    // Gestion de l'identifiant
    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "DEP" << setw(3) << setfill('0') << compteurID;
        id_departement = oss.str();
    }
    else
    {
        id_departement = id;
        int num = extraireNumeroIDDep(id);
        if (num > compteurID)
            compteurID = num;
    }

    nom_departement = nom;
    responsable = e;
    responsable->ajouterDepartementGere(this);

    ListeDepartement.push_back(this);
}


//Setteurs
void Departement::setNom_departement(string nom_d)
{
    nom_departement = nom_d;
}

//Getteurs
string Departement::getId_departement()const
{
    return id_departement;
}

string Departement::getNom_departement()const
{
    return nom_departement;
}

Enseignant* Departement::getResponsable() const
{
    return responsable;
}

list<Enseignant*> Departement::getEnseignants() const
{
    return enseignants;
}

list<UE*> Departement::getUEs() const
{
    return ues;
}


void Departement::ajouterEnseignant(Enseignant* e)
{
    enseignants.push_back(e);
}

void Departement::ajouterUE(UE* ue)
{
    ues.push_back(ue);
}


//Calcul Cout Departement en fonction UE
float Departement::chargeHoraireDepartement(string nomDep)
{
    list<UE*>::iterator it;

    float cout_dep = 0;

    for(it = ues.begin(); it != ues.end(); it++)
    {
        cout_dep += (*it)->calculETD();
    }

    return cout_dep;
}


//Calcul Cout departement enseignants
float Departement::calculCoutEnseignantDep()
{
    list<Enseignant*>::iterator it;

    float cout_ens_dep = 0;

    for(it = enseignants.begin(); it != enseignants.end(); it++)
    {
        if((*it)->getNbH_ETD() == 192)
        {
            cout_ens_dep += (*it)->getNbH_ETD();
        }
    }

    return cout_ens_dep;
}


//Taux d'encadrement
float Departement::tauxEncadrementDep(string nomDep)
{
    float cout_dep = chargeHoraireDepartement(nomDep);

    float cout_ens = calculCoutEnseignantDep();

    if(cout_dep == 0)
        cout << "\nLe departement n'a pas d'UE associee.\n";
        return 0; 

    return cout_ens / cout_dep;
}


//Afficher les informations d'un département
void Departement::AfficherDepartement()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" DEPARTEMENT : " + id_departement) << "\n";
    cout << bleu("----------------------------------") << "\n";

    cout << jaune(" Nom :") << " " << nom_departement << "\n";

    cout << jaune(" Responsable :") << " " << responsable->getNom() << " " << responsable->getPrenom() << "\n";
    
    if (enseignants.size() != 0)
    {
        cout << jaune(" Liste des enseignants :") << "\n";
        list<Enseignant*>::iterator itEns;

        for (itEns = enseignants.begin(); itEns != enseignants.end(); itEns++)
        {
            if (*itEns != nullptr)
                cout << "  - " << (*itEns)->getNom() << "\n";
        }
    }

    if (ues.size() != 0)
    {
        cout << jaune(" Liste des UE gerees :") << "\n";
        list<UE*>::iterator it;

        for (it = ues.begin(); it != ues.end(); it++)
        {
            if (*it != nullptr)
                cout << "  - " << (*it)->getNomUE() << "\n";
        }
    }

    cout << "\n";
}

void ajouterDepartement()
{
    string nomDep;
    string idResp;
    Enseignant* resp = nullptr;

    cout << "Nom du departement : ";
    cin.ignore();
    getline(cin, nomDep);

    cout << "ID de l'enseignant responsable : ";
    cin >> idResp;
    resp = rechercherEnseignant(idResp);

    if (!resp)
    {
        cout << "\n\nEnseignant introuvable. Creation du departement annulee.\n\n";
        return;
    }

    Departement* d = new Departement(nomDep, resp);
    cout << "\nDepartement cree avec ID : " << d->getId_departement() << "\n\n";
}

//Afficher tous les départements
void afficherDepartements()
{
    if (ListeDepartement.empty())
    {
        cout << "Aucun departement enregistre.\n\n";
        return;
    }

    cout << "\n===== LISTE DES DEPARTEMENTS =====\n";
    for (Departement* d : ListeDepartement)
    {
        if (d != nullptr)
            d->AfficherDepartement();
    }
}


