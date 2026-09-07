#include "../include/bst.h"
static void insertBST(BSTree *T, Student *stu) {
    if (*T == NULL) {
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = stu;
        (*T)->lchild = (*T)->rchild = NULL;
        return;
    }
    if (strcmp(stu->id, (*T)->data->id) < 0)
        insertBST(&(*T)->lchild, stu);
    else
        insertBST(&(*T)->rchild, stu);
}

BSTree createBST(Student *head) {
    BSTree T = NULL;
    Student *p = head;
    while (p) {
        insertBST(&T, p);
        p = p->next;
    }
    return T;
}

BSTNode* searchBST(BSTree T, char *id) {
    if (!T) return NULL;
    int cmp = strcmp(id, T->data->id);
    if (cmp == 0) return T;
    else if (cmp < 0) return searchBST(T->lchild, id);
    else return searchBST(T->rchild, id);
}

void freeBST(BSTree T) {
    if (T) {
        freeBST(T->lchild);
        freeBST(T->rchild);
        free(T);
    }
}