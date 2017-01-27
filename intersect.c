#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>


typedef struct wordnode{
     char *word;
    struct wordnode *left;
    struct wordnode *right;
	int count;
}wordnode;


void destroy_array(char **save)
{
	printf("in destroy");
	int a = 0;
	while(save[a]!=NULL)
	{
		free(save[a]);
		a++;
	}
	free(save);
}



void print_node(wordnode *root)
{

	if(root->left)
	{
		print_node(root->left);
	}
	printf("%s\n", root->word);
	if (root -> right)
	{
		print_node(root->right);
	}
	
}

void destroy_wordtree(wordnode* root){
     if (root == NULL) // or if (!root)
          return;
       
     destroy_wordtree(root->left);  
     destroy_wordtree(root->right);
	 free(root->word);
     free(root);
} 

bool word_check(char * string, wordnode *root)
{
	if(root == NULL)
	{
		return true;
	}
	word_check(string, root->left);
	word_check(string, root->right);
	
	if(strcasecmp(string, root->word) == 0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}
wordnode *Insert(wordnode *root, char *string)
{
	if(root==NULL) 
	{
		root = (wordnode *) malloc(sizeof(*root));

		if(root == NULL)
		{
			printf("Memory Error");
			return NULL; 
		}
		else
		{
			
			root->word = calloc(1,256);
			strncpy(root->word, string, strlen(string));
			root->count = 1;
			root->left = root->right = NULL;
		}
	}
	else
	{
		if(strcasecmp(string, root->word) < 0) 
		{ 
			root->left = Insert(root->left, string); 
		}
		else if(strcasecmp(string, root->word) > 0)
		{
			root->right = Insert(root->right, string); 
		}
		
	}
	return root; 
}

//Input code taken from my codec project off github. 
int main(int argc, char *argv[])
{
	FILE *encodeFile;
	//FILE *testFile;
    struct stat *buf = malloc(sizeof(*buf));
	//struct stat *file2 = malloc(sizeof(*file2));
    stat(argv[1], buf);
	//stat(argv[2], buf);

    off_t fileEnd = buf->st_size;
	//off_t fileEnd2 = file2->st_size;

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
		//testFile = fopen(argv[2], "r");
        if (!encodeFile)
        {
            return EX_USAGE;
        }

    }

    char *tmpBuff = calloc(1, fileEnd+1);
	for(int count = 0; count < fileEnd; count ++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}
		
	char *token;
	token = strtok(tmpBuff, " \t\n");

	wordnode *root = NULL;
	while(token != NULL)
	{
		if(word_check(token,root))
		{
			root = Insert(root, token);
		}
		token = strtok(NULL, " \n\t");
	}
	
	//memset(tmpBuff, 0, sizeof(tmpBuff);
	

	print_node(root);

	destroy_wordtree(root);
	free(tmpBuff);
	//free(secondFile);
	//free(file2);
	free(buf);
	fclose(encodeFile);
	//fclose(testFile);
	
}

 
