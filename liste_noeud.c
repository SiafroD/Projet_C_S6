#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

/* TODO */

static liste_noeud_t creer_liste() {
    liste_noeud_t nouvelle_liste = malloc(sizeof(liste_noeud_t));
    if (nouvelle_liste == NULL) {
        // Gestion de l'erreur d'allocation de mémoire ou allocation de mémoire
        // de taille 0.
        return NULL;
    }
    nouvelle_liste->tete = NULL; // Initialisation de la liste comme vide
    return nouvelle_liste;
}




static void detruire_liste(liste_noeud_t* liste_ptr){

    noeud_t* act = (*liste_ptr)->tete;
    noeud_t* suivant;
    // Parcourir la liste est libére les noeuds les uns après les autres.
    while (suivant != NULL) {
        suivant = act->suivant;
        free(act);
        act = suivant;
    }
    free(*liste_ptr);
    liste_ptr = NULL;
}


static bool est_vide_liste(liste_noeud_t liste_noeuds) {
    return liste_noeuds->tete == NULL;
}


static bool contient_noeud_liste(const liste_noeud_t* liste, noeud_id_t id_noeud) {

    noeud_t* act = (*liste)->tete;
    noeud_t* suivant;

    // Si le noeud cherché est le 1er
    if (act->noeud == id_noeud) {
        return true;
    }
    // Sinon on parcours la liste pour le chercher
    while (suivant != NULL) {
        suivant = act->suivant;
        act = suivant;
        if (act->noeud == id_noeud) {
            return true;
        }
    }
    return false;
}


static bool contient_arrete_liste(const liste_noeud_t* liste, noeud_id_t source, noeud_id_t destination) {

    noeud_t* act = (*liste)->tete;
    noeud_t* suivant;

    while (suivant != NULL) {
        if ((act->noeud == source && suivant->noeud == destination) ||
        (act->noeud == destination) && (suivant->noeud == source )) {
            return true;
        }
    }
    return false;
}


static double distance_noeud_liste(liste_noeud_t liste_noeud, noeud_t noeud) {

    noeud_t* act = liste_noeud->tete;
    noeud_id_t id_noeud = noeud.noeud;

    while (act != NULL) {
        if (act->noeud == id_noeud) { 
            return act->distance;
        }
        act = act->suivant;
    }
    return INFINITY;
    }



static noeud_t precedent_noeud_liste(liste_noeud_t liste_noeud, noeud_t noeud) {
    noeud_t* act = liste_noeud->tete;
    noeud_id_t id_noeud = noeud.noeud;

    while (act != NULL) {
        //Si les indices du noeud actuel et cherché sont égaux
        if (act->noeud == id_noeud) { 
            return *act->suivant;
        }
        act = act->suivant;
    }
    // Avec un return NULL y'a pas le bon type
    printf("NO_ID");
}


static noeud_t min_noeud_liste(liste_noeud_t liste_noeud) {
    double min = INFINITY;
    noeud_t* id_min;
    noeud_t* act = liste_noeud->tete;

    while (act != NULL) {
        if (min > act->distance) { 
            min = act->distance;
            id_min = act;
        }
    }
    return *id_min;
}


void inserer_noeud_liste(liste_noeud_t liste_noeud, noeud_t noeud, noeud_t precedent, double distance) {
    
}
