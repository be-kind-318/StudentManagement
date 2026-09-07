#include "../include/ui.h"
#include "../include/student.h"
#include "../include/fileio.h"
#include "../include/query.h"
#include "../include/sort.h"
#include "../include/score.h"
#include "../include/bst.h"

int inputCheck(int min, int max) {
    int op;
    while(1) {
        scanf("%d", &op);
        if(op >= min && op <= max) return op;
        printf("输入非法，请重新输入%d~%d：", min, max);
    }
}

void studentMenu() {
    int op;
    char id[20];
    while(1) {
        printf("\n====学生信息管理====\n");
        printf("1.添加学生 2.删除学生 3.修改学生 4.查看全部 0.返回主菜单\n");
        printf("请选择：");
        op = inputCheck(0,4);
        switch(op) {
            case 1: addStudent(); break;
            case 2: printf("输入要删除学号："); scanf("%s",id); deleteStudent(id); break;
            case 3: printf("输入要修改学号："); scanf("%s",id); modifyStudent(id); break;
            case 4: showAllStudent(); break;
            case 0: return;
        }
    }
}

void statMenu() {
    int op;
    char buf[20];
    float a,b;
    while(1) {
        printf("\n====排序查询统计子菜单====\n");
        printf("1.按总分排序 2.按学号排序 3.BST学号查找 4.姓名模糊查询 5.班级查询 6.分数区间查询 7.成绩分析导出图表 8.导出完整成绩Excel表格  0.返回主菜单\n");
        printf("请输入功能序号：");
        op = inputCheck(0,8);
        switch(op) {
            case 1:
                sortByTotal();
                break;
            case 2:
                sortById();
                break;
            case 3: {
                printf("输入要查找的学号：");
                scanf("%s",buf);
                BSTree T = createBST(head);
                BSTNode *res = searchBST(T, buf);
                if(res)
                    printf("查找成功：学号%s 姓名%s 总分%.1f\n", res->data->id, res->data->name, res->data->total);
                else
                    printf("未找到该学号学生\n");
                freeBST(T); // 必须释放BST内存，防止内存堆积卡死
                break;
            }
            case 4: {
                printf("输入姓名关键字：");
                scanf("%s",buf);
                queryByName(buf);
                break;
            }
            case 5: {
                printf("输入班级名称：");
                scanf("%s",buf);
                queryByClass(buf);
                break;
            }
            case 6:
                printf("输入最低平均分、最高平均分（空格分隔）：");
                scanf("%f%f",&a,&b);
                queryByScoreRange(a,b);
                break;
            case 7:
                scoreAnalysisAndExport();
                break;
            case 8:
                exportScoreToCSV();
                break;
            case 0:
                printf("即将返回主菜单...\n");
                return; // 唯一退出子菜单逻辑，回到mainMenu
            default:
                printf("输入序号超出范围，请输入0~8！\n");
        }
        printf("\n按回车继续浏览子菜单...");
        while(getchar()!='\n'); // 清空输入缓冲区，防止连续乱跳
        getchar();
    }
}
void mainMenu() {
    int op;
    while(1) {
        printf("\n====学生成绩管理系统====\n");
        printf("1.学生信息管理 2.排序/查询/成绩统计 3.保存数据 4.加载历史数据 0.退出系统\n");
        printf("请输入操作：");
        op = inputCheck(0,4);
        switch(op) {
            case 1: studentMenu(); break;
            case 2: statMenu(); break;
            case 3: saveStudents(); break;
            case 4: loadStudents(); break;
            case 0: saveStudents(); printf("已自动保存数据，程序退出\n"); freeAllList(); exit(0);
        }
    }
}