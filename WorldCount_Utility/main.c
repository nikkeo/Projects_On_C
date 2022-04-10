#include <stdio.h>
#include <stdlib.h>

int finder(const char *strig, char ch){
    int i = 0;
    while (strig[i] != '\0'){
        if (strig[i] == ch){
            return 1;
        }
        ++i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int ch;
    int sumforlines = 0, sumforbytes = 0, sumforwords = 0;
    char *str = argv[1];
    char *filename = argv[2];
    int bool = 0, cnt = 0;

    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("File is not opening");
        exit(EXIT_FAILURE);
    }

    while((ch=fgetc(fp)) != EOF) {
        sumforbytes++;
        if (sumforlines == 0){
            sumforlines++;
        }

        if (bool){
            sumforlines++;
            bool = 0;
        }

        if ((ch == ' ')){
            if (cnt){
                sumforwords++;
            }
            cnt = 0;
        }
        else{
            if (ch == '\n'){
                bool = 1;
                if (cnt){
                    sumforwords++;
                }
                cnt = 0;
            }
            else{
                cnt = 1;
            }
        }
    }

    if (cnt){
        sumforwords++;
    }

    if (finder(str, 'l')){
        printf("%d\t", sumforlines);
    }
    if((finder(str, 'c')) || (finder(str, 'b'))){
        printf("%d\t", sumforbytes);
    }
    if((finder(str, 'w'))){
        printf("%d\t", sumforwords);
    }
    return 0;
}
