#include "../include/score.h"

void scoreAnalysisAndExport() {
    if (!head) {
        printf("暂无学生数据，无法分析！\n");
        return;
    }
    Student *p = head;
    int totalStu = 0;
    float sumAll = 0;
    float maxTotal = 0, minTotal = 9999;
    int fail = 0, mid = 0, excellent = 0; // <60 60~80 >=80

    while (p) {
        totalStu++;
        sumAll += p->avg;
        if (p->total > maxTotal) maxTotal = p->total;
        if (p->total < minTotal) minTotal = p->total;
        if (p->avg < 60) fail++;
        else if (p->avg < 80) mid++;
        else excellent++;
        p = p->next;
    }
    float avgAll = sumAll / totalStu;

    // 1. 文字分析报告
    printf("==========成绩分析报告==========\n");
    printf("总人数：%d\n全体平均分为：%.2f\n最高总分：%.1f 最低总分：%.1f\n", totalStu, avgAll, maxTotal, minTotal);
    printf("不及格(<60)：%d人 | 中等(60~80)：%d人 | 优秀(≥80)：%d人\n", fail, mid, excellent);

    // 2. 控制台文本柱状统计图
    printf("\n====分数段柱状图====\n");
    printf("不及格 |");
    for(int i=0; i<fail; i++) printf("■");
    printf(" %d\n", fail);
    printf("中等   |");
    for(int i=0; i<mid; i++) printf("■");
    printf(" %d\n", mid);
    printf("优秀   |");
    for(int i=0; i<excellent; i++) printf("■");
    printf(" %d\n", excellent);

    // 3. 导出统计文件到data/score_stat.txt，Excel可直接绘图
    FILE *fp = fopen("data/score_stat.txt", "w");
    if (fp) {
        fprintf(fp,"分数段,人数\n");
        fprintf(fp,"不及格,%d\n中等,%d\n优秀,%d\n",fail,mid,excellent);
        fprintf(fp,"总人数,%d\n全局平均分,%.2f\n最高总分,%.1f\n最低总分,%.1f",totalStu,avgAll,maxTotal,minTotal);
        fclose(fp);
        printf("\n统计数据已导出至 data/score_stat.txt，导入Excel生成折线/柱状图\n");
    } else {
        printf("导出统计文件失败\n");
    }
}

void exportScoreToCSV()
{
    if (!head)
    {
        printf("暂无学生数据，无法导出表格！\n");
        return;
    }
    FILE *fp = fopen("data/学生成绩总表.csv", "w");
    if (fp == NULL)
    {
        printf("文件创建失败，请检查项目目录下是否存在data文件夹！\n");
        return;
    }

    // 【删除UTF8-BOM，改用系统默认GBK编码，WPS/Excel直接识别中文】
    // CSV表头（Excel列名）
    fprintf(fp, "学号,姓名,班级,性别,联系电话,科目1,科目2,科目3,总分,平均分,成绩等级\n");

    Student *p = head;
    int count = 0;
    while (p != NULL)
    {
        char level[10];
        if (p->avg >= 90)
            strcpy(level, "优秀");
        else if (p->avg >= 80)
            strcpy(level, "良好");
        else if (p->avg >= 70)
            strcpy(level, "中等");
        else if (p->avg >= 60)
            strcpy(level, "及格");
        else
            strcpy(level, "不及格");

        fprintf(fp, "%s,%s,%s,%c,%s,%.1f,%.1f,%.1f,%.1f,%.2f,%s\n",
                p->id, p->name, p->className, p->gender, p->phone,
                p->scores[0], p->scores[1], p->scores[2],
                p->total, p->avg, level);
        p = p->next;
        count++;
    }
    fclose(fp);
    printf("导出完成！成功导出 %d 位学生数据\n", count);
    printf("文件路径：项目data文件夹/学生成绩总表.csv\n");
    printf("操作提示：双击该文件，将自动使用WPS/Excel打开完整表格\n");
}