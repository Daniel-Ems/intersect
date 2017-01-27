#include "inter_func.h"


int main(int argc, char *argv[])
{
	FILE *dictionaryFile;

    struct stat *buf = malloc(sizeof(*buf));
	int i = 1;
    off_t fileEnd;

	for(i = 1; i < argc; i++)
	{
    	stat(argv[i], buf);
		fileEnd = buf->st_size;
		if(fileEnd == 0)
		{
			printf("Empty Files not allowed\n");
			return EX_USAGE;
		}
	}


    if (argc < 3)
    {
        printf("Please pass a file\n");
        return EX_USAGE;
    }
    else
    {
       	dictionaryFile = fopen(argv[1], "r");

        if (!dictionaryFile)
        {
            return EX_USAGE;
        }

    }


    char *tmpBuff = calloc(1, MAX_WORD_SIZE);
	if(tmpBuff == NULL)
	{
		printf("calloc failed\n");
		return EX_USAGE;
	}

 	wordnode *root = NULL;
	int count = 0;
	char letter = 'a';
	while(letter != EOF)
 	{
		letter = fgetc(dictionaryFile);
 		tmpBuff[count] = letter;
		if(isspace(letter))
		{
			tmpBuff[count] = '\0';
			root = Insert(root, tmpBuff);
			memset(tmpBuff, '\0', strlen(tmpBuff));
			count = 0;
		} 
		else
		{
			count++;
		}
				
	}

	count = 0;

	int curFile = TEST_FILES;
	FILE *intersectFiles;
	while(curFile <= argc-1)
	{
		intersectFiles = fopen(argv[curFile], "r");
		if(!intersectFiles)
		{
			printf("Bad File\n");
			return EX_USAGE;
		}	
		letter='a';
		while(letter!=EOF)
		{
			letter = fgetc(intersectFiles);
			tmpBuff[count] = letter;
	
			if(isspace(letter))
			{
				tmpBuff[count] ='\0';
				word_check(tmpBuff, root, curFile);
				memset(tmpBuff, '\0', strlen(tmpBuff));
				count = 0;

			}
			else
			{
				count++;
			}
		}

		fclose(intersectFiles);
		memset(tmpBuff, '\0', strlen(tmpBuff));
		curFile++;
	}
						
	print_node(root, argc -1);

	destroy_wordtree(root);
	free(tmpBuff);
	free(buf);
	fclose(dictionaryFile);
	//fclose(intersectFiles);
	
}

 
