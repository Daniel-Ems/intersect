#include "inter_func.h"



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


void destroy_wordtree(wordnode *root){
     if (root == NULL) // or if (!root)
          return;
       
     destroy_wordtree(root->left);  
     destroy_wordtree(root->right);
	 free(root->word);
     free(root);
} 


void word_check(char *string, wordnode *root, int argv)
{
	//bool match = false;
	if(root == NULL)
	{
		return;
	}
	
	while(root != NULL && strcasecmp(string, root->word) != 0)
	{
		if(strcasecmp(string, root->word) < 0)
		{
			root = root->left;
		}
		else if(strcasecmp(string, root->word) > 0)
		{
			root = root->right;
		}
	}
	if(root != NULL && strcasecmp(string, root->word) == 0)
	{
		if(root->count < argv)
		{
			root->count++;
		}
		return;
	}
	else 
	{	
		return;
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
			
			root->word = calloc(1,MAX_WORD_SIZE);
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
		else
		{
			return root;
		}
		
	}
	return root; 
}
