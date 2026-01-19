#include "Enseignant.h"
#include "departement.h"
#include "Intervention.h"
#include "gestion_liste.h"

#include <iostream>
#include <iomanip> // pour setw et setfill
#include <sstream>
#include <algorithm>
#include <cctype>

//--------------------CLASS ENSEIGNANT-----------------------
int Enseignant::compteurID = 0;

/*
Fonctions utilitaires pour supprimer les espaces dans le nom ou le prenom,
mettre le nom et le prenom en minuscule pour avoir un bon format d'email
*/
string supprimerEspaces(string s)
{
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

string enMinuscules(string s)
{
    for (char &c : s)
        c = tolower(c);
    return s;
}

//Constructeur
static int extraireNumeroID(const string& id)
{
    if (id.size() < 2) return 0;
    return stoi(id.substr(1)); // "E012" -> 12
}

//Constructeur
Enseignant::Enseignant(
    string nom,
    string prenom,
    string adresse,
    string email,
    string id
)
{
    // Gestion de l'identifiant
    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "E" << setw(3) << setfill('0') << compteurID;
        id_enseignant = oss.str();
    }
    else
    {
        id_enseignant = id;
        int num = extraireNumeroID(id);
        if (num > compteurID)
            compteurID = num;
    }

    nom_enseignant = nom;
    prenom_enseignant = prenom;
    adresse_enseignant = adresse;

    // Gestion de l'email
    if (email.empty())
    {
        email_enseignant =
            enMinuscules(
                supprimerEspaces(nom) + "." +
                supprimerEspaces(prenom)
            ) + "@unilim.fr";
    }
    else
    {
        email_enseignant = email;
    }

    departementRattache = nullptr;

    ListeEnseignant.push_back(this);
}



//Setteurs
void Enseignant::setNom(string nom)
{
    nom_enseignant = nom;
}

void Enseignant::setPrenom(string prenom)
{
    prenom_enseignant = prenom;
}

void Enseignant::setAdresse(string adresse)
{
    adresse_enseignant = adresse;
}

void Enseignant::setEmail(string email)
{
    email_enseignant = email;
}

//Getteurs
string Enseignant::getId() const
{
    return id_enseignant;
}

string Enseignant::getNom() const
{
    return nom_enseignant;
}

string Enseignant::getPrenom() const
{
    return prenom_enseignant;
}

string Enseignant::getAdresse() const
{
    return adresse_enseignant;
}

string Enseignant::getEmail() const
{
    return email_enseignant;
}


int Enseignant::getNbH_ETD() const
{
    return 0;
}

void Enseignant::ajouterUEResponsable(UE* ue)
{
    uesResponsable.push_back(ue);
}

void Enseignant::ajouterIntervention(Intervention* i)
{
    interventions.push_back(i);
}

void Enseignant::ajouterDepartementGere(Departement* d)
{
    departementsGeres.push_back(d);
}



void Enseignant::rattacherDepartement(Departement* d)
{
    departementRattache = d;
    d->ajouterEnseignant(this);
}


//Calcul du charge horaire d'un enseignant
float Enseignant::chargeHoraireEnseignant(string nomE)
{
    float cout_horaire = 0;

    float etd_ue = 0;

    list<Intervention*>::iterator it;

    for(it = interventions.begin(); it != interventions.end(); it++)
    {
        etd_ue = (*it)->getNbH_cours_intr() + (*it)->getNbH_td_intr() + (*it)->getNbH_tp_intr();

        cout_horaire += etd_ue;
    }

    return cout_horaire;
}

void Enseignant::AfficherEnseignant()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" ENSEIGNANT : " + id_enseignant ) << "\n";
    cout << bleu("----------------------------------") << "\n";
    cout << jaune(" Nom : ") << nom_enseignant<< "\n";
    cout << jaune(" Prenom : ") << prenom_enseignant << "\n";
    cout << jaune(" Adresse : ") << adresse_enseignant << "\n";
    cout << jaune(" Email : ") << email_enseignant <<"\n";

    if (departementRattache != nullptr)
         cout << jaune(" Departement Rattache :") << departementRattache->getNom_departement()<<"\n";
    else
        cout << jaune(" Departement Rattache :") << " Non defini\n";


    if(uesResponsable.size()!=0)
    {
        cout << jaune("  Liste des UEs gerees: ") << endl;
        list<UE*>::iterator it;

        for(it = uesResponsable.begin(); it != uesResponsable.end(); it++)
        {
            cout << "  - " << (*it)->getNomUE() << endl;
        }
    }

     if(interventions.size()!=0)
    {
        cout << jaune(" Liste des interventions:") << endl;
        list<Intervention*>::iterator it;

        for(it = interventions.begin(); it != interventions.end(); it++)
        {
            cout << "  - " << (*it)->getUE()->getNomUE() << endl;
        }
    }

    if(departementsGeres.size()!=0)
    {
        cout << jaune(" Liste des departements geres:") << endl;
        list<Departement*>::iterator it;

        for(it = departementsGeres.begin(); it != departementsGeres.end(); it++)
        {
            cout << "  - " << (*it)->getNom_departement() << endl;
        }
    }

}



//--------------------CLASS ENSEIGNANT-CHERCHEUR-----------------------

//Constructeur
EnseignantChercheurs::EnseignantChercheurs(string nom, string prenom, string adresse,TypeEnseignantCherc t, string sujet_rech, string email, string id):Enseignant(nom, prenom, adresse, email, id)
{
    type_e = t;
    sujet_recherche = sujet_rech;
}

void EnseignantChercheurs::setTypeE(TypeEnseignantCherc t)
{
    type_e = t;
}

void EnseignantChercheurs::setSujet_recherche( string sujet_rech)
{
    sujet_recherche = sujet_rech;
}

//Getteurs
TypeEnseignantCherc EnseignantChercheurs::getTypeE() const
{
    return type_e;
}

string EnseignantChercheurs::getSujet_recherche() const
{
    return sujet_recherche;
}

int EnseignantChercheurs::getNbH_ETD() const
{
    return NbH_ETD;
}

void EnseignantChercheurs::AfficherEnseignant()
{
    Enseignant::AfficherEnseignant();
    cout << jaune(" Nombre d'heures ETD :") << " " << getNbH_ETD() << "\n";
    cout << jaune(" Type d'enseignant :") << " " << (type_e == TypeEnseignantCherc::MC ? "MC" : "PR") << "\n";
    cout << jaune(" Sujet de recherche :") << " " << sujet_recherche << "\n";
    cout << endl;
}

//--------------------CLASS AUTRE_ENSEIGNANT-----------------------
//Constructeur
AutreEnseignant::AutreEnseignant(string nom, string prenom, string adresse, string email, string id): Enseignant(nom, prenom, adresse, email, id)
{
}


//Getteurs
int AutreEnseignant::getNbH_ETD() const
{
    return NbH_ETD;
}

void AutreEnseignant::AfficherEnseignant()
{
    Enseignant::AfficherEnseignant();
    cout << jaune(" Nombre d'heures ETD :") << " " << getNbH_ETD() << "\n";
    cout << endl;
}