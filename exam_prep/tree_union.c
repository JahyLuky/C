#include <stdlib.h>
#include <stdio.h>

typedef struct Tree{
    struct Tree * left;
    struct Tree * right;
    int val;
} TREE;



/*
    pro vytvoření příkladu
*/
// printovací funkce, kterou jsem opsal od Vogela 
int inorder(TREE * root, int d, int i){
    if (root == NULL) return 0;
    d+=1; // počet teček
    i += inorder(root->left, d, i);
    printf("%2d: ", i + 1);
    i++;
    for (int i = 0; i < d; i++) printf(".");
    printf("%2d\n", root->val);
    i += inorder(root->right, d, i);
    d-=1;
    return i;
}
// creates a binary search tree: left node values are smaller, right node values are bigger or equal
TREE * insertToTree(TREE ** root, int val){
    if (*root == NULL){
        TREE * inserted = (TREE *) malloc( sizeof( TREE ) );
        inserted -> val = val;
        inserted -> left = NULL;
        inserted -> right = NULL;
        return inserted;
    }
    if (val < (*root)->val){
        (*root)->left = insertToTree(&((*root)->left), val);
    }
    else{
        (*root)->right = insertToTree(&((*root)->right), val);
    }
    return *root;
}

////
/* */




TREE * cloneTree( TREE * root){
    if (root == NULL){
        return NULL;
    }
    TREE * inserted = (TREE *) malloc( sizeof( TREE ) );
    inserted -> val = root->val;

    inserted->left = cloneTree(root->left);
    inserted->right = cloneTree(root->right);

    return inserted;
}
TREE * _treeUnion(TREE * cloned, TREE *root2){
    // cloned is missing node
    if (cloned == NULL && root2 != NULL){
        TREE * insert = (TREE *) malloc(sizeof(TREE));
        insert->left = _treeUnion(NULL, root2 ->left);
        insert->right = _treeUnion(NULL, root2 ->right);
        insert->val=root2->val;
        return insert;
    } 
    // součet
    else if (cloned != NULL && root2 != NULL){
        cloned->val += root2->val;
        cloned->left =  _treeUnion(cloned->left , root2 ->left);
        cloned->right = _treeUnion(cloned->right, root2 ->right);
        return cloned;
    }
    // root ends cloned doesnt
    else if (cloned != NULL && root2 == NULL){
        return cloned; // dont continue recursion
    }
    // both are leaf
    else{ 
        return NULL;
    }
}
/* 
* Klonování prvního stromu, 
* prvky které chybý v prvním stromu se dokopírují z druhého
* u prvků kde se stromy překrývají se "val" sečtou 
*/
TREE * treeUnion(TREE * root1, TREE * root2){ // inicializační funkce
    TREE * cloned = cloneTree(root1);
    cloned = _treeUnion(cloned, root2);
    return cloned;
}

void clearTree(TREE * root){//čistota je důležitá
    if (root == NULL){
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    free(root);
}

int main(int argc, char const *argv[])
{
    // Tvorba prvního stromu
    TREE * root1 = NULL;
    root1 = insertToTree(&root1, 10);
    root1 = insertToTree(&root1, 12);
    root1 = insertToTree(&root1, 11);
    root1 = insertToTree(&root1, 6);
    printf("Root1:\n");
    inorder(root1, 0, 0);

    // Tvorba druhého stromu
    TREE * root2 = NULL;
    root2 = insertToTree(&root2, 3);
    root2 = insertToTree(&root2, 2);
    root2 = insertToTree(&root2, 5);
    root2 = insertToTree(&root2, 1);
    printf("Root2:\n");
    inorder(root2, 0, 0);


    // Sjednocení stromů
    TREE * unitedRoot = treeUnion(root1, root2); 
    printf("United Root\n");
    inorder(unitedRoot, 0, 0);


    // rekurzivní uvolnění malloců
    clearTree(root1);
    clearTree(root2);
    clearTree(unitedRoot);
    return 0;
}

