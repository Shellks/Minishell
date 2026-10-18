# minishell

Un shell inspiré de bash, écrit en C.
Projet de l'École 42 (Lyon), réalisé à deux en 2023.

Le programme lit une ligne de commande, la découpe et l'analyse, puis l'exécute en créant
les processus nécessaires (`fork`, `execve`), reliés par des pipes (`pipe`, `dup2`).

## Fonctionnalités

- Invite de commande avec historique (flèches haut et bas), via `readline`
- Commandes du `PATH` ou par chemin (`ls`, `/bin/ls`, `./script.sh`)
- Pipes : `ls -l | grep minishell | wc -l`
- Redirections : `<`, `>`, `>>`, et here-document `<<`
- Guillemets simples (aucune interprétation) et doubles (variables interprétées)
- Variables d'environnement `$VAR`, et code de retour de la dernière commande `$?`
- Signaux comme dans bash : Ctrl+C (nouvelle invite), Ctrl+D (quitter), Ctrl+\ (ignoré)
- Commandes intégrées (builtins) :
  - `echo` avec l'option `-n`
  - `cd` (chemin relatif ou absolu, `cd` seul pour revenir à `HOME`, `cd -`)
  - `pwd`, `export`, `unset`, `env`, `exit`

## Prérequis

Linux, avec un compilateur C, `make` et la bibliothèque `readline`.
Sous Ubuntu ou Debian :

```bash
sudo apt install build-essential libreadline-dev
```

## Compiler et lancer

```bash
make
./minishell
```

Pour quitter : `exit`, ou Ctrl+D.

## Essayer en deux minutes

À taper dans le minishell :

```bash
echo "Bonjour $USER"
echo 'Bonjour $USER'
ls -l | grep src | wc -l
echo "première ligne" > test.txt
echo "deuxième ligne" >> test.txt
cat < test.txt
cat << FIN
le here-document s'arrête au mot FIN
FIN
ls fichier_inexistant
echo $?
export PROJET=minishell
env | grep PROJET
unset PROJET
cd /tmp
pwd
cd -
exit
```

Ce qu'il faut observer :
- les guillemets doubles remplacent `$USER` par sa valeur, les guillemets simples non ;
- `$?` affiche le code de retour de la commande précédente ;
- `cd -` ramène au dossier précédent.

## Avec de vraies commandes du quotidien

Toute commande installée sur la machine fonctionne : le minishell la cherche dans le `PATH`,
puis la lance avec `execve`. Ces exemples utilisent `/etc/passwd`, présent sur tout Linux.

```bash
awk -F: '{print $1}' /etc/passwd | head -5
awk -F: '$3 >= 1000 {print $1, $6}' /etc/passwd
cut -d: -f7 /etc/passwd | sort | uniq -c | sort -rn
grep -c nologin /etc/passwd
echo "$HOME" | awk -F/ '{print $NF}'
ls /usr/bin | grep '^a' | wc -l
sleep 10
```

Ce qu'il faut observer :
- dans les commandes `awk`, les guillemets simples protègent `$1`, `$3` et `$NF` : ils doivent
  arriver intacts à `awk`, sans être remplacés par le minishell ;
- dans `echo "$HOME" | awk ...`, le minishell remplace `$HOME` (guillemets doubles), mais
  pas `$NF` (guillemets simples) ;
- pendant `sleep 10`, Ctrl+C interrompt la commande et rend l'invite.

## Ce qui n'est pas géré

- le séparateur `;` et la barre oblique inverse `\` : exclus par le sujet ;
- les opérateurs `&&` et `||`, et les jokers (`*.c`) : ils faisaient partie des bonus,
  que nous n'avons pas réalisés.

## Comment ça marche

Chaque ligne passe par quatre étapes :

1. **Lexer** (`src/lexer/`) : découpe la ligne en éléments (mots, pipes, redirections)
   en respectant les guillemets.
2. **Expansion** (`src/expand/`) : remplace `$VAR` et `$?` par leur valeur, retire les guillemets.
3. **Parser** (`src/parsing/`) : regroupe les éléments en commandes, chacune avec ses
   arguments et ses redirections.
4. **Exécution** (`src/exec/`) :
   - une commande intégrée seule (`cd`, `export`…) s'exécute dans le shell lui-même,
     sinon elle n'aurait aucun effet sur lui ;
   - sinon, un processus enfant par commande (`fork`), les pipes et redirections branchées
     avec `dup2`, puis le programme lancé avec `execve`. Le shell attend la fin avec `waitpid`
     et récupère le code de retour pour `$?`.

## Vérifier les fuites mémoire

`readline` garde volontairement de la mémoire jusqu'à la fin du programme. Le fichier
`valgrind_ignore` masque ces fausses alertes, pour ne voir que les fuites du projet :

```bash
valgrind --leak-check=full --suppressions=valgrind_ignore ./minishell
```

## Auteurs

acarlott, nibernar (École 42 Lyon)
