#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
}flag;

void s21_grep(int argc, char *argv[]);

#endif // SRC_S21_GREP_H_