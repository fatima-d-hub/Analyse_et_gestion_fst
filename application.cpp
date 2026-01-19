#include "Application.h"
#include "enseignant.h"
#include "gestion_liste.h"
#include "departement.h"
#include "UE.h"
#include "intervention.h"
#include "inscription.h"
#include "diplome.h"
#include "sauvegarde.h"
#include "couleur.h"

#include <iostream>
#include <cstdlib> 

using namespace std;

//------------------ VERIFICATION DES DONNEES ----------------------
// Vérifie si au moins un fichier de données existe et n'est pas vide
bool donneesExistantes()
{
    return fichierExisteEtNonVide("data/enseignants.txt")
        || fichierExisteEtNonVide("data/departements.txt")
        || fichierExisteEtNonVide("data/ues.txt");
}

// ------------------- LANCEMENT APPLICATION ---------------------
// Démarrage principal de l'application
void Application::lancer()
{
    // Si des données sauvegardées existent
    if (donneesExistantes())
    {
        char rep;
        system("cls");
        cout << "Des donnees sauvegardees ont ete trouvees.\n\n";
        cout << "Voulez-vous les charger ? (o/n) : ";
        cin >> rep;
        cout << endl;

        // Chargement des données si l'utilisateur accepte
        if (rep == 'o' || rep == 'O')
        {
            chargerEnseignants();
            chargerDepartements();
            chargerDiplomes();
            chargerSemestres();
            chargerUEs();
            chargerInterventions();
            chargerInscriptions();

            cout << endl;
            system("pause");
            cout << "\n\nDonnees chargees avec succes.\n";
        }
    }
    else
    {
        // Aucun fichier trouvé
        cout << "\nAucune donnee sauvegardee trouvee.\n";
        cout << "\nDemarrage avec une application vide.\n";
    }

    // Accès au menu principal
    menuPrincipal();
}

// --------------------- MENU PRINCIPAL ------------------------
void Application::menuPrincipal()
{
    int choix;

    do
    {
        system("cls");
        cout << jaune("============================================\n");
        cout << jaune("    GESTION DES ENSEIGNEMENTS DE LA FST\n");
        cout << jaune("============================================\n\n");

        // Options principales
        cout << "1. Gestion des enseignants\n";
        cout << "2. Gestion des departements\n";
        cout << "3. Gestion des UEs\n";
        cout << "4. Gestion des interventions et inscriptions\n";
        cout << "5. Gestion des semestres et diplomes\n";
        cout << "6. Sauvegarder les Donnees\n";
        cout << "7. Reinitialiser l'application\n";
        cout << "0. Quitter\n\n";

        cout << "Choix : ";
        cin >> choix;
        system("cls");

        // Redirection selon le choix
        switch (choix)
        {
        case 1: menuEnseignants(); break;
        case 2: menuDepartement(); break;
        case 3: menuUE(); break;
        case 4: menuInterventions_Inscriptions(); break;
        case 5: menuSemestresDiplomes(); break;
        case 6: sauvegarderToutesLesDonnees(); break;

        case 7:
        {
            // Confirmation avant suppression
            char rep;
            cout << "\nATTENTION : toutes les donnees seront SUPPRIMEES.\n";
            cout << "Confirmer ? (o/n) : ";
            cin >> rep;

            if (rep == 'o' || rep == 'O')
            {
                viderToutesLesDonnees();
                supprimerFichiersDonnees();
                cout << "\nReinitialisation complete.\n";
            }
            else
            {
                cout << "\nOperation annulee.\n";
            }

            system("pause");
            break;
        }

        case 0:
            cout << "Au revoir \n";
            break;

        default:
            cout << "\nChoix invalide !\n";
        }

    } while (choix != 0);

    // Proposition de sauvegarde avant quitter
    char rep;
    cout << "\nSauvegarder avant de quitter ? (o/n) : ";
    cin >> rep;
    if (rep == 'o' || rep == 'O')
        sauvegarderToutesLesDonnees();
}

