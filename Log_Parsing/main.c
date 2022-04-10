#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct TimeElement {
    int time;
    int index;
    struct TimeElement* prev;
    struct TimeElement* next;
} TimeElement;
typedef struct {
    TimeElement* first;
    TimeElement* last;
} TimeList;

void push(TimeList* timeList, int timeValue, int index)
{
    TimeElement* elementToPush = (TimeElement*)malloc(sizeof(TimeElement));
    elementToPush->time = timeValue;
    elementToPush->index = index;
    elementToPush->prev = NULL;
    elementToPush->next = NULL;
    if (timeList->first == NULL)
        timeList->last = elementToPush;
    else
    {
        elementToPush->next = timeList->first;
        timeList->first->prev = elementToPush;
    }
    timeList->first = elementToPush;
}

void popTail(TimeList* timeList)
{
    TimeElement* elementToPop = timeList->last;
    if (elementToPop != NULL)
    {
        if (elementToPop->prev != NULL)
        {
            timeList->last = elementToPop->prev;
            timeList->last->next = NULL;
        }
        else
        {
            timeList->first = NULL;
            timeList->last = NULL;
        }
        free(elementToPop);
    }
}

int count(TimeList* timeList){
    TimeElement* tour = timeList->first;
    int cnt = tour->index;

    while (tour != timeList->last){
        tour = tour->next;
        cnt += tour->index;
    }

    return cnt;
}

int main(){

    FILE *fp;

    TimeList queue = { NULL, NULL };

    printf("Time window u wanna check (in seconds, limit: 1000000 seconds):\n");
    char Mode[1000000];
    scanf("%s", Mode);
    int mode = atoi(Mode);

    printf("Do u prefer to check errors (type 'NO' or 'YES'):\n");
    char cha[3];
    int n;
    scanf("%s", cha);
    if (cha[0] == 'Y'){
        n = 1;
    }
    else{
        n = 0;
    }


    char ch[200];
    int ERROr = 0;
    int currentTime = 0, currentSaver = 0, prevousTime = 0, curMode = 1, maxi = 0;

    fp = fopen("NASA_access_log_Jul95", "r");
    //1 is a FILE using for simple tests :)
    //fp = fopen("1", "r");

    int cnt = 0;
    while(fgets(ch, 200, fp)){

        //FOR TIME COUNTING
        int i = 0;

        while ((ch[i] != '[')){
            if (i > 100){
                break;
            }
            i++;
        }
        if (ch[i] == '['){
            i++;
            currentTime = (ch[i] - '0') * 10 * 86400;
            i++;
            currentTime += (ch[i] - '0') * 86400;

            while ((ch[i] != ':')){
                i++;
            }
            i++;

            currentTime += (ch[i] - '0') * 10 * 3600;
            i++;
            currentTime += (ch[i] - '0') * 3600;
            i++;

            i++;
            currentTime += (ch[i] - '0') * 10 * 60;
            i++;
            currentTime += (ch[i] - '0') * 60;
            i++;

            i++;
            currentTime += (ch[i] - '0') * 10;
            i++;
            currentTime += (ch[i] - '0');
            i++;
        }

        if (currentTime != prevousTime){
            currentSaver++;

            push(&queue, currentTime, currentSaver);

            if (curMode != mode){
                curMode++;
            }
            else{
                if (count(&queue) > maxi){
                    maxi = count(&queue);
                }
                popTail(&queue);
            }

            prevousTime = currentTime;
            currentSaver = 0;
        }
        else{
            currentSaver++;
        }


        // FOR ERRORS
        int j = 0;
        while (ch[j] != '\0'){
            j++;
        }
        while (j > 0 && ch[j] != ' '){
            j--;
        }
        if ((ch[j - 3] - '0') == 5){
            ERROr++;
            if (n == 1){
                printf("%s\n", ch);
            }
        }
    }

    printf("Number of Errors:\n%d\n", ERROr);


    printf("Maximum of requests:\n%d", maxi);
    fclose(fp);
}


