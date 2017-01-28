#include "inter_func.h"


int
main (int argc, char *argv[])
{
  FILE *dictionaryFile;

  //Struct stat is a built in structure that gives you multiple file 
  //properties. It is being used here for the size of file. 
  struct stat *buf = malloc (sizeof (*buf));
  int i = 1;
  off_t fileEnd;

  //The for loop iterates through all files passed through the command line.
  //The for loop then checks to make sure that none of the files are empty.
  for (i = 1; i < argc; i++)
    {
      stat (argv[i], buf);
      fileEnd = buf->st_size;
      if (fileEnd == 0)
	{
	  printf ("Empty Files not allowed\n");
	  return EX_USAGE;
	}
    }

  //This will check to be sure more than one file was passed to the program.
  //If this is true, then the first file will be assigned to a file pointer.
  if (argc < 3)
    {
      printf ("Please pass a file\n");
      return EX_USAGE;
    }
  else
    {
      dictionaryFile = fopen (argv[1], "r");

      if (!dictionaryFile)
	{
	  return EX_USAGE;
	}

    }

  //This temporary buffer is used to bring in words. The pointer is calloced
  //to the size of MAX_WORD_SIZE, an enumed value of 256, the maximum word
  //size the program will see. 
  char *tmpBuff = calloc (1, MAX_WORD_SIZE);
  if (tmpBuff == NULL)
    {
      printf ("calloc failed\n");
      return EX_USAGE;
    }

  wordnode *tree = NULL;
  int count = 0;
  char letter = 'a';
  //This while loop will work with the first file and create a binary search
  //tree that will act as a dictionary to check for matching words amongst
  //the following files.
  while (letter != EOF)
    {
      //Letter takes the first charachter of the first file
      letter = fgetc (dictionaryFile);
      //Letter is assigned to tmpBuff
      tmpBuff[count] = letter;
      //Letter is then checked whether or not it is white space. if it is then
      //that position is set to a null byte to terminate the string Then
      //that string is passed to the insert function. 
      if (isspace (letter))
	{
	  tmpBuff[count] = '\0';
	  tree = Insert (tree, tmpBuff);
	  //memset will set the buffer to null to allow for the next word to begin. 
	  memset (tmpBuff, '\0', strlen (tmpBuff));
	  count = 0;
	}
      else
	{
	  count++;
	}

    }

  count = 0;
  //This for loop will cycle through the remaining files, and check them
  //respectively against the dictionary tree already made.
  int curFile = TEST_FILES;	//The current file position in argc. begins at 2.
  FILE *intersectFiles;
  while (curFile <= argc - 1)
    {
      intersectFiles = fopen (argv[curFile], "r");
      if (!intersectFiles)
	{
	  printf ("Bad File\n");
	  return EX_USAGE;
	}
      letter = 'a';
      //This while loop will act similar to the one prior. It will pull from 
	  //the file, letter by letter, populating the buffer until white space
	  //is found, a NULL byte set, and a word is formed.  
      while (letter != EOF)
	{
	  letter = fgetc (intersectFiles);
	  tmpBuff[count] = letter; 

	  if (isspace (letter))
	    {
	      tmpBuff[count] = '\0';
	      //Rather than sending the word to Insert, it is sent to word_
	      //check where it will see if a word is in the dictionary. If so,
	      //then the node counter is incremented. 
	      word_check (tmpBuff, tree, curFile);
	      memset (tmpBuff, '\0', strlen (tmpBuff));
	      count = 0;

	    }
	  else
	    {
	      count++;
	    }
	}

      fclose (intersectFiles);
      memset (tmpBuff, '\0', strlen (tmpBuff));
      curFile++;
    }


  print_tree (tree, argc - 1);

  destroy_wordtree (tree);
  free (tmpBuff);
  free (buf);
  fclose (dictionaryFile);


}
