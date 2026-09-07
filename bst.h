#ifndef BST_H
#define BST_H
#include "student.h"

// 根据链表构建BST
BSTree createBST(Student *head);
// BST按学号快速查找
BSTNode* searchBST(BSTree T, char *id);
// 释放BST内存
void freeBST(BSTree T);

#endif