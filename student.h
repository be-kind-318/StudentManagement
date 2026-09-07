#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct Student {
    char id[20];        // 学号
    char name[20];      // 姓名
    char className[20]; // 班级
    char gender;        // 性别 F/M
    char phone[20];     // 电话
    float scores[3];    // 3门课程成绩
    float total;        // 总分
    float avg;          // 平均分
    struct Student *next;
} Student;

// 二叉排序树节点（学号查找）
typedef struct BSTNode {
    Student *data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

// 全局链表头（所有模块共用）
extern Student* head;

// 链表基础操作声明
void addStudent();
int deleteStudent(char *id);
int modifyStudent(char *id);
void showAllStudent();
void freeAllList();

#endif