#ifndef INTERVENTION_H_INCLUDED
#define INTERVENTION_H_INCLUDED

#include <string>

class UE;
class Enseignant;


class Intervention{
    

    public:
    static int compteurID;
    private:
    //Declaration des Attributs
    string Id_intervention;
    int nbH_cours_intr;
    int nbH_td_intr;
    int nbH_tp_intr;

    Enseignant* enseignant;
    UE* ue;

    //Declaration des Methodes
    public:
        //Constructeur
        Intervention(Enseignant*, UE*, int, int, int, string id = "");

        //Setteurs
        void setNbH_cours_intr(int);
        void setNbH_td_intr(int);
        void setNbH_tp_intr(int);

        //Getteurs
        string getId_intervention()const;
        int  getNbH_cours_intr() const;
        int  getNbH_td_intr() const;
        int  getNbH_tp_intr() const;
        UE* getUE() const;
        Enseignant* getEnseignant() const;

        //Afficher les informations d'une intervention
        void AfficherIntervention();
};


#endif // INTERVENTION_H_INCLUDED