// ------------------- SAUVEGARDE -----------------------
// Sauvegarde toutes les listes dans les fichiers
void Application::sauvegarderToutesLesDonnees()
{
    sauvegarderEnseignants();
    sauvegarderDepartements();
    sauvegarderUEs();
    sauvegarderInterventions();
    sauvegarderInscriptions();
    sauvegarderSemestres();
    sauvegarderDiplomes();

    cout << "\nToutes les donnees ont ete sauvegardees.\n\n";
    system("pause");
}

// ---------------------- SUPPRESSION DES FICHIERS ------------------------
void Application::supprimerFichiersDonnees()
{
    // Liste des fichiers de données
    const char* fichiers[] =
    {
        "data/enseignants.txt",
        "data/departements.txt",
        "data/ues.txt",
        "data/interventions.txt",
        "data/inscriptions.txt",
        "data/semestres.txt",
        "data/diplomes.txt"
    };

    // Suppression de chaque fichier
    for (const char* f : fichiers)
    {
        remove(f);
    }

    cout << "Tous les fichiers de donnees ont ete supprimes.\n";
}

// -------------------- NETTOYAGE MEMOIRE ---------------------------
// Libération de la mémoire dynamique
void Application::viderToutesLesDonnees()
{
    for (Enseignant* e : ListeEnseignant) delete e;
    for (Departement* d : ListeDepartement) delete d;
    for (UE* ue : ListeUE) delete ue;
    for (Intervention* i : ListeIntervention) delete i;
    for (Inscription* i : ListeInscription) delete i;
    for (Semestre* s : ListeSemestre) delete s;
    for (Diplome* d : ListeDiplome) delete d;

    // Vidage des listes
    ListeEnseignant.clear();
    ListeDepartement.clear();
    ListeUE.clear();
    ListeIntervention.clear();
    ListeInscription.clear();
    ListeSemestre.clear();
    ListeDiplome.clear();

    cout << "\nToutes les donnees en memoire ont ete supprimees.\n";
}

// ---------------------- GESTION DES ENSEIGNANTS ---------------------
// Menu dédié aux enseignants
void Application::menuEnseignants()
{
    int choix;
    string id;

    do
    {
        system("cls");
        cout << jaune("\n========== GESTION DES ENSEIGNANTS ==========\n\n");
        cout << "1. Ajouter un enseignant\n";
        cout << "2. Afficher les enseignants\n";
        cout << "3. Consulter la charge horaire d'un enseignant\n";
        cout << "4. Rechercher un enseignant\n";
        cout << "5. Actions sur un enseignant\n";
        cout << "0. Retour\n\n";

        cout << "Choix : ";
        cin >> choix;

        // Gestion des erreurs de saisie
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nChoix invalide ! Veuillez entrer un nombre.\n";
            continue;
        }

        system("cls");

        // Traitement du choix
        switch (choix)
        {
            case 1: ajouterEnseignant(); system("pause"); break;
            case 2: afficherEnseignants(); system("pause"); break;

            case 3:
            {
                cout << "ID enseignant : ";
                cin >> id;
                Enseignant* e = rechercherEnseignant(id);
                if (e)
                    cout << jaune("\nCharge horaire : ") << e->chargeHoraireEnseignant(id) << "\n\n";
                else
                    cout << "\nEnseignant introuvable.\n\n";
                system("pause");
                break;
            }

            case 4:
            {
                cout << "ID enseignant : ";
                cin >> id;
                Enseignant* e = rechercherEnseignant(id);
                if (e)
                    e->AfficherEnseignant();
                else
                    cout << "\nEnseignant introuvable.\n\n";
                system("pause");
                break;
            }

            case 5:
                cout << "ID enseignant : "; 
                cin >> id;
                menuActionsEnseignant(id);
                break;

            case 0:
                break;

            default:
                cout << "\nChoix invalide !\n";
        }

    } while (choix != 0);
}

