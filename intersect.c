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
typedef struct wordnode 

->The char *word holds the string to be stored.
->The wordnode *left and *right build the tree.
->The int count is used to determine whether the word is intersected.

CITE: The struct wordnode is a modification the the BSTnode we were given in
Datastructures and Algortithims I.
*******************************************************************************/
typedef struct wordnode{
     char *word;
    struct wordnode *left;
    struct wordnode *right;

}wordnode;


/*******************************************************************************
void print_node(wordnode *root, int argv) 

->The wordnode *root, points to the root node of the tree to be printed. 
->The int argv, is the the current argv[] position in the array. 

The function print_node recursively moves left, until it hits null, and then it 
will print the char *word of the node as long as the root->count matches argv.
	
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
		printf("%s\n", root->word);
	if (root -> right)
	{
		print_node(root->right, argv);
	}
	
}

/*******************************************************************************
void destroy_wordtree(wordnode *root)

->wordnode *root points to the root of the tree. 

the function destroy_wordtree will move left looking for a null node, and then
will recursvely free word, and then root. 

CITE: The function destroy_wordtree was modified from the BSTnode exercise 
handed out during Datastructures and Algorithims I.
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
bool word_check(char *string, wordnode *root, int argv)

-> char *string is used as the check case for root->word.
-> wordnode *root is a pointer the beginning of the tree. 
-> int argv is the current.
 
The function word_check is used to see whether or not char *string is already in
the tree. The int argv is used to be sure that the word did not enter the tree
from the same file. This would be a false count step. 

Bool is returned so I may
check whether or not a word exists within a tree before the word inserts. 
*******************************************************************************/
bool word_check(char *string, wordnode *root)
{
	if(root == NULL)
	{
		return false;
	}
	word_check(string, root->left);
	word_check(string, root->right);
	
	if(strcasecmp(string, root->word) == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/*******************************************************************************
wordnode *Insert(wordnode *root, char *string)

->wordnote *root points to the root of the tree. 
->char *string is the word that i am inserting.

The function Insert will strcasecmp the string with root->words, and will then
either insert the node to the left (if smaller), or to the right (if greater).
The word is not inserted if the strcasecmp returns 0. The function then returns
the pointer.

CITE: The function Insert was modified from the BSTnode exercise given during
Datastructres and Algorithims I.
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
		if(!word_check(token,root))
		{
			root = Insert(root, token);
		}
		token = strtok(NULL, " \n\t");
	}
	
	memset(tmpBuff, '\0', 256);
	
	wordnode *new = NULL;
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
				if(word_check(tmpBuff, root))
				{
					new = Insert(new, tmpBuff);
				}
				memset(tmpBuff, '\0', strlen(tmpBuff));
				count = 0;
			}
			else
			{
				count++;
			}
		}
		destroy_wordtree(root);
		root = NULL;
		root = new;
		new = NULL;
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

 
