#ifndef DEPARTEMENT_H_INCLUDED
#define DEPARTEMENT_H_INCLUDED

#include <string>
#include <list>

class UE;
class Enseignant;
class Semestre;

using namespace std;

class Departement {

    public:
        static int compteurID;
    private:
    //declaration des attributs
    string id_departement;
    string nom_departement;

    Enseignant* responsable;
    list<Enseignant*> enseignants;
    list<UE*> ues;

    //declaration des methodes
    public:
        //Constructeur
        Departement( string, Enseignant*, string id = "");

        //Setteurs
        void setNom_departement(string );

        //Getteurs
        string getId_departement()const;
        string getNom_departement()const;

        Enseignant* getResponsable() const;
        list<Enseignant*> getEnseignants() const;
        list<UE*> getUEs() const;

        void ajouterEnseignant(Enseignant*);
        void ajouterUE(UE*);

        //Calcul Cout Departement en fonction UE
        float chargeHoraireDepartement(string);

        //Calcul Cout departement enseignants
        float calculCoutEnseignantDep();

        //Taux d'encadrement
        float tauxEncadrementDep(string);
        
        //Afficher les informations d'un département 
        void AfficherDepartement();

        



};


#endif // DEPARTEMENT_H_INCLUDED