#ifndef MY_CAT_H_
#define MY_CAT_H_

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
void my_cat(int argc, char *argv[]);

#endif // MY_CAT_H_