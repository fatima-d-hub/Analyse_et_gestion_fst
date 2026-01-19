#include <iostream>
#include <string>

#include "UE.cpp"
#include "semestre.cpp"
#include "diplome.cpp"
#include "inscription.cpp"
#include "enseignant.cpp"
#include "departement.cpp"
#include "intervention.cpp"
#include "couleur.cpp"
#include "gestion_liste.cpp"
#include "application.cpp"
#include "sauvegarde.cpp"



using namespace std;



int main()
{
    Application app; // Création de l'application
    app.lancer();    // Lancement du menu principal et de la logique du programme

    return 0;
}
