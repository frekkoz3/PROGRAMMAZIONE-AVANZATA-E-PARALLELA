#ifndef _NODE_H
#define _NODE_H
struct _tree_node {
    int key;
    void *value;
    struct _tree_node *left;
    struct _tree_node *right;
    struct _tree_node *parent;
};
typedef struct _tree_node *t_node;
t_node make_t_node (void);
void delete_t_node (t_node tmp);
#endif