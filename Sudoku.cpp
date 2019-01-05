/***********************************************************************
* Program:
*    Project 13, Sudoku
*    Brother Macbeth, CS124
* Author:
*    Heather Mason
* Summary: 
*    Load a sudoku board from a file. Display instructions with appropriate
*    prompts, then go to different functions for each prompt. Display
*    errors when invalid info is entered. make sure all values are correct.
*
*    Estimated:  4.0 hrs   
*    Actual:     5.0 hrs
*      Working out the loops for checking the values.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**********************************************************************
 * Test if the value will violate the Sudoku Row Rule for the specified 
 * row. Return true if the rule is satisfied. 
 * ********************************************************************/
bool testRow(int board[][9], const int size, const int row, const int value)
{
   for (int col = 0; col < size; col++)
   {
      if (board[row][col] == value)
      {
         return false;
      }
   } 
   return true;
}

/**********************************************************************
 * Test if the value will violate the Sudoku Column Rule for the specified
 * column. Return true if the rule is satisfied.
 * ********************************************************************/
bool testColumn(int board[][9], const int size, const int col, 
                const int value)
{

   for (int row = 0; row < size; row++)
   {
      if (board[row][col] == value)
      {
         return false;
      }
   }
   return true;
}

/**********************************************************************
 * Test if the value will violate the Sudoku Rule for a 3x3 square 
 * containing the specified row and column. Return true if the rule is 
 * satisfied.
 * ********************************************************************/
bool testSquare(int board[][9], const int size, const int row, 
                const int col, const int value)
{
   int startRow = 0;
   int startCol = 0;

   startRow = (row / 3) * 3;
   startCol = (col / 3) * 3;
   
   for (int r = startRow; r < (startRow + 3); r++)
   {
      for (int c = startCol; c < (startCol + 3); c++)
      {
         if (board[r][c] == value)
         {
            return false;
         }
      }
   }
   return true;
}

/**********************************************************************
 * Test if a value can be put into the Sudoku board at the
 * specified row and column without violating any of the Sudoku Rules.
 * Return true if all 3 rules are satisfied.
 * ********************************************************************/
