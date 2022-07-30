#include "s21_cat.h"

int main(int argc, char *argv[]) {
    flag.b = flag.e = flag.s = flag.n = flag.t = flag.T = flag.E = flag.v = 0;
    flages(argc, argv);
    s21_cat(argc, argv);
    return 0;
    }

void flages(int argc, char *argv[]) {
    int option_index = 0;
    const char* short_options = "benstETv";
    const struct option long_options[] = {
        {"number-nonblanck", 0, NULL, 'b'},
        {"show-ends", 0, NULL, 'e'},
        {"number", 0, NULL, 'n'},
        {"squeeze-blank", 0, NULL, 's'},
        {"show-tabs", 0, NULL, 't'},
        {NULL, 0, NULL, 0}
    };
    int rez = 0;
    //  передает длинные и короткие параметры
    while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (rez) {
            //  нумерует только непустые строки
            case 'b' : {
                flag.b = 1;
                break;
            }
            //  также отображает символы конца строки как $ с -v
            case 'e' : {
                flag.e = 1;
                flag.v = 1;
                break;
            };
            //  сжимает несколько смежных пустых строк
            case 's' : {
                flag.s = 1;
                break;
            };
            //  нумерует все выходные строки
            case 'n' : {
                flag.n = 1;
                break;
            }
            //  также отображает табы как ^I с -v
            case 't' : {
                flag.t = 1;
                flag.v = 1;
                break;
            }
            //  также отображает символы конца строки как $ но без -v
            case 'E' : {
                flag.E = 1;
                break;
            }
            //  также отображает табы как ^I но без -v
            case 'T' : {
                flag.T = 1;
                break;
            }
            default : printf("ERROR");
        }
    }
}

void s21_cat(int argc, char *argv[]) {
    // printf("%d\n", optind);
    FILE *smt_out_there;
    for (int i = optind; i < argc; i++) {
        if ((smt_out_there = fopen(argv[i], "r")) != NULL) {
            int schetchik = 1;
            int szhimatel_strok_3000 = 0;
            char stroka[4096] = "";
            while (fgets(stroka, 4095, smt_out_there) != NULL) {
                char where[4096] = "";
                if (flag.v == 1) {
                    int count_w = 0;
                    int count_w_f = 0;
                    for (; stroka[count_w_f] != 0 && stroka[count_w_f] != '\n'; count_w_f++) {
                        if ((stroka[count_w_f] >= 1) && (stroka[count_w_f] <= 31)
                            && (stroka[count_w_f] != 9) && (stroka[count_w_f] != 10)) {
                            where[count_w] = '^';
                            count_w++;
                            where[count_w] = stroka[count_w_f] + 64;
                        } else if (stroka[count_w_f] == 127) {
                            where[count_w] = '^';
                            count_w++;
                            where[count_w] = stroka[count_w_f] - 64;
                        } else if (((unsigned char)stroka[count_w_f] <= 160) &&
                                    ((unsigned char)stroka[count_w_f] > 127)) {
                            where[count_w] = 'M';
                            count_w++;
                            where[count_w] = stroka[count_w_f] - 64;
                        } else if ((unsigned char)stroka[count_w_f] > 160) {
                            where[count_w] = '^';
                            count_w++;
                            where[count_w] = '@';
                        } else {
                            where[count_w] = stroka[count_w_f];
                        }
                        count_w++;
                    }
                    // printf("%s", where);
                    where[count_w] = stroka[count_w_f];
                    strcpy(stroka, where);
                }
                if (flag.b == 1) {
                    if (stroka[0] != '\n') {
                        printf("%6d\t%s", schetchik, stroka);
                        schetchik++;
                    } else if (stroka[0] == '\n') {
                        printf("%s", stroka);
                    }
                } else if (flag.n == 1) {
                    printf("%6d\t%s", schetchik, stroka);
                    schetchik++;
                }
                if (flag.e == 1 || flag.E == 1) {
                    for (int schet_q = 0; stroka[schet_q] != 0; schet_q++) {
                        if (stroka[schet_q] == '\n') {
                            stroka[schet_q] = '$';
                            schet_q++;
                            stroka[schet_q] = '\n';
                            break;
                        }
                    }
                    printf("%s", stroka);
                }
                if (flag.s == 1) {
                    if (stroka[0] == '\n' && szhimatel_strok_3000 == 0) {
                        printf("%s", stroka);
                        szhimatel_strok_3000 = 1;
                    } else if (stroka[0] != '\n') {
                        printf("%s", stroka);
                        szhimatel_strok_3000 = 0;
                    }
                }
                if (flag.t == 1 || flag.T == 1) {
                    char str_baha[4096] = "";
                    int k = 0;
                    for (int schetchik_t = 0; stroka[schetchik_t] != '\n'
                        && stroka[schetchik_t] != '\0'; schetchik_t++) {
                        if (stroka[schetchik_t] == '\t') {
                            str_baha[k] = '^';
                            k++;
                            str_baha[k] = 'I';
                        } else {
                            str_baha[k] = stroka[schetchik_t];
                        }
                        k++;
                    }
                    strcpy(stroka, str_baha);
                    printf("%s\n", stroka);
                }
                if ((flag.b == 0) && (flag.e == 0) && (flag.s == 0) && (flag.n == 0)
                    && (flag.t == 0) && (flag.E == 0) && (flag.T == 0) && (flag.v == 0)) {
                    printf("%s", stroka);
                }
                memset(stroka, 0, 4096);
            }
            fclose(smt_out_there);
        } else {
            printf("%s: %s: Cannot open file.\n", argv[0], argv[i]);
        }
    }
}
