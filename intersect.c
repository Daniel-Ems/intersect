#include "inter_func.h"


int main(int argc, char *argv[])
{
	FILE *encodeFile;

    struct stat *buf = malloc(sizeof(*buf));

    stat(argv[1], buf);


    off_t fileEnd = buf->st_size;


    if (fileEnd == 0)
    {
        return EX_USAGE;
    }

    if (argc < 3)
    {
        printf("Please pass a file\n");
        return EX_USAGE;
    }
    else
    {
        encodeFile = fopen(argv[1], "r");

        if (!encodeFile)
        {
            return EX_USAGE;
        }

    }


    char *tmpBuff = calloc(1, MAX_WORD_SIZE);
	if(tmpBuff == NULL)
	{
		printf("calloc failed");
		return EX_USAGE;
	}

 	wordnode *root = NULL;
	int count = 0;
	char letter = 'a';
	while(letter != EOF)
 	{
		letter = fgetc(encodeFile);
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

	int a = 2;
	FILE *checkFile;
	while(a <= argc-1)
	{
		checkFile = fopen(argv[a], "r");	
		letter='a';
		while(letter!=EOF)
		{
			letter = fgetc(checkFile);
			tmpBuff[count] = letter;
	
			if(isspace(letter))
			{
				tmpBuff[count] ='\0';
				word_check(tmpBuff, root, a);
				memset(tmpBuff, '\0', strlen(tmpBuff));
				count = 0;

			}
			else
			{
				count++;
			}
		}

		fclose(checkFile);
		memset(tmpBuff, '\0', strlen(tmpBuff));
		a++;
	}
				
				
	print_node(root, argc-1);

	destroy_wordtree(root);
	free(tmpBuff);
	free(buf);
	fclose(encodeFile);
	//fclose(checkFile);
	
}

 
