#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main(int argc, char *argv[]) {

    FILE *fp, *fout;

    int max_generation = -1;
    int cur_generation = 0;
    int frequence = 1;
    int current_frequence = 1;
    char width[4];
    char height[4];
    char *outputDIR;

    for (int i = 1; i < ((argc)); i += 2){
        if (argv[i][2] == 'i'){
            fp = fopen(argv[i + 1], "r");
        }
        else if(argv[i][2] == 'o'){
            outputDIR = argv[i + 1];
        }
        else if(argv[i][2] == 'm'){
            max_generation = atoi(argv[i + 1]);
        }
        else{
            frequence = atoi(argv[i + 1]);
        }
    }

    char directory[strlen(outputDIR)];

    for (int i = 0; i < strlen(outputDIR); ++i){
        directory[i] = outputDIR[i];
    }
    strcat(directory, "/");

    char ch;
    char data[54];

    for (int i = 0; i < 14; ++i){
        ch = fgetc(fp);
        data[i] = ch;
    }
    for (int i = 0; i < 40; ++i){
        ch = fgetc(fp);
        data[i + 14];

        if (i == 4){
            width[3] = ch;
        }
        if (i == 5){
            width[2] = ch;
        }
        if (i == 6){
            width[1] = ch;
        }
        if (i == 7){
            width[0] = ch;
        }
        if (i == 8){
            height[3] = ch;
        }
        if (i == 9){
            height[2] = ch;
        }
        if (i == 10){
            height[1] = ch;
        }
        if (i == 11){
            height[0] = ch;
        }
    }

    int widthh = ((width[0] * 256 + width[1]) * 256 + width[2]) * 256 + width[3];
    int hightt = ((height[0] * 256 + height[1]) * 256 + height[2]) * 256 + height[3];

    char arr[hightt][widthh];
    char cur_arr[hightt][widthh];
    char ChForZero, ChForOne;

    for (int i = 0; i < hightt; ++i){
        for (int u = 0; u < widthh; ++u){
            ch = fgetc(fp);
            int num = ch - '0';
            num *= -1;

            if (num == 48){
                ChForZero = ch;
                arr[i][u] = 0;
                cur_arr[i][u] = 0;
                //printf("%d", 0);
            }
            else{
                ChForOne = ch;
                arr[i][u] = 1;
                cur_arr[i][u] = 1;
                //printf("%d", 1);
            }
        }
        //printf("\n");
    }

    int cur_cnt = 0;
    int cnt = 1;

    printf("\n\n");

    while (1){
        for (int j = 0; j < widthh; ++j){
            cur_cnt = 0;

            if (j == 0){
                if (arr[0][j + 1] == 1){
                    cur_cnt++;
                }
                if (arr[1][j] == 1){
                    cur_cnt++;
                }
                if (arr[1][j + 1] == 1){
                    cur_cnt++;
                }
            }
            else if (j == (widthh - 1)){
                if (arr[0][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[1][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[1][j] == 1){
                    cur_cnt++;
                }
            }
            else{
                if (arr[0][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[0][j + 1] == 1){
                    cur_cnt++;
                }
                if (arr[1][j] == 1){
                    cur_cnt++;
                }
                if (arr[1][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[1][j + 1] == 1){
                    cur_cnt++;
                }
            }

            if (cur_cnt == 3){
                cur_arr[0][j] = 1;
            }
            else if(cur_cnt != 2){
                cur_arr[0][j] = 0;
            }

        }

        for (int i = 1; i < (hightt - 1); ++i){
            for (int j = 0; j < widthh; j++){
                cur_cnt = 0;

                if (j == 0){
                    if (arr[i][j + 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j + 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j + 1] == 1){
                        cur_cnt++;
                    }
                }

                else if (j == (widthh - 1)){
                    if (arr[i][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j] == 1){
                        cur_cnt++;
                    }
                }

                else{
                    if (arr[i][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i][j + 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i + 1][j + 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j - 1] == 1){
                        cur_cnt++;
                    }
                    if (arr[i - 1][j + 1] == 1){
                        cur_cnt++;
                    }
                }

                if (cur_cnt == 3){
                    cur_arr[i][j] = 1;
                }
                else if(cur_cnt != 2){
                    cur_arr[i][j] = 0;
                }
            }
        }

        for (int j = 0; j < widthh; ++j){
            cur_cnt = 0;

            if (j == 0){
                if (arr[(widthh - 1)][j + 1] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j + 1] == 1){
                    cur_cnt++;
                }
            }
            else if (j == (widthh - 1)){
                if (arr[(widthh - 1)][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j - 1] == 1){
                    cur_cnt++;
                }
            }
            else{
                if (arr[(widthh - 1)][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 1)][j + 1] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j - 1] == 1){
                    cur_cnt++;
                }
                if (arr[(widthh - 2)][j + 1] == 1){
                    cur_cnt++;
                }
            }
            if (cur_cnt == 3){
                cur_arr[widthh - 1][j] = 1;
            }
            else if(cur_cnt != 2){
                cur_arr[widthh - 1][j] = 0;
            }
        }

        if (max_generation != -1){
            cur_generation++;
            if (cur_generation > max_generation){
                break;
            }
        }

        if (current_frequence == frequence){
            char current_directory[strlen(directory)];
            strcpy(current_directory, directory);
            char dop[1000];
            itoa(cnt, dop);
            strcat(current_directory, dop);
            strcat(current_directory, ".bmp");

            printf("%s\n", current_directory);
            fout = fopen(current_directory, "w");
            //fputc(1, fout);
//            for (int i = 0; i < 54; ++i){
//                fputc(data[i], fout);
//            }

            for (int i = 0; i < hightt; ++i){
                for (int j = 0; j < widthh; ++j){
                    arr[i][j] = cur_arr[i][j];
                    if (arr[i][j] == 0){
                        //printf("%c", (254 + '0'));
                    }
                    else{
                        //printf("%c", (255 + '0'));
                    }
                }
                //printf("\n");
            }
            cnt++;
            //printf("\n\n\n");
            current_frequence = 1;
            fclose(fout);
        }
        else{

            for (int i = 0; i < hightt; ++i){
                for (int j = 0; j < widthh; ++j){
                    arr[i][j] = cur_arr[i][j];
                }
            }

            current_frequence++;
        }
    }

    return 0;
}
