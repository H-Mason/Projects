/***********************************************************************
* Program:
*    Project 10, Madlibs
*    Brother Macbeth, CS124
* Author:
*    Heather Mason
* Summary: 
*    Get a file name from the user, use that to open the file and then 
*    loop through the words to pull out the question tags. use those to
*    prompt input from the user, and replace the question tags with 
*    those inputs in order to make the madlib
*
*    Estimated:  4.0 hrs   
*    Actual:     5.0 hrs
*      figuring out the correct loops and if statements for spacing.
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

/**********************************************************************
 * Get the fileName
 * ********************************************************************/
void getFileName(char fileName[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin >> fileName;
   cin.ignore();
}

/**********************************************************************
 * determine if a word is a question tag
 * ********************************************************************/
bool isQuestionTag(char word[])
{
   if (word[0] == '<')
   {
      if (word[1] == '#' || word[1] == '{' || word[1] == '}' ||
          word[1] == '[' || word[1] == ']')
      {
         return false;
      }
      else
      {
         return true;
      }
   }
   else
   {
      return false;
   }
}

/**********************************************************************
 * display a word from inside the question tag and ask for a response
 * ********************************************************************/
void replaceQuestionTag(char word[])
{
   int i = 2;

   cout << "\t" << (char)toupper(word[1]);
   while (word[i] != '\0')
   {
      if (word[i] == '_')
      {
         cout << " ";
      }
      else if (word[i] != '>')
      {
         cout << (char)tolower(word[i]);
      }
      i++;
   }
   cout << ": ";
   cin.getline(word, 32);
}

/**********************************************************************
 * open the file, put the words into the story array. if it's a question
 * tag, get a word from the user with replaceQuestionTag.
 * ********************************************************************/
int readFile(char fileName[], char story[][32])
{
   ifstream fileIn(fileName);
   int count = 0;

   if (fileIn.fail())
   {
      return 0;
   }
   else
   {
      while (fileIn >> story[count])
      {
         if (isQuestionTag(story[count]) == true)
         { 
            replaceQuestionTag(story[count]);
         }
         count++;
      }
      fileIn.close();
      return count;
   }
}

/**********************************************************************
 * prints out the story
 * ********************************************************************/
void displayStory(char story[][32], int numWords)
{
   for (int i = 0; i < numWords; i++)
   {
      switch (story[i][1])
      {
         case '#':
            story[i][0] = '\n';
            story[i][1] = '\0';
            break;
         case '{':
            story[i][0] = ' ';
            story[i][1] = '\"';
            story[i][2] = '\0';
            break;
         case '}':
            story[i][0] = '\"';
            story[i][1] = '\0';
            break;
         case '[':
            story[i][0] = ' ';
            story[i][1] = '\'';
            story[i][2] = '\0';
            break;
         case ']':
            story[i][0] = '\'';
            story[i][1] = '\0';
            break;
      }
   }
   
   for (int i = 0; i < numWords; i++)
   {
      if (i == 0)
      {
         cout << story[i];
      }
      else if (story[i][0] == '\n' || story[i][0] == '\''
               || story[i][0] == '\"')
      {
         cout << story[i];
      }
      else if (story[i][0] == ' ')
      {
         if (story[i - 1][0] == '\n')
         {
            if (story[i][1] == '\"')
            {
               cout << "\"";
            }
            else if (story[i][1] == '\'')
            {
               cout << "\'";
            }
            else
            {
               cout << story[i];
            }
         }
         else
         {
            cout << story[i];
         }
      }
      else if (story[i - 1][0] == '\n' || story[i - 1][0] == ' ')
      {
         cout << story[i];
      }
      else if (ispunct(story[i][0]))
      {
         cout << story[i];
      }
      else
      {
         cout << " " << story[i];
      }
   }  
}

/**********************************************************************
 * determines if the user wants to play again
 * ********************************************************************/
bool askPlayAgain()
{
   char response;
   cout << "Do you want to play again (y/n)? ";
   cin >> response;

   if (response == 'y')
   {
      return true;
   }
   else
   {
      return false;
   }
}

/**********************************************************************
 * Driver
 ***********************************************************************/
int main()
{
   char fileName[256];
   char word[32];
   char story[256][32];
   int numWords = 0;
   bool playAgain = true;

   while (playAgain == true)
   {
      getFileName(fileName);
      numWords = readFile(fileName, story);
      cout << endl;
      displayStory(story, numWords);
      cout << endl;
      playAgain = askPlayAgain();
   }

   cout << "Thank you for playing." << endl;

   return 0;
}
