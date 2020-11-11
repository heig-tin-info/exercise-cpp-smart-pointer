# Smart pointers

La vidéo du YouTubeur **The Chemo** consacrée aux Smart Pointers est très complète : https://www.youtube.com/watch?v=UOB7-B2MfwA. Commencez par visionner cette vidéo. Référez-vous également à la page Wikipedia https://en.wikipedia.org/wiki/Smart_pointer.

Dans les langages de haut niveau deux mécanismes permettent de garder sous contrôle l'usage de la mémoire et ainsi éviter soit des erreurs de segmentation (accès à une ressource qui n'existe plus), ou bien un fuite mémoire (heap overflow). Une fuite mémoire appraît lorsqu'un objet n'est pas convenablement détruit et devient un *zombie* en mémoire. C'est à dire que la mémoire est allouée à cet objet, mais que plus aucun pointeur ne permet d'accéder à cette ressource.

Les pointeurs sont utiles pour véhiculer des objets par référence et donc sans avoir à les copier en mémoire. On utilisera préférablement une référence `&` lorsqu'un objet existe toujours, mais on devra parfois utiliser des pointeurs lorsque ces derniers peuvent être nuls (c'est à dire ne pointer sur aucun objet)

Face à ce problème de contrôle des ressources allouées en mémoire il existe deux mécanismes distincts :

- Le *garbage collector* (ramasse-miette en français)
- Les *smart pointers* ou pointeurs intelligents

Ces deux mécanismes peuvent tous deux utiliser le *comptage de références* ; pour savoir si un objet alloué dynamiquement est encore utilisé, il faut connaître le nombre de pointeurs pointant sur cet espace mémoire. Lorsque le nombre de références tombe à zéro, la ressource peut être libérée.

# Objectifs de l'exercice

1. Visionner la vidéo de *The Chemo*.
2. Écrire un programme mettant en oeuvre les trois smart pointers du C++ :
  - `unique_ptr` ;
  - `shared_ptr` ;
  - `weak_ptr`.
3. Imaginer un contexte ou ce type de pointeur pourrait être utile.
4. Prendre connaissance des ficheirs `unique.cpp` et `shared.cpp`.
5. Répondre aux questions suivantes :
  - Que veut dire `= delete` les fichiers `unique.cpp` et `shared.cpp` ?
  - Pourquoi est-ce que le compteur de référence `Counter` doit être stocké sur le *heap* ?
  - 
# Quel est le besoin ?

Il est parfois essentiel

```c++
char* str = new char [5];
delete [] str;
```
