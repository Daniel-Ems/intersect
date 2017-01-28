#ifndef INTER_FUNC_H

#define INTER_FUNC_H

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


enum
{ TEST_FILES = 2 };         //the 2nd file is the first to be tested.
enum
{ MAX_WORD_SIZE = 256 };	//This is the maximum size of a word.
/*******************************************************************************
typedef struct wordnode 

->The char *word holds the string to be stored.
->The wordnode *left and *right build the tree.
->The int count is used to determine whether the word is intersected.

CITE: The struct wordnode is a modification the the BSTnode we were given in
Datastructures and Algortithims I.
*******************************************************************************/
typedef struct wordnode
{
  char *word;
  struct wordnode *left;
  struct wordnode *right;
  int count;

} wordnode;

/******************************************************************************
void print_node(wordnode *tree, int argv) 

->The wordnode *tree, points to the node of the tree to be printed. 
->The int argv, is the the current argv[] position in the array. 

The function print_node recursively moves left, until it hits null, and then it 
will print the tree->word of the node as long as the tree->count matches argv. 
The function will then recursively move right and repeat the print process.
	
	**This is used to ensure that words are found in all the files that 
	have been passed through the command line. 

CITE: The function print_node was modified from the BSTnode exercise handed out 
during Datastructures and Algorithims I.
*******************************************************************************/
void print_tree (wordnode *tree, int argv);

/*******************************************************************************
void destroy_wordtree(wordnode *tree)

->wordnode *tree points to the node of the tree. 

the function destroy_wordtree will move until a null is found, and then
will recursvely free tree->word, and then tree. 

CITE: The function destroy_wordtree was modified from the BSTnode exercise 
handed out during Datastructures and Algorithims I.
*******************************************************************************/
void destroy_wordtree (wordnode *tree);

/*******************************************************************************
void word_check(char *string, wordnode *tree, int argv)

-> char *string is used as the check case for tree->word.
-> wordnode *tree is a pointer the beginning of the tree. 
-> int argv is the current file being checked.
 
The function is passed *string which is used to check against all the words in
the tree, wordnode *tree.  If the string is found, the node's counter is checked
against int argv. If the counter is < int argv, then the counter is incrmented.
 
CITE: Washington helped me nail down the logic for the word_check. 
*******************************************************************************/
void word_check (char *string, wordnode *tree, int argv);

/*******************************************************************************
wordnode *Insert(wordnode *tree, char *string)

->wordnote *tree points to the node of the tree. 
->char *string is the word being inserted.

char *string is compared to tree->word using strcasecmp. if the string is < 0,
the new node is created to the left of tree. If the string is > 0,
the new node is created to the right of tree. If the string is == 0 no node is 
created. If tree==NULL, a new node is created.

CITE: The function Insert was modified from the BSTnode exercise given during
Datastructres and Algorithims I.
*******************************************************************************/
wordnode *Insert (wordnode *tree, char *string);

#endif
