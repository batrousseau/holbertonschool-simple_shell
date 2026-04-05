# Simple Shell

![Langage](https://img.shields.io/badge/langage-C-blue)
![Plateforme](https://img.shields.io/badge/plateforme-Linux-lightgrey)
![Statut](https://img.shields.io/badge/statut-projet%20d'apprentissage-orange)

Un interpréteur de commandes UNIX minimaliste écrit en **C** dans le cadre du cursus **Holberton School**.

Ce projet se concentre sur les mécanismes de base d’un shell :
- lecture de l’entrée utilisateur
- découpage de la commande en tokens
- recherche des exécutables via `PATH`
- création de processus fils avec `fork()`
- exécution de programmes avec `execve()`
- attente de la fin du processus fils avant d’afficher le prompt suivant

---

## Sommaire

- [Présentation](#présentation)
- [Comportement actuel](#comportement-actuel)
- [Structure du dépôt](#structure-du-dépôt)
- [Prérequis](#prérequis)
- [Compilation](#compilation)
- [Utilisation](#utilisation)
- [Fonctionnement](#fonctionnement)
- [Cas pris en charge](#cas-pris-en-charge)
- [Limites connues](#limites-connues)
- [Exemple de session](#exemple-de-session)
- [Objectifs pédagogiques](#objectifs-pédagogiques)
- [Pistes d’amélioration](#pistes-damélioration)
- [Auteurs](#auteurs)
- [Licence](#licence)

---

## Présentation

`simple_shell` est un prototype de shell léger conçu pour mieux comprendre le fonctionnement interne d’un interpréteur de commandes.

À l’heure actuelle, le shell :
- affiche le prompt `Bat2mort$` en mode interactif
- lit une ligne avec `getline()`
- supprime le retour à la ligne final
- découpe la commande sur les espaces
- vérifie si la commande est déjà un chemin (`/bin/ls`, `./a.out`, etc.)
- sinon, recherche l’exécutable dans les dossiers définis dans `PATH`
- lance la commande dans un processus fils
- attend la fin du processus avant de continuer

Le projet reste volontairement compact et centré sur **l’exécution de processus** et **le parsing basique d’une ligne de commande**.

---

## Comportement actuel

Pour le moment, le shell se comporte comme un lanceur de commandes minimal.

### Fonctionnalités implémentées

- Détection du mode interactif avec `isatty()`
- Lecture de l’entrée avec `getline()`
- Tokenisation basique avec `strtok(..., " ")`
- Extraction et découpage de `PATH`
- Exécution directe d’un chemin (`/bin/ls`, `./programme`)
- Recherche d’une commande dans `PATH`
- Création de processus avec `fork()`
- Exécution du programme avec `execve()`
- Attente du processus fils avec `wait()`

### Fonctionnalités non implémentées

- Builtins comme `cd`, `exit` ou `env`
- Pipes et redirections
- Gestion des guillemets
- Séparateurs de commandes comme `;`, `&&`, `||`
- Expansion de variables d’environnement
- Parsing complet comparable à celui d’un shell de production

---

## Structure du dépôt

```text
.
├── 0_Exercices/
├── 0-shell_tools.c
├── 1-main_shell.c
├── 2-debug_tools.c
├── 3-general_tools.c
├── 4-fork_and_exec.c
├── 5-general_tools_2.c
├── 6-shell_tools_2.c
├── AUTHORS
├── man_1_simple_shell
├── README.md
├── shell
└── shell.h
```

### Fichiers principaux

- **`1-main_shell.c`** : boucle principale du shell
- **`0-shell_tools.c`** : lecture de l’entrée, nettoyage du `\n`, tokenisation, découpage de `PATH`
- **`4-fork_and_exec.c`** : logique d’exécution (`fork`, `execve`, helpers de recherche)
- **`3-general_tools.c` / `5-general_tools_2.c` / `6-shell_tools_2.c`** : fonctions utilitaires
- **`2-debug_tools.c`** : fonctions de debug
- **`shell.h`** : prototypes et headers nécessaires
- **`AUTHORS`** : contributeurs du projet
- **`man_1_simple_shell`** : ébauche de page de manuel / documentation projet

---

## Prérequis

- Environnement Ubuntu / Linux
- GCC
- Bibliothèque standard du C
- Appels système POSIX

Flags recommandés :
- `-Wall`
- `-Wextra`
- `-Werror`
- `-pedantic`

---

## Compilation

Compiler tous les fichiers C pour produire l’exécutable du shell :

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

Puis lancer le programme avec :

```bash
./hsh
```

---

## Utilisation

En mode interactif, le shell affiche :

```text
Bat2mort$
```

Tu peux ensuite saisir des commandes comme :

```bash
ls
pwd
whoami
/bin/ls
./programme
```

---

## Fonctionnement

Le programme suit globalement cette logique :

1. `clean_getline()` lit une ligne de commande.
2. `no_new_line()` supprime le `\n` final.
3. `stroke_getline()` découpe la ligne en tokens.
4. `get_clean_path_directories()` récupère `PATH` et le découpe en répertoires.
5. `launch_with_dir()` vérifie si la commande ressemble déjà à un chemin.
6. Sinon, `launch_with_command()` reconstruit des chemins candidats comme `/bin/ls`.
7. `fork_and_launch()` crée un processus fils.
8. Le fils lance `execve()`.
9. Le parent attend la fin du processus puis recommence la boucle.

### Modèle d’exécution

```text
Prompt -> Lecture ligne -> Tokenisation -> Résolution exécutable -> fork() -> execve() -> wait() -> Prompt
```

---

## Cas pris en charge

Les cas les plus sûrs avec le code actuel sont des commandes simples comme :

```bash
ls
pwd
whoami
ls -l
/bin/ls
./mon_programme
```

---

## Limites connues

Le dépôt est fonctionnel, mais reste encore très simplifié.

### 1. Parsing très basique

Le shell découpe uniquement sur les espaces :

```c
strtok(command_line, " ")
```

Cela signifie qu’il n’y a pas de gestion de :
- chaînes entre guillemets
- espaces échappés
- règles de parsing avancées

### 2. Tableau de tokens de taille fixe

Le tableau de tokens est alloué avec une taille fixe de 64 entrées et ne se redimensionne pas dynamiquement.

### 3. Absence de builtins

Les commandes qui nécessitent un comportement interne au shell ne sont pas encore implémentées, notamment :

```bash
cd /tmp
exit
env
```

### 4. Pas de pipes ni de redirections

Les cas suivants ne sont pas pris en charge à ce stade :

```bash
ls | wc -l
cat fichier > out.txt
echo hello >> log.txt
```

### 5. Environnement non transmis au processus fils

L’exécution actuelle utilise `execve(path, prompt, NULL)`, ce qui signifie que le processus fils est lancé avec un environnement `NULL` au lieu d’hériter de l’environnement du shell.

### 6. Gestion d’erreurs encore limitée

Le projet est avant tout pédagogique et ne fournit pas encore des messages d’erreur aussi robustes qu’un shell complet.

---

## Exemple de session

```text
$ ./hsh
Bat2mort$ ls
0-shell_tools.c  1-main_shell.c  2-debug_tools.c  3-general_tools.c  4-fork_and_exec.c  5-general_tools_2.c  6-shell_tools_2.c  AUTHORS  README.md  shell.h
Bat2mort$ pwd
/home/user/holbertonschool-simple_shell
Bat2mort$ /bin/echo hello
hello
Bat2mort$
```

---

## Objectifs pédagogiques

Ce projet permet de pratiquer concrètement plusieurs notions fondamentales en C et en systèmes UNIX :

- manipulation de chaînes de caractères
- allocation et libération mémoire
- gestion de processus
- appels système POSIX
- recherche d’exécutables via `PATH`
- organisation modulaire d’un projet en C
- compréhension du cycle d’exécution d’un shell

---

## Pistes d’amélioration

Voici les évolutions les plus naturelles pour faire progresser ce shell :

- implémenter des builtins (`exit`, `env`, `cd`)
- transmettre correctement l’environnement à `execve()`
- améliorer la gestion des erreurs
- gérer les espaces multiples, les guillemets et les cas limites
- ajouter les redirections et les pipes
- prendre en charge le mode non interactif plus complètement
- compléter la page de manuel
- enrichir la documentation et les tests

---

## Auteurs

Voir le fichier **`AUTHORS`** du dépôt.

---

## Licence

Projet académique réalisé dans le cadre de **Holberton School**.

Aucune licence spécifique n’est indiquée dans le dépôt à ce stade.
