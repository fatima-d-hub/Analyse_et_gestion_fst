#ifndef SEMESTRE_H_INCLUDED
#define SEMESTRE_H_INCLUDED

#include <string>
#include <list>

class Diplome;
class Departement;
class Inscription;

using namespace std;

class Semestre{

     public:
    static int compteurID;
    private:
    //Declaration des Attributs
    string id_semestre;
    string nom_semestre;

    Diplome* diplome;
    list<Inscription*> inscriptions;


    //declaration des methodes
    public:
        //Constructeur
        Semestre(string, Diplome*, string id = "");

        //Getteurs
        string getId_semestre()const;
        string getNom_semestre()const;
        Diplome* getDiplome() const;

        void ajouterInscription(Inscription*);

        //Calcul cout semestre
        float calculCoutSemestre();

        //Afficher les informations d'un semestre
        void AfficherSemestre();
};

#endif // SEMESTRE_H_INCLUDED