// ------------------------ ACTIONS SUR UN ENSEIGNANT -----------------------
void Application::menuActionsEnseignant(const string& id)
{
    system("cls");

    // Recherche de l'enseignant par son ID
    Enseignant* e = rechercherEnseignant(id);
    if (!e)
    {
        cout << "\nEnseignant introuvable.\n\n";
        return;
    }

    int choix;
    do
    {
        system("cls");
        cout << jaune("\n===== ACTIONS ENSEIGNANT =====\n\n");
        cout << "1. Rattacher a un departement\n";
        cout << "2. Ajouter une UE au responsable\n";
        cout << "3. Ajouter une intervention\n";
        cout << "4. Ajouter un departement a gere\n";
        cout << "0. Retour\n\n";

        cout << "Choix : ";
        cin >> choix;

        // Vérification de la saisie
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nChoix invalide ! Veuillez entrer un nombre.\n";
            continue;
        }

        system("cls");
        switch (choix)
        {
            case 1: // Rattachement à un département
            {
                string idDep;
                cout << "ID du departement : ";
                cin >> idDep;

                Departement* d = rechercherDepartement(idDep);  
                if (!d)
                {
                    cout << "\nDepartement introuvable.\n\n";
                    break;
                }

                e->rattacherDepartement(d);
                cout << "\nDepartement rattache avec succes.\n\n";
                system("pause");
                break;
            }

            case 2: // Ajout d'une UE responsable
            {
                string idUE;
                cout << "ID de l'UE : ";
                cin >> idUE;

                UE* ue = rechercherUE(idUE);
                if (!ue)
                {
                    cout << "\nUE introuvable.\n\n";
                    break;
                }

                e->ajouterUEResponsable(ue);
                cout << "\nUE ajoutee au responsable.\n\n";
                system("pause");
                break;
            }

            case 3: // Ajout d'une intervention existante
            {
                string idInter;
                cout << "ID de l'intervention : ";
                cin >> idInter;

                Intervention* i = rechercherIntervention(idInter);
                if (!i)
                {
                    cout << "\nIntervention introuvable.\n\n";
                    break;
                }

                e->ajouterIntervention(i);
                cout << "\nIntervention ajoutee.\n\n";
                system("pause");
                break;
            }

            case 4: // Ajout d'un département géré
            {
                string idDep;
                cout << "ID du departement : ";
                cin >> idDep;

                Departement* d = rechercherDepartement(idDep);
                if (!d)
                {
                    cout << "\nDepartement introuvable.\n\n";
                    break;
                }

                e->ajouterDepartementGere(d);
                cout << "\nDepartement ajoute comme gere.\n\n";
                system("pause");
                break;
            }

            case 0:
                break;

            default:
                cout << "\nChoix invalide !\n";
        }

    } while (choix != 0);
}

// ------------------------- GESTION DES DEPARTEMENTS ---------------------------
void Application::menuDepartement()
{
    int choix;
    do
    {
        system("cls");
        cout << jaune("\n======= GESTION DES DEPARTEMENTS =======\n\n");
        cout << "1. Ajouter un departement\n";
        cout << "2. Afficher les departements\n";
        cout << "3. Rechercher un departement\n";
        cout << "4. Consulter la charge d'un departement\n";
        cout << "5. Consulter le taux d'encadrement\n"; 
        cout << "0. Retour\n\n";

        cout << "Choix : ";
        cin >> choix;
        system("cls");

        switch (choix)
        {
            case 1:
                ajouterDepartement();
                system("pause");
                break;

            case 2:
                afficherDepartements();
                system("pause");
                break;

            case 3: // Recherche d'un département
            {
                string id;
                cout << "ID Departement : ";
                cin >> id;

                Departement* d = rechercherDepartement(id);
                if (d)
                    d->AfficherDepartement();
                else
                    cout << "\nDepartement introuvable.\n\n";

                system("pause");    
                break;
            }

            case 4: // Charge horaire d'un département
            {
                string id;
                cout << "ID Departement : ";
                cin >> id;

                Departement* d = rechercherDepartement(id);
                if (d)
                    cout << jaune("\nCharge Horaire du departement : ")
                         << d->chargeHoraireDepartement(d->getNom_departement())
                         << " heures\n\n";
                else
                    cout << "\nDepartement introuvable.\n\n";

                system("pause");    
                break;
            }

            case 5: // Taux d'encadrement
            {
                string idDep;
                cout << "ID du departement : ";
                cin >> idDep;

                Departement* d = rechercherDepartement(idDep);
                if (!d)
                {
                    cout << "\nDepartement introuvable.\n\n";
                    break;
                }

                float taux = d->tauxEncadrementDep(d->getNom_departement());
                cout << jaune("\nTaux d'encadrement du departement: ")
                     << taux * 100 << " %\n\n";

                system("pause");
                break;
            }

            case 0:
                break;

            default:
                cout << "\nChoix invalide !\n";
                cin.clear();
                cin.ignore(10000, '\n');
        }

    } while (choix != 0);
}


