//mycopy
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
 {
    FILE *fp, *wfp;
    char buffer[BUFFER_SIZE];
    int i;

    if (argc < 3) 
    {
        printf("Usage: <inputfile1> <inputfile2> ... <outputfile>\n");
        return 1;
    }

    wfp = fopen(argv[argc - 1], "w");
    if (wfp == NULL) 
    {
        perror("Error opening output file");
        return 1;
    }


    for (i = 1; i < argc - 1; i++) 
    {
		
        fp = fopen(argv[i], "r");
        
        if (fp == NULL)
         {
            perror("Error opening input file");
            continue; 
        }
        
		fprintf(wfp,"\n\nfile content are:%s\n",argv[i]);
	    
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) 
        {
            fputs(buffer, wfp);
        }

        fclose(fp); 
    }

    fclose(wfp);

    printf("Files merged successfully.\n");
    return 0;
}
