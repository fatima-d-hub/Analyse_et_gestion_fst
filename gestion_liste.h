#ifndef GESTION_LISTE_H
#define GESTION_LISTE_H

#include <list>
#include <string>
#include "enseignant.h"
#include "UE.h"
#include "semestre.h"
#include "diplome.h"
#include "inscription.h"
#include "departement.h"
#include "intervention.h"

using namespace std;

extern list<Enseignant*> ListeEnseignant;
extern list<UE*> ListeUE;
extern list<Departement*> ListeDepartement;
extern list<Semestre*> ListeSemestre;
extern list<Inscription*> ListeInscription;
extern list<Intervention*> ListeIntervention;
extern list<Diplome*> ListeDiplome;

Enseignant* rechercherEnseignant(const string & id);
void ajouterEnseignant();
void afficherEnseignants();
void ajouterEnseignant();

void ajouterDiplome();
void afficherDiplomes();

UE* rechercherUEcon(const string& id);
Departement* rechercherDepartement(const string& id);
Semestre* rechercherSemestre(const string& id);
Inscription* rechercherInscription(const string& id);
Intervention* rechercherIntervention(const string& id);
Diplome* rechercherDiplome(const string& id);

#endif
