#include "../include/fileio.h"
#include "../include/student.h"
Student* head = NULL;
void addStudent() {
    Student *s = (Student*)malloc(sizeof(Student));
    printf("输入学号：");
    scanf("%s", s->id);
    printf("输入姓名：");
    scanf("%s", s->name);
    printf("输入班级：");
    scanf("%s", s->className);
    printf("输入性别(F/M)：");
    scanf(" %c", &s->gender);
    printf("输入电话：");
    scanf("%s", s->phone);
    printf("输入3门成绩(空格分隔)：");
    scanf("%f %f %f", &s->scores[0], &s->scores[1], &s->scores[2]);
    // 计算总分平均分
    s->total = s->scores[0] + s->scores[1] + s->scores[2];
    s->avg = s->total / 3.0f;
    s->next = NULL;
    // 尾插法插入链表
    if (head == NULL) {
        head = s;
    } else {
        Student *p = head;
        while (p->next) p = p->next;
        p->next = s;
    }
    printf("添加成功！\n");
}

int deleteStudent(char *id) {
    if (head == NULL) {
        printf("暂无学生数据\n");
        return 0;
    }
    Student *p = head, *pre = NULL;
    while (p && strcmp(p->id, id) != 0) {
        pre = p;
        p = p->next;
    }
    if (!p) {
        printf("未找到该学号学生\n");
        return 0;
    }
    if (pre == NULL) head = p->next;
    else pre->next = p->next;
    free(p);
    printf("删除成功\n");
    return 1;
}

int modifyStudent(char *id) {
    Student *p = head;
    while (p && strcmp(p->id, id) != 0) p = p->next;
    if (!p) {
        printf("未找到学生\n");
        return 0;
    }
    printf("修改姓名：");
    scanf("%s", p->name);
    printf("修改班级：");
    scanf("%s", p->className);
    printf("修改三门成绩：");
    scanf("%f %f %f", &p->scores[0], &p->scores[1], &p->scores[2]);
    p->total = p->scores[0] + p->scores[1] + p->scores[2];
    p->avg = p->total / 3;
    printf("修改完成\n");
    return 1;
}

void showAllStudent() {
    if (!head) {
        printf("无学生数据\n");
        return;
    }
    printf("学号\t姓名\t班级\t总分\t平均分\n");
    Student *p = head;
    while (p) {
        printf("%s\t%s\t%s\t%.1f\t%.2f\n", p->id, p->name, p->className, p->total, p->avg);
        p = p->next;
    }
}

void freeAllList() {
    Student *p = head, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    head = NULL;
}