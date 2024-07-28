//mycat

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) 
{
    FILE *fp;
    char ch;
    int i;

    if (argc < 2) 
    {
        printf("Usage: <file1> [<file2> <file3> ...]\n");
        return 1;  
    }

    for (i = 1; i < argc; i++)
     {
        fp = fopen(argv[i], "r");
        if (fp == NULL) 
        {
            perror("Error");
            continue;  
        }

        printf("Contents of %s:\n", argv[i]);
        while ((ch = fgetc(fp)) != EOF) 
        {
            printf("%c", ch);
        }

        fclose(fp);
        printf("\n");
    }

    return 0;
}
