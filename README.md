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

* [x] Création de la classe `CTransaction`
* [x] Ajout du champ **catégorie** sur chaque transaction
* [x] Création et tests de la classe `CTransactionManager` :

  * Ajout, suppression, comptage, solde
  * Filtres avancés (mois/année, catégorie, plage de montants, type)
  * Suppression d’une transaction par index
* [x] Export CSV des transactions
* [x] Écriture systématique des **tests unitaires** (TDD)
* [x] **Documentation Doxygen** configurée et active

## ✨ Prochaines fonctionnalités (roadmap)

* [ ] Export PDF des transactions (optionnel)
* [ ] Vue graphique avec filtres temporels (Qt Charts)
* [ ] Notification en cas de dépassement de budget

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
