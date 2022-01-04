#include<stdio.h>
#include <string.h>
int estla(char *str, char *search)
{
    int count1 = 0, count2 = 0, i, j, flag;
    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    if (flag == 1)
        return 1;
    else
        return 0;
}

int main(void)
{
    char str[80], search[10];
    printf("Enter a string:");
    gets(str);
    printf("Enter search substring:");
    gets(search);
    if(estla(str, search))
        printf("test");
    return 0;
}