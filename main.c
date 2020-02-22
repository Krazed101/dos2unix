#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    FILE* fp = NULL;
    char* file_path = NULL;
    char* line = NULL;
    char* tmp = NULL;
    unsigned int new_position = 0;
    unsigned int old_position = 0;
    long int offset = 0;
    const char* NEEDLE = "\r\n";

    if ( argc > 2 )
    {
        printf("Too many arguements.\ndos2unix <filename>");
        return 0;
    }
    else if ( argc < 2)
    {
        printf("Too few arguements.\ndos2unix <filename>");
        return 0;
    }
    else
    {
        file_path = (char*)calloc(strlen(argv[1]), sizeof(char));
        memcpy(file_path,argv[1],strlen(argv[1]));
        line = (char*)calloc(256,sizeof(char));
        printf("File Path: %s", file_path);

        if ( fp = fopen(file_path,"r+"), fp == NULL )
        {
            printf("File failed to open.\n");
        }
        while( 1 )
        {
            if ( feof(fp) ) break;
            
            fgets(line,512,fp);
            printf("%s", line);
            old_position += strlen(line);
            while(tmp = strstr(line, NEEDLE), tmp != NULL)
            {
                printf("Removed \\r\n");
                for (size_t i = 1; i < strlen(tmp); i++)
                {
                    tmp[i] = tmp[i+1];
                }
                offset++;
            }
            fseek(fp, 0, new_position);
            printf("New Position %d\n", strlen(line));
            new_position += strlen(line);
            fputs(line,fp);
            printf("old_position %d\n", old_position);
            fseek(fp, 0, old_position);
        }

    }
    fclose(fp);
    free(line);
    return 1;
}