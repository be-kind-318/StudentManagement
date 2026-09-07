#ifndef QUERY_H
#define QUERY_H
#include "student.h"

void queryById(char *id);
void queryByName(char *name);
void queryByClass(char *cls);
void queryByScoreRange(float min, float max);

#endif