// ----------------- SAISIE D'UN ENTIER POSITIF ------------------
/* Fonction utilitaire :
 - Demande un entier positif à l'utilisateur
 - Autorise 3 tentatives maximum
 - Lance une exception après 3 erreurs
*/
int saisirEntierPositif(const string& message)
{
    int valeur;
    int essais = 0;

    while (essais < 3)
    {
        cout << message;
        cin >> valeur;

        // Erreur de saisie (lettre, symbole, etc.)
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nSaisie invalide. Entrez un nombre !\n";
            essais++;
        }
        // Valeur négative interdite
        else if (valeur < 0)
        {
            cout << "\nValeur negative interdite !\n";
            essais++;
        }
        // Saisie valide
        else
        {
            cin.ignore(10000, '\n');
            return valeur;
        }
    }

    // Trop de tentatives
    throw runtime_error("\nNombre maximum d'essais depasse !\n");
}

// ======================= GESTION DES UES =======================
void Application::menuUE()
{
    int choix;
    string id;

    do
    {
        system("cls");
        cout << jaune("\n======== GESTION DES UES ========\n\n");
        cout << "1. Ajouter une UE\n";
        cout << "2. Afficher toutes les UE\n";
        cout << "3. Rechercher une UE\n";
        cout << "4. Consulter le total d'heures (ETD) d'une UE\n";
        cout << "0. Retour\n\n";

        cout << "Choix : ";
        cin >> choix;

        // Vérification de la saisie utilisateur
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nChoix invalide ! Veuillez entrer un nombre !\n";
            system("pause");
            continue;
        }

            system("cls");
        switch(choix)
        {
            case 1: // Ajout d'une UE
            {
                try
                {
                    string nomUE, descUE, idDep, idResp;

                    // Saisie du nom de l'UE
                    cout << "Nom de l'UE : ";
                    cin >> ws;
                    getline(cin, nomUE);

                    // Saisie de la description
                    cout << "Description de l'UE : ";
                    getline(cin, descUE);

                    // Saisie contrôlée des heures
                    int hCours   = saisirEntierPositif("Nombre d'heures de cours : ");
                    int hTD      = saisirEntierPositif("Nombre d'heures de TD : ");
                    int hTP      = saisirEntierPositif("Nombre d'heures de TP : ");

                    // Saisie du nombre de groupes
                    int nbGCours = saisirEntierPositif("Nombre de groupes Cours : ");
                    int nbGTD    = saisirEntierPositif("Nombre de groupes TD : ");
                    int nbGTP    = saisirEntierPositif("Nombre de groupes TP : ");

                    // Rattachement au département
                    cout << "ID du departement : ";
                    cin >> idDep;

                    Departement* d = rechercherDepartement(idDep);
                    if (!d)
                    {
                        cout << "\nDepartement introuvable. UE non creee.\n\n";
                        system("pause");
                        break;
                    }

                    // Désignation de l'enseignant responsable
                    cout << "ID de l'enseignant responsable: ";
                    cin >> idResp;

                    Enseignant *ens = rechercherEnseignant(idResp);
                    if(!ens)
                    {
                        cout << "\nEnseignant Responsable introuvable. UE non creee\n\n";
                        system("pause");
                        break;
                    }

                    // Création de l'UE
                    UE* ue = new UE(
                        nomUE, descUE,
                        hCours, hTD, hTP,
                        nbGCours, nbGTD, nbGTP,
                        d, ens
                    );

                    cout << "UE ajoutee avec succes !\n\n";
                }
                catch (const exception& e)
                {
                    // Gestion des erreurs (saisie ou logique)
                    cout << "ERREUR : " << e.what() << "\n";
                }

                system("pause");
                break;
            }

            case 2: // Affichage de toutes les UE
                AfficherUEs();
                system("pause");
                break;

            case 3: // Recherche d'une UE par ID
                cout << "ID de l'UE : ";
                cin >> id;
                {
                    UE* ue = rechercherUE(id);
                    if(ue)
                        ue->AfficherUE();
                    else
                        cout << "\nUE introuvable.\n\n";
                }
                system("pause");
                break;

            case 4: // Calcul et affichage du total d'heures ETD
                cout << "ID de l'UE : ";
                cin >> id;
                {
                    UE* ue = rechercherUE(id);
                    if(ue)
                        cout << jaune("\nTotal d'heures (ETD) : ")
                             << ue->calculETD() << " h\n";
                    else
                        cout << "\nUE introuvable.\n\n";
                }
                system("pause");
                break;

            case 0: // Retour au menu principal
                break;

            default:
                cout << "Choix invalide !\n";
                system("pause");
        }

    } while(choix != 0);
}


