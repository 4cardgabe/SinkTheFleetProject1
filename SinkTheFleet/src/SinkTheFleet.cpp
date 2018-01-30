//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "fleet.h"
#include <Windows.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
extern const char* shipNames[7];
void printPlayerGrids(Player* game, short currentPlayer, char gridSize, bool clear = true);
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by: Ethan Lindemann and Gabe Blumenthal
// 
// Date:		12/9/2010
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				loadGridFromFile()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	short currentPlayer = 0;
	short enemyPlayer = 1;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message;
	ostringstream prompt("");
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS];	// the two players in an array
	// YOUR CODE GOES HERE ...
	string s2("");
	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

		numRows = (toupper(gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		numCols = (toupper(gridSize) == 'L') ? LARGECOLS : SMALLCOLS;
		
		initializePlayer(game);		
		initializePlayer(game + 1);

		allocMem(game, gridSize);

		system("cls");
		for(currentPlayer = 0; currentPlayer < NUMPLAYERS; currentPlayer++)
		{
			header(cout);
			// Request a game file
			string filename("");
			prompt.str("");
			prompt << "Player " << (currentPlayer + 1) << ", Would you like to read starting grid from a file?";
			const char openFile = safeChoice(prompt.str());
			
			if (openFile == 'Y')
			{
				// Get filename
				cout << "Input starting grid filename <name>.shp: ";
				cin >> noskipws >> filename;
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				// Check file exists
				bool exists = GetFileAttributes(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
				if (exists)
				{
					bool loaded = loadGridFromFile(game, currentPlayer, gridSize, filename);
					if (!loaded)
					{
						cout << "Failed to load grid. Press <enter> to continue.";
						cin.ignore(INT_MAX, '\n');
						currentPlayer--;
						system("cls");
						continue;
					}
				}
				else
				{
					cout << "File does not exist. Press <enter> to continue.";
					cin.ignore(INT_MAX, '\n');
					currentPlayer--;
					system("cls");
					continue;
				}
			}
			else
			{
				setships(game, gridSize, currentPlayer);
			}
			const char gridOkay = safeChoice("Would you like to accept this grid?");
			if (gridOkay == 'Y')
			{
				system("cls");
				continue;
			}
			else
			{
				currentPlayer--;
				continue;
			}
		}

		cout << "Press <enter> to start battle...";
		cin.ignore(INT_MAX, '\n');

		// Enter game loop
		currentPlayer = 0;
		while(!gameOver)
		{
			// Show current player's grid
			header(cout);
			printPlayerGrids(game, currentPlayer, gridSize);

			// Get current player's move
			cout << "Player " << (currentPlayer + 1) << ", Enter coordinates for firing." << endl;
			auto coord = getCoord(cin, gridSize);

			// Make sure coordinates are valid
			bool valid = game[currentPlayer].m_gameGrid[1][coord.m_row][coord.m_col] < Ship::HIT;
			if (!valid)
			{
				cout << "Location already entered. Press <enter> to try again.";
				cin.ignore(FILENAME_MAX, '\n');
				continue;
			}

			// Perform hit logic
			bool hit = testHit(game, currentPlayer, enemyPlayer, coord);
			Ship shipSunk = sunkShip(game, enemyPlayer, coord);

			// Update the player's grid
			header(cout);
			printPlayerGrids(game, currentPlayer, gridSize);
			
			// Show player made changes
			cout << "Player " << (currentPlayer + 1) << (hit ? " landed a hit!" : " missed!") << endl;
			if (shipSunk > Ship::NOSHIP && shipSunk < Ship::HIT) {
				cout << "Player " << (currentPlayer + 1) << " sunk Player " << (enemyPlayer + 1) << "'s " << shipNames[shipSunk] << endl;
			}

			if (game[enemyPlayer].m_piecesLeft <= 0)
			{
				endBox(currentPlayer);
				gameOver = true;
			}

			cout << "Press <enter> to continue." << endl;
			cin.ignore(FILENAME_MAX, '\n');

			if (hit) continue;

			// Switch players
			currentPlayer = !currentPlayer;
			enemyPlayer = !enemyPlayer;
		}
		// clean up memory ...
		deleteMem(game, gridSize);

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	}
	while(again == 'Y');
	
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
} 

void printPlayerGrids(Player* game, short currentPlayer, char gridSize, bool clear) 
{
	if (clear) system("cls");
	cout << "Player " << (currentPlayer + 1) << "'s Hit and Miss grid." << endl;
	printGrid(cout, game[currentPlayer].m_gameGrid[1], gridSize);
	cout << endl << "Player " << (currentPlayer + 1) << "'s ship grid." << endl;
	printGrid(cout, game[currentPlayer].m_gameGrid[0], gridSize);
}