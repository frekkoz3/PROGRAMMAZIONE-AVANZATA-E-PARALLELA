#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ctree.h"

ctree make_cnode(int key, float val)
{
  ctree t = (ctree) malloc(sizeof(struct _ctree_node));
  t->first_free = 1;
  t->key[0] = key;
  t->val[0] = val;
  for(int i = 0; i < N + 1; i++){
    t->children[i] = NULL;
  }  
  return t;
}

ctree cinsert(ctree t, int key, float val)
{
  // se siamo ad un puntatore nullo semplicemente istanziamo un nuovo nodo
  if (t == NULL) {
    return make_cnode(key, val);
  }
  // trovo la posizione della chiave (che sia interna o nei sottoalberi)
  int index = 0;
  while(t->key[index] < key && index < t->first_free){
    index++;
  }
  // verifichiamo se la chiave è già presente
  if (index < t -> first_free && t->key[index] == key){
    t -> val[index] = val;
    return t;
  }
  // la inseriamo nella posizione corretta
  if (t -> first_free < N){
    for(int i = t -> first_free; i > index; i--){
      t->key[i] = t->key[i-1];
      t->val[i] = t->val[i-1];
    }
    t->key[index] = key;
    t->val[index] = val;
    t->first_free++;
    return t;
  }
  // se invece siamo in uno dei figli
  t->children[index] = cinsert(t->children[index], key, val);
  return t;
}

bool csearch(ctree t, int key, float * val)
{
  if (t == NULL){
    return false;
  }
  // trovo la posizione della chiave (che sia interna o nei sottoalberi)
  int index = 0;
  while(t->key[index] < key && index < t->first_free){
    index ++;
  };
  if (index < t -> first_free && t->key[index] == key){
    *val = t-> val[index];
    return true;
  }
  return csearch(t->children[index], key, val);
}

void print_ctree(ctree t)
{
  printf(" _ ");
}