// --------------------- SAISIE DES HEURES D'INTERVENTION -------------------------
/* Vérifie que les heures saisies :
 - ne sont pas négatives
 - ne dépassent pas les heures restantes de l'UE
 - max 3 tentatives
*/
int saisirHeuresInterv(const string& message, int max)
{
    int valeur;
    int essais = 0;

    while (true)
    {
        cout << message;
        cin >> valeur;

        // Erreur de saisie
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nSaisie invalide. Entrez un nombre !\n";
            continue;
        }

        // Valeur négative
        if (valeur < 0)
        {
            cout << "\nValeur negative interdite !\n";
            essais++;
        }
        // Dépassement des heures disponibles
        else if (valeur > max)
        {
            cout << "\nDepassement ! Maximum possible : " << max << " heures !\n";
            essais++;
        }
        // Saisie valide
        else
        {
            return valeur;
        }

        // Trop de tentatives
        if (essais >= 3)
        {
            throw runtime_error("\nTrop de tentatives invalides. Abandon de l'operation !\n");
        }
    }
}

// ------------------- GESTION DES INTERVENTIONS & INSCRIPTIONS -----------------------
void Application::menuInterventions_Inscriptions()
{
    int choix;
    string id;
    Intervention* i = nullptr;

    do
    {
        system("cls");

        cout << jaune("\n==== GESTION DES INTERVENTIONS & INSCRIPTIONS ====\n\n");
        cout << "1. Ajouter une intervention\n";
        cout << "2. Afficher toutes les interventions\n";
        cout << "3. Ajouter une inscription\n";
        cout << "4. Afficher toutes les inscriptions\n";
        cout << "0. Retour\n\n";
        cout << "Choix : ";
        cin >> choix;

        // Vérification de la saisie
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nChoix invalide ! Veuillez entrer un nombre !\n";
            system("pause");
            continue;
        }

        system("cls");
        switch (choix)
        {
            case 1: // Ajout d'une intervention
            {
                try
                {
                    // Recherche enseignant
                    string idEns, idUE;
                    cout << "ID de l'enseignant : ";
                    cin >> idEns;
                    Enseignant* e = rechercherEnseignant(idEns);
                    if(!e) throw runtime_error("\nEnseignant introuvable !\n\n");

                    // Recherche UE
                    cout << "ID de l'UE : ";
                    cin >> idUE;
                    UE* ue = rechercherUE(idUE);
                    if(!ue) throw runtime_error("\nUE introuvable !\n\n");

                    // Calcul des heures restantes
                    int resteCours = ue->getNbHCours() - ue->heuresCoursAffectees();
                    int resteTD    = ue->getNbHTd() - ue->heuresTdAffectees();
                    int resteTP    = ue->getNbHTp() - ue->heuresTpAffectees();

                    // Vérifie s'il reste des heures
                    if (resteCours <= 0 && resteTD <= 0 && resteTP <= 0)
                    {
                        cout << "\nToutes les heures de cette UE ont deja ete affectees !\n";
                        system("pause");
                        break;
                    }

                    int hCours = 0, hTD = 0, hTP = 0;

                    // Saisie contrôlée des heures
                    if (resteCours > 0)
                        hCours = saisirHeuresInterv("Nombre d'heures de cours (max " + to_string(resteCours) + ") : ", resteCours);
                    else
                        cout << "Aucune heure de cours disponible pour cette UE.\n";

                    if (resteTD > 0)
                        hTD = saisirHeuresInterv("Nombre d'heures de TD (max " + to_string(resteTD) + ") : ", resteTD);
                    else
                        cout << "Aucune heure de TD disponible pour cette UE.\n";

                    if (resteTP > 0)
                        hTP = saisirHeuresInterv("Nombre d'heures de TP (max " + to_string(resteTP) + ") : ", resteTP);
                    else
                        cout << "Aucune heure de TP disponible pour cette UE.\n";

                    // Création de l'intervention
                    Intervention* i = new Intervention(e, ue, hCours, hTD, hTP);
                    cout << "Intervention ajoutee avec succes !\n";
                }
                catch (const exception& ex)
                {
                    cout << "ERREUR : " << ex.what() << endl;
                }

                system("pause");
                break;
            }

            case 2: // Affichage des interventions
                afficherInterventions();
                system("pause");
                break;

            case 3: // Ajout d'une inscription
            {
                try
                {
                    string idUE, id_semestre;

                    cout << "ID UE : ";
                    cin >> idUE;
                    UE* ue = rechercherUE(idUE);
                    if(!ue) throw runtime_error("\nUE introuvable !\n\n");

                    cout << "ID du semestre : ";
                    cin >> id_semestre;
                    Semestre* s = rechercherSemestre(id_semestre);
                    if(!s) throw runtime_error("\nSemestre introuvable !\n\n");

                    int nb_i = saisirEntierPositif("Nombre d'inscrits : ");
                    Inscription* insc = new Inscription(nb_i, ue, s);
                    cout << "Inscription ajoutee avec succes.\n";
                }
                catch(const exception& ex)
                {
                    cout << "ERREUR : " << ex.what() << endl;
                }

                system("pause");
                break;
            }

            case 4: // Affichage des inscriptions
                afficherInscriptions();
                system("pause");
                break;

            case 0:
                break;

            default:
                cout << "Choix invalide !\n";
                cin.clear();
                cin.ignore(10000, '\n');
                system("pause");
        }

    } while (choix != 0);
}

