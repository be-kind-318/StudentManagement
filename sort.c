#include "../include/sort.h"
#include "../include/student.h"
#include <stdlib.h>
#include <string.h>

extern Student* head;

static void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// 链表转指针数组
static Student** listToArray(Student *head, int *cnt) {
    *cnt = 0;
    Student *p = head;
    while (p) { (*cnt)++; p = p->next; }
    Student **arr = (Student**)malloc((*cnt)*sizeof(Student*));
    p = head;
    for(int i=0; i<*cnt; i++) { arr[i] = p; p = p->next; }
    return arr;
}

// 总分降序快排
static void quickSortTotal(Student **arr, int l, int r) {
    if(l >= r) return;
    int i=l, j=r;
    Student *mid = arr[(l+r)/2];
    while(i<=j) {
        while(arr[i]->total > mid->total) i++;
        while(arr[j]->total < mid->total) j--;
        if(i<=j) {
            Student* tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++; j--;
        }
    }
    quickSortTotal(arr, l, j);
    quickSortTotal(arr, i, r);
}

// 修复：排序后重新串联链表，覆盖全局head
void sortByTotal() {
    if(head == NULL) {
        printf("暂无学生数据，无法排序！\n");
        return;
    }
    int n;
    Student **arr = listToArray(head, &n);
    quickSortTotal(arr, 0, n-1);
    // 重新串联链表，同步到全局head
    head = arr[0];
    for(int i=0; i<n-1; i++) arr[i]->next = arr[i+1];
    arr[n-1]->next = NULL;
    free(arr);
    printf("====已按总分降序完成排序！====\n");
    showAllStudent(); // 排序后自动展示结果
}

// 学号升序快排
static void quickSortId(Student **arr, int l, int r) {
    if(l >= r) return;
    int i=l, j=r;
    Student *mid = arr[(l+r)/2];
    while(i<=j) {
        while(strcmp(arr[i]->id, mid->id) < 0) i++;
        while(strcmp(arr[j]->id, mid->id) > 0) j--;
        if(i<=j) {
            Student* tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++; j--;
        }
    }
    quickSortId(arr, l, j);
    quickSortId(arr, i, r);
}

// 修复：同步更新全局head
void sortById() {
    if(head == NULL) {
        printf("暂无学生数据，无法排序！\n");
        return;
    }
    int n;
    Student **arr = listToArray(head, &n);
    quickSortId(arr, 0, n-1);
    head = arr[0];
    for(int i=0; i<n-1; i++) arr[i]->next = arr[i+1];
    arr[n-1]->next = NULL;
    free(arr);
    printf("====已按学号升序完成排序！====\n");
    showAllStudent();
}