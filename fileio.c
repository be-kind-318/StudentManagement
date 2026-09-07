#include "../include/fileio.h"
#include "../include/student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//实现学生管理系统的数据持久化功能，包括保存和加载两个核心操作。
// 外部全局链表头声明
extern Student* head;

int saveStudents() {
    FILE *fp = fopen("data/student.txt", "w");
    if (fp == NULL) {
        printf("【错误】文件打开失败，请检查项目根目录是否存在 data 文件夹！\n");
        return 0;
    }

    Student *p = head;
    int saveCnt = 0;
    while (p != NULL) {
        fprintf(fp, "%s %s %s %c %s %.1f %.1f %.1f %.1f %.2f\n",
                p->id,
                p->name,
                p->className,
                p->gender,
                p->phone,
                p->scores[0],
                p->scores[1],
                p->scores[2],
                p->total,
                p->avg);
        saveCnt++;
        p = p->next;
    }

    fclose(fp);
    printf("数据保存成功，共写入 %d 名学生记录\n", saveCnt);
    return 1;
}

int loadStudents() {
    FILE *fp = fopen("data/student.txt", "r");
    if (fp == NULL) {
        printf("提示：未找到历史数据文件 data/student.txt，系统使用空白数据\n");
        return 0;
    }

    // 清空原有链表，防止新旧数据重叠
    freeAllList();
    char buf[256];
    int loadCnt = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // 跳过空行
        if (strlen(buf) <= 1)
            continue;

        Student *s = (Student*)malloc(sizeof(Student));
        if (s == NULL) {
            printf("【错误】内存分配失败，部分学生数据加载中断！\n");
            break;
        }

        // 按存储格式解析一行学生数据
        int ret = sscanf(buf,
            "%s %s %s %c %s %f %f %f %f %f",
            s->id,
            s->name,
            s->className,
            &s->gender,
            s->phone,
            &s->scores[0],
            &s->scores[1],
            &s->scores[2],
            &s->total,
            &s->avg);

        // 格式校验：必须读取到10个数据项才算合法记录
        if (ret != 10) {
            free(s);
            printf("警告：存在格式错误的行，已跳过该行数据\n");
            continue;
        }

        s->next = NULL;
        // 尾插法存入链表
        if (head == NULL) {
            head = s;
        } else {
            Student *p = head;
            while (p->next != NULL)
                p = p->next;
            p->next = s;
        }
        loadCnt++;
    }

    fclose(fp);
    printf("历史数据加载完成，共读取 %d 名学生记录\n", loadCnt);
    return 1;
}