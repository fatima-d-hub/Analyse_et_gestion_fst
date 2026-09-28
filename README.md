# 🎓 PROJET - Système de Gestion de Scolarité & Pilotage Académique

**Licence Informatique 3ème année – UE Analyse et Programmation Orientées Objets / C++**  
**Année : 2025-2026**

Ce projet consiste à créer une application C++ dans le cadre de l’UE Analyse et Programmation Orientées Objets.
Il a pour objectif de développer un mini logiciel de gestion pédagogique et administrative d’une faculté, de la phase d’analyse UML à l’implémentation en C++.

---

## Objectif du projet

Le logiciel centralise la gestion des enseignements à la Faculté des Sciences et Techniques :

- **Hiérarchie des enseignements** : Diplôme ➔ Semestre ➔ Unité d’Enseignement (UE)  
- **Suivi des enseignants** : statuts, charges horaires, interventions  
- **Calcul des coûts** : heures ETD, coûts horaires des diplômes  
- **Statistiques par département** : taux d’encadrement, charge horaire totale  
- **Persistance des données** : sauvegarde et chargement depuis des fichiers


---

## Architecture du projet

### Organisation des classes (UML & POO)

Le projet applique strictement les principes de la POO. Chaque classe a un rôle précis.

#### Hiérarchie des Enseignants

- **Classe `Enseignant`**  
  - Attributs : ID unique, nom, email généré automatiquement  
  - Rôle : représenter tout enseignant, centraliser les données communes  

- **Classe `EnseignantChercheur`** (hérite de `Enseignant`)  
  - Attributs : 192h ETD annuelles, sujet de recherche  
  - Rôle : gérer les enseignants-chercheurs avec service réduit et recherche  

- **Classe `AutreEnseignant`** (hérite de `Enseignant`)  
  - Attributs : 384h ETD standard, pas de recherche  
  - Rôle : gérer les intervenants extérieurs ou enseignants hors statut MC/PR  

- **Méthode clé** : `virtual getNbH_ETD()` → calcul polymorphique selon le type d’enseignant  

 **Concepts appliqués** : polymorphisme, encapsulation, héritage


#### Classe `Departement`

- Attributs : nom, liste d’enseignants, liste d’UE, responsable (pointeur vers un enseignant)  
- Rôle : centraliser la gestion d’un département, calculer le taux d’encadrement et la charge totale des UE  
- UML : relation **agrégation** avec l’enseignant responsable  



####  Classes `Diplome` & `Semestre`

- `Diplome` contient une ou plusieurs instances de `Semestre` (**composition**)  
- Rôle : organiser les UE en semestres, calculer le coût total d’un diplôme  
- Algorithme : **traversée récursive** pour sommer les coûts des semestres et UE



####  Classe `UE` (Unité d’Enseignement)

- Attributs : volumes horaires CM/TD/TP, nombre de groupes  
- Rôle : gérer les enseignements, calculer les **heures ETD** selon coefficients :  
  - CM = 1.5, TD = 1, TP = 2/3  
- Capacité à appartenir à **plusieurs semestres/diplômes** et répartir le coût proportionnellement  

 **Concept clé** : encapsulation pour garantir l’exactitude des calculs

---

## Fonctionnalités Techniques Avancées

### Gestion Intelligente des Identifiants

- Les IDs (ex: ENS001, DEP012) sont générés automatiquement  
- Au démarrage, le programme analyse les fichiers existants pour reprendre le compteur au bon numéro, évitant les doublons après redémarrage

### Système de Persistance (Fichiers)

- **Sérialisation** : objets en mémoire convertis en format texte structuré dans le dossier `/data`  
- **Désérialisation** : recrée les liens (pointeurs) entre les objets lors du chargement

### Interface Console (UX)

- Utilisation du module `couleur.cpp` pour améliorer la lisibilité  
- **Codes ANSI** : Cyan pour les IDs, Jaune pour les libellés, Rouge pour les erreurs système  
- Persistance des données : sérialisation/désérialisation depuis `/data`

---

##  Arborescence du projet

Projet_Analyse_gestion_UML_POO/ <br>
├── data/ # fichiers .txt pour persistance <br>
├── output/ # dossier pour sorties / résultats <br>
├── main.cpp # fichier principal <br>

├── application.cpp # gestion des menus <br>
├── application.h

├── sauvegarde.cpp # logique d'entrée/sortie fichiers   <br>
├── sauvegarde.h <br>

├── couleur.cpp # gestion des couleurs console   <br>
├── couleur.h <br>

├── Enseignant.cpp # implémentation de la classe Enseignant   <br>
├── Enseignant.h <br>

├── Departement.cpp # implémentation de la classe Departement  <br>
├── Departement.h <br>

├── Diplome.cpp # implémentation de la classe Diplome <br>
├── Diplome.h <br>

├── Semestre.cpp # implémentation de la classe Semestre <br>
├── Semestre.h <br>

├── UE.cpp # implémentation de la classe UE <br>
├── UE.h  <br>

├── Inscription.cpp # implémentation de la classe Inscription  <br>
├── Inscription.h  <br>

├── Intervention.cpp # implémentation de la classe Intervention  <br>
├── Intervention.h  <br>

├── gestion_liste.cpp # implémentation des fonctions de gestion de listes  <br>
├── gestion_liste.h   <br>

└── README.md 

## Technologies & Concepts appliqués

- **Langage** : C++  
- **STL** : `std::list`, `std::stringstream`  
- **UML** : diagrammes de classes, relations d’agrégation et de composition 

