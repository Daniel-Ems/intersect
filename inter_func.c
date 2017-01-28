#include "inter_func.h"



void
print_tree (wordnode *tree, int argv)
{
  //The function will move to the bottom left. 
  if (tree->left)
    {
      print_tree (tree->left, argv);
    }
  //The function will check to make sure the count is == to int argv. 
  //int argv is the number of files passed to the program. If the count
  //matches, it will print the tree->word. 
  if (tree->count == argv)
    {
      printf ("%s\n", tree->word);
    }
  //The program will then move to the right recursively, and repeat the 
  //process. 
  if (tree->right)
    {
      print_tree (tree->right, argv);
    }

}


void
destroy_wordtree (wordnode * tree)
{
  if (tree == NULL)
    {
      return;
    }
  //The function will recursively move to the bottom until it hits null.
  //It will then free the tree->word and then the node.  
  destroy_wordtree (tree->left);
  destroy_wordtree (tree->right);
  free (tree->word);
  free (tree);
}


void
word_check (char *string, wordnode * tree, int argv)
{

  if (tree == NULL)
    {
      return;
    }

  //strcasecmp returns -1,0,1 respectively according to the comparison between
  //string and tree->word.
  while (tree != NULL && strcasecmp (string, tree->word) != 0)
    {
      //If the result is less than the 0, the program needs to check left. 
      if (strcasecmp (string, tree->word) < 0)
	{
	  tree = tree->left;
	}
      //If the reuslt is greater than 0, then the program needs to check right. 
      else if (strcasecmp (string, tree->word) > 0)
	{
	  tree = tree->right;
	}
    }
  //Once the loop breaks, it has either found a match, or has found null, and
  //there for, no match. 
  if (tree != NULL && strcasecmp (string, tree->word) == 0)
    {
      if (tree->count < argv)
	{
	  tree->count++;
	}
      return;
    }
  else
    {
      return;
    }

}


wordnode *
Insert (wordnode * tree, char *string)
{
  //result is the retrun value of strcasecmp. This prevents multiple calls to 
  //strcasecmp.
  int result;
  //If tree == NULL, a new node is created.
  if (tree == NULL)
    {
      //Mallocs for the size of the node.
      tree = (wordnode *) malloc (sizeof (*tree));
      if (tree == NULL)
	{
	  printf ("Memory Error");
	  return NULL;
	}
      else
	{
	  //callocs for the size of the string. The string is then strncpy'd
	  //into tree->word.
	  tree->word = calloc (1, MAX_WORD_SIZE);
	  strncpy (tree->word, string, strlen (string));
	  //The count is initated to 1 because it is the first instance of 
	  //the word. This can also be seen as the word was found in file 1.
	  tree->count = 1;
	  //The node's tree->left and tree->right are then initiated to NULL.
	  tree->left = tree->right = NULL;
	}
    }
  //If tree is not == NULL, then the results of strcasecmp is used to 
  //appropriately place the word within the tree.
  else
    {
      result = strcasecmp (string, tree->word);
      if (result < 0)
	{
	  tree->left = Insert (tree->left, string);
	}
      else if (result > 0)
	{
	  tree->right = Insert (tree->right, string);
	}
      else
	{
	  return tree;
	}

    }
  return tree;
}
