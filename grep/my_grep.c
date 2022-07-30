#include "my_grep.h"

int main(int argc, char *argv[]) {
    flag.e = flag.i = flag.v = flag.c = flag.l = flag.n = flag.h = flag.s = flag.f = flag.o = 0;
    my_grep(argc, argv);
    return 0;
}

void my_grep(int argc, char *argv[]) {
    const char* short_options = "eivclnhsfo";
    struct option long_options[] = {
        {"--exclude", 0, NULL, 'e'},
        {"--ignore-case", 0, NULL, 'i'},
        {"--invert-match", 0, NULL, 'v'},
        {"--count", 0, NULL, 'c'},
        {"--files-with-matches", 0, NULL, 'l'},
        {"--line-number", 0, NULL, 'n'},
        {NULL, 0, NULL, 0}
    };
    int regflag = 0;
    //  передает длинные и короткие параметры
    while ((regflag = getopt_long(argc, argv, short_options, long_options, &optind)) != -1) {
        switch (regflag) {
            case 'e' : {
                flag.e = 1;
                break;
            }
            case 'i' : {
                flag.i = 1;
                break;
            };
            case 'v' : {
                flag.v = 1;
                break;
            };
            case 'c' : {
                flag.c = 1;
                break;
            }
            case 'l' : {
                flag.l = 1;
                break;
            }
            case 'n' : {
                flag.n = 1;
                break;
            }
            case 'h' : {
                flag.h = 1;
                break;
            }
            case 's' : {
                flag.s = 1;
                break;
            }
            case 'f' : {
                flag.f = 1;
                break;
            }
            case 'o' : {
                flag.o = 1;
                break;
            }
            default : printf("ERROR");
        }
    }
    FILE *smt_out_there;
    regex_t regex;
    //  ищет рег выраж в строке 0 - успех, REG_NOMATCH - провал
    int success;
    //  переменная для регкомпа (REG_ICASE / REG_NOBUS ... etc.)
    char cflag = REG_EXTENDED;
    if (flag.i) cflag = REG_ICASE;
    //  счетчик строк в флаге н
    int count_num = 0;
    //  указатель на строку из файла
    char where_we_record[8192] = "";
    //  переменные для флага о
    int size, search, search_index = 0;
    for (int i = optind + 1; i < argc; i++) {
        count_num = 0;
        if ((smt_out_there = fopen(argv[i], "r")) != NULL) {
            //  компилирует рег выраж 0 - успех, 1 - провал
            // получает регулярные выражения из файла
            if (flag.f) {
                FILE *temporary_file;
                //  ищет рег выраж в строке 0 - успех, REG_NOMATCH - провал
                int successes = 0;
                //  здесь хранится рег выражение из файла
                char record_temporary[8192] = "";
                while ((fgets(where_we_record, 8191, smt_out_there)) != NULL) {
                    if ((temporary_file = fopen(argv[optind], "r")) != NULL) {
                        while ((fgets(record_temporary, 8191, temporary_file)) != NULL) {
                            regex_t reg;
                            if (record_temporary[strlen(record_temporary) - 1] == '\n')
                                record_temporary[strlen(record_temporary) - 1] = 0;
                            int var_f = regcomp(&reg, record_temporary, cflag);
                            if (var_f == 0) {
                                successes = regexec(&reg, where_we_record, 0, NULL, 0);
                                if (successes == 0) {
                                    if ((argc - optind - 1) != 1) {
                                        printf("%s:%s", argv[i], where_we_record);
                                        regfree(&reg);
                                        break;
                                    } else {
                                        printf("%s", where_we_record);
                                        regfree(&reg);
                                        break;
                                    }
                                }
                            }
                            regfree(&reg);
                        }
                        fclose(temporary_file);
                    } else {
                        printf("No such file or directory");
                    }
                }
            }
            int var_main = regcomp(&regex, argv[optind], cflag);
            if (var_main == 0) {
                int count_c = 0;
                //  берет строку
                while (fgets(where_we_record, 8191, smt_out_there) != NULL) {
                    //  ищет рег выраж в строке 0 - успех, REG_NOMATCH - провал
                    success = regexec(&regex, where_we_record, 0, NULL, 0);
                    if ((flag.e == 0) && (flag.i == 0) && (flag.v == 0) && (flag.c == 0)
                        && (flag.l == 0) && (flag.n == 0) && (flag.h == 0) && (flag.s == 0)
                        && (flag.f == 0) && (flag.o == 0)) {
                            if (success == 0) {
                                if ((argc - optind - 1) != 1) {
                                    printf("%s:%s", argv[i], where_we_record);
                                } else {
                                    printf("%s", where_we_record);
                                }
                            }
                    }
                    //  игнорирует различия регистра
                    if (flag.i) {
                        if (success == 0) {
                            if ((argc - optind - 1) != 1) {
                                printf("%s:%s", argv[i], where_we_record);
                            } else {
                                printf("%s", where_we_record);
                            }
                        }
                    }
                    //  шаблон / выводит только количество совпажающих строк
                    if (flag.e || flag.s) {
                        if (success == 0 && (flag.e || flag.s)) {
                            if ((argc - optind - 1) != 1) {
                                printf("%s:%s", argv[i], where_we_record);
                            } else {
                                printf("%s", where_we_record);
                            }
                        }
                    }
                    if (flag.c) {
                        if (success == 0) {
                            count_c++;
                        }
                    }
                    //  Инвертирует смысл поиска соответствий.
                    if (flag.v) {
                        if (success != 0) {
                            if ((argc - optind - 1) != 1) {
                                printf("%s:%s", argv[i], where_we_record);
                            } else {
                                printf("%s", where_we_record);
                            }
                        }
                    }
                    //  Выводит только совпадающие файлы.
                    if (flag.l) {
                            if (success == var_main) {
                                    printf("%s\n", argv[i]);
                                    break;
                            }
                    }
                    //  Предваряет каждую строку вывода номером строки из файла ввода.
                    if (flag.n) {
                        count_num++;
                        if (((argc - optind - 1) != 1) && (success == 0)) {
                            printf("%s:%d:%s", argv[i], count_num, where_we_record);
                        } else if (success == 0) {
                            printf("%d:%s", count_num, where_we_record);
                        }
                    }
                    //  выводит совпадающие строки, не предваряя их именами файлов
                    if (flag.h) {
                        if (success == 0) {
                                printf("%s", where_we_record);
                        }
                    }
                    //  печатает только совпадающие (непустые) части совпавшей строки
                    if (flag.o) {
                        regmatch_t array[2];
                        int reg_expres = 0;
                        // printf("")
                        while ((reg_expres = regexec(&regex, where_we_record + search_index, 2,
                                array, 0)) == 0) {
                            //  находим длинну шаблона
                            size = array[0].rm_eo - array[0].rm_so;
                            //  расстояние от начала строки до первого вхождения шаблона
                            search = array[0].rm_so + search_index;
                            //  длинна от начальной позиции в строке, до конца првого вхождения шаблона
                            search_index = size + search;
                            if ((argc - optind - 1) != 1) {
                                printf("%s:%.*s\n", argv[i], size, where_we_record + search);
                            } else {
                                printf("%.*s", size, where_we_record + search);
                            }
                        }
                        search_index = 0;
                    }
                }
                if (flag.c) {
                    if ((argc - optind - 1) != 1) {
                        printf("%s:%d\n", argv[i], count_c);
                    } else {
                        printf("%d\n", count_c);
                    }
                }
            }
            regfree(&regex);
            fclose(smt_out_there);
            //  подавляет сообщения об ошибках о несуществующих или нечитаемых файлах
        } else if (!flag.s) {
            if ((argc - optind - 1) != 1) {
                printf("%s:No such file or directory", argv[i]);
            } else {
                printf("No such file or directory");
            }
        }
    }
}
