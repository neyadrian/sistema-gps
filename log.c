#include <stdio.h>
#include <time.h>
#include "log.h"

void registrarLog(const char *mensagem) {
    FILE *file = fopen("logs.txt", "a"); 
    if (file == NULL) return;

    time_t agora = time(NULL); //define o tempo
    struct tm *t = localtime(&agora);//tempo local

    fprintf(file, "[%02d/%02d/%04d %02d:%02d:%02d] %s\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec,mensagem);

    fclose(file);
}