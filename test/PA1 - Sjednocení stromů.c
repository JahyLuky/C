#include <stdio.h>
#include <stdlib.h>


typedef struct TNode
 {
    struct TNode * m_L, * m_R;
    int m_Val;
 } TNODE;
 
 TNODE * VytvorStrom1()
 {
    TNODE * ret = (TNODE*)malloc(sizeof(TNODE));
    ret->m_Val = 5;
    
    ret->m_L = (TNODE*)malloc(sizeof(TNODE));
    ret->m_L->m_Val = 3;
    ret->m_L->m_L = NULL;
    ret->m_L->m_R = NULL;
    
    ret->m_R = (TNODE*)malloc(sizeof(TNODE));
    ret->m_R->m_Val = 1;
    ret->m_R->m_R = NULL;
    
    ret->m_R->m_L = (TNODE*)malloc(sizeof(TNODE));
    ret->m_R->m_L->m_Val = -2;
    ret->m_R->m_L->m_L = NULL;
    
    ret->m_R->m_L->m_R = (TNODE*)malloc(sizeof(TNODE));
    ret->m_R->m_L->m_R->m_Val = 8;
    ret->m_R->m_L->m_R->m_L = NULL;
    ret->m_R->m_L->m_R->m_R = NULL;
    
    return ret;
 }
 
 TNODE * VytvorStrom2()
 {
    TNODE * ret = (TNODE*)malloc(sizeof(TNODE));
    ret->m_Val = 8;
    
    ret->m_L = (TNODE*)malloc(sizeof(TNODE));
    ret->m_L->m_Val = 9;
    ret->m_L->m_L = NULL;
    ret->m_L->m_R = (TNODE*)malloc(sizeof(TNODE));
    ret->m_L->m_R->m_Val = -7;
    ret->m_L->m_R->m_L = NULL;
    ret->m_L->m_R->m_R = (TNODE*)malloc(sizeof(TNODE));
    ret->m_L->m_R->m_R->m_Val = 5;
    ret->m_L->m_R->m_R->m_L = NULL;
    ret->m_L->m_R->m_R->m_R = NULL;
    
    ret->m_R = (TNODE*)malloc(sizeof(TNODE));
    ret->m_R->m_Val = 4;
    ret->m_R->m_R = NULL;
    ret->m_R->m_L = NULL;
    
    return ret;
 }
 
 void VypisStrom(TNODE * koren)
 {
    if(koren != NULL)
    {
        printf("%d ", koren->m_Val);
        VypisStrom(koren->m_L);
        VypisStrom(koren->m_R);
    }
 }
 
TNODE * unionTree ( TNODE * a, TNODE * b )
{
    TNODE * koren = NULL;
    if(a != NULL && b != NULL)
    {
        koren = (TNODE*)malloc(sizeof(TNODE));
        koren->m_Val = a->m_Val + b->m_Val;
        koren->m_L = unionTree(a->m_L, b->m_L);
        koren->m_R = unionTree(a->m_R, b->m_R);
    }
    else if(a != NULL)
    {
        koren = (TNODE*)malloc(sizeof(TNODE));
        koren->m_Val = a->m_Val;
        koren->m_L = unionTree(a->m_L, NULL);
        koren->m_R = unionTree(a->m_R, NULL);
    }
    else if(b != NULL)
    {
        koren = (TNODE*)malloc(sizeof(TNODE));
        koren->m_Val = b->m_Val;
        koren->m_L = unionTree(NULL, b->m_L);
        koren->m_R = unionTree(NULL, b->m_R);
    }
    
    return koren;
}

void SmazStrom(TNODE * koren)
{
    if(koren != NULL)
    {
        SmazStrom(koren->m_L);
        SmazStrom(koren->m_R);
        
        free(koren);
    }
}

int main(int argc, char** argv) {

    TNODE * s1 = VytvorStrom1();
    TNODE * s2 = VytvorStrom2();
    TNODE * s3;
    
    VypisStrom(s1);
    printf("\n\n");
    VypisStrom(s2);
    printf("\n\n");
    
    s3 = unionTree(s1, s2);
    
    VypisStrom(s3);
    
    SmazStrom(s1);
    SmazStrom(s2);
    SmazStrom(s3);
    return (EXIT_SUCCESS);
}