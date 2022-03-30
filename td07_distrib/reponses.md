# Exercice 1 
1. les yeux suivent la souris 
2. sur le terminal il y a écrit 
```sh
$ xeyes
^Z
[1]+  Arrêté                xeyes
```
et les yeux arretent de suivre la souris 
3. 
```sh
$ xeyes
^Z
[1]+  Arrêté                xeyes
$ bg
[1]+ xeyes &
```
les yeux se remettent a suivre la souris 

4. ok 6249

5. 
```sh
$ kill -SIGSTOP 6249

[1]+  Arrêté                xeyes
```
tout comme Ctrl + Z

6. signal numéro 18 `SIGCONT`

7. avec la commande killall 
```sh
$ killall xeyes
[1]+  Complété              xeyes
```