bool testBoard(int board[][9], const int size, const int row, 
               const int col, const int value)
{
   bool testR = testRow(board, size, row, value);
   bool testC = testColumn(board, size, col, value);
   bool testS = testSquare(board, size, row, col, value);

   if (testR == true && testC == true && testS == true)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/**********************************************************************
 * Prompt the user for a filename and then populate the board array with 
 * the values from the file. If there is an error opening the file then 
 * display an error message and return false.
 * ********************************************************************/
bool loadGame(int board[][9], const int size)
{
   string fileName;
   
   cout << "Where is your board located? ";
   cin >> fileName;

   ifstream fin(fileName.c_str());

   if (fin.fail())
   {
      cout << "Error" << endl;
      return false;
   }

   for (int row = 0; row < size; row++)
   {
      for (int col = 0; col < size; col++)
      {
         fin >> board[row][col];
      }
   }

   fin.close();
   return true;
}

/**********************************************************************
 * Prompt the user for a filename (using the string class) and then 
 * populate that file with the contents of the board array. If there is 
 * an error opening the file then display an error message. Otherwise, 
 * display “Board written successfully” after saving the file.
 * ********************************************************************/
bool saveGame(int board[][9], const int size)
{
   string fileName;

   cout << "What file would you like to write your board to: ";
   cin >> fileName;

   ofstream fout(fileName.c_str());

   if (fout.fail())
   {
      cout << "Error" << endl;
      return false;
   }

   for (int row = 0; row < size; row++)
   {
      for (int col = 0; col < size; col++)
      {
         fout << board[row][col] << " ";
      }
      fout << endl;
   }

   cout << "Board written successfully" << endl;
   return true;
}

/**********************************************************************
 * Display the instructions
 * ********************************************************************/
void displayInstructions()
{
   cout << "Options:" << endl;
   cout << "   ?  Show these instructions" << endl;
   cout << "   D  Display the board" << endl;
   cout << "   E  Edit one square" << endl;
   cout << "   S  Show the possible values for a square" << endl;
   cout << "   Q  Save and Quit" << endl << endl;
}

/**********************************************************************
 * Display the contents of the Sudoku board array
 * ********************************************************************/
void displayBoard(int board[][9], const int size)
{
   cout << "   A B C D E F G H I" << endl;

   for (int row = 0; row < size; row++)
   {
      if (row % 3 == 0 && row != 0)
      {
         cout << "   -----+-----+-----" << endl;
         cout << row + 1 << " ";
      }
      else
      {
         cout << row + 1 << " ";
      }

      for (int col = 0; col < size; col++)
      {
         if (col % 3 == 0 && col != 0)
         {
            cout << "|";
         }
         else
         {
            cout << " ";
         }
         if (board[row][col] == 0)
         {
            cout << " ";
         }
         else
         {
            cout << board[row][col];
         }
      }
      cout << endl;
   }
}

/**********************************************************************
 * Convert a 2 character coordinate
 * ********************************************************************/
void convertCoordinate(const char colChar, const char rowChar, int &row, 
                       int &col)
{
   if (colChar == 'A')
   {
      col = 0;
   }
   else if (colChar == 'B')
   {
      col = 1;
   }
   else if (colChar == 'C')
   {
      col = 2;
   }
   else if (colChar == 'D')
   {
      col = 3;
   }
   else if (colChar == 'E')
   {
      col = 4;
   }
   else if (colChar == 'F')
   {
      col = 5;
   }
   else if (colChar == 'G')
   {
      col = 6;
   }
   else if (colChar == 'H')
   {
      col = 7;
   }
   else if (colChar == 'I')
   {
      col = 8;
   }
   else
   {
      cout << "Invalid Column Coordinate";
   }

   if (rowChar == '1')
   {
      row = 0;
   }
   else if (rowChar == '2')
   {
      row = 1;
   }
   else if (rowChar == '3')
   {
      row = 2;
   }
   else if (rowChar == '4')
   {
      row = 3;
   }
   else if (rowChar == '5')
   {
      row = 4;
   }
   else if (rowChar == '6')
   {
      row = 5;
   }
   else if (rowChar == '7')
   {
      row = 6;
   }
   else if (rowChar == '8')
   {
      row = 7;
   }
   else if (rowChar == '9')
   {
      row = 8;
   }
   else
   {
      cout << "Invalid Row Coordinate";
   }
}

/**********************************************************************
 * The user provides a coordinate and value to place there.
 * ********************************************************************/
void editSquare(int board[][9], const int size)
{
   string coordinate;
   int row = 0;
   int col = 0;
   int value = 0;

   cout << "What are the coordinates of the square: ";
   cin >> coordinate;

   coordinate[0] = toupper(coordinate[0]); 
   convertCoordinate(coordinate[0], coordinate[1], row, col);

   if (board[row][col] == 0)
   {
      cout << "What is the value at '" << coordinate << "': ";
      cin >> value;
      if (testBoard(board, size, row, col, value) == true)
      {
         board[row][col] = value;
      }
      else
      {
         cout << "ERROR: Value '" << value << "' in square '" <<
                 coordinate << "' is invalid" << endl;
      } 
   }
   else
   {
      cout << "ERROR: Square '" << coordinate << "' is filled" << endl;
   }

}

/**********************************************************************
 * The user provides a coordinate and the possible values are displayed
 * ********************************************************************/
void showValues(int board[][9], const int size)
{
   bool first = true;
   string coordinate;
   int row = 0;
   int col = 0;

   cout << "What are the coordinates of the square: ";
   cin >> coordinate;

   coordinate[0] = toupper(coordinate[0]);
   convertCoordinate(coordinate[0], coordinate[1], row, col);
   cout << "The possible values for '" << coordinate << "' are: ";

   for (int num = 1; num <= 9; num++)
   {
      if (testBoard(board, size, row, col, num) == true)
      {
         if (first == false)
         {
            cout << ", " << num;
         }
         else
         {
            cout << num;
            first = false;
         }
      }
   }
   cout << endl;
}

/**********************************************************************
 * Display the prompt "> " and then return the selection made by the 
 * user.
 * ********************************************************************/
char prompt()
{
   char selection;
   cout << "> ";
   cin >> selection;

   return selection;
}

/**********************************************************************
 * Driver
 ***********************************************************************/
int main()
{
   int board[9][9];
   int size = 9;
   char selection;
   
   loadGame(board, size);
   displayInstructions();
   displayBoard(board, size);
   cout << endl;

   do
   {
      selection = prompt();
      selection = toupper(selection);
      if (selection == '?')
      {
         displayInstructions();
         cout << endl;
      }
      else if (selection == 'D')
      {
         displayBoard(board, size);
         cout << endl;
      }
      else if (selection == 'E')
      {
         editSquare(board, size);
         cout << endl;
      }
      else if (selection == 'S')
      {
         showValues(board, size);
         cout << endl;
      }
      else if (selection == 'Q')
      {
         saveGame(board, size);
         return 0;
      }
      else
      {
         cout << "Invalid entry" << endl;
      }
   }
   while (selection != '?' || selection != 'D' || selection != 'E' || 
          selection != 'S' || selection != 'Q');
   return 0;
}
