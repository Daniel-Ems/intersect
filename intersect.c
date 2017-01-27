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

/*******************************************************************************
wordnode holds a char *string, wordnode *left and right nodes, 
and an int counter. 

The char *word holds the string to be stored.
The wordnode *left and *right build the tree.
The int count is used to determine whether the word is intersected.

CITE: The struct wordnode is a modification the the BSTnode we were given in
Datastructures and Algortithims I.
*******************************************************************************/
typedef struct wordnode{
     char *word;
    struct wordnode *left;
    struct wordnode *right;
	int count;
}wordnode;


/*******************************************************************************
print_node takes a wordnode *, as well as an int argv. 

The wordnode *, points to the root node of the tree to be searced. 
The int argv, is the the current argv[] positioin

The function recursively moves left, until it hits null, and then it will
print the char *word of the node as long as the root->count matches argv.
	
	**This is used to ensure that words are found in all the files that 
	have been passed through the command line. 

CITE: The function print_node was modified from the BSTnode exercise handed out 
during Datastructures and Algorithims I.
*******************************************************************************/
void print_node(wordnode *root, int argv)
{

	if(root->left)
	{
		print_node(root->left, argv);
	}
	if(root->count == argv)
	{
		printf("%s\n", root->word);
	}
	if (root -> right)
	{
		print_node(root->right, argv);
	}
	
}

/*******************************************************************************
destroy_wordtree takes a wordnode *root.

wordnode *root points to the root of the tree. 

the function will move left looking for a null node, and then will recursvely 
free word, and then root. 

CITE: 
*******************************************************************************/
void destroy_wordtree(wordnode *root){
     if (root == NULL) // or if (!root)
          return;
       
     destroy_wordtree(root->left);  
     destroy_wordtree(root->right);
	 free(root->word);
     free(root);
} 

/*******************************************************************************



*******************************************************************************/
bool word_check(char *string, wordnode *root, int argv)
{
	if(root == NULL)
	{
		return false;
	}
	word_check(string, root->left, argv);
	word_check(string, root->right, argv);
	
	if(strcasecmp(string, root->word) == 0)
	{
		if(root->count < argv)
		{
			root->count++;
		}
		return true;
	}
	else 
	{
		return false;
	}
}

/*******************************************************************************



*******************************************************************************/
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
		if(!word_check(token,root, 1))
		{
			root = Insert(root, token);
		}
		token = strtok(NULL, " \n\t");
	}
	
	memset(tmpBuff, '\0', strlen(tmpBuff));
	
	int a = 2;
	int count = 0;
	FILE *checkFile;
	while(a <= argc-1)
	{
		checkFile = fopen(argv[a], "r");		
		char letter = '\0';
		while(letter!=EOF)
		{
			letter = fgetc(checkFile);
			tmpBuff[count] = letter;
	
			if(isspace(letter))
			{
				tmpBuff[count] ='\0';
				word_check(tmpBuff, root,a);
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
				
				
				
		
	

	print_node(root, (argc-1));

	destroy_wordtree(root);
	free(tmpBuff);
	free(buf);
	fclose(encodeFile);
	//fclose(checkFile);
	
}

 
