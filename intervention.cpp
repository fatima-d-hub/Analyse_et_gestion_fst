#include "intervention.h"
#include "enseignant.h"
#include "UE.h"
#include "gestion_liste.h"

#include <sstream>
#include <iomanip>

using namespace std;

int Intervention::compteurID = 0;

static int extraireNumeroIDIntervention(const string& id)
{
    // "INT012" -> 12
    if (id.size() <= 3) return 0;
    return stoi(id.substr(3));
}

Intervention::Intervention(Enseignant* e, UE* u, int nbHc, int nbHtd, int nbHtp, string id)
{
    if (!e || !u) return;

    if (id.empty())
    {
        compteurID++;
        ostringstream oss;
        oss << "INT" << setw(3) << setfill('0') << compteurID;
        Id_intervention = oss.str();
    }
    else
    {
        Id_intervention = id;
        int num = extraireNumeroIDIntervention(id);
        if (num > compteurID) compteurID = num;
    }

    nbH_cours_intr = nbHc;
    nbH_td_intr    = nbHtd;
    nbH_tp_intr    = nbHtp;

    enseignant = e;
    ue = u;

    e->ajouterIntervention(this);
    u->ajouterIntervention(this);

    ListeIntervention.push_back(this);
}



//Setteurs
void Intervention::setNbH_cours_intr(int nbHc)
{
    nbH_cours_intr = nbHc;
}

void Intervention::setNbH_td_intr(int nbHtd)
{
    nbH_td_intr = nbHtd;
}

void Intervention::setNbH_tp_intr(int nbHtp)
{
    nbH_tp_intr = nbHtp;
}

//Getteurs
string Intervention::getId_intervention()const
{
    return Id_intervention;
}

int Intervention::getNbH_cours_intr()const
{
    return nbH_cours_intr;
}

int Intervention::getNbH_td_intr()const
{
    return nbH_td_intr;
}

int Intervention::getNbH_tp_intr()const
{
    return nbH_tp_intr;
}

UE* Intervention::getUE() const
{
    return ue;
}

Enseignant* Intervention::getEnseignant() const
{
    return enseignant;
}



void Intervention::AfficherIntervention()
{
    cout << bleu("----------------------------------") << "\n";
    cout << cyan(" INTERVENTION " + Id_intervention) << "\n";
    cout << bleu("----------------------------------") << "\n";

    cout << jaune(" Enseignant :") << " " << enseignant->getNom() << "\n";
  
    cout << jaune(" UE :") << " " << ue->getNomUE() << "\n";

    cout << jaune(" Heures :") << " "
         << nbH_cours_intr << "h C, "
         << nbH_td_intr << "h TD, "
         << nbH_tp_intr << "h TP\n";

    cout << "\n";
}


void afficherInterventions()
{
    if (ListeIntervention.empty())
    {
        cout << "\nAucune intervention enregistree.\n\n";
        return;
    }

    list<Intervention*>::iterator it;

    for (it = ListeIntervention.begin(); it != ListeIntervention.end(); ++it)
    {
        (*it)->AfficherIntervention();
    }
}