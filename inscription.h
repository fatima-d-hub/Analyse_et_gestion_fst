#ifndef INSCRIPTION_H_INCLUDED
#define INSCRIPTION_H_INCLUDED

#include <string>

class UE;
class Semestre;

class Inscription{

    public:
    static int compteurID;

    private:
    //Declaration des Attributs
    string Id_inscription;
    int nb_inscrit;

    UE* ue;
    Semestre* semestre;

    //Declaration des Methods
    public:
        //Constructeur
        Inscription(int, UE*, Semestre*, string id = "");

        //Setteurs
        void setNbInscrit(int);

        //Getteurs
        string getId_inscription()const;
        int getNbInscrit()const;
        UE* getUE() const;
        Semestre* getSemestre() const;

        //Afficher les informations d'une inscription
        void AfficherInscription();

};


#endif // INSCRIPTION_H_INCLUDED