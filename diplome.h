#ifndef DIPLOME_H_INCLUDED
#define DIPLOME_H_INCLUDED

#include <string>
#include <list>

class Semestre;
 
using namespace std;

class Diplome{

    public:
    static int compteurID;  

    private:
    //Declaration des attributs
    string id_diplome;
    string nom_diplome;

    list<Semestre*> semestres;

    //Declaration des methodes
    public:
        //Constructeur
        Diplome(string, string id = "");

        //Setteurs
        void setNomDiplome(string);

        //Getteurs
        string getIdDiplome()const;
        string getNomDiplome()const;
        list<Semestre*> getSemestres() const;

        void ajouterSemestre(Semestre*);
        Semestre* rechercherSemestreNom(string) const;

        //Calcul Cout diplôme
        float coutDiplome(string);

        //Afficher les informations d'un diplome 
        void AfficherDiplome();


};




#endif // DIPLOME_H_INCLUDED