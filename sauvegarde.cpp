#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Enseignant.h"
#include "Departement.h"
#include "UE.h"
#include "gestion_liste.h"

using namespace std;




// OUTILS
// test si un fichier existe et n'est pas vide
bool fichierExisteEtNonVide(const string& nomFichier)
{
    ifstream f(nomFichier);
    return f.good() && f.peek() != ifstream::traits_type::eof();
}


// Split une chaine de caracteres selon un delimiteur
static vector<string> split(const string& s, char delim)
{
    vector<string> elems;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}


static string trim(const string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}





// SAUVEGARDE ET CHARGEMENT DES ENSEIGNANTS
void sauvegarderEnseignants()
{
    ofstream f("data/enseignants.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/enseignants.txt\n";
        cout << "Verifiez que le dossier 'data' existe.\n";
        return;
    }

    for (Enseignant* e : ListeEnseignant)
    {
        if (!e) continue;

        if (auto* ec = dynamic_cast<EnseignantChercheurs*>(e))
        {
            f << e->getId() << "|CHERCHEUR|"
              << e->getNom() << "|"
              << e->getPrenom() << "|"
              << e->getAdresse() << "|"
              << e->getEmail() << "|"
              << (ec->getTypeE() == TypeEnseignantCherc::MC ? "MC" : "PR") << "|"
              << ec->getSujet_recherche() << "\n";
        }
        else
        {
            f << e->getId() << "|AUTRE|"
              << e->getNom() << "|"
              << e->getPrenom() << "|"
              << e->getAdresse() << "|"
              << e->getEmail() << "\n";
        }
    }

    cout << "Sauvegarde des enseignants terminee.\n";
}


// CHARGEMENT DES ENSEIGNANTS
void chargerEnseignants()
{
    ifstream f("data/enseignants.txt");
    if (!f)
    {
        cout << "Aucun fichier enseignants.txt trouve.\n";
        return;
    }

    ListeEnseignant.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() < 6) continue;

        string id = p[0];
        string type = p[1];
        string nom = p[2];
        string prenom = p[3];
        string adresse = p[4];
        string email = p[5];

        int numID = extraireNumeroID(id);
        if (numID > Enseignant::compteurID)
            Enseignant::compteurID = numID;

        if (type == "CHERCHEUR" && p.size() >= 8)
        {
            TypeEnseignantCherc t =
                (p[6] == "MC") ? TypeEnseignantCherc::MC : TypeEnseignantCherc::PR;

            string sujet = p[7];

            new EnseignantChercheurs(
                nom, prenom, adresse, t, sujet, email, id
            );
        }
        else
        {
            new AutreEnseignant(
                nom, prenom, adresse, email, id
            );
        }
    }

    cout << "Chargement des enseignants termine.\n";
}

//SAUVEGARDE ET CHARGEMENT DES DEPARTEMENTS
void sauvegarderDepartements()
{
    ofstream f("data/departements.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/departements.txt\n";
        return;
    }

    for (Departement* d : ListeDepartement)
    {
        if (!d) continue;

        f << d->getId_departement() << "|"
          << d->getNom_departement() << "|";

        // Responsable
        Enseignant* resp = d->getResponsable();
        if (resp)
            f << resp->getId();
        f << "|";

        // Liste enseignants
        bool first = true;
        for (Enseignant* e : d->getEnseignants())
        {
            if (!e) continue;
            if (!first) f << ",";
            f << e->getId();
            first = false;
        }

        f << "\n";
    }

    cout << "Sauvegarde des departements terminee.\n";
}

