#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[26]={0};

    FILE *fp=fopen("facebook.txt","r");
    char c;
    int i;
    
    while((c=fgetc(fp)) !=EOF)
    {
        if(isalpha(c))
        {
            arr[toupper(c)-'A']++;
        }
    }

    for(i=0;i<26;i++)
    {
        printf("%c : %d\n",i+'A',arr[i]);
    }

    fclose(fp);
}
