#include "../include/query.h"

void queryById(char *id) {
    Student *p = head;
    while(p && strcmp(p->id, id) != 0) p = p->next;
    if(!p) { printf("无该学生\n"); return; }
    printf("学号:%s 姓名:%s 班级:%s 总分:%.1f\n", p->id,p->name,p->className,p->total);
}

void queryByName(char *name) {
    Student *p = head;
    int flag = 0;
    while(p) {
        if(strstr(p->name, name)) {
            printf("学号:%s 姓名:%s 总分:%.1f\n", p->id,p->name,p->total);
            flag = 1;
        }
        p = p->next;
    }
    if(!flag) printf("未匹配到学生\n");
}

void queryByClass(char *cls) {
    Student *p = head;
    int flag = 0;
    while(p) {
        if(strcmp(p->className, cls) == 0) {
            printf("%s %s %.1f\n", p->id,p->name,p->total);
            flag = 1;
        }
        p = p->next;
    }
    if(!flag) printf("该班级无学生\n");
}

void queryByScoreRange(float min, float max) {
    Student *p = head;
    int flag = 0;
    while(p) {
        if(p->avg >= min && p->avg <= max) {
            printf("%s %s 平均分:%.2f\n", p->id,p->name,p->avg);
            flag = 1;
        }
        p = p->next;
    }
    if(!flag) printf("无区间内学生\n");
}