void chargerDepartements()
{
    // Ouverture du fichier de sauvegarde des departements
    ifstream f("data/departements.txt");
    if (!f)
    {
        cout << "Aucun fichier departements.txt trouve.\n";
        return;
    }

    // Nettoyage de la liste avant chargement
    ListeDepartement.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;

        // Decoupage de la ligne selon le separateur '|'
        auto p = split(line, '|');
        if (p.size() < 3)
            continue;

        // Lecture et nettoyage des champs
        string idDep    = trim(p[0]);
        string nomDep   = trim(p[1]);
        string idResp   = trim(p[2]);
        string listeEns = (p.size() > 3 ? trim(p[3]) : "");

        // Recherche de l'enseignant responsable
        Enseignant* resp = rechercherEnseignant(idResp);
        if (!resp)
        {
            cout << "Responsable introuvable pour departement " << idDep << "\n";
            continue;
        }

        // Creation du departement a partir des donnees chargees
        Departement* d = new Departement(nomDep, resp, idDep);

        // Rattachement des enseignants au departement
        if (!listeEns.empty())
        {
            auto ids = split(listeEns, ',');
            for (string idE : ids)
            {
                idE = trim(idE);
                Enseignant* e = rechercherEnseignant(idE);
                if (e)
                    e->rattacherDepartement(d);
            }
        }
    }

    cout << "Chargement des departements termine.\n";
}

//SAUVEGARDE ET CHARGEMENT DES UES

void sauvegarderUEs()
{
    ofstream f("data/ues.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/ues.txt\n";
        return;
    }

    for (UE* ue : ListeUE)
    {
        if (!ue) continue;

        f << ue->getIdUE() << "|"
          << ue->getNomUE() << "|"
          << ue->getDescriptionUE() << "|"
          << ue->getNbHCours() << "|"
          << ue->getNbHTd() << "|"
          << ue->getNbHTp() << "|"
          << ue->getNbGCours() << "|"
          << ue->getNbGTd() << "|"
          << ue->getNbGTp() << "|"
          << ue->getDepartement()->getId_departement() << "|";

        if (ue->getResponsable())
            f << ue->getResponsable()->getId();

        f << "\n";
    }

    cout << "Sauvegarde des UE terminee.\n";
}

void chargerUEs()
{
    ifstream f("data/ues.txt");
    if (!f)
    {
        cout << "Aucun fichier ues.txt trouve.\n";
        return;
    }

    ListeUE.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;

        auto p = split(line, '|');
        if (p.size() < 11)   
            continue;

        string id   = trim(p[0]);
        string nom  = trim(p[1]);
        string desc = trim(p[2]);

        int nbHc  = stoi(trim(p[3]));
        int nbHtd = stoi(trim(p[4]));
        int nbHtp = stoi(trim(p[5]));

        int nbGc  = stoi(trim(p[6]));
        int nbGtd = stoi(trim(p[7]));
        int nbGtp = stoi(trim(p[8]));

        string idDep  = trim(p[9]);
        string idResp = trim(p[10]);

        // Recherche du departement
        Departement* dep = rechercherDepartement(idDep);
        if (!dep)
        {
            cout << "Departement introuvable pour UE " << id << "\n";
            continue;
        }

        // Recherche du responsable
        Enseignant* resp = rechercherEnseignant(idResp);
        if (!resp)
        {
            cout << "Responsable introuvable pour UE " << id << "\n";
            continue;
        }

        // Creation de l'UE
        new UE(
            nom, desc,
            nbHc, nbHtd, nbHtp,
            nbGc, nbGtd, nbGtp,
            dep,
            resp,
            id
             
        );
    }

    cout << "Chargement des UE termine.\n";
}

//SAUVEGARDE ET CHARGEMENT DES INTERVENTIONS
void sauvegarderInterventions()
{
    ofstream f("data/interventions.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/interventions.txt\n";
        return;
    }

    for (Intervention* i : ListeIntervention)
    {
        if (!i) continue;

        Enseignant* e = i->getEnseignant();
        UE* u = i->getUE();
        if (!e || !u) continue;

        f << i->getId_intervention() << "|"
          << e->getId() << "|"
          << u->getIdUE() << "|"
          << i->getNbH_cours_intr() << "|"
          << i->getNbH_td_intr() << "|"
          << i->getNbH_tp_intr() << "\n";
    }

    cout << "Sauvegarde des interventions terminee.\n";
}

void chargerInterventions()
{
    ifstream f("data/interventions.txt");
    if (!f)
    {
        cout << "Aucun fichier interventions.txt trouve.\n";
        return;
    }

    ListeIntervention.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() < 6) continue;

        string idInt = trim(p[0]);
        string idEns = trim(p[1]);
        string idUE  = trim(p[2]);

        int hC  = stoi(trim(p[3]));
        int hTD = stoi(trim(p[4]));
        int hTP = stoi(trim(p[5]));

        Enseignant* e = rechercherEnseignant(idEns);
        UE* u = rechercherUE(idUE);

        if (!e || !u)
        {
            cout << "Intervention " << idInt << " ignoree (enseignant ou UE introuvable).\n";
            continue;
        }

        new Intervention(e, u, hC, hTD, hTP, idInt);
    }

    cout << "Chargement des interventions termine.\n";
}

