# 💰 Finance Tracker

> Une application de gestion des finances personnelles écrite en **C++ avec Qt**, basée sur le **TDD** et les **design patterns modernes** (style KDAB).


## 🚀 Objectifs du projet

- Suivre les **transactions** (revenus, dépenses)
- Gérer les **budgets mensuels par catégorie**
- Afficher des **graphiques clairs** (Qt Charts)
- Avoir une interface graphique fluide et minimaliste
- Appliquer le **Test Driven Development (TDD)** avec **Google Test**
- Concevoir une architecture **modulaire, testable, maintenable**

## 🛠️ Technologies

- C++17 / Qt 5.15+
- CMake
- Qt Widgets / Qt Charts
- Google Test
- Git, GitHub, Linux

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
````


## 📚 Structure du projet

```
.
├── src/              # Code source principal (main.cpp, transaction.cpp, ...)
├── include/          # Headers du projet
├── tests/            # Tests unitaires GoogleTest
├── build/            # Répertoire de compilation (à ignorer)
├── CMakeLists.txt    # Fichier de configuration CMake
└── README.md
```


## ✨ Prochaines fonctionnalités (roadmap)

* [ ] Ajout d’un `TransactionManager`
* [ ] Export CSV / PDF des transactions
* [ ] Vue graphique avec filtres temporels
* [ ] Notification en cas de dépassement de budget


## 🧪 Tests automatisés

Lancer tous les tests avant de lancer l'application :

```bash
./run_with_tests.sh
```

## 🔐 Auteur

Développé par **Neil** — Projet personnel pour améliorer mes compétences en développement logiciel robuste avec Qt.
