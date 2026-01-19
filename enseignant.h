#ifndef ENSEIGNANT_H_INCLUDED
#define ENSEIGNANT_H_INCLUDED

#include <string>
#include <list>

class UE;
class Departement;
class Intervention;

using namespace std;



//---------------------------CLASS ENSEIGNANT-------------------------------
class Enseignant {
    public:
        static int compteurID;
    protected:
        string id_enseignant;
        string nom_enseignant;
        string prenom_enseignant;
        string adresse_enseignant;
        string email_enseignant;

        Departement* departementRattache;
        list<UE*> uesResponsable;
        list<Intervention*> interventions;
        list<Departement*> departementsGeres;

    //Declarations des Methodes
    public:
        //constructeur
        Enseignant(string ,string , string, string email = "", string id = "");


        //setters
        void setNom(string );
        void setPrenom(string );
        void setAdresse(string );
        void setEmail(string );

        //getters
        string getId() const;
        string getNom() const;
        string getPrenom() const;
        string getAdresse() const;
        string getEmail() const;



        virtual int getNbH_ETD() const;


        void ajouterUEResponsable(UE*);
        void ajouterIntervention(Intervention*);
        void ajouterDepartementGere(Departement*);
        void rattacherDepartement(Departement*);

        //Calcul du charge horaire d'un enseignant
        float chargeHoraireEnseignant(string);

        //Afficher les informations d'un enseignant
        virtual void AfficherEnseignant();

       





};

//---------------------------CLASS ENSEIGNANT-CHERCHEUR-------------------------------

//Declaration de l'enumeration pour le type d'enseignant (MC ou PR)
enum class TypeEnseignantCherc{
    MC,
    PR,
};

class EnseignantChercheurs:public Enseignant
{
    //Declaration des Attributs
    const int NbH_ETD = 192;
    TypeEnseignantCherc type_e;
    string sujet_recherche;

    //Declaration des Methodes
    public:
        //Constructeur
        EnseignantChercheurs(string, string, string,  TypeEnseignantCherc, string, string email = "", string id_ens = "");


        //Setteurs
        void setTypeE(TypeEnseignantCherc);
        void setSujet_recherche(string);

        //Getteurs
        int getNbH_ETD() const;
        TypeEnseignantCherc getTypeE() const;
        string getSujet_recherche() const;
        void AfficherEnseignant();

};


//---------------------------CLASS AUTRE_ENSEIGNANT-------------------------------
class AutreEnseignant:public Enseignant
{

    //Declaration des Attributs
    const int NbH_ETD = 384;

    //Declaration des methodes
    public:
        //Constructeur
        AutreEnseignant(string, string, string, string email = "",string id = "");

        //Getteur
        int getNbH_ETD() const;
        void AfficherEnseignant();

};


#endif
