#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "node.h"
#include "bst.h"
#include "printtree.h"

void print_tree(t_node t){
    if (t == NULL){
        printf("NULL\n");
    }else if (t->left == NULL && t->right == NULL){
        printf("%d \n", (t->key));
    }else{
        printf("%d \n", (t->key));
        print_tree(t->left);
        print_tree(t->right);
    }
}
