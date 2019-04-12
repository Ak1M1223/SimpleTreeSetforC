#include <stdio.h>
#include <stdlib.h>
 
struct node {
    struct node* left;
    struct node* right;
    struct node* parent;
    int value;
};
 
//tworzenie wezla
struct node* initializeNode(int val) {
    struct node* pointer;
    pointer = (struct node*)malloc(sizeof(struct node));
    pointer->left = NULL;
    pointer->right = NULL;
    pointer->parent = NULL;
    pointer->value = val;
    return pointer;
 
}
//dodawanie wezla
struct node* insertNode(struct node* root, struct node* in) {
    struct node* y = NULL;
    struct node* x = root;
    while (x != NULL) {
        y = x;
        if (in->value < x->value)
            x = x->left;
        else x = x->right;
    }
    in->parent = y;
    if (y == NULL)
    root = in;
    else if (in->value < y->value)
        y->left = in;
   
    else y->right = in;
 
    return root;
}
//transplantacja poddrzewa //co autor mia³ na mysli
struct node* transplantSubTree(struct node* root, struct node* u, struct node* v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
 
    return root;
}
//daj minimum zaczynajac od poddrzewa x
struct node* treeMin(struct node* x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}
//usun wezel i przesun poddrzewa
struct node* deleteNode(struct node* root, struct node* z) {
    if (z->left == NULL)
        root=transplantSubTree(root, z, z->right);
    else if (z->right == NULL)
        root=transplantSubTree(root, z, z->left);
    else {
        struct node *y = treeMin(z->right);
        if (y->parent != z) {
            root=transplantSubTree(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root=transplantSubTree(root, z, y);
        y->left = z->left;
        y->left->parent = y;
 
    }
    return root;
}
//przejdz przez drzewo
void treeWalk(struct node* x) {
    if (x != NULL) {
        treeWalk(x->left);
        printf("%d\n", x->value);
        treeWalk(x->right);
    }
}
 
 
int main() {
    struct node* root=NULL;//to jest wsk na korzen
 
    struct node* test;//nowy node
    test = initializeNode(5);//inicjalizuj node wartoscia 5
    root=insertNode(root, test);//wstaw test do drzewa gdzie korzeniem jest root, aktualizuj root jezeli potrzeba
 
 
 
    struct node* test2;
    test2 = initializeNode(2);
    root=insertNode(root, test2);
 
    struct node* test3;
    test3 = initializeNode(3);
    root=insertNode(root, test3);
 
    struct node* test4;
    test4 = initializeNode(7);
    root=insertNode(root, test4);
 
    root = deleteNode(root, test);//usun test z drzewa o korzeniu root,przesun poddrzewa zgodnie z regula BST, aktualizuj root jezeli konieczne
 
    treeWalk(root);//przechodzimy metoda inorder
 
    printf("root val %d", root->value);
 
   
    getchar();
 
 
 
 
 
 
    return 0;
}
