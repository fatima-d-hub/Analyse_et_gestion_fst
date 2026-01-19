#ifndef APPLICATION_H
#define APPLICATION_H

// Classe principale de l'application
// Elle centralise tous les menus et la logique globale du programme
class Application
{
public:
    // Lance l'application
    void lancer();

private:
    // Menu principal de l'application
    void menuPrincipal();

    // Menu de gestion des enseignants
    void menuEnseignants();

    // Menu d'actions spécifiques pour un enseignant donné (via son ID)
    void menuActionsEnseignant(const string& id);

    // Menu de gestion des départements
    void menuDepartement();

    // Menu de gestion des Unités d'Enseignement (UE)
    void menuUE();

    // Menu de gestion des interventions et des inscriptions
    void menuInterventions_Inscriptions();

    // Menu de gestion des semestres et des diplômes
    void menuSemestresDiplomes();

    // Sauvegarde toutes les données de l'application dans des fichiers
    void sauvegarderToutesLesDonnees();

    // Vide toutes les données en mémoire
    void viderToutesLesDonnees();

    // Supprime les fichiers de sauvegarde existants
    void supprimerFichiersDonnees();
};

#endif
