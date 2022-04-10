#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>



//file size
int64_t getFileSize(const char* file_name){
    int64_t _file_size = 0;
    FILE* fd = fopen(file_name, "rb");
    if(fd == NULL){
        _file_size = -1;
    }
    else{
        fseek(fd, 0, SEEK_END);
        _file_size = ftello(fd);
        fclose(fd);
    }
    return _file_size;
}


//creates new cut string
char* slice(char*s, int from, int to)
{
    int j = 0;
    for(int i = from; i <= to; ++i)
        s[j++] = s[i];
    s[j] = 0;
    return s;
};


//reversing the string
char* reverse(char s[])
{
    int i, j;
    char *newString;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        newString = s[i];
    }

    return newString;
}


//int to str
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



// This program works with ZIP files
int main(int argc, char *argv[]) {

    FILE *fp, *fout;

    // zip files into ARC file
    if (argv[4][2] == 'c'){
        fout = fopen(argv[3], "w");

        int lenght = strlen(argv) - 3;

        int copy;
        char *filenames[lenght];
        for (int i = 5; i < sizeof(argv); ++i){
            filenames[i - 5] = argv[i];
        }

        copy = lenght;

        while (lenght > 0){
            fputc(lenght%10 + '0', fout);
            lenght /= 10;
        }

        lenght = copy;

        for (int i = 0; i < lenght; ++i){
            fp = fopen(filenames[i], "r");

            int curfilelenght, copy;
            curfilelenght = getFileSize(filenames[i]);
            copy = curfilelenght;

            fputc('\n', fout);

            for (int j = 0; j < strlen(filenames[i]); ++j){
                fputc(filenames[i][j], fout);
            }

            fputc(' ', fout);

            while (curfilelenght > 0){
                fputc(((curfilelenght % 10) + '0'), fout);
                curfilelenght /= 10;
            }
            curfilelenght = copy;
            char ch;

            fputc('\n', fout);

            for (int i = 0; i < curfilelenght; ++i){
                ch = fgetc(fp);
                fputc(ch, fout);
            }

            fclose(fp);
        }

        fclose(fout);
    }


    //unzipping files from ARC file
    if (argv[4][2] == 'e'){
        fp = fopen(argv[3], "rh");

        unsigned char ch;

        int cntFiles = 0;
        ch = fgetc(fp);
        while (ch != '\n'){
            cntFiles *= 10;
            cntFiles += (ch - '0');
            ch = fgetc(fp);
        }

        for (int i = 0; i < cntFiles; ++i){
            int cnt = 0;
            char *filename;

            while (ch != ' '){
                if (ch != ' ' && ch != '\n'){
                    filename[cnt++] = ch;
                }
                ch = fgetc(fp);
            }
            fout = fopen(slice(filename, 0, cnt - 1), "w");

            int dop = 1;
            int filelenght = 0;

            while (ch != '\n'){
                ch = fgetc(fp);
                if (ch != '\n'){
                    filelenght += ((ch - '0') * dop);
                    dop *= 10;
                }
            }

            for (int j = 0; j < filelenght; ++j){
                fputc(fgetc(fp), fout);
            }
            fclose(fout);
        }
    }


    //showing list of files which are in ARC file
    if (argv[4][2] == 'l'){
        fp = fopen(argv[3], "rh");

        unsigned char ch;

        int cntFiles = 0;
        ch = fgetc(fp);
        while (ch != '\n'){
            cntFiles *= 10;
            cntFiles += (ch - '0');
            ch = fgetc(fp);
        }
        unsigned char *filename;

        for (int i = 0; i < cntFiles; ++i){
            int cnt = 0;

            while (ch != ' '){
                if (ch != ' ' && ch != '\n'){
                    filename[cnt++] = ch;
                }
                ch = fgetc(fp);
            }
            printf("%s\n", slice(filename, 0, cnt - 1));

            int dop = 1;
            int filelenght = 0;

            while (ch != '\n'){
                ch = fgetc(fp);
                if (ch != '\n'){
                    filelenght += ((ch - '0') * dop);
                    dop *= 10;
                }
            }

            for (int j = 0; j < filelenght; ++j){
                fgetc(fp);
            }
        }
    }

    return 0;
}
