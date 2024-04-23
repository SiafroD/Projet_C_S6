#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>



liste_noeud_t* creer_liste() {
    liste_noeud_t* nouvelle_liste = malloc(sizeof(liste_noeud_t));
    if (&nouvelle_liste == NULL) {
        // Gestion de l'erreur d'allocation de mémoire ou allocation de mémoire
        // de taille 0.
        return NULL;
    }
    nouvelle_liste->tete = NULL; // Initialisation de la liste comme vide
    return nouvelle_liste;
}




void detruire_liste(liste_noeud_t* liste_ptr){

    noeud_t* act = liste_ptr->tete;
    noeud_t* prec;
    // Parcourir la liste est libére les noeuds les uns après les autres.
    while (act != NULL) {
        prec = act->prec;
        free(act);
        act = prec;
    }
    free(liste_ptr);
    liste_ptr = NULL;
}




bool est_vide_liste(liste_noeud_t* liste_noeuds) {
    return liste_noeuds->tete == NULL;
}




bool contient_noeud_liste(const liste_noeud_t* liste, int id_noeud) {

    noeud_t* act = liste->tete;
    noeud_t* prec;

    // Si le noeud cherché est le 1er
    if (act->noeud == id_noeud) {
        return true;
    }
    // Sinon on parcours la liste pour le chercher
    while (prec != NULL) {
        prec = act->prec;
        act = prec;
        if (act->noeud == id_noeud) {
            return true;
        }
    }
    return false;
}




 bool contient_arrete_liste(const liste_noeud_t* liste, int source, int destination) {

    noeud_t* act = liste->tete;
    noeud_t* prec;

    while (prec != NULL) {
        if ((act->noeud == source && prec->noeud == destination) ||
        (act->noeud == destination) && (prec->noeud == source )) {
            return true;
        }
    }
    return false;
}




double distance_noeud_liste(liste_noeud_t* liste_noeud, int noeud) {

    noeud_t* act = liste_noeud->tete;
    while (act != NULL) {
        if (act->noeud == noeud) { 
            return act->distance;
        }
        act = act->prec;
    }
    return INFINITY;
}




int precedent_noeud_liste(liste_noeud_t* liste_noeud, int noeud) {
    noeud_t* act = liste_noeud->tete;

    while (act != NULL) {
        // Si les indices du noeud actuel et cherché sont égaux
        if (act->noeud == noeud) { 
            return act->prec;
        }
        act = act->prec;
    }
    // Avec un return NULL y'a pas le bon type
    printf("NO_ID");
}




int min_noeud_liste(liste_noeud_t* liste_noeud) {
    double min = INFINITY;
    noeud_t* id_min;
    noeud_t* act = liste_noeud->tete;

    while (act != NULL) {
        if (min > act->distance) { 
            min = act->distance;
            id_min = act;
        }
        act = act->prec;
    }
    return id_min;
}




void inserer_noeud_liste(liste_noeud_t* liste_noeud, int noeud, int precedent, double distance) {
        // Créer un nouveau noeud
    noeud_t* nouveau_noeud = malloc(sizeof(noeud_t));
    if (nouveau_noeud == NULL) {
        // Gestion de l'erreur d'allocation de mémoire
        return;
    }
        // Etablir les paramètres de ce noeud
    nouveau_noeud->noeud = noeud;
    nouveau_noeud->distance = distance;
    nouveau_noeud->prec = NULL;

    // Si la liste est vide, le nouveau noeud est la tête
    if (est_vide_liste(liste_noeud)) {
        liste_noeud->tete = nouveau_noeud;
        return;
    }

    // Insertion à une position spécifique
    noeud_t* act = liste_noeud->tete;
    while (act != NULL) {
        if (act->noeud == precedent) {
            nouveau_noeud->prec = act; // MAJ du paramètre prec du nouveau noeud pour que ça soit le noeud
                                       // en entrée
            act->prec = nouveau_noeud; // Insérer le nouveau noeud après le noeud précédent
            return;
        }
        act = act->prec;
    }

    // Si le noeud précédent n'est pas trouvé, le nouveau noeud est ajouté à la fin
    act = liste_noeud->tete;
    while (act->prec != NULL) {
        act = act->prec;
    }
    act->prec = nouveau_noeud; // Ajouter le nouveau noeud à la fin
}




void changer_noeud_liste(liste_noeud_t* liste_noeud, int noeud, int precedent, double distance) {
    bool present = false;
    noeud_t* act = liste_noeud->tete;

// Recherche du noeud à modifier
    while (act != NULL) {
        if (act->noeud == noeud) {
            present = true;
            act->distance = distance;
            act->prec = &precedent;
            break; //Evite de continuer dans la boucle alors qu'on a changé le noeud.
        }
    }
    if (!present) {
        inserer_noeud_liste(liste_noeud, noeud, precedent, distance);
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste_noeud, int noeud) {
    noeud_t* act = liste_noeud->tete;
    noeud_t* precedent = NULL;
    // On a egalement besoin du noeud précédent pour supprimer.

    while (act != NULL && act->noeud == noeud) {
        precedent = act;
        act = act->prec; // On a donc dans act le noeud actuel qu'il faut supprimer
                         // et dans prec son précédent.
    }

    // Si il n'a pas de précédent, alors c'est que le noeud est la tête de liste
    // il faut donc mettre à jour le pointeur de cette tête, de plus, il n'y a pas
    // de MAJ du précédent à faire.
    if (precedent == NULL) {
        liste_noeud->tete = act->prec; // Effectivement, la nouvelle tête est le precedent
                                       // de act, qu'on veut supprimer.
    } else {
        // Si le noeud cherché n'est pas le 1er:
        precedent->prec = act->prec; // Décalage des précédents pour conserver le lien de 
                                     // passage d'une cellule à la suivante
    }
    //Libère la mémoire du noeud supprimé
    free(act);
}
