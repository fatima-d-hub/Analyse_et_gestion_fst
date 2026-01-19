#ifndef UE_H_INCLUDED
#define UE_H_INCLUDED

#include <string>
#include <list>

class Enseignant;
class Departement;
class Intervention;
class Inscription;

using namespace std;

class UE{

    public:
    static int compteurID;
    private:
    //DECLARATION DES ATTRIBUTS
    string id_UE;
    string nom_UE;
    string description_UE;

    int nbH_cours;
    int nbH_td;
    int nbH_tp;

    const float coefficient_cours = (float)3/2;
    const float coefficient_td = 1;
    const float coefficient_tp = (float)2/3;

    int nbG_cours = 0;
    int nbG_td = 0;
    int nbG_tp = 0;

    Departement* departement;
    Enseignant* responsable;
    list<Intervention*> interventions;
    list<Inscription*> inscriptions;

    //DECLARATION DES METHODES
    public:
        //Constructeur
        UE(string, string, int, int, int, int, int, int, Departement*, Enseignant*, string id = "");



        //Setteurs
        void setNomUE(string);
        void setDescriptionUE(string);

        void setNbHCours(int);
        void setNbHTd(int);
        void setNbHTp(int);

        void setNbGCours(int);
        void setNbGTd(int);
        void setNbGtp(int);

        void setResponsable(Enseignant*);

        //Getteurs
        string getIdUE()const;
        string getNomUE()const;
        string getDescriptionUE()const;

        int getNbHCours()const;
        int getNbHTd()const;
        int getNbHTp()const;

        int getCoefficientCours()const;
        int getCoefficientTd()const;
        int getCoefficientTp()const;

        int getNbGCours()const;
        int getNbGTd()const;
        int getNbGTp()const;

        Enseignant* getResponsable() const;
        Departement* getDepartement() const;


        //Autres fonctions

        void ajouterIntervention(Intervention*);
        void ajouterInscription(Inscription*);

        //Calcul ETD
        float calculETD() const;

        //Nombre inscrit UE
        int nombre_inscrit();

        //Affichage d'une UE
        void AfficherUE() const;

        int heuresCoursAffectees() const;
        int heuresTdAffectees() const;
        int heuresTpAffectees() const;
    
};


#endif // UE_H_INCLUDED