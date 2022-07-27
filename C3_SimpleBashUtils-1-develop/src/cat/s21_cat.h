#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

struct flags {
    int b;
    int e;
    int s;
    int t;
    int n;
    int E;
    int T;
    int v;
}flag;

void flages(int argc, char *argv[]);
void s21_cat(int argc, char *argv[]);

#endif // SRC_S21_CAT_H_