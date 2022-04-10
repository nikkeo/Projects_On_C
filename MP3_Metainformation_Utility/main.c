#include <stdio.h>

int main(int argc, char *argv[]) {

    int str;

    char *mode = argv[3];
    char *filename = argv[2];
    char dp[100];
    int i = 0;

    while (filename[i] != '='){
        i++;
    }
    int q = 0;
    i++;
    while (filename[i] != '.'){
        dp[q++] = filename[i++];
    }
    dp[q++] = '.';
    dp[q++] = 'm';
    dp[q++] = 'p';
    dp[q++] = '3';

    char new[q];

    for (int i = 0; i < q; ++i){
        new[i] = dp[i];
    }

    FILE *fp;

    fp = fopen(new, "r+");

    char ch[4];
    int b = 1;

    int forDP[10];
    //file title
    for (int i = 0; i < 10; ++i){
        str = fgetc(fp);
        forDP[i] = str;
    }

    if (mode[3] == 'h'){
        while (b){
            //frame name
            for (int i = 0; i < 4; ++i) {
                str = fgetc(fp);
                if ((str - '0') < 0){
                    b = 0;
                    break;
                }
                ch[i] = str;
                //printf("%c", str);
            }

            //if frame is bad :/
            if (!b){
                break;
            }

            //printf frame meaning
            if (ch[1] == 'C'){
                printf("Genre:");
            }
            else if (ch[3] == '2'){
                printf("Title:");
            }
            else if(ch[3] == '1'){
                printf("Author:");
            }
            else if(ch[1] == 'A'){
                printf("Album:");
            }
            else{
                for (int i = 0; i < 4; ++i){
                    printf("%c", ch[i]);
                }
            }

            printf("\n");

            //for for counting frame lenght
            int frame_lenght = 0;
            for (int i = 3; i >= 0; --i) {
                str = fgetc(fp);
                int dop = str - '0';
                if (dop < 0){
                    dop *= -1;
                    str = dop + '0';
                    dop = dop - '0';
                }

                if (dop < 0){
                    dop *= -1;
                }

                frame_lenght += dop;
            }

            //flags
            for (int i = 0; i < 2; ++i){
                str = fgetc(fp);
            }

            //working with current frame
            int nfirst = 0;
            for (int i = 0; i < frame_lenght; ++i){

                str = fgetc(fp);

                int num = str - '0';

                if (num > 16 && num < 43 && nfirst){
                    printf(" ");
                }

                if ((num) > 0){
                    printf("%c", str );
                    nfirst = 1;
                }
            }
            printf("\n");
            printf("\n");
        }
    }
    else if(mode[2] == 'g'){
        char Sframe[4];
        Sframe[0] = mode[6];
        Sframe[1] = mode[7];
        Sframe[2] = mode[8];
        Sframe[3] = mode[9];
        int boolPrint = 1;

        while (b){
            //frame name
            for (int i = 0; i < 4; ++i) {
                str = fgetc(fp);
                if ((str - '0') < 0){
                    b = 0;
                    break;
                }
                ch[i] = str;
                //printf("%c", str);
            }

            //if frame is bad :/
            if (!b){
                break;
            }

            //printf frame meaning
            if (ch[0] == Sframe[0] && ch[1] == Sframe[1] && ch[2] == Sframe[2] && ch[3] == Sframe[3]){
                boolPrint = 1;
            }

            //for for counting frame lenght
            int frame_lenght = 0;
            for (int i = 3; i >= 0; --i) {
                str = fgetc(fp);
                int dop = str - '0';
                if (dop < 0){
                    dop *= -1;
                    str = dop + '0';
                    dop = dop - '0';
                }

                if (dop < 0){
                    dop *= -1;
                }

                frame_lenght += dop;
            }

            //flags
            for (int i = 0; i < 2; ++i){
                str = fgetc(fp);
            }

            //working with current frame
            int nfirst = 0;
            for (int i = 0; i < frame_lenght; ++i){

                str = fgetc(fp);
                if (boolPrint){
                    int num = str - '0';

                    if (num > 16 && num < 43 && nfirst){
                        printf(" ");
                    }

                    if ((num) > 0){
                        printf("%c", str );
                        nfirst = 1;
                    }
                    b = 0;
                }
            }
        }
    }
    else{

        FILE *dop;

        dop = fopen("dop.mp3", "w");

        for (int i = 0; i < 10; ++i){
            fputc(forDP[i], dop);
        }

        char Sframe[4];
        char *Getnewvalue = argv[4];
        char newValue[50];
        char *NotCuttedNewValue;
        Sframe[0] = mode[6];
        Sframe[1] = mode[7];
        Sframe[2] = mode[8];
        Sframe[3] = mode[9];
        int boolPrint = 0;
        int cnt = 0;

        int i = 0;
        cnt = 0;
        while (Getnewvalue[i] != '\0'){
            if (boolPrint){
                newValue[cnt++] = Getnewvalue[i];
            }
            if (Getnewvalue[i] == '='){
                boolPrint = 1;
            }
            i++;
        }
        char newValueTrue[cnt];
        for (int i = 0; i < cnt; ++i){
            newValueTrue[i] = newValue[i];
        }
        char newer[cnt];
        for (int i = 0; i < cnt; ++i){
            newer[i] = newValueTrue[i];
        }

        boolPrint = 0;
        while (b){
            //frame name
            for (int i = 0; i < 4; ++i) {
                str = fgetc(fp);
                fputc(str, dop);
                if ((str - '0') < 0){
                    b = 0;
                    break;
                }
                ch[i] = str;
                //printf("%c", str);
            }

            if (ch[0] == Sframe[0] && ch[1] == Sframe[1] && ch[2] == Sframe[2] && ch[3] == Sframe[3]){
                boolPrint = 1;
            }

            //if frame is bad :/
            if (!b){
                break;
            }


            //for for counting frame lenght
            int frame_lenght = 0;
            for (int i = 3; i >= 0; --i) {
                str = fgetc(fp);
                fputc(str, dop);
                int dop = str - '0';
                if (dop < 0){
                    dop *= -1;
                    str = dop + '0';
                    dop = dop - '0';
                }

                if (dop < 0){
                    dop *= -1;
                }

                frame_lenght += dop;
            }

            //flags
            for (int i = 0; i < 2; ++i){
                str = fgetc(fp);
                fputc(str, dop);
            }

            //working with current frame
            if (boolPrint){
                for (int i = 0; i < sizeof(newer); ++i){
                    fputc(newer[i], dop);
                }
                for (int i = 0; i < frame_lenght; ++i){

                    str = fgetc(fp);
                }
                boolPrint = 0;
            }
            else{
                for (int i = 0; i < frame_lenght; ++i){

                    str = fgetc(fp);
                    fputc(str, dop);
                }
            }
        }

        while((str = fgetc(fp)) != EOF){
            fputc(str, dop);
        }
        fclose(dop);
        fclose(fp);

        dop = fopen("dop.mp3", "r");
        fp = fopen(new, "w");

        while ((str = fgetc(dop)) != EOF){
            fputc(str, fp);
        }
    }
    return 0;
}