// ------------------- GESTION DES SEMESTRES ET DIPLOMES ---------------------
void Application::menuSemestresDiplomes()
{
    system("cls");
    int choix;
    string id;

    do
    {
        system("cls");
        cout << jaune("\n===== GESTION DES SEMESTRES & DIPLOMES =====\n\n");
        cout << "1. Ajouter un diplome\n";
        cout << "2. Ajouter un semestre a un diplome\n";
        cout << "3. Afficher les diplomes\n";
        cout << "4. Afficher les semestres\n";
        cout << "5. Consulter le cout d'un diplome\n";
        cout << "0. Retour\n\n";
        cout << "Choix : ";
        cin >> choix;

        system("cls");
        // Vérification de la saisie
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nChoix invalide ! Veuillez entrer un nombre.\n";
            system("pause");
            continue;
        }

        switch (choix)
        {
        
            case 1:
                ajouterDiplome();
                system("pause");
                break;

            case 2:
                ajouterSemestre();
                system("pause");
                break;

            case 3:
                afficherDiplomes();
                system("pause");
                break;

            case 4:
                afficherSemestres();
                system("pause");
                break;

            case 5: // Calcul du coût d'un diplôme
            {
                cout << "ID Diplome : ";
                cin >> id;

                Diplome* d = rechercherDiplome(id);
                if (!d)
                {
                    cout << "Diplome introuvable !\n\n";
                    break;
                }

                cout << "Cout du diplome : "
                     << d->coutDiplome(d->getNomDiplome())
                     << " h ETD\n";

                system("pause");
                break;
            }

            case 0:
                break;

            default:
                cout << "Choix invalide !\n";
                cin.clear();
                cin.ignore(10000, '\n');
                system("pause");
        }

    } while (choix != 0);
}
