# 💰 Finance Tracker

> Une application de gestion des finances personnelles écrite en **C++ avec Qt**, basée sur le **TDD** et les **design patterns modernes** (style KDAB).

## 🚀 Objectifs du projet

* Suivre les **transactions** (revenus, dépenses)
* Gérer les **budgets mensuels par catégorie**
* Afficher des **graphiques clairs** (Qt Charts)
* Avoir une interface graphique fluide et minimaliste
* Appliquer le **Test Driven Development (TDD)** avec **Google Test**
* Concevoir une architecture **modulaire, testable, maintenable**
* Générer la **documentation technique** automatiquement avec **Doxygen**

## 🛠️ Technologies

* C++17 / Qt 5.15+
* CMake
* Qt Widgets / Qt Charts
* Google Test (tests unitaires automatisés)
* Doxygen (documentation du code)
* Git, GitHub, Linux

## 📦 Build & Lancement

```bash
# Clone le repo
git clone git@github.com:TonUtilisateur/finance-tracker.git
cd finance-tracker

# Build
mkdir build && cd build
cmake ..
make

# Tests
./finance_tracker_tests

# Lancement
./finance_tracker

# Générer la documentation Doxygen
doxygen Doxyfile
```

## 📚 Structure du projet

```
.
├── src/              # Code source principal (main.cpp, transaction.cpp, ...)
├── include/          # Headers du projet
├── tests/            # Tests unitaires GoogleTest
├── build/            # Répertoire de compilation (à ignorer)
├── docs/ or html/    # Documentation générée par Doxygen (à ignorer)
├── CMakeLists.txt    # Fichier de configuration CMake
├── Doxyfile          # Fichier de configuration Doxygen
└── README.md
```

## ✨ Avancement & fonctionnalités réalisées

* [x] **Architecture Backend** :
    * [x] Création de la classe `CTransaction`.
    * [x] Création et tests de la classe `CTransactionManager` (ajout, suppression, filtres avancés, etc.).
    * [x] Logique de gestion de **budgets** (`CBudget`, `CBudgetManager`).
    * [x] Export CSV des transactions.
* [x] **Interface Graphique (UI)** :
    * [x] Vue principale avec **graphique** (Qt Charts) affichant les dépenses par catégorie.
    * [x] **Filtres temporels** avancés (mois en cours, 3 derniers mois, année, personnalisé).
    * [x] Boîte de dialogue pour l'**ajout de nouvelles transactions**.
    * [x] **Notification** en cas de dépassement de budget lors de l'ajout d'une dépense.
* [x] **Qualité & Tests** :
    * [x] Écriture systématique des **tests unitaires** (TDD) pour toute la logique métier.
    * [x] Tests unitaires pour la logique de l'**interface graphique** (en mode headless).
    * [x] **Documentation Doxygen** complète pour toutes les classes.
    * [x] Refactorisation du **build system CMake** vers une architecture modulaire avec une librairie `core`.

## ✨ Prochaines fonctionnalités (roadmap)

* [ ] **Gestion des Budgets via l'UI** :
    * [ ] Interface pour créer, modifier et supprimer des budgets.
* [ ] **Gestion des Transactions via l'UI** :
    * [ ] Affichage des transactions dans un tableau (`QTableView`).
    * [ ] Possibilité de modifier ou supprimer une transaction existante.
* [ ] **Persistance des Données** :
    * [ ] Sauvegarde et chargement des transactions et des budgets depuis un fichier (CSV, JSON ou SQLite).
* [ ] **Améliorations Visuelles** :
    * [ ] Ajout de nouveaux types de graphiques (ex: camembert pour les catégories).
    * [ ] Amélioration du design général.
* [ ] **Export PDF** des transactions (optionnel).

## 🧪 Tests automatisés

Lancer tous les tests avant de lancer l'application :

```bash
./run_with_tests.sh
```

## 📖 Documentation technique

Générer la documentation :

```bash
doxygen Doxyfile
# Ouvrir docs/index.html ou html/index.html dans un navigateur
```

## 🔐 Auteur

Développé par **Neil** — Projet personnel pour améliorer mes compétences en développement logiciel robuste avec Qt.

## Licence et contributions

Le code source de ce projet est mis à disposition pour consultation publique.

- **Modification et utilisation interdites sans mon accord.**
- Vous pouvez proposer des améliorations via des pull requests ou signaler des problèmes via les issues.
- Toute utilisation ou redistribution sans autorisation est interdite.

Pour toute demande, contactez-moi à [neil.lf007@hotmail.com].
