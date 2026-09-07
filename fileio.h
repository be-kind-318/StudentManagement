#ifndef FILEIO_H
#define FILEIO_H

#include "student.h"
#include <stdio.h>

/**
 * @brief 将全局学生链表数据持久化写入 data/student.txt
 * @return 保存成功返回1；文件打开失败返回0
 */
int saveStudents();

/**
 * @brief 程序启动时从 data/student.txt 读取数据加载至全局链表
 * @return 读取到数据返回1；文件不存在/读取失败返回0
 */
int loadStudents();

#endif