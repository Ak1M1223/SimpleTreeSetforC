 //Budowanie BST oraz balansowanie wysokosci
//Kompilacja testowana 02.06.2018 na mingw gcc
//œrodowisko vs 2017
//
#define _CRT_SECURE_NO_WARNINGS//niektore kompilatory nie pozwola bez tej dyrektywy preprocesora na zaladowanie funkcji c ktore sa przedawnione
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
 
 
typedef struct node {
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
//transplantacja poddrzewa
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
        root = transplantSubTree(root, z, z->right);
    else if (z->right == NULL)
        root = transplantSubTree(root, z, z->left);
    else {
        struct node *y = treeMin(z->right);
        if (y->parent != z) {
            root = transplantSubTree(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplantSubTree(root, z, y);
        y->left = z->left;
        y->left->parent = y;
 
    }
    return root;
}
//przejdz przez drzewo
void treeWalk(struct node* x,int h) {
    if (x != NULL) {
        treeWalk(x->left,h+1);
        printf("wartosc %d glebokosc %d\n", x->value,h);
        treeWalk(x->right,h+1);
    }
}
//funkcja do obliczenia log2 z x
unsigned log2(unsigned x)
{
    unsigned y = 1;
 
    while ((x >>= 1) > 0) y <<= 1;
 
    return y;
}
//rotuj w lewo
struct node* rotateL(struct node* root, struct node* rot) {
    struct node* b = rot->right;
    struct node *p = rot->parent;
 
    if (b != NULL) {
        rot->right = b->left;
        if (rot->right != NULL)
            rot->right->parent = rot;
        b->left = rot;
        b->parent = p;
        rot->parent = b;
 
        if (p != NULL) {
            if (p->left == rot)
                p->left = b;
            else p->right = b;
        }
        else root = b;
    }
    return root;
}
//rotuj w prawo
struct node* rotateR(struct node* root, struct node* rot) {
    struct node* b = rot->left;
    struct node *p = rot->parent;
 
    if (b != NULL) {
        rot->left = b->right;
        if (rot->left != NULL)
            rot->left->parent = rot;
        b->right = rot;
        b->parent = p;
        rot->parent = b;
 
        if (p != NULL) {
            if (p->left == rot)
                p->left = b;
            else p->right = b;
        }
        else root = b;
    }
    return root;
}
//balansowanie drzewa, ustaw liniowo i rotuj co 2 wezel
struct node* balanceTree(struct node* root) {
	//pierwsza faza
    unsigned int n, s;
    struct node* p;
    n = 0;
    p = root;
    while (p != NULL)
        if (p->left != NULL) {
            root = rotateR(root, p);
            p = p->parent;
        }
        else {
            n++;
            p = p->right;
        }
 		//druga faza
        s = n + 1 - log2(n + 1);
        p = root;
        int i;
        for (i = 0; i < s;i++) {
            root = rotateL(root, p);
            p = p->parent->right;
        }
 
        n = n - s;
        while (n > 1) {
            n >>= 1;
            p = root;
            for (i = 0; i < n; i++) {
                root = rotateL(root, p);
                p = p->parent->right;
            }
        }
        return root;
}
//malowanie drzewka
typedef struct arr {//to c wiec aby przekazac char[] przez wartosc potrzebna jest struktura oslonowa
    char str[512];
};
struct arr cr, cl, cp;//globalne ramki
 
void printBT(struct arr sp, struct arr sn, struct node * v)//malowanie drzewa w c, czyli bawienie sie c stringami
{
    struct arr s;
    struct arr pom;
 
    if (v != NULL)
    {
        strcpy(s.str, sp.str);
        if (strcmp(sn.str, cr.str) == 0) s.str[(int)strlen(s.str) - 2] = 32;
        strcpy(pom.str, s.str);
        strcat(pom.str, cp.str);
        printBT(pom, cr, v->right);
 		int i;
        for (i = 0; i < (int)strlen(sp.str) - 2; i++) {
            printf("%c", s.str[i]);
        }
 
            printf("%s%d\n", sn.str, v->value);
 
        strcpy(s.str, sp.str);
        if (strcmp(sn.str, cl.str) == 0) s.str[(int)strlen(s.str) - 2] = 32;
        strcpy(pom.str, s.str);
        strcat(pom.str, cp.str);
        printBT(pom, cl, v->left);
    }
}
 
 
int main() {
    struct node* root = NULL;//to jest wsk na korzen
 
 //BUDUJEMY RANDOMOWE 20 ELEMENTOWE drzewo wyszukiwan binarnych
    srand(time(NULL));
    struct node *test;
    int i;
    for (int i = 0; i < 50; i++) {
        int r = rand();
        test = initializeNode(r);
        root = insertNode(root, test);
    }
 
 
 
    printf("/////////////PRZED ZBALANSOWANIEM DRZEWA/////////////\n");
    treeWalk(root,0);//przechodzimy metoda inorder
 
    printf("root val %d\n", root->value);
    //malujemy drzewko
    cr.str[0] = 218; cr.str[1] = 196;//ramki do malowania drzewka
    cl.str[0] = 192; cl.str[1] = 196;
    cp.str[0] = 179; cp.str[1] = 32;
    struct arr nothing;//dumb structure
    printBT(nothing, nothing, root);
 
 
 
    root = balanceTree(root);//BALANSUJ DRZEWO
    printf("/////////////PO ZBALANSOWANIU DRZEWA/////////////\n");
    treeWalk(root,0);
    printf("root val %d\n", root->value);
 
    //malujemy drzewko
    printBT(nothing, nothing, root);
 
    getchar();//pauza
 
    return 0;
}