//SAUVEGARDE ET CHARGEMENT DES semestres
void sauvegarderSemestres()
{
    ofstream f("data/semestres.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/semestres.txt\n";
        return;
    }

    for (Semestre* s : ListeSemestre)
    {
        if (!s || !s->getDiplome()) continue;

        f << s->getId_semestre() << "|"
          << s->getNom_semestre() << "|"
          << s->getDiplome()->getIdDiplome() << "\n";
    }

    cout << "Sauvegarde des semestres terminee.\n";
}

void chargerSemestres()
{
    ifstream f("data/semestres.txt");
    if (!f)
    {
        cout << "Aucun fichier semestres.txt trouve.\n";
        return;
    }

    ListeSemestre.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() < 3) continue;

        string id     = trim(p[0]);
        string nom    = trim(p[1]);
        string idDip  = trim(p[2]);

        Diplome* d = rechercherDiplome(idDip);
        if (!d)
        {
            cout << "Diplome introuvable pour semestre " << id << "\n";
            continue;
        }

        new Semestre(nom, d, id);
    }

    cout << "Chargement des semestres termine.\n";
}


//SAUVEGARDE ET CHARGEMENT DES INSCRIPTIONS
void sauvegarderInscriptions()
{
    ofstream f("data/inscriptions.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/inscriptions.txt\n";
        return;
    }

    for (Inscription* i : ListeInscription)
    {
        if (!i) continue;

        f << i->getId_inscription() << "|"
          << i->getUE()->getIdUE() << "|"
          << i->getSemestre()->getId_semestre() << "|"
          << i->getNbInscrit() << "\n";
    }

    cout << "Sauvegarde des inscriptions terminee.\n";
}

void chargerInscriptions()
{
    ifstream f("data/inscriptions.txt");
    if (!f)
    {
        cout << "Aucun fichier inscriptions.txt trouve.\n";
        return;
    }

    ListeInscription.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() < 4) continue;

        string idIns = trim(p[0]);
        string idUE  = trim(p[1]);
        string idSem = trim(p[2]);
        int nb       = stoi(trim(p[3]));

        UE* u = rechercherUE(idUE);
        Semestre* s = rechercherSemestre(idSem);

        if (!u || !s)
        {
            cout << "Inscription ignoree (" << idIns << ") : UE ou semestre introuvable\n";
            continue;
        }

        new Inscription(nb, u, s, idIns);
    }

    cout << "Chargement des inscriptions termine.\n";
}

//SAUVEGARDE ET CHARGEMENT DES DIPLOMES
void sauvegarderDiplomes()
{
    ofstream f("data/diplomes.txt");
    if (!f)
    {
        cout << "Erreur ouverture fichier data/diplomes.txt\n";
        return;
    }

    for (Diplome* d : ListeDiplome)
    {
        if (!d) continue;

        f << d->getIdDiplome() << "|"
          << d->getNomDiplome() << "|";

        bool first = true;
        for (Semestre* s : d->getSemestres())
        {
            if (!first) f << ",";
            f << s->getId_semestre();
            first = false;
        }

        f << "\n";
    }

    cout << "Sauvegarde des diplomes terminee.\n";
}

void chargerDiplomes()
{
    ifstream f("data/diplomes.txt");
    if (!f)
    {
        cout << "Aucun fichier diplomes.txt trouve.\n";
        return;
    }

    ListeDiplome.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() < 3) continue;

        string id  = trim(p[0]);
        string nom = trim(p[1]);
        string sems = trim(p[2]);

        Diplome* d = new Diplome(nom, id);

        auto ids = split(sems, ',');
        for (string idSem : ids)
        {
            Semestre* s = rechercherSemestre(trim(idSem));
            if (s)
                d->ajouterSemestre(s);
        }
    }

    cout << "Chargement des diplomes termine.\n";
}





