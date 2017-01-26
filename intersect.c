#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//Input code taken from my codec project off github. 
int main(int argc, char *argv[])
{
	FILE *encodeFile;
    //FILE *writeFile;

    struct stat *buf = malloc(sizeof(*buf));

    stat(argv[1], buf);

    off_t fileEnd = buf->st_size;

    if (fileEnd == 0)
    {
        return EX_USAGE;
    }

    if (argc == 1)
    {
        printf("Please pass a file\n");
        return EX_USAGE;
    }
    else
    {
        encodeFile = fopen(argv[1], "rb");
        if (!encodeFile)
        {
            return EX_USAGE;
        }
		/*
        writeFile = fopen(argv[2], "wb");
        if (!writeFile)
        {
            return EX_USAGE;
        }
		*/
    }

    char *tmpBuff = calloc(1, fileEnd + 1);

	 for (int count = 0; count < fileEnd; count++)
    {
        tmpBuff[count] = fgetc(encodeFile);
	}
	printf("%s\n", tmpBuff);
	free(tmpBuff);
}


