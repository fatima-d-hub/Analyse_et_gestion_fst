#include "diplome.h"
#include "gestion_liste.h"
#include <iostream>
#include <iomanip> 
#include <algorithm>
#include <cctype>


using namespace std;

int Diplome::compteurID = 0;

static int extraireNumeroIDDiplome(const string& id)
{
    
    if (id.size() <= 3) return 0;
    return stoi(id.substr(3));
}

// Constructeur 
Diplome::Diplome(string nom, string id)
{
    // Gestion de l'identifiant
    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "DIP" << setw(3) << setfill('0') << compteurID;
        id_diplome = oss.str();
    }
    else
    {
        id_diplome = id;
        int num = extraireNumeroIDDiplome(id);
        if (num > compteurID)
            compteurID = num;
    }

    nom_diplome = nom;
    ListeDiplome.push_back(this);
}

//Setteurs
void Diplome::setNomDiplome(string nom)
{
    nom_diplome = nom;
}

//Getteurs
string Diplome::getIdDiplome()const
{
    return id_diplome;
}

string Diplome::getNomDiplome()const
{ 
    return nom_diplome;
}

list<Semestre*> Diplome::getSemestres() const
{
    return semestres;
}


void Diplome::ajouterSemestre(Semestre* s)
{
    if (s != nullptr)
        semestres.push_back(s);
}


//Calcul Cout diplôme
float Diplome::coutDiplome(string nomD)
{
    float cout_dip = 0;

    list<Semestre*>::iterator it;

    for(it = semestres.begin(); it != semestres.end(); it++)
    {
        cout_dip += (*it)->calculCoutSemestre();
    }

    return cout_dip;
}

//Afficher les informations d'un diplome 
void Diplome::AfficherDiplome()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" DIPLOME : " + id_diplome) << "\n";
    cout << bleu("----------------------------------") << "\n";

    cout << jaune(" Nom :") << " " << nom_diplome << "\n";

    if (semestres.size() != 0)
    {
        cout << jaune(" Liste des semestres :") << "\n";
        list<Semestre*>::iterator it;

        for (it = semestres.begin(); it != semestres.end(); it++)
        {
            if (*it != nullptr)
                cout << "  - " << (*it)->getNom_semestre() << "\n";
        }
    }

    cout << "\n";
}


//Convertir tout en minuscule
string toLower(const string& s)
{
    string res = s;
    transform(res.begin(), res.end(), res.begin(),
              [](unsigned char c){ return tolower(c); });
    return res;
}

//Rechercher un semestre par nom parmi les semestres d'un diplome
Semestre* Diplome::rechercherSemestreNom(string n) const
{
    for (Semestre* s : semestres)
    {
        if (toLower(s->getNom_semestre()) == toLower(n))
            return s;
    }
    return nullptr;
}




