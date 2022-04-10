#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
{
    uint32_t *number;
}uint1024_t;


uint1024_t UintCreation(int num){
    uint1024_t newEl;
    newEl.number = (uint32_t *)malloc(32*sizeof(uint32_t));

    for (int i = 1; i < 32; i++)
    {
        newEl.number[i] = 0;
    }
    newEl.number[0] = num;

    return newEl;
}


uint32_t UintCharTransformation(char ch){
    if (ch > 'A' && ch < 'F'){
        return ch - 'a' + 10;
    }
    return ch - '0';
}


uint1024_t HexToUint(char *ch)
{
    int len = strlen(ch);
    uint1024_t newOne = UintCreation(0);
    int parts = len / 8;
    int remain = len % 8;
    int startLocation = len - 1;

    for(int i=0; i < parts; i++)
    {
        uint32_t num = 0;
        for(int j = 0; j < 8; j++)
            num = num | (UintCharTransformation(ch[startLocation - j])<<(j * 4));
        newOne.number[i] = num;
        startLocation = len - i*8 - 9;
    }

    uint32_t num = 0;
    for(int i = 0; i <remain; i ++)
        num = num | (UintCharTransformation(ch[startLocation - i])<<(i * 4));
    newOne.number[parts - 1] = num;


    return newOne;
}


char* UintToHex(uint1024_t cur)
{
    char *res = malloc(257*sizeof(char));
    res[0] = '0';
    res[1] = '\0';
    char hexStr[16] = "0123456789abcdef";
    int cnt=31;

    for(cnt; cnt>=0 && cur.number[cnt]==0; cnt--);

    int position = 0;
    for(cnt; cnt>=0; cnt--)
    {
        uint32_t num = cur.number[cnt];
        for(int i=0; i<8; i++){
            int val = num>>(4*i);
            res[position+7-i] = hexStr[val & 15];
        }
        position += 8;
    }
    res[position] = '\0';

    return res;
}


uint1024_t UintSub(uint1024_t x, uint1024_t y)
{
    uint1024_t newOne;
    newOne.number = (uint32_t *)malloc(32*sizeof(uint32_t));
    newOne.number[0] = abs(x.number[0] - y.number[0]);

    for(int i=1; i<32; i++)
    {
        newOne.number[i] = abs(x.number[i] - y.number[i]);
        if(newOne.number[i-1] > x.number[i-1])
            newOne.number[i]--;
    }

    return newOne;
}


uint1024_t UintAdd(uint1024_t x, uint1024_t y)
{
    uint1024_t newOne;
    newOne.number = (uint32_t *)malloc(32*sizeof(uint32_t));
    newOne.number[0] = x.number[0] + y.number[0];

    for(int i=1; i<32; i++)
    {
        newOne.number[i] = x.number[i] + y.number[i];
        if(newOne.number[i-1] < x.number[i-1])
            newOne.number[i]++;
    }

    return newOne;
}


uint1024_t UintMul(uint1024_t x, uint1024_t y)
{
    uint1024_t newOnew;
    newOnew.number = (uint32_t *)malloc(32*sizeof(uint32_t));

    uint64_t hight[32];
    uint64_t down[32];
    uint64_t final[32][32];

    for(int i=0; i<32; i++)
    {
        hight[31-i] = (uint64_t)x.number[i];
        down[31-i] = (uint64_t)y.number[i];
    }

    for(int i=31; i>-1; i--)
    {
        for(int j=31; j>-1; j--)
        {
            final[31-j][i] = hight[j] * down[i];
        }
    }

    uint64_t results[32] = {0};
    for(int i=0; i<32; i++)
    {
        results[i] += (final[i][31] & 0xffffffff);
        for(int j=30; j>=i; j--)
        {
            results[i+31-j] += (final[i][j] & 0xffffffff) + (final[i][j+1] >> 32);
        }
    }

    for(int i=1; i<32; i++)
        results[i]  += results[i-1] >> 32;

    for(int i=0; i<32; i++)
    {
        results[i]  &= 0xffffffff;
        newOnew.number[i] = results[i];
    }

    return newOnew;
}


void UintPrint(uint1024_t num){
    for (int i = 1; i < 32; ++i){
        if (num.number[31 - i - 1] != num.number[31 - i])
            printf("%u", num.number[31 - i]);
    }
}


void UintTest(uint1024_t x, uint1024_t y){
    printf("FIRST ONE IS ZIRO - CONST:\n");
    printf("first number:\n");
    UintPrint(x);
    printf("\nsecond number:\n");
    UintPrint(y);
    printf("\nfirst + second:\n");
    UintPrint(UintAdd(x, y));
    printf("\nfirst - second:\n");
    printf("NOT WORKING IF X < Y\n");
    UintPrint(UintSub(x, y));
    printf("\nfirst * second:\n");
    UintPrint(UintMul(x, y));
}



int main() {

    int x, y;
    scanf("%d %d", &x, &y);

    uint1024_t tx = UintCreation(x);
    uint1024_t ty = UintCreation(y);

    UintTest(tx, ty);

    return 0;
}
