#include "gestion_liste.h"

//Gestion Enseignant
// Gestion Enseignant
list<Enseignant*> ListeEnseignant;

Enseignant* rechercherEnseignant(const string& id)
{
    for (auto it = ListeEnseignant.begin(); it != ListeEnseignant.end(); ++it)
    {
        if ((*it)->getId() == id)
            return *it;
    }
    return nullptr;
}

// Gestion UE
list<UE*> ListeUE;

UE* rechercherUE(const string& id)
{
    for (auto it = ListeUE.begin(); it != ListeUE.end(); ++it)
    {
        if ((*it)->getIdUE() == id)
            return *it;
    }
    return nullptr;
}

// Gestion Departement
list<Departement*> ListeDepartement;

Departement* rechercherDepartement(const string& id)
{
    for (auto it = ListeDepartement.begin(); it != ListeDepartement.end(); ++it)
    {
        if ((*it)->getId_departement() == id)
            return *it;
    }
    return nullptr;
}

// Gestion Semestre
list<Semestre*> ListeSemestre;

Semestre* rechercherSemestre(const string& id)
{
    for (auto it = ListeSemestre.begin(); it != ListeSemestre.end(); ++it)
    {
        if ((*it)->getId_semestre() == id)
            return *it;
    }
    return nullptr;
}

// Gestion Inscription
list<Inscription*> ListeInscription;

Inscription* rechercherInscription(const string& id)
{
    for (auto it = ListeInscription.begin(); it != ListeInscription.end(); ++it)
    {
        if ((*it)->getId_inscription() == id)
            return *it;
    }
    return nullptr;
}

// Gestion Intervention
list<Intervention*> ListeIntervention;

Intervention* rechercherIntervention(const string& id)
{
    for (auto it = ListeIntervention.begin(); it != ListeIntervention.end(); ++it)
    {
        if ((*it)->getId_intervention() == id)
            return *it;
    }
    return nullptr;
}

// Gestion Diplome
list<Diplome*> ListeDiplome;

Diplome* rechercherDiplome(const string& id)
{
    for (auto it = ListeDiplome.begin(); it != ListeDiplome.end(); ++it)
    {
        if ((*it)->getIdDiplome() == id)
            return *it;
    }
    return nullptr;
}



//Ajouter un enseignant
void ajouterEnseignant()
{
    string nom, prenom, adresse;
    cout << jaune("\n=== AJOUT ENSEIGNANT ===\n\n");
    cout << "Nom : ";
    cin >> ws; // pour consommer les espaces
    getline(cin, nom);
    cout << "Prenom : "; 
    getline(cin, prenom);
    cout << "Adresse : "; 
    getline(cin, adresse);

    int type;
    cout << cyan("\nType enseignant :\n\n");
    cout << "1. Enseignant-Chercheur\n";
    cout << "2. Autre Enseignant\n\n";
    cout << "Choix : ";
    cin >> type;

    Enseignant* e = nullptr;  

    if (type == 1)
    {
        int t;
        string sujet;

        cout << "\nType (0 = MC, 1 = PR) : ";
        cin >> t;
        cin.ignore();  // vide le buffer

        cout << "Sujet de recherche : ";
        getline(cin, sujet);

        e = new EnseignantChercheurs(
            nom,
            prenom,
            adresse,
            t == 0 ? TypeEnseignantCherc::MC : TypeEnseignantCherc::PR,
            sujet
        );
    }
    else
    {
        e = new AutreEnseignant(nom, prenom, adresse);
    }

    cout << "\nEnseignant ajoute avec succes\n\n";
}



// Afficher tous les enseignants
void afficherEnseignants()
{
    if (ListeEnseignant.empty())
    {
        cout << "\nAucun enseignant enregistre.\n\n";
        return;
    }

    list<Enseignant*>::iterator it;

    for (it = ListeEnseignant.begin(); it != ListeEnseignant.end(); ++it)
    {
        (*it)->AfficherEnseignant();
    }
}

//Afficher les semestres
void afficherSemestres()
{
    if (ListeSemestre.empty())
    {
        cout << "\nAucun semestre enregistre.\n\n";
        return;
    }

    list<Semestre*>::iterator it;
    for (it = ListeSemestre.begin(); it != ListeSemestre.end(); ++it)
    {
        (*it)->AfficherSemestre();
    }
}

//Ajouter un semestre
void ajouterSemestre()
{
    string idDiplome;
    string numSemestre;
    string nomSemestre;

    cout << "ID du diplome : ";
    cin >> idDiplome;

    Diplome* d = rechercherDiplome(idDiplome);
    if (!d)
    {
        cout << "\nDiplome introuvable !\n";
        return;
    }

    cin.ignore();
    cout << "Nom du semestre : ";
    getline(cin, nomSemestre);

    // Vérification : semestre déjà existant ?
    if (d->rechercherSemestreNom(nomSemestre))
    {
        cout << "\nCe semestre existe deja pour ce diplome.\n\n";
        return;
    }

    // Création du semestre
    Semestre* s = new Semestre(nomSemestre, d);

    cout << "\nSemestre ajoute avec succes au diplome\n\n"
         << d->getNomDiplome() << ".\n";
}

void afficherDiplomes()
{
    if (ListeDiplome.empty())
    {
        cout << "\nAucun diplome enregistre.\n\n";
        return;
    }

    list<Diplome*>::iterator it;

    for (it = ListeDiplome.begin(); it != ListeDiplome.end(); ++it)
    {
        (*it)->AfficherDiplome();
    }
}

void ajouterDiplome()
{
    string nom;

    cin.ignore();
    cout << "Nom du diplome : ";
    getline(cin, nom);

    Diplome* d = new Diplome(nom);

    cout << "\nDiplome ajoute avec succes.\n";
    cout << "ID genere : " << d->getIdDiplome() << endl;
}


