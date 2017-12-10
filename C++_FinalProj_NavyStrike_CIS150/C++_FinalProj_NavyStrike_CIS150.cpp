//AUTHOR(s): Erik English, Chuck, and Tristan
//eMails: erik.m.english@gmail.com \ eenglish13820@my.monroe.edu, tludwig33344@my.monroeccc.edu, ccurtis2@my.monroeccc.edu
//DATE: 11/11/17

/*DESCRIPTION: Final Project - Naval Strike a game based off of Battleship.  */
//VERSION: 2017

#define _WIN32_WINNT 0x0500 //Must have defined before Windows.h (Citation given on line 71)

#include "stdafx.h"    // Precompiled Header
#include <iostream>    // Standard input output ease of use on std::
#include <stdio.h>     // Instead of using cin.getline you can use cin.gets(),parameter is stdio.h
//#include <istream>   // Has to do with getline  get()
#include <string>      // string x
#include <iomanip>     // setw(x) and others for output formating
#include "fstream"     // For opening up files. like .txt  // we may need this for the ascii art, it could be infinitely easier.
#include <Windows.h>   // To use Sleep
#include <Ctime>       // To use the random number generator for onePlayer.
//#include <sstream>	   // to convert a string to a integer to raise its ascii value and then change it back to a string. 'a' ++ now == 'b' https://www.youtube.com/watch?v=LM6EDIKS5Pk
//#include "vector" //In case we use vectors in the future
#include "MMSystem.h" //To play sound
#include <time.h> //to use time and date

using namespace std;

//Code found from cplusplus.com: SOURCE: http://www.cplusplus.com/forum/beginner/105484/ ; User: Giblit
enum COLOR
{
	black, blue,
	green, cyan,
	red, magenta,
	brown, normal,
	darkgrey, lightblue,
	lightgreen, lightcyan,
	lightred, lightmagenta,
	yellow, white
};


//Not entirely sure what this does but is necessary for coloring text.
ostream& operator<<(ostream &stm, const COLOR &c)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out_handle, c);
	return(stm);
}
//End of found code from cplusplus.com

//global variables
static bool victoryScreen = false;
static bool endInput = false;

//==================Function Prototypes==============
void intro(int&);
int mainMenu(); //In order to display the main menu, and not the ENTIRE intro every time, we need the menu part in a different function
				
void placeShipsPlayerOne();

void onePlayer(int, int, bool);
void TwoPlayer(int);
void Options(int&, int&, bool&);
void firstCoordOne(string, int&, string[][11], bool&);
void firstCoordTwo(string, int&, bool&, string[], int&, string[][11], string[][11], bool&); //Needed to change this to "firstCoordTwo" because you use more variables than Single Player
void secCoord(int&, bool&, string[][11], string[], int&, string[][11], bool&);
void secCoordOne(int&, bool&, string[][11]);
bool refresh(int&, string[][11], string[][11], int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, bool&);
void errorRefresh(bool&, bool&);
void invalidInputRefresh();
void displayBlankTwo(string[][11], string[][11], bool&);
void displayBlankOne(string[][11]);
void displayMiss(int, int);
void displayHit(int, int);
void exit();

//movement positions.
void setPos(int&, int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, string[][11], string[], bool&, string[][11], bool&);
void up(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void down(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void left(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void right(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);

//ship Hp

void shipDestroyed();

void shipHPCounter(string[][11], string[][11], bool&);
void HPsystemOne(string[][11], string[][11], int&, int&, int&, int&, int&, int, int);
void displayBlankTwoa(string[][11], string[][11], bool&);

//ship Placement



//Happy with the placement? or reset/redo > then turn controls to player two
bool happyPlacement(bool&, string[][11], string[][11]);
void boardRESET(string[][11]);

//start of missile strikes / player2
void playerTwoTakeOver();
void singlePlayerTakeOver();
void missiles(string[][11], string[][11], string&, int&, int&, bool&, int&, bool&);
void firstMissileYAxis(string&, int&, string[][11], string[][11], int&, bool&, bool&, int&);
void secondMissileXAxis(int&, string[][11], string[][11], int&, bool&, bool&, int&);

//sounds
void startSound();
void missSound();
void hitSound();
void sinkSound();
void vicSound();
void introSound();
void chooseSound();
void fightSound();
void youLoseSound();
void errorSound();

void credits();



int main()
{
	//Used to set window size for our command prompt. Found at http://www.cplusplus.com/forum/beginner/1481/
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	//MoveWindow(console, r.left, r.top, 800, 800, TRUE);


	//Variables
	int players; //Player Choice on the main menu


				 //Functions

	intro(players);  //currently to test deeper code comment this out, set players = 2;
	//mainMenu(); //Skip past the intro straight into the main menu;		

	cout << white << endl << endl << endl;
	system("pause");
	return 0;
}

//============================== ALL Functions=================




//================================ERIK'S FUNCTIONS BELOW==============================================================================

void intro(int &players)
{
	//any-key to skip some stuff? possible?


	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(65) << cyan << "Loading..." << endl;
			Sleep(1000);
		}
		else if (i == 1)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(65) << "Loading.." << endl;
			Sleep(1000);
		}
		else if (i == 2)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(75) << "Counting missed shots.." << endl;
			Sleep(1000);
		}
		else if (i == 3)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(80) << "Loading. Please wait patiently." << endl;
			Sleep(1000);
		}
		else if (i == 4)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(70) << "Undocking ships." << endl;
			Sleep(1000);
		}
	}

	


	//title
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
		Sleep(10);
	}

	// very sensitive to spaces and tabs do not change.
	cout << cyan;
	cout << "          _/      _/                                  _/        _/_/_/    _/                _/  _/                " << endl;
	cout << "         _/_/    _/    _/_/_/  _/      _/    _/_/_/  _/      _/        _/_/_/_/  _/  _/_/      _/  _/      _/_/  " << endl;
	cout << "        _/  _/  _/  _/    _/  _/      _/  _/    _/  _/        _/_/      _/      _/_/      _/  _/_/      _/_/_/_/ " << endl;
	cout << "       _/    _/_/  _/    _/    _/  _/    _/    _/  _/            _/    _/      _/        _/  _/  _/    _/        " << endl;
	cout << "      _/      _/    _/_/_/      _/        _/_/_/  _/      _/_/_/        _/_/  _/        _/  _/    _/    _/_/_/   " << endl;
	//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php

	// very sensitive to spaces and tabs do not change.

	// to utilize back space use \\ twice.
	//ascii art, SOURCE: http://ascii.co.uk/art/battleship
	cout << endl << endl << endl << endl << endl << endl << darkgrey;
	cout << "                                                        |__" << endl;
	cout << "                                                        |\\/" << endl;
	cout << "                                                        ---" << endl;
	cout << "                                                        / | [" << endl;
	cout << "                                                 !      | |||" << endl;
	cout << "                                               _/|     _/|-++'" << endl;
	cout << "                                           +  +--|    |--|--|_ |-" << endl;
	cout << "                                        { /|__|  |/\\__|  |--- |||__/" << endl;
	cout << "                                       +---------------___[}-_===_.'____                 /\\ " << endl;
	cout << "                                   ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _" << endl;
	cout << "                    __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7" << endl;
	cout << "                   |                                                                     BB-61/" << endl;
	cout << lightblue << "~~~~~~~~~~~~~~~~~~~~" << darkgrey << "\\_________________________________________________________________________|" << lightblue << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                      ~               ~                ~               ~                ~               " << endl;
	//ascii art, SOURCE: http://ascii.co.uk/art/battleship
	cout << endl << endl;
	introSound();
	//Sleep(3500);  //if returning to the color switch change the timer to something less than 5.5seconds
	system("cls");
	// very sensitive to spaces and tabs do not change.

	//authors
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
		Sleep(10);
	}

	cout << setw(65) << white << "Created By," << endl << setw(70) << "Erik, Tristan and Chuck" << endl << setw(65) << "Version 1.00a" << endl; //update version count, for every day in class? we will be at 0.08 on Dec 6, 2017 	
	for (int i = 0; i < 16; i++)
	{
		cout << endl;
		Sleep(100);
	}
	Sleep(1500);
	system("cls");
	players = mainMenu();

}

int mainMenu()
{
	while (!endInput)
	{
		int players = 0;
		static int difficulty = 50; //How many guesses the player has before losing the game
		static int boardNum;
		static bool boardChoose = false;
		bool menuNumber = false;
		static bool heardItonce = false;
		//MENU

		//players = mainMenu();
		//players = 2; //comment this out on release. and uncomment players = intro();
		//players = 1; //comment this out on release and uncomment players = 2 or players = intro();
		//players = 3; //comment this out on release and uncomment players = 2 or players = intro();

		do
		{
			//Run this at least once
			system("cls");
			cout << endl << endl << endl << endl;

			//cout << setw(68) << cyan << "Welcome to Navy Strike" << endl;
			cout << white;

			cout << "        _ _ _ ____ _    ____ ____ _  _ ____    ___ ____    _  _ ____ _  _ ____ _       ____ ___ ____ _ _  _ ____ " << endl;
			cout << "        | | | |___ |    |    |  | |\\/| |___     |  |  |    |\\ | |__| |  | |__| |       [__   |  |__/ | |_/  |___ " << endl;
			cout << "        |_|_| |___ |___ |___ |__| |  | |___     |  |__|    | \\| |  |  \\/  |  | |___    ___]  |  |  \\ | | \\_ |___ " << endl;
			//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php




			cout << endl << endl << endl << endl;
			cout << setw(76) << white << "Choose how you would like to play. \n";
			cout << endl << setw(65) << "1. ONE PLAYER \n";
			cout << setw(66) << "2. TWO PLAYERS \n"; //Only two player will work for the time being, 1 player will require an ai.
			cout << setw(62) << "3. OPTIONS \n"; //If time allows, come back to try to edit colors.
			cout << setw(62) << "4. CREDITS \n"; 
			cout << setw(59) << "5. EXIT \n";



												 // very sensitive to spaces and tabs do not change.
			cout << yellow << " . _  .    ." << red << "__ " << yellow << " .  .  __,--' " << endl;
			cout << yellow << "  (_)    ' " << red << "/__\\" << yellow << " __,--' " << endl;
			cout << yellow << "'  .  ' . '" << white << "| " << yellow << "o" << white << "|" << yellow << "' " << endl;
			cout << "          " << white << "[" << brown << "IIII" << white << "]" << yellow << "`--.__ " << endl;
			cout << white << "           |  |       " << yellow << "`--.__ " << endl;
			cout << red << "           | :|             " << yellow << "`--.__ " << endl;
			cout << white << "           |  |                   " << yellow << "`--.__ " << endl;
			cout << lightblue << "._,,.-," << darkgrey << ".__." << white << "'__`" << darkgrey << ".___." << lightblue << ",.,.-..,_.,.,.,-._..`" << yellow << "--" << lightblue << ".." << yellow << "-" << lightblue << ".,._.,,._,-,..,._..,.,_,,._.,,._,-,..,._..,.,_,,._.,,._,-,..,._..,.,_,,.,, " << endl;
			//SOURCE: http://ascii.co.uk/art/lighthouse Made originally by: unknown
			// very sensitive to spaces and tabs do not change.

			cout << endl << setw(62) << white << "Enter 1 - 5: ";
			//keep running until the player gives an appropriate number

			if (heardItonce == false)
			{
				startSound();
				heardItonce = true;
			}
			cin >> players;
			


			//players has to equal 1-3 if it does not, run it again.
			if (players == 1 || players == 2 || players == 3 || players == 4 || players == 5)//HERE doesnt seem to want to loop for some reason also need an array for the player choice since this is staying a void function to pass on the choice 1 or 2 Maybe an OPTION button to change the colors? that would be cool. maybe a few presets
			{
				menuNumber = true;
			}
			else if (players != 1 || players != 2 || players != 3 || players != 4 || players != 5)
			{
				system("cls");
				cout << endl << endl << endl << endl << endl << endl << endl;
				cout << setw(75) << lightred << "Invalid Input, please try a number 1-5" << endl;
				cin.clear();
				cin.ignore(10000, '\n'); // cin clear and cin.ignore was important to have to stop a infinite loop if someone puts a character into the main menu. and not 1-3
				//players = 0;
				errorSound();
				Sleep(1000);
				//menuNumber = false;
				//break;
			}
			else
			{
				cout << "Your trying to break my program, are you? I can do that myself, try again." << endl;
				Sleep(1000);
				errorSound();
			}


		} while (menuNumber == false);
		system("cls");

		if (players == 1)//1 player vs ai.
		{
			onePlayer(difficulty, boardNum, boardChoose);

		}
		else if (players == 2)//2 players - Primary Focus
		{

			TwoPlayer(difficulty);

		}
		else if (players == 3)//Options
		{
			Options(difficulty, boardNum, boardChoose);
		}
		else if (players == 4)
		{
			credits();
		}
		else if (players == 5)
		{
			exit();
		}
		else
		{
			cout << "How'd you get here? Your not supposed to be here." << endl;
			errorSound();

		}

		return players;
	}
}

void TwoPlayer(int difficulty)
{
	//Variables
	string PlayerX;

	const int ROWS = 11;
	const int COLUMNS = 11;

	string userDirectionalInput;

	string spaceOne = " "; //letter that player enters for coordinate 1
	int spaceTwo = 0; //Number that player enters for coordinate 2
	int spaceOneNum = 0; //Number conversion between char and int for spaceOne

	bool validInput = false; //Making sure their guess stays within bounds of the board ...
							 //validInput will be tied to chkPlacement(); if the placement is good it will return 
							 //that it is okay and the next ship will be able to be placed. Erik- 11/26/17
	bool promptCheck = false;

	const int ships = 5;

	//directional variables
	//accounting for the first input, each additional variable -
	// - will be based on the points availble to it. Destroyer has two points -
	// - so along with the first cord put in, we need one additional input.
	// etc. Erik 11.15.2017

	//with the initial cord this makes 2 spots
	int destroy = 0;
	int destroy1 = 0;

	//with the initial cord this makes 3 spots
	int sub = 0;
	int sub1 = 0;
	int sub2 = 0;


	/*sub, cruis, battleship, carrier
	int&, int&, int&, int&
	int &sub, int &cruis, int &battleship, int &carrier*/

	//with the initial cord this makes 3 spots
	int cruis = 0;
	int cruis1 = 0;
	int cruis2 = 0;

	//with the initial cord this makes 4 spots
	int battleship = 0;
	int battleship1 = 0;
	int battleship2 = 0;
	int battleship3 = 0;

	//with the initial cord this makes 5 spots
	int carrier = 0;
	int carrier1 = 0;
	int carrier2 = 0;
	int carrier3 = 0;
	int carrier4 = 0;

	//redo ship placement
	bool happy = false;
	int redoShipsPlace = 0;

	 

	//11.14.17 observation Erik
	// our ships arent actually tied to anything in our arrays..
	// were replacing ~ with Xs for place holders of the ships but they dont actually represent Destroyer equals 3 spots
	// but not just that we cant - a point from the ship, of course the entire ship will make up a point a piece per array but if we kept coding now it would
	// be more difficult to try to fix what the destroyer represents on the board.
	//11.15.17 Erik.
	//Currrent setup is more like the missile attack then the ship placement.

	string shipName[ships] = { "Destroyer","Submarine","Cruiser","Battleship","Carrier" };
	int shipsLeft = ships;


	string board[ROWS][COLUMNS] = { { " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "B",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "C",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "D",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "E",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "F",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "G",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "H",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "I",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "J",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" } };

	//could these boards be their own function to use repeatedly? pretty sure we will need a third board.

	string shipsPlaced[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
											{ "A",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "B",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "C",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "D",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "E",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "F",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "G",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "H",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "I",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
											{ "J",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };


	//new individual ship boards, Erik 11/27/17 this will replace shipsPlaced

	//Obsolete boards, Erik 11/28/17, need to remove where their being sent to before deleting / commenting out.

	placeShipsPlayerOne();


	//Player One

	//another loop surronding all this for shipName[ships] until all ships are placed on the board.
	do //for happy with placement?
	{
		if (redoShipsPlace != 0)
		{
			boardRESET(shipsPlaced);

		}
		for (int count = 0; count < ships; count++)
		{
			if (redoShipsPlace != 0)
			{
				count = 0;
				redoShipsPlace = 0;
			}


			//dowhile and valid input are work on progress for ship placement to avoid stacking and ship placement over the board. Erik 11/26/17
			do {
				validInput = false;
				firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced, happy); // count and ships could go into here to move the cout prompt down?
				secCoord(spaceTwo, promptCheck, board, shipName, count, shipsPlaced, happy);


				setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck, shipsPlaced, happy);
				cout << endl << endl;
				validInput = refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, validInput);
			} while (validInput == false);

		}


		redoShipsPlace++;
		happy = happyPlacement(happy, shipsPlaced, board);

	} while (happy == false);

	playerTwoTakeOver();
	missiles(board, shipsPlaced, spaceOne, spaceTwo, spaceOneNum, promptCheck, difficulty, happy);

}

void up(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{

	//put a check in the directionals to decide if its overlapping ships / board?

	if (count == 0) // 0 is the destroyer, 2 spots
	{
		destroy = spaceOneNum;
		destroy1 = (spaceOneNum - 1);   // may be prudent to make an additional variable since spaceOneNum will rewrite all the time. like..
										// destroy = spaceOneNum;   Erik 11/15/17
	}
	else if (count == 1) // 1 is the submarine, 3 spots
	{
		sub = spaceOneNum;
		sub1 = (spaceOneNum - 1);
		sub2 = (spaceOneNum - 2);

	}
	else if (count == 2) // 2 is the cruiser, 3 spots
	{
		cruis = spaceOneNum;
		cruis1 = (spaceOneNum - 1);
		cruis2 = (spaceOneNum - 2);
	}
	else if (count == 3) // 3 is the battleship, 4 spots
	{
		battleship = spaceOneNum;
		battleship1 = (spaceOneNum - 1);
		battleship2 = (spaceOneNum - 2);
		battleship3 = (spaceOneNum - 3);

	}
	else if (count == 4) // 4 is the airship carrier, 5 spots
	{
		carrier = spaceOneNum;
		carrier1 = (spaceOneNum - 1);
		carrier2 = (spaceOneNum - 2);
		carrier3 = (spaceOneNum - 3);
		carrier4 = (spaceOneNum - 4);

	}

}

void down(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{



	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceOneNum;
		destroy1 = (spaceOneNum + 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceOneNum;
		sub1 = (spaceOneNum + 1);
		sub2 = (spaceOneNum + 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceOneNum;
		cruis1 = (spaceOneNum + 1);
		cruis2 = (spaceOneNum + 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceOneNum;
		battleship1 = (spaceOneNum + 1);
		battleship2 = (spaceOneNum + 2);
		battleship3 = (spaceOneNum + 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceOneNum;
		carrier1 = (spaceOneNum + 1);
		carrier2 = (spaceOneNum + 2);
		carrier3 = (spaceOneNum + 3);
		carrier4 = (spaceOneNum + 4);

	}

}

void left(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{


	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceTwo;
		destroy1 = (spaceTwo - 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceTwo;
		sub1 = (spaceTwo - 1);
		sub2 = (spaceTwo - 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceTwo;
		cruis1 = (spaceTwo - 1);
		cruis2 = (spaceTwo - 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceTwo;
		battleship1 = (spaceTwo - 1);
		battleship2 = (spaceTwo - 2);
		battleship3 = (spaceTwo - 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceTwo;
		carrier1 = (spaceTwo - 1);
		carrier2 = (spaceTwo - 2);
		carrier3 = (spaceTwo - 3);
		carrier4 = (spaceTwo - 4);

	}

}

void right(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{


	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceTwo;
		destroy1 = (spaceTwo + 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceTwo;
		sub1 = (spaceTwo + 1);
		sub2 = (spaceTwo + 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceTwo;
		cruis1 = (spaceTwo + 1);
		cruis2 = (spaceTwo + 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceTwo;
		battleship1 = (spaceTwo + 1);
		battleship2 = (spaceTwo + 2);
		battleship3 = (spaceTwo + 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceTwo;
		carrier1 = (spaceTwo + 1);
		carrier2 = (spaceTwo + 2);
		carrier3 = (spaceTwo + 3);
		carrier4 = (spaceTwo + 4);

	}

}

bool refresh(int &spaceOneNum, string board[][11], string shipsPlaced[][11], int &spaceTwo, int &destroy1, int &count, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy, bool &validInput)
{
	//reduced 500 lines of code in refresh(); by making error messages a function. Erik 11/29/17

	//rows and columns may be obsolete now.
	//There may be an excessive amount of 'validInput = true;' may need only 1 per direction?
	//Erik 11.27.17
	//const int ROWS = 11;
	//const int COLUMNS = 11;
	bool continu3 = true;

	//initial ship placement idea by Tristan
	//board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];


	if (count == 0) // 0 is the destroyer, 2 spots
	{
		continu3 = true;



		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{
			//older version of code to place ships. Erik, 11/27/17
			//board[spaceOneNum][spaceTwo] = destroyerBOARD[destroy][spaceTwo];
			//board[destroy1][spaceTwo] = destroyerBOARD[destroy1][spaceTwo];

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true) // if theirs an "O" at this location procede to mark shipsPlaced and write shiphits to destroyerBOARD.
			{

				//might be bloat since we found a side-step to this way.
				//destroyerBOARD[spaceOneNum][spaceTwo] = shipHits[destroy][spaceTwo]; //setting an X marker from the shipHits[][] board onto DestroyerBOARD[][]

				shipsPlaced[spaceOneNum][spaceTwo] = "d"; // visualizing the placement of the ship for player 1.

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}


			if (shipsPlaced[destroy1][spaceTwo] == "O" && continu3 == true)
			{

				shipsPlaced[destroy1][spaceTwo] = "d";
				validInput = true;
			}
			else if (shipsPlaced[destroy1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}

			//destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}


		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "d";
			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}


			if (shipsPlaced[destroy1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[destroy1][spaceTwo] = "d";
				validInput = true;
			}
			else if (shipsPlaced[destroy1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}

			//destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}

		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "d";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}


			if (shipsPlaced[spaceOneNum][destroy1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][destroy1] = "d";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][destroy1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}


			//destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "d";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][destroy1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][destroy1] = "d";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][destroy1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}

			//destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else
		{
			invalidInputRefresh();
		}

	}

	else if (count == 1) // 1 is the submarine, 3 spots
	{
		continu3 = true;
		//what if the board isnt updating the position of the ship because spaceonenum / space two arent updating to the right number..

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "s";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[sub1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[sub1][spaceTwo] = "s";

			}
			else if (shipsPlaced[sub1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}

			if (shipsPlaced[sub2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[sub2][spaceTwo] = "s";
				validInput = true;
			}
			else if (shipsPlaced[sub2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
				shipsPlaced[sub1][spaceTwo] = "O";
			}

			//submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "s";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[sub1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[sub1][spaceTwo] = "s";

			}
			else if (shipsPlaced[sub1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
			}

			if (shipsPlaced[sub2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[sub2][spaceTwo] = "s";
				validInput = true;
			}
			else if (shipsPlaced[sub2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[sub1][spaceTwo] = "O"; //reset
				shipsPlaced[spaceOneNum][spaceTwo] = "O";
			}

			//submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "s";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][sub1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][sub1] = "s";

			}
			else if (shipsPlaced[spaceOneNum][sub1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[spaceOneNum][sub2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][sub2] = "s";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][sub2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[spaceOneNum][sub1] = "O";
			}

			//submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "s";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][sub1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][sub1] = "s";

			}
			else if (shipsPlaced[spaceOneNum][sub1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[spaceOneNum][sub2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][sub2] = "s";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][sub2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[spaceOneNum][sub1] = "O";
			}

			//submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else
		{
			invalidInputRefresh();
		}

	}
	else if (count == 2) // 2 is the cruiser, 3 spots
	{
		continu3 = true;

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "c";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[cruis1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[cruis1][spaceTwo] = "c";

			}
			else if (shipsPlaced[cruis1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[cruis2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[cruis2][spaceTwo] = "c";
				validInput = true;
			}
			else if (shipsPlaced[cruis2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[cruis1][spaceTwo] = "O";
			}

			//cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "c";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[cruis1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[cruis1][spaceTwo] = "c";

			}
			else if (shipsPlaced[cruis1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[cruis2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[cruis2][spaceTwo] = "c";
				validInput = true;
			}
			else if (shipsPlaced[cruis2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[cruis1][spaceTwo] = "O";
			}

			//cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "c";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][cruis1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][cruis1] = "c";

			}
			else if (shipsPlaced[spaceOneNum][cruis1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[spaceOneNum][cruis2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][cruis2] = "c";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][cruis2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";					//reset
				shipsPlaced[spaceOneNum][cruis1] = "O";
			}

			//cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "c";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][cruis1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][cruis1] = "c";

			}
			else if (shipsPlaced[spaceOneNum][cruis1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[spaceOneNum][cruis2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][cruis2] = "c";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][cruis2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[spaceOneNum][cruis1] = "O";
			}

			//cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else
		{
			invalidInputRefresh();
		}

	}
	else if (count == 3) // 3 is the battleship, 4 spots
	{
		continu3 = true;

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "b";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[battleship1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship1][spaceTwo] = "b";

			}
			else if (shipsPlaced[battleship1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[battleship2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship2][spaceTwo] = "b";

			}
			else if (shipsPlaced[battleship2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[battleship1][spaceTwo] = "O";
			}

			if (shipsPlaced[battleship3][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship3][spaceTwo] = "b";
				validInput = true;
			}
			else if (shipsPlaced[battleship3][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[battleship1][spaceTwo] = "O";	//reset
				shipsPlaced[battleship2][spaceTwo] = "O";
			}

			//battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{
			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "b";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[battleship1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship1][spaceTwo] = "b";

			}
			else if (shipsPlaced[battleship1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[battleship2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship2][spaceTwo] = "b";

			}
			else if (shipsPlaced[battleship2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[battleship1][spaceTwo] = "O";
			}

			if (shipsPlaced[battleship3][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[battleship3][spaceTwo] = "b";
				validInput = true;
			}
			else if (shipsPlaced[battleship3][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[battleship1][spaceTwo] = "O";	//reset
				shipsPlaced[battleship2][spaceTwo] = "O";
			}

			//battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "b";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

			}

			if (shipsPlaced[spaceOneNum][battleship1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship1] = "b";

			}
			else if (shipsPlaced[spaceOneNum][battleship1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[spaceOneNum][battleship2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship2] = "b";

			}
			else if (shipsPlaced[spaceOneNum][battleship2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[spaceOneNum][battleship1] = "O";
			}

			if (shipsPlaced[spaceOneNum][battleship3] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship3] = "b";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][battleship3] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][battleship1] = "O";	//reset
				shipsPlaced[spaceOneNum][battleship2] = "O";
			}

			//battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "b";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[spaceOneNum][battleship1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship1] = "b";

			}
			else if (shipsPlaced[spaceOneNum][battleship1] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
			}

			if (shipsPlaced[spaceOneNum][battleship2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship2] = "b";

			}
			else if (shipsPlaced[spaceOneNum][battleship2] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][battleship1] = "O";
			}

			if (shipsPlaced[spaceOneNum][battleship3] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][battleship3] = "b";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][battleship3] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][battleship1] = "O";	//reset
				shipsPlaced[spaceOneNum][battleship2] = "O";
			}

			//battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else
		{
			invalidInputRefresh();
		}

	}
	else if (count == 4) // 4 is the airship carrier, 5 spots
	{
		continu3 = true;

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "a";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[carrier1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier1][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
			}

			if (shipsPlaced[carrier2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier2][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
				shipsPlaced[carrier1][spaceTwo] = "O";
			}

			if (shipsPlaced[carrier3][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier3][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier3][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[carrier1][spaceTwo] = "O";			//reset
				shipsPlaced[carrier2][spaceTwo] = "O";
			}

			if (shipsPlaced[carrier4][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier4][spaceTwo] = "a";
				validInput = true;
			}
			else if (shipsPlaced[carrier4][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[carrier1][spaceTwo] = "O";			//reset
				shipsPlaced[carrier2][spaceTwo] = "O";			//reset
				shipsPlaced[carrier3][spaceTwo] = "O";
			}

			//carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "a";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);
			}

			if (shipsPlaced[carrier1][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier1][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier1][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
			}

			if (shipsPlaced[carrier2][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier2][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier2][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[carrier1][spaceTwo] = "O";

			}

			if (shipsPlaced[carrier3][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier3][spaceTwo] = "a";

			}
			else if (shipsPlaced[carrier3][spaceTwo] != "O" && continu3 == true)
			{
				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[carrier1][spaceTwo] = "O";			//reset
				shipsPlaced[carrier2][spaceTwo] = "O";
			}

			if (shipsPlaced[carrier4][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[carrier4][spaceTwo] = "a";
				validInput = true;
			}
			else if (shipsPlaced[carrier4][spaceTwo] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[carrier1][spaceTwo] = "O";			//reset
				shipsPlaced[carrier2][spaceTwo] = "O";			//reset
				shipsPlaced[carrier3][spaceTwo] = "O";
			}

			//carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "a";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

			}

			if (shipsPlaced[spaceOneNum][carrier1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier1] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier1] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset


			}

			if (shipsPlaced[spaceOneNum][carrier2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier2] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier2] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";

			}

			if (shipsPlaced[spaceOneNum][carrier3] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier3] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier3] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier2] = "O";

			}

			if (shipsPlaced[spaceOneNum][carrier4] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier4] = "a";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][carrier4] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier2] = "O";						//reset
				shipsPlaced[spaceOneNum][carrier3] = "O";

			}

			//carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{

			if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][spaceTwo] = "a";

			}
			else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);


			}


			if (shipsPlaced[spaceOneNum][carrier1] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier1] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier1] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset

			}


			if (shipsPlaced[spaceOneNum][carrier2] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier2] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier2] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";

			}

			if (shipsPlaced[spaceOneNum][carrier3] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier3] = "a";

			}
			else if (shipsPlaced[spaceOneNum][carrier3] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier2] = "O";

			}

			if (shipsPlaced[spaceOneNum][carrier4] == "O" && continu3 == true)
			{
				shipsPlaced[spaceOneNum][carrier4] = "a";
				validInput = true;
			}
			else if (shipsPlaced[spaceOneNum][carrier4] != "O" && continu3 == true)
			{

				errorRefresh(validInput, continu3);

				shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier1] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier2] = "O";		//reset
				shipsPlaced[spaceOneNum][carrier3] = "O";

			}

			//carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
		}
		else
		{

			invalidInputRefresh();


		}

	}


	return validInput;

}

void errorRefresh(bool &validInput, bool &continu3)
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(85) << lightred << "---------------------------------" << endl;
	cout << setw(85) <<	"You can not place your ship here." << endl;
	cout << setw(85) <<	"---------------------------------" << endl;
	errorSound();
	Sleep(1500);
	validInput = false;
	continu3 = false;

}

void invalidInputRefresh()
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(75) << lightred << "--------------------------" << endl;
	cout << setw(75) << "Invalid input. Try again." << endl;
	cout << setw(75) << "--------------------------" << endl;
	errorSound();
}

void shipHPCounter(string board[][11], string shipsPlaced[][11], bool &happy)
{
	//code in destHP etc to fill in here to point to the asci art on hits etc. Erik 11/29/17

	int dCounter = 0;
	int sCounter = 0;
	int cCounter = 0;
	int bCounter = 0;
	int aCounter = 0;
	int totalCounter;

	static bool onceThrough = false;

	bool sunkUnsunk = false;
	static bool totalCounterUnlock = false;

	static bool dSunk = false;
	static bool sSunk = false;
	static bool cSunk = false;
	static bool bSunk = false;
	static bool aSunk = false;

	//int sevenTeen = 18;
	//happy is in 10+ functions to get it into shipHPCounter, will be a pain to remove, do later.

	//static int twoPlayerCounter = 0;
	
	//happy = true; // never changes from true ><
	cout << endl;
	//counter is weird at the moment, set to 17.

	//if (happy == true) // weird errors on reset.  // 11/30/17 Erik, extra steps were unnecessary code is working exactly how I want, adding extra steps on how I thought it SHOULD work made it not work.
	//{
	//	sevenTeen = (sevenTeen + sevenTeen);

	//}

	//if (twoPlayerCounter < sevenTeen) // may need to adjust the less than or the != in the else if statement will see once hit is up.
	//{
	if (victoryScreen == false)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int z = 0; z < 11; z++)
			{
				if (shipsPlaced[i][z] == "d") // had it set to ships placed && comparing to board before maybe why not working.
				{
					dCounter++;
				}

				else if (shipsPlaced[i][z] == "s")
				{
					sCounter++;
				}

				else if (shipsPlaced[i][z] == "c")
				{
					cCounter++;
				}

				else if (shipsPlaced[i][z] == "b")
				{
					bCounter++;
				}

				else if (shipsPlaced[i][z] == "a")
				{
					aCounter++;
				}
			}


		}


		//}
		//else if (twoPlayerCounter > sevenTeen)
		//{
			//dCounter = 2;
			//sCounter = 3;
			//cCounter = 3;
			//bCounter = 4;
			//aCounter = 5;


		for (int y = 0; y < 11; y++)
		{
			for (int x = 0; x < 11; x++)
			{

				if (board[y][x] == "X" && shipsPlaced[y][x] == "d") // not counting correctly
				{
					dCounter--;


					if (dCounter == 0 && dSunk == false)
					{

						shipDestroyed();
						cout << setw(65) << "You sunk my destroyer!" << endl;
						sinkSound();
						Sleep(1500);
						sunkUnsunk = true;
						dSunk = true;
						system("cls");
						displayBlankTwoa(board, shipsPlaced, happy);
						totalCounterUnlock = true; //have to destroy at LEAST one ship to unlock game over scenario


					}
				}

				if (board[y][x] == "X" &&  shipsPlaced[y][x] == "s")
				{
					sCounter--;


					if (sCounter == 0 && sSunk == false)
					{

						shipDestroyed();
						cout << setw(65) << "You sunk my submarine!" << endl;
						sinkSound();
						Sleep(1500);
						sunkUnsunk = true;
						sSunk = true;
						system("cls");
						displayBlankTwoa(board, shipsPlaced, happy);
						totalCounterUnlock = true; //have to destroy at LEAST one ship to unlock game over scenario

					}
				}

				if (board[y][x] == "X" && shipsPlaced[y][x] == "c")
				{
					cCounter--;


					if (cCounter == 0 && cSunk == false)
					{

						shipDestroyed();
						cout << setw(65) << "You sunk my cruiser!" << endl;
						sinkSound();
						Sleep(1500);
						sunkUnsunk = true;
						cSunk = true;
						system("cls");
						displayBlankTwoa(board, shipsPlaced, happy);
						totalCounterUnlock = true; //have to destroy at LEAST one ship to unlock game over scenario
					}
				}

				if (board[y][x] == "X" && shipsPlaced[y][x] == "b")
				{
					bCounter--;


					if (bCounter == 0 && bSunk == false)
					{

						shipDestroyed();
						cout << setw(65) << "You sunk my battleship!" << endl;
						sinkSound();
						Sleep(1500);
						sunkUnsunk = true;
						bSunk = true;
						system("cls");
						displayBlankTwoa(board, shipsPlaced, happy);
						totalCounterUnlock = true; //have to destroy at LEAST one ship to unlock game over scenario
					}
				}

				if (board[y][x] == "X" && shipsPlaced[y][x] == "a")
				{
					aCounter--;


					if (aCounter == 0 && aSunk == false)
					{

						shipDestroyed();
						cout << setw(65) << "You sunk my air-carrier!" << endl;
						sinkSound();
						Sleep(1500);
						sunkUnsunk = true;
						aSunk = true;
						system("cls");
						displayBlankTwoa(board, shipsPlaced, happy);
						totalCounterUnlock = true; //have to destroy at LEAST one ship to unlock game over scenario
					}
				}
			}
		}

		totalCounter = (dCounter + sCounter + cCounter + bCounter + aCounter);

		//}
		//twoPlayerCounter++;
		//cout << twoPlayerCounter; //testing where the counters were at and for the boolean, pay no mind to these.
		//cout << " " << happy;
		//cout << totalCounter;
		if (sunkUnsunk == false)
		{
			cout << setw(25) << white << "Destroyer: " << lightgreen << dCounter << white << "   Sub: " << lightgreen << sCounter << white << "   Cruiser: " << lightgreen << cCounter << white << "   Battleship: " << lightgreen << bCounter << white << "   Air-carrier: " << lightgreen << aCounter << endl;
		}

		if (totalCounter == 0 && totalCounterUnlock == true)//game over scenario.
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(75) << lightgreen << "==========================================" << endl;
			cout << setw(75) << lightgreen << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
			cout << setw(75) << lightgreen << "==========================================" << endl;
			if (onceThrough == false)
			{
				onceThrough = true;
				vicSound();
			}
			victoryScreen = true;
			
			//cout << victoryScreen; //testing

		}

	}

}

bool happyPlacement(bool &happy, string shipsPlaced[][11], string board[][11])
{
	string yesNo;
	bool noYes = false;
	
	do
	{
		system("cls");
		displayBlankTwo(board, shipsPlaced, happy);
		cout << endl << endl << setw(60) << white << "Are you happy with your ships placement? (" << yellow << "y" << white << "/" << yellow << "n" << white << "): ";
		cin >> yesNo;
		if (yesNo == "yes" || yesNo == "YES" || yesNo == "Yes" || yesNo == "y" || yesNo == "Y" || yesNo == "no" || yesNo == "NO" || yesNo == "No" || yesNo == "n" || yesNo == "N")
		{
			noYes = true;
		}

	} while (noYes == false);

	if (yesNo == "yes" || yesNo == "YES" || yesNo == "Yes" || yesNo == "y" || yesNo == "Y")
	{
		happy = true;
	}
	else if (yesNo == "no" || yesNo == "NO" || yesNo == "No" || yesNo == "n" || yesNo == "N")
	{
		happy = false;
	}

	return happy;

}

void boardRESET(string shipsPlaced[][11])
{
	for (int i = 1; i < 11; i++) // keep at i and e = 1 or it will reset A-J and 1-10 Erik. 11/29/17
	{
		for (int e = 1; e < 11; e++)
		{
			shipsPlaced[i][e] = "O";

		}
	}

}

void missiles(string board[][11], string shipsPlaced[][11], string &spaceOne, int &spaceTwo, int &spaceOneNum, bool &promptCheck, int &difficulty, bool &happy)
{
	bool hitCheck = false;
	string exitVal;
	bool exitInput = false;
	victoryScreen = false;
	//cout << victoryScreen; //testing
	//while (!victoryScreen) // not working >< argh
	//{
		//change 100 to difficulty base that into options then difficulty will equal easy, normal or hard and each of those will have their own variables.
	
		for (int count = 0; count < difficulty; count++)
		{
			shipHPCounter(board, shipsPlaced, happy);
			if (victoryScreen == true)
			{
				count = difficulty - 1;
				//break;
				//hitCheck = true;
			}
			else if (victoryScreen == false)
			{

			
				//hitCheck = true;
			//}
			//hitCheck = false;
				do 
				{
						hitCheck = false;
						//system("cls");
						//displayBlankTwoa(board, shipsPlaced);

						
							firstMissileYAxis(spaceOne, spaceOneNum, board, shipsPlaced, count, promptCheck, happy, difficulty);
							secondMissileXAxis(spaceTwo, board, shipsPlaced, count, promptCheck, happy, difficulty);
					
						if (board[spaceOneNum][spaceTwo] == "X" || board[spaceOneNum][spaceTwo] == "O")
						{
							system("cls");
							cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
							cout << setw(75) << lightred << "===================================" << endl;
							cout << setw(75) << lightred << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
							cout << setw(75) << lightred << "===================================" << endl;
							errorSound();
							Sleep(1500);
						}


						if (board[spaceOneNum][spaceTwo] == "~")
						{
							board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

							if (board[spaceOneNum][spaceTwo] == "d" || board[spaceOneNum][spaceTwo] == "s" || board[spaceOneNum][spaceTwo] == "c" || board[spaceOneNum][spaceTwo] == "b" || board[spaceOneNum][spaceTwo] == "a")
							{

								board[spaceOneNum][spaceTwo] = "X";
								hitCheck = true;
								displayHit(count, difficulty);
								Sleep(1500);
							}
							else if (board[spaceOneNum][spaceTwo] == "O")
							{
								displayMiss(count, difficulty);
								Sleep(1500);
								hitCheck = true;
							}
						}
					


				} while (hitCheck == false);


			} 
		}
		while (!exitInput)
		{
			cout << endl << endl << endl;
			cout << setw(65) << white << "DO YOU WISH TO PLAY AGAIN? "<< yellow << "y" << white << "/" << yellow << "n" << white <<": ";
			cin >> exitVal;
			if (exitVal == "N" || exitVal == "n" || exitVal == "No" || exitVal == "no" || exitVal == "NO")
			{
				exitInput = true;
				endInput = true;
				mainMenu();
			}
			else if (exitVal == "Y" || exitVal == "y" || exitVal == "Yes" || exitVal == "yes" || exitVal == "YES")
			{
				exitInput = true;
				mainMenu();
			}
			else
			{
				invalidInputRefresh();
				Sleep(2000);
				system("cls");
			}
		}
}

void firstMissileYAxis(string &spaceOne, int &spaceOneNum, string board[][11], string shipsPlaced[][11], int &count, bool &promptCheck, bool &happy, int &difficulty)
{
	//variables
	const int ROWS = 11;
	string sletter = "a";
	string sLETTER = "A";
	char letter;
	char cLETTER;
	

	//===========FOR TWO PLAYER==========================================================================
	cin.clear();
	cin.ignore(10000, '\n');
	if (victoryScreen == false)
	{
		do
		{
			do
			{
				//board_intilization(spaceOneNum, spaceTwo);
				system("cls");
				displayBlankTwoa(board, shipsPlaced, happy); //board // lets you visualize the board when placing the ships cord on the X - ROWS axis

				cout << endl;
				cout << white << setw(55) << "Player two, you have " << yellow << (difficulty - count) << white << " missiles left" << endl; //change this to be like st, nd, rd, th on count

				cout << setw(45) << white << "Using letters "<< yellow << "A" << white << "-" << yellow << "J" << white << ", enter your coordinates: ";
				cin >> spaceOne;
			} while (spaceOne.length() != 1);

			//check to see if input is a-j or A-J before sending it on.
			if ((spaceOne >= "a" && spaceOne <= "j") || (spaceOne >= "A" && spaceOne <= "J"))
			{
				promptCheck = true;



			}
			else
			{
				cout << endl;
				cout << setw(74) << lightred << "=========================================================" << endl;
				cout << setw(75) << "This is not a valid input. Try again, using a letter a-j. " << endl;
				cout << setw(74) << "=========================================================" << endl;
				errorSound();
				Sleep(1500);
				cin.clear();
				cin.ignore(10000, '\n');
				system("cls");

			}
		} while (promptCheck == false);
	}
		//============================END TWO PLAYER==============================================================

		//talking about the loop below not above.
		//Now this loops through ROWS which is not dynamic at the moment, with the function 
		//in board_intilization(); so if we change one manually has to do both inless
		//we change board_intilization(); from a void into an int and carry it over; or use &

		//'i' will cycle through the number of rows, and increment i, i will only add
		//to spaceonenum if the letter equals spaceOne. should catch before hand if
		//their is a letter that is not a-j before here. adding +1 to i as my board
		// will be including A-J and the 1-9 will also carry a plus 1; oh and 0 == 10 inless
		// we can figure out a way to implement that char into a string? to carry more than one value.




		for (int i = 0; i < ROWS; i++) //once a char has been chosen highlight it another color to help the user see the change on the board? cyan > red?
		{
			if ((spaceOne == sletter) || (spaceOne == sLETTER))
			{
				spaceOneNum = (i + 1);
			}

			//new conversion for ++ on the letter.
			letter = sletter.at(0);
			letter++;
			sletter = letter;

			cLETTER = sLETTER.at(0);
			cLETTER++;
			sLETTER = cLETTER;

			//old conversion that worked with the char boards.
			//letter++;
			//cLETTER++;
		}

	
}

void secondMissileXAxis(int &spaceTwo, string board[][11], string shipsPlaced[][11], int &count, bool &promptCheck, bool &happy, int &difficulty)
{
	promptCheck = false;
	cin.clear();
	cin.ignore(10000, '\n');

	if (victoryScreen == false)
	{
		while (!promptCheck)
		{

			system("cls");
			//board_intilization(spaceOneNum, spaceTwo);
			displayBlankTwoa(board, shipsPlaced, happy); //board // lets you visualize the board when placing the ships cord on the Y - COlS axis

			cout << endl;
			cout << white << setw(55) << "Player two, you have " << yellow << (difficulty - count) << white << " missiles left." << endl;
			cout << setw(40) << white << "Using numbers " << yellow << "1" << white << "-" << yellow << "10" << white << ", enter your second coordinate: ";
			cin >> spaceTwo;


			if (spaceTwo >= 1 && spaceTwo <= 10)
			{
				promptCheck = true;
				spaceTwo = (spaceTwo);

			}
			else
			{
				cout << endl;
				cout << setw(75) << lightred << "============================================================" << endl;
				cout << setw(75) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
				cout << setw(75) << "============================================================" << endl;
				errorSound();
				//cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
				cout << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				Sleep(1500);
				system("cls");

			}

		}
		promptCheck = false;
	}

}

//ascii art

//Erik 11/13/17
//           ascii art place holder until we get to it.
//if things look off center its because \\ is required for one 
//backslash to be recognized in cout. if things are not lining 
//up in the command prompt it may be because i missed a backslash
//game over / you won! with x amount of shots left. time left? or with a total time.

void displayHit(int count, int difficulty) // not set to anything yet.
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(100) << yellow << "	                (                                                 (   (      (   " << endl;
	cout << setw(100) << yellow << "  *   )   (     )\\ ) (           *   )     (       (    (         )\\ ))\\ )   )\\ )   " << endl;
	cout << setw(100) << lightred << "` )  /(   )\\   (()/( )\\ )   (  ` )  /(     )\\      )\\ ( )\\     ( (()/(()/(( (()/(   " << endl;
	cout << setw(100) << red << " ( )(_)|(((_)(  /(_)|()/(   )\\  ( )(_)) ((((_)(  (((_))((_)    )\\ /(_))(_))\\ /(_))  " << endl;
	cout << setw(17) << red << "(" << white << "_" << red << "(" << white << "_" << red << "()) )\\ " << white << "_ " << red << ")\\(" << white << "_" << red << "))  /(" << white << "_" << red << "))" << white << "_" << red << "((" << white << "_" << red << ")(" << white << "_" << red << "(" << white << "_" << red << "())   )\\ " << white << "_ " << red << ")\\ )\\" << white << "__" << red << "((" << white << "_" << red << ")" << white << "_  _ " << red << "((" << white << "_" << red << "|" << white << "_" << red << "))(" << white << "_" << red << "))((" << white << "_" << red << "|" << white << "_" << red << "))" << white << "_   " << endl;
	cout << setw(100) << "|_   _| (_)_\\(_) _ \\(_)) __| __|_   _|   (_)_\\(_|(/ __/ _ \\| | | |_ _| _ \\ __|   \\  " << endl;
	cout << setw(100) << "  | |    / _ \\ |   /  | (_ | _|  | |      / _ \\  | (_| (_) | |_| || ||   / _|| |) | " << endl;
	cout << setw(100) << "  |_|   /_/ \\_\\|_|_\\   \\___|___| |_|     /_/ \\_\\  \\___\\__\\_\\\\___/|___|_|_\\___|___/  " << endl;

	//cout << victoryScreen; //testing


	//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php
	count = (difficulty - 1) - count; // change 30 to 'difficulty' and adjust difficulty to amount of shots

	cout << endl << setw(54) << "You have, " << count << " shots left." << endl;
	cout << endl << endl << endl << endl;
	hitSound();

	if (count == 0)
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(70) << white << "=====================" << endl;
		cout << setw(71) << white << "TARGETS EVADED ATTACK\n" << setw(64) << lightred << "YOU LOSE" << endl;
		cout << setw(70) << white << "=====================" << endl;
		//Sleep(2000);
		youLoseSound();
	}

}

void displayMiss(int count, int difficulty) //Still unable to get displayed properly in command window
{
	//collaberated on by both tristan and erik.
	system("cls");
	//when shot was missed trigger this
	//green?
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(86) << " __   _____  _   _   __  __ ___ ____ ____  _____ ____  " << endl;
	cout << setw(86) << " \\ \\ / / _ \\| | | | |  \\/  |_ _/ ___/ ___|| ____|  _ \\ " << endl;
	cout << setw(86) << "  \\ \V / | | | | | | | |\\/| || |\\___ \\___ \\|  _| | | | |" << endl;
	cout << setw(86) << "   | || |_| | |_| | | |  | || | ___) |__) | |___| |_| |" << endl;
	cout << setw(86) << "   |_| \\___/ \\___/  |_|  |_|___|____/____/|_____|____/ " << endl;

	//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php
	count = (difficulty - 1) - count; // change 30 to 'difficulty' and adjust difficulty to amount of shots
	//cout << victoryScreen; //testing
	cout << endl << setw(55) << "You have, " << count << " shots left." << endl;
	cout << endl << endl << endl << endl;
	missSound();
	
	if (count == 0)
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(70) << white << "=====================" << endl;
		cout << setw(71) << white << "TARGETS EVADED ATTACK\n" << setw(64) << lightred << "YOU LOSE" << endl;
		cout << setw(70) << white << "=====================" << endl;
		//Sleep(2000);
		youLoseSound();
	}
}

void shipDestroyed()
{
	//this needs to be tested if it needs to be formated still, and colorized. Erik 11/27/17
	system("cls");
	//ship blows up use this,
	//red and orange black/grey
	cout << endl << endl << endl << endl << endl << endl;
	cout << setw(62) << yellow << "                             \\         .  ./" << endl;
	cout << setw(65) << yellow << "                           \\      .: ; '.:..    /" << endl;
	cout << setw(53) << yellow << "                               (M^^."<< lightred <<"^~~:.' )." << endl;
	cout << setw(54) << yellow << "                         -   (/  .   "<< lightred <<" . . \\ \\)  -" << endl;
	cout << setw(53) << yellow << "                            ((| :. ~"<< red <<" ^  :. .|))" << endl;
	cout << setw(55) << red << "                         -   (\\- |  \\ "<< yellow <<"/  |  /)  -" << endl;
	cout << setw(56) << yellow << "                              -\\  \\    "<< red <<" /  /-" << endl;
	cout << setw(60) << red << "                                \\  \\   /  /" << endl;
	cout << setw(55) << yellow << "                                  |  | "<< red <<" |  |" << endl;
	cout << setw(60) << yellow << "                                  |  |  |  |" << endl;

	cout << endl;
	//Made with the help of this site, SOURCE:	 http://www.chris.com/ascii/index.php?art=objects/explosives

	// you blew up // you lost your // x ship.				 
}

void displayBlankTwoa(string board[][11], string shipsPlaced[][11], bool &happy)
{
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	const int ROWS = 11;
	const int COLUMNS = 11;

	cout << setw(115) << darkgrey << div << endl; // divider ' === '
	for (int i = 0; i < ROWS; i++)
	{
		cout << darkgrey << setw(5) << "|";
		for (int s = 0; s < COLUMNS; s++)
		{
			//if else added by Tristan to make our X equal red & 0 equal white.
			if (board[i][s] == "X")
			{
				cout << setw(5) << red << board[i][s] << setw(5) << darkgrey << "|";
			}
			else if (board[i][s] == "O")
			{
				cout << setw(5) << white << board[i][s] << setw(5) << darkgrey << "|";
			}
			//ship colors
			else if (board[i][s] == "d" || board[i][s] == "s" || board[i][s] == "c" || board[i][s] == "b" || board[i][s] == "a")
			{
				cout << setw(5) << lightgreen << board[i][s] << setw(5) << darkgrey << "|"; // using lightgreen, magneta looked bright as well. I want something that is visible and seperate from the border text
			}
			else if (board[i][s] == "~")
			{
				cout << setw(5) << lightcyan << board[i][s] << setw(5) << darkgrey << "|";
			}
			else
			{
				cout << setw(5) << cyan << board[i][s] << setw(5) << darkgrey << "|";
			}
		}
		if (i != ROWS - 1)
		{
			cout << endl << setw(115) << between << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << setw(115) << darkgrey << div << endl;


	shipHPCounter(board, shipsPlaced, happy);
	//cout << victoryScreen;
}

void playerTwoTakeOver()
{
	string readyStatus;
	bool notReady = false;

	//http://www.cplusplus.com/forum/beginner/6397/ wanted to use current date in the mission report found this. user: Corpus
	char date[9];
	_strdate(date);

	do
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(40) << white << "Mission Report:                  "<< date << endl;
		cout << left << darkgrey << "======================================================" << endl;
		cout << left << white << "There are five enemy ships about to enter your border." << endl;
		cout << left << white << "Set a trap for them." << endl;
		cout << left << white << "Don't let them escape!" << endl;
		cout << left << white << "                                  Admiral Gial Ackbar~" << endl;
		cout << left << darkgrey << "======================================================" << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(70) << right << white << "Waiting for player two to enter, '" << yellow << "R" << white << "eady' " << endl << endl;
		cout << setw(55) << right << "Enter: ";
		cin >> readyStatus;
		if (readyStatus == "Ready" || readyStatus == "ready" || readyStatus == "r" || readyStatus == "R")
		{
			notReady = true;
		}

	} while (notReady == false);
	fightSound();
	cout << endl;

	 // beat your last time, score or change message, Erik 11/29/17
	
}

void placeShipsPlayerOne()
{
	string readyStatusOne;
	bool notReadyOne = false;

	//http://www.cplusplus.com/forum/beginner/6397/ wanted to use current date in the mission report found this. user: Corpus
	char date[9];
	_strdate(date);

	do
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(40) << white << "Mission Report:                  " << date << endl;
		cout << darkgrey <<"===========================================================" << endl;
		cout << white << "Captain, this area will be a rough one to navigate through, " << endl;
		cout << white << "there have been scout reports of enemy activity in the area." << endl;
		cout << white << "Make sure you place your ships so that they will take the " << endl;
		cout << white << "least amount of damage." << endl;
		cout << white << "                                        President Skroob~" << endl;
		cout << darkgrey << "===========================================================" << endl;
		cout << endl << endl << endl << endl;
		cout << setw(75) << right << white << "Waiting for player one to enter, '"<< yellow << "R" << white << "eady' " << endl << endl;
		cout << setw(55) << right << "Enter: ";
		cin >> readyStatusOne;

		

		if (readyStatusOne == "Ready" || readyStatusOne == "ready" || readyStatusOne == "r" || readyStatusOne == "R")
		{
			notReadyOne = true;
		}

	} while (notReadyOne == false);

	chooseSound();
	
}

void exit()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << setw(65) << white << "Come back soon!" << endl;
	Sleep(3000);
}

void credits()
{
	for (int i = 0; i < 20; i++)
	{
		cout << endl;
		Sleep(100);
	}

	cout << setw(68) << white << "GAME PRODUCED BY \n \n" 
		<< setw(65) << "Chuck \n \n " 
		<< setw(63) << "Erik \n \n " 
		<< setw(62) << "Tristan \n" << endl;


	for (int i = 0; i < 8; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 7)
		{
			Sleep(3500);
		}
	}

	cout << setw(65) << white << "SOUNDS BY \n \n" 
		<< setw(61) << "Chuck \n" << endl;
	

	for (int i = 0; i < 8; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 7)
		{
			Sleep(3500);
		}
	}

	cout << setw(65) << white << "SOUNDS FROM \n \n" 
		<< setw(70) << "Dark Souls - youLose \n \n " 
		<< setw(68) << "Mortal Kombat - Choose \n \n" 
		<< setw(68) << "Mortal Kombat - fight \n \n" 
		<< setw(68) << "Kung fury - Error \n \n" 
		<< setw(68) << "Bastion - intro \n \n" 
		<< setw(69) << "Team fortress 2 Announcer - victory \n \n" 
		<< setw(80) << "You sunk my battleship! - Jim Carrey in Batman \n \n" << endl;


	for (int i = 0; i < 8; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 7)
		{
			Sleep(3500);
		}
	}

	cout << setw(65) << white << "GRAPHICS BY \n \n" 
		<< setw(61) <<"Erik \n \n " 
		<< setw(59) << "Tristan \n" << endl;

	for (int i = 0; i < 8; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 7)
		{
			Sleep(3500);
		}
	}

	cout << setw(65) << white << "ASCI ART FROM \n \n" << setw(78) << "http://www.kammerl.de/ascii/AsciiSignature.php - You missed \n \n " << setw(77) << "http://www.kammerl.de/ascii/AsciiSignature.php - Target Acquired \n" << endl;
	Sleep(350);
	cout << setw(75) << white << "http://www.chris.com/ascii/index.php?art=objects/explosives - ship destroyed \n \n" << endl;
	Sleep(350);
	cout << setw(80) << white << "http://www.kammerl.de/ascii/AsciiSignature.php - Welcome screen \n \n" << endl;
	Sleep(350);
	cout << setw(75) << white << "http://ascii.co.uk/art/lighthouse - light house \n \n" << endl;
	Sleep(350);
	cout << setw(77) << white << "http://ascii.co.uk/art/battleship - battleship \n \n" << endl;
	Sleep(350);
	cout << setw(76) << white << "http://www.kammerl.de/ascii/AsciiSignature.php - splash screen \n \n" << endl;
	Sleep(350);
	//cout << setw(65) << white << " \n \n" << endl;

	for (int i = 0; i < 8; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 7)
		{
			Sleep(3500);
		}
	}

	cout << setw(75) << white << "MADE WITH THE HELP OF... \n \n" << endl; Sleep(350);
	cout << setw(75) << white << "For explaining a hard subject easier, \n \n" << setw(70) << "Zackary Moore \n \n" << endl;
	Sleep(350);
	cout << setw(75) << white << "For bringing Color to our project \n" << setw(75) << " http://www.cplusplus.com/forum/beginner/105484/ \n" << setw(70) << " User: Giblit \n \n" << endl;
	Sleep(350);
	cout << setw(75) << white << "Youtube for research  \n \n" << endl;
	Sleep(350);
	cout << setw(72) << white << "Friends & Family \n \n" << endl;
	Sleep(350);
	cout << setw(75) << white << "Beta Tester - Jake Pavuk \n \n" << endl;
	Sleep(350);
	//cout << setw(75) << white << " \n \n" << endl;
	//Sleep(350);
	//cout << setw(75) << white << " \n \n" << endl;
	//Sleep(350);
	//cout << setw(75) << white << " \n \n" << endl;
	//Sleep(350);
	cout << setw(75) << white << "Valhalla Java (Coffee) \n \n" << endl;
	Sleep(350);
	cout << setw(67) << white << "Pizza \n \n" << endl;


	for (int i = 0; i < 12; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 11)
		{
			Sleep(3500);
		}
	}
	
	cout << setw(71) << white << "Thank you! \n \n" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << endl;
		Sleep(350);

		if (i == 10)
		{
			Sleep(3500);
		}
	}

	Sleep(3000);
	mainMenu();
}

//================================ERIK'S FUNCTIONS ABOVE==============================================================================




//===========================CHUCK'S FUNCTIONS BELOW===================================================
void startSound()
{
	Beep(576.65, 598.3); Beep(576.65, 598.3); Beep(576.65, 598.3); 
	Beep(796.74, 448.2); Beep(1153, 299.1); Beep(2054.95, 167.9); Beep(1939.61, 177.9); Beep(1728, 199.7); Beep(1539.47, 224.1); Beep(2306.6, 149.6);
	Sleep(10);
	Beep(1027.47, 335.8); Beep(969.81, 355.7); Beep(864, 399.3); 
	Beep(769.74, 448.2); Beep(1153.3, 299.1); Beep(513.74, 671.5); Beep(969.81, 355.7); Beep(1027.47, 335.8); Beep(432, 798.6);
	Sleep(10);
	Beep(576.65, 598.3); Beep(576.65, 598.3); Beep(576.65, 598.3); 
	Beep(796.74, 448.2); Beep(1153, 299.1); Beep(2054.95, 167.9); Beep(1939.61, 177.9); Beep(1728, 199.7); Beep(1539.47, 224.1); Beep(2306.6, 149.6);
	Sleep(10);
	Beep(1027.47, 335.8); Beep(969.81, 355.7); Beep(864, 399.3); Beep(769.74, 448.2); 
	Beep(1153.3, 299.1); Beep(513.74, 671.5); Beep(969.81, 355.7); Beep(1027.47, 335.8); Beep(432, 798.6);
	Sleep(10);
	Beep(576.65, 598.3); Beep(576.65, 598.3); Beep(576.65, 598.3); 
	Beep(796.74, 448.2); Beep(1153, 299.1); Beep(2054.95, 167.9); Beep(1939.61, 177.9); Beep(1728, 199.7); Beep(1539.47, 224.1); Beep(2306.6, 149.6);
	Sleep(10);
	Beep(1027.47, 335.8); Beep(969.81, 355.7); Beep(864, 399.3); Beep(769.74, 448.2); 
	Beep(1153.3, 299.1); Beep(513.74, 671.5); Beep(969.81, 355.7); Beep(1027.47, 335.8); Beep(432, 798.6);

}

void vicSound()
{
	PlaySound(TEXT("victory.wav"), NULL, SND_SYNC);
}

void missSound()
{

	PlaySound(TEXT("misssound.wav"), NULL, SND_SYNC);
}

void hitSound()
{
	PlaySound(TEXT("hitsound.wav"), NULL, SND_SYNC);
}

void sinkSound()
{
	PlaySound(TEXT("sunksound.wav"), NULL, SND_SYNC);
}

void introSound()
{
	PlaySound(TEXT("intro.wav"), NULL, SND_SYNC);

}

void chooseSound()
{
	PlaySound(TEXT("choose.wav"), NULL, SND_SYNC);
}

void fightSound()
{
	PlaySound(TEXT("fight.wav"), NULL, SND_SYNC);
}

void youLoseSound()
{
	PlaySound(TEXT("youLose.wav"), NULL, SND_SYNC);
}

void errorSound()
{
	PlaySound(TEXT("siren.wav"), NULL, SND_SYNC);
	PlaySound(TEXT("denied.wav"), NULL, SND_SYNC);
}

//===========================CHUCK'S FUNCTIONS ABOVE===================================================




//=====================TRISTAN'S FUNCTIONS BELOW=========================================

void onePlayer(int difficulty, int boardNum, bool boardChoose)
{
	srand(time(NULL));
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	bool promptCheck = false;
	bool hitCheck = false;
	bool exitInput = false;
	const int size = 11;
	string spaceOne = " "; //letter that player enters for coordinate 1
	int spaceTwo = 0;    //Number that player enters for coordinate 2
	int spaceOneNum = 0; //Number conversion between char and int for spaceOne
	int random;          //variable that determines which board the user uses
	int maxNum = 10;     //Setting the random number not to exceed 10
	int allShips = 0;    //Variable used to count how many hits have been detected. There are a total of 17 hits before all ships are sunk. So, if this number reaches 17, the game is won. Most likely a placeholder for whenever we get
						 //Hit detection properly
	int dCounter = 2;//}
	int sCounter = 3;//}
	int cCounter = 3;//} COUNTERS FOR SINGLE PLAYER HP-SYSTEM
	int bCounter = 4;//}
	int aCounter = 5;//}
	string exitVal;
	bool validInput = false; //Making sure their guess stays within bounds of the board

							 //int shotsLeft = 30; see its in 'count'

	string blank[size][size] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "B",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "C",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "D",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "E",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "F",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "G",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "H",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "I",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" },
									{ "J",  "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" , "~" } };

	string shipsPlaced[11][11] = {  { " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "G",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardOne[11][11] = { { " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
								{ "A",  "d" , "O" , "O" , "O" , "O" , "s" , "s" , "s" , "O" , "O" },
								{ "B",  "d" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "C",  "O" , "O" , "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "D",  "O" , "O" , "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "E",  "O" , "O" , "c" , "O" , "a" , "a" , "a" , "a" , "a" , "O" },
								{ "F",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "G",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "H",  "O" , "b" , "b" , "b" , "b" , "O" , "O" , "O" , "O" , "O" },
								{ "I",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "J",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardTwo[11][11] = { { " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
								{ "A", "O" , "O" , "O" , "O" , "d" , "O" , "O" , "O" , "O" , "O" },
								{ "B", "O" , "O" , "O" , "O" , "d" , "O" , "O" , "O" , "O" , "O" },
								{ "C", "O" , "O" , "c" , "c" , "c" , "O" , "O" , "O" , "O" , "O" }, //C3-5 is a 3-spot ship
								{ "D", "O" , "s" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "E", "O" , "s" , "O" , "O" , "O" , "b" , "b" , "b" , "b" , "O" },
								{ "F", "O" , "s" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "I", "O" , "O" , "a" , "a" , "a" , "a" , "a" , "O" , "O" , "O" },
								{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardThree[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "c" , "c" , "c" , "O" , "O" },
									{ "C", "O" , "d" , "d" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" },
									{ "F", "b" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" },
									{ "G", "b" , "O" , "s" , "s" , "s" , "O" , "O" , "O" , "a" , "O" },
									{ "H", "b" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" },
									{ "I", "b" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardFour[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "a" , "a" , "a" , "a" , "a" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "b" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "b" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "b" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "s" , "s" , "s" , "O" , "b" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "c" , "c" , "c" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "d" , "d" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardFive[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "s" , "O" , "c" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "s" , "O" , "c" , "O" },
									{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "s" , "O" , "c" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "d" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "d" , "O" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "b" , "b" , "b" , "b" , "O" },
									{ "J", "O" , "a" , "a" , "a" , "a" , "a" , "O" , "O" , "O" , "O" } };

	string boardSix[11][11] = { { " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
								{ "A", "O" , "O" , "O" , "s" , "s" , "s" , "O" , "O" , "O" , "b" },
								{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "b" },
								{ "C", "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" , "O" , "b" },
								{ "D", "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" , "O" , "b" },
								{ "E", "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" , "O" , "O" },
								{ "F", "d" , "d" , "O" , "O" , "a" , "O" , "O" , "O" , "O" , "O" },
								{ "G", "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" , "O" , "O" },
								{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "J", "c" , "c" , "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardSeven[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "s" , "c" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "s" , "c" , "d" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "s" , "c" , "d" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "b" , "b" , "b" , "b" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "a" , "a" , "a" , "a" , "a" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardEight[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "s" , "c" , "O" , "O" , "O" , "b" , "b" , "b" , "b" },
									{ "D", "O" , "s" , "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "s" , "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "a" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "d" , "d" , "O" , "O" , "a" , "O" , "O" , "O" } };

	string boardNine[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "d" , "d" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "c" , "O" , "O" , "s" , "s" , "s" , "O" , "O" , "O" , "O" },
									{ "D", "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "c" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "a" , "a" , "a" , "a" , "a" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "b" , "b" , "b" , "b" , "O" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardTen[11][11] = { { " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
								{ "A", "d" , "d" , "s" , "s" , "s" , "a" , "a" , "a" , "a" , "a" }, // 2, 3, 5 
								{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "F", "O" , "O" , "c" , "c" , "c" , "O" , "b" , "b" , "b" , "b" },
								{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
								{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };
	singlePlayerTakeOver();

	if (boardChoose)
	{
		random = boardNum;
	}

	else if (!boardChoose)
	{
		do
		{
			random = (rand() % maxNum);
		} while (random == 0);
	}

	for (int count = 0; count < 3; count++)
	{
		cout << setw(67) << endl << endl << endl << endl << endl << endl << "Your board number is: " << random << "." << endl << endl;
		Sleep(1000);
		system("cls");
		Sleep(100);
	}

	if (random == 1)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardOne[spaceOneNum][spaceTwo] == "d" || boardOne[spaceOneNum][spaceTwo] == "c" || boardOne[spaceOneNum][spaceTwo] == "s" || boardOne[spaceOneNum][spaceTwo] == "b" || boardOne[spaceOneNum][spaceTwo] == "a")
				{
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
				}

				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
				{

					if (blank[spaceOneNum][spaceTwo] == "~")
					{
						hitCheck = true;
						allShips++;
						displayHit(count, difficulty);
						Sleep(2000);
						HPsystemOne(boardOne, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
					else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					{
						system("cls");
						cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
						cout << setw(75) << lightred << "===================================" << endl;
						cout << setw(75) << lightred << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
						cout << setw(75) << lightred << "===================================" << endl;
						errorSound();
					}
				}
				else
				{
					hitCheck = true;
				}
			} while (!hitCheck);

				blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

				if (blank[spaceOneNum][spaceTwo] == "O")
				{
					displayMiss(count, difficulty);
					Sleep(2000);
				}
				

			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << lightred << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}

	else if (random == 2)
	{
		for (int count = 0; count < difficulty; count++)
		{
			
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardTwo[spaceOneNum][spaceTwo] == "d" || boardTwo[spaceOneNum][spaceTwo] == "c" || boardTwo[spaceOneNum][spaceTwo] == "s" || boardTwo[spaceOneNum][spaceTwo] == "b" || boardTwo[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				
					if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardTwo, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);

			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 3)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardThree[spaceOneNum][spaceTwo] == "d" || boardThree[spaceOneNum][spaceTwo] == "c" || boardThree[spaceOneNum][spaceTwo] == "s" || boardThree[spaceOneNum][spaceTwo] == "b" || boardThree[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardThree, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
			} while (!hitCheck);

			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 4)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardFour[spaceOneNum][spaceTwo] == "d" || boardFour[spaceOneNum][spaceTwo] == "c" || boardFour[spaceOneNum][spaceTwo] == "s" || boardFour[spaceOneNum][spaceTwo] == "b" || boardFour[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardFour, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 5)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardFive[spaceOneNum][spaceTwo] == "d" || boardFive[spaceOneNum][spaceTwo] == "c" || boardFive[spaceOneNum][spaceTwo] == "s" || boardFive[spaceOneNum][spaceTwo] == "b" || boardFive[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardFive, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}


	}
	else if (random == 6)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardSix[spaceOneNum][spaceTwo] == "d" || boardSix[spaceOneNum][spaceTwo] == "c" || boardSix[spaceOneNum][spaceTwo] == "s" || boardSix[spaceOneNum][spaceTwo] == "b" || boardSix[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardSix, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 7)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardSeven[spaceOneNum][spaceTwo] == "d" || boardSeven[spaceOneNum][spaceTwo] == "c" || boardSeven[spaceOneNum][spaceTwo] == "s" || boardSeven[spaceOneNum][spaceTwo] == "b" || boardSeven[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardSeven, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 8)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
			hitCheck = false;
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			if (boardEight[spaceOneNum][spaceTwo] == "d" || boardEight[spaceOneNum][spaceTwo] == "c" || boardEight[spaceOneNum][spaceTwo] == "s" || boardEight[spaceOneNum][spaceTwo] == "b" || boardEight[spaceOneNum][spaceTwo] == "a")
				 {
				shipsPlaced[spaceOneNum][spaceTwo] = "X";
				}
			if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
				 {
				hitCheck = true;
				allShips++;
				displayHit(count, difficulty);
				Sleep(2000);
				HPsystemOne(boardEight, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
				}
			else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
				 {
				system("cls");
				cout << endl << endl << endl << endl << endl << endl << endl << endl;
				cout << setw(77) << red << "===================================" << endl;
				cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
				cout << setw(77) << "===================================" << endl;
				errorSound();
				Sleep(2000);
				}
			else
				 {
				hitCheck = true;
				}
			
				
		} while (!hitCheck);
			
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}



			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 9)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardNine[spaceOneNum][spaceTwo] == "d" || boardNine[spaceOneNum][spaceTwo] == "c" || boardNine[spaceOneNum][spaceTwo] == "s" || boardNine[spaceOneNum][spaceTwo] == "b" || boardNine[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardNine, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);
			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	else if (random == 10)
	{
		for (int count = 0; count < difficulty; count++)
		{
			do
			{
				hitCheck = false;
				firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
				secCoordOne(spaceTwo, promptCheck, blank);
				if (boardTen[spaceOneNum][spaceTwo] == "d" || boardTen[spaceOneNum][spaceTwo] == "c" || boardTen[spaceOneNum][spaceTwo] == "s" || boardTen[spaceOneNum][spaceTwo] == "b" || boardTen[spaceOneNum][spaceTwo] == "a")
					 {
					shipsPlaced[spaceOneNum][spaceTwo] = "X";
					}
				if (shipsPlaced[spaceOneNum][spaceTwo] == "X" && blank[spaceOneNum][spaceTwo] != "X")
					 {
					hitCheck = true;
					allShips++;
					displayHit(count, difficulty);
					Sleep(2000);
					HPsystemOne(boardTen, shipsPlaced, dCounter, sCounter, cCounter, bCounter, aCounter, spaceOneNum, spaceTwo);
					}
				else if (blank[spaceOneNum][spaceTwo] == "X" || blank[spaceOneNum][spaceTwo] == "O")
					 {
					system("cls");
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					cout << setw(77) << red << "===================================" << endl;
					cout << setw(77) << "THIS SPACE HAS ALREADY BEEN GUESSED" << endl;
					cout << setw(77) << "===================================" << endl;
					errorSound();
					Sleep(2000);
					}
				else
					 {
					hitCheck = true;
					}
				
					
			} while (!hitCheck);
			blank[spaceOneNum][spaceTwo] = boardTen[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")
			{
				displayMiss(count, difficulty);
				Sleep(1500);
			}


			system("cls");
			displayBlankOne(blank);

			if (allShips == 17)
			{
				system("cls");
				count = difficulty - 1;
				cout << endl << endl << endl << endl << endl << endl;
				cout << setw(70) << lightgreen << "==========================================" << endl;
				cout << setw(70) << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << setw(70) << "==========================================" << endl;
				vicSound();
			}
		}
		if (allShips != 17)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(35) << white << "=====================" << endl;
			cout << setw(36) << white << "TARGETS EVADED ATTACK\n" << setw(27) << red << "YOU LOSE" << endl;
			cout << setw(35) << white << "=====================" << endl;
			youLoseSound();
		}
	}
	while (!exitInput)
	{
		cout << endl << endl << endl;
		cout << setw(65) << white << "DO YOU WISH TO PLAY AGAIN? " << yellow << "y" << white << "/" << yellow << "n" << white << ": ";
		cin >> exitVal;
		if (exitVal == "N" || exitVal == "n" || exitVal == "No" || exitVal == "no" || exitVal == "NO")
		{
			exitInput = true;
			endInput = true;
			mainMenu();
		}
		else if (exitVal == "Y" || exitVal == "y" || exitVal == "Yes" || exitVal == "yes" || exitVal == "YES")
		{
			exitInput = true;
			mainMenu();
		}
		else
		{
			invalidInputRefresh();
			Sleep(2000);
			system("cls");
		}
	}
}

//1player
void firstCoordOne(string spaceOne, int& spaceOneNum, string blank[][11], bool& promptCheck)
{

	const int ROWS = 11;
	string sletter = "a";
	string sLETTER = "A";
	//int letterASCI = 0;
	//int cLETTERASCI = 0;
	char letter;
	char cLETTER;


	do
	{
		do {
			//board_intilization(spaceOneNum, spaceTwo);
			system("cls");
			displayBlankOne(blank);
			cout << endl;
			//cout << setw(75) << white << "Using letters A-J, and then a number 1-10, enter your coordinates: ";
			cout << setw(75) << white << "Using letters A-J, enter your coordinates: ";
			cin >> spaceOne;
		} while (spaceOne.length() != 1);


		//check to see if input is a-j or A-J before sending it on.
		if (spaceOne.length() > 1)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(84) << lightred << "=========================================================" << endl;
			cout << setw(85) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(84) << "=========================================================" << endl;
			errorSound();
			Sleep(1500);
			
		}
		else if ((spaceOne >= "a" && spaceOne <= "j") || (spaceOne >= "A" && spaceOne <= "J"))
		{
			promptCheck = true;



		}
		else
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(84) << lightred << "=========================================================" << endl;
			cout << setw(85) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(84) << "=========================================================" << endl;
			errorSound();
			Sleep(1500);
			

		}
	} while (promptCheck == false);
	//============================END TWO PLAYER==============================================================

	//talking about the loop below not above.
	//Now this loops through ROWS which is not dynamic at the moment, with the function 
	//in board_intilization(); so if we change one manually has to do both inless
	//we change board_intilization(); from a void into an int and carry it over; or use &

	//'i' will cycle through the number of rows, and increment i, i will only add
	//to spaceonenum if the letter equals spaceOne. should catch before hand if
	//their is a letter that is not a-j before here. adding +1 to i as my board
	// will be including A-J and the 1-9 will also carry a plus 1; oh and 0 == 10 inless
	// we can figure out a way to implement that char into a string? to carry more than one value.




	for (int i = 0; i < ROWS; i++) //once a char has been chosen highlight it another color to help the user see the change on the board? cyan > red?
	{
		if ((spaceOne == sletter) || (spaceOne == sLETTER))
		{
			spaceOneNum = (i + 1);
		}

		//new conversion for ++ on the letter.
		letter = sletter.at(0);
		letter++;
		sletter = letter;

		cLETTER = sLETTER.at(0);
		cLETTER++;
		sLETTER = cLETTER;


	}
}

void secCoordOne(int &spaceTwo, bool &promptCheck, string board[][11])
{

	promptCheck = false;
	while (!promptCheck)
	{

		system("cls");
		//board_intilization(spaceOneNum, spaceTwo);
		displayBlankOne(board);
		cout << endl;
		cout << setw(75) << white << "Using numbers 1-10, enter your second coordinate: ";
		cin >> spaceTwo;



		if (spaceTwo >= 1 && spaceTwo <= 10)
		{
			promptCheck = true;
			spaceTwo = (spaceTwo);

		}
		else
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(85) << lightred << "============================================================" << endl;
			cout << setw(85) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
			cout << setw(85) << "============================================================" << endl;
			errorSound();
			//cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
			cout << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			Sleep(1500);
			

		}

	}
	promptCheck = false;



}

void displayBlankOne(string board[][11])
{
	//Erik 11/13/17
	//dragging variables down from, board_intilization(); uncertain when calling the 
	//function to put things inside of it when I dont want to use it inside that function 
	//but just send stuff will do something I do not want it to do. will expirment more with this later.
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	const int ROWS = 11;
	const int COLUMNS = 11;

	cout << setw(115) << darkgrey << div << endl; // divider ' === '
	for (int i = 0; i < ROWS; i++)
	{
		cout << darkgrey << setw(5) << "|";
		for (int s = 0; s < COLUMNS; s++)
		{
			//if else added by Tristan to make our X equal red & 0 equal white.
			if (board[i][s] == "X")
			{
				cout << setw(5) << red << board[i][s] << setw(5) << darkgrey << "|";
			}
			else if (board[i][s] == "O")
			{
				cout << setw(5) << white << board[i][s] << setw(5) << darkgrey << "|";
			}
			//ship colors
			else if (board[i][s] == "d" || board[i][s] == "s" || board[i][s] == "c" || board[i][s] == "b" || board[i][s] == "a")
			{
				cout << setw(5) << lightgreen << board[i][s] << setw(5) << darkgrey << "|"; // using lightgreen, magneta looked bright as well. I want something that is visible and seperate from the border text
			}
			else if (board[i][s] == "~")
			{
				cout << setw(5) << lightcyan << board[i][s] << setw(5) << darkgrey << "|";
			}
			else
			{
				cout << setw(5) << cyan << board[i][s] << setw(5) << darkgrey << "|";
			}
		}
		if (i != ROWS - 1)
		{
			cout << endl << setw(115) << between << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << setw(115) << darkgrey << div << endl;

	

}

//2player
void firstCoordTwo(string spaceOne, int &spaceOneNum, bool &promptCheck, string shipName[], int &count, string board[][11], string shipsPlaced[][11], bool &happy)
{
	//variables
	const int ROWS = 11;
	string sletter = "a";
	string sLETTER = "A";
	char letter;
	char cLETTER;
	string visualHelper;

	//===========FOR TWO PLAYER==========================================================================

	do
	{
		do {
			visualHelper = " ";
			if (count == 0)
			{
				visualHelper = "Two";
			}
			else if (count == 1 || count == 2)
			{
				visualHelper = "Three";
			}
			else if (count == 3)
			{
				visualHelper = "Four";
			}
			else if (count == 4)
			{
				visualHelper = "Five";
			}

			//board_intilization(spaceOneNum, spaceTwo);
			system("cls");
			displayBlankTwo(board, shipsPlaced, happy); //board // lets you visualize the board when placing the ships cord on the X - ROWS axis

			cout << endl << setw(20) << white << "The " << yellow << shipName[count] << white << " has " << yellow << visualHelper << white << " places it can be placed along the board." << endl;
			cout << white << setw(59) << "Player one, enter your coordinates for the " << yellow << shipName[count] << endl;
			//cout << setw(75) << white << "Using letters A-J, and then a number 1-10, enter your coordinates: ";
			cout << setw(40) << white << "Using letters "<< yellow <<"A"<< white << "-" << yellow << "J" << white <<"," << "enter your coordinates: ";
			cin >> spaceOne;
		} while (spaceOne.length() != 1);

		//check to see if input is a-j or A-J before sending it on.
		if ((spaceOne >= "a" && spaceOne <= "j") || (spaceOne >= "A" && spaceOne <= "J"))
		{
			promptCheck = true;



		}
		else
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(84) << lightred << "=========================================================" << endl;
			cout << setw(85) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(84) << "=========================================================" << endl;
			errorSound();
			Sleep(1500);
			//system("cls");

		}
	} while (promptCheck == false);
	//============================END TWO PLAYER==============================================================

	//talking about the loop below not above.
	//Now this loops through ROWS which is not dynamic at the moment, with the function 
	//in board_intilization(); so if we change one manually has to do both inless
	//we change board_intilization(); from a void into an int and carry it over; or use &

	//'i' will cycle through the number of rows, and increment i, i will only add
	//to spaceonenum if the letter equals spaceOne. should catch before hand if
	//their is a letter that is not a-j before here. adding +1 to i as my board
	// will be including A-J and the 1-9 will also carry a plus 1; oh and 0 == 10 inless
	// we can figure out a way to implement that char into a string? to carry more than one value.




	for (int i = 0; i < ROWS; i++) //once a char has been chosen highlight it another color to help the user see the change on the board? cyan > red?
	{
		if ((spaceOne == sletter) || (spaceOne == sLETTER))
		{
			spaceOneNum = (i + 1);
		}

		//new conversion for ++ on the letter.
		letter = sletter.at(0);
		letter++;
		sletter = letter;

		cLETTER = sLETTER.at(0);
		cLETTER++;
		sLETTER = cLETTER;

	}

	//cout << spaceOneNum; //testing to see if it counts right.

}

void secCoord(int &spaceTwo, bool &promptCheck, string board[][11], string shipName[], int &count, string shipsPlaced[][11], bool &happy)
{
	string visualHelper; 
	promptCheck = false;
	while (!promptCheck)
	{
		visualHelper = " ";

		if (count == 0)
		{
			visualHelper = "Two";
		}
		else if (count == 1 || count == 2)
		{
			visualHelper = "Three";
		}
		else if (count == 3)
		{
			visualHelper = "Four";
		}
		else if (count == 4)
		{
			visualHelper = "Five";
		}


		system("cls");
		//board_intilization(spaceOneNum, spaceTwo);
		displayBlankTwo(board, shipsPlaced, happy); //board // lets you visualize the board when placing the ships cord on the Y - COlS axis

		cout << endl << setw(20) << white << "The " << yellow << shipName[count] << white << " has " << yellow << visualHelper << white << " places it can be placed along the board." << endl;
		cout << white << setw(59) << "Player one, enter your coordinates for the " << yellow << shipName[count] << endl;
		cout << setw(40) << white << "Using numbers "<< yellow << "1" << white << "-" << yellow << "10" << white <<", enter your second coordinate: ";
		cin >> spaceTwo;


		if (spaceTwo >= 1 && spaceTwo <= 10)
		{
			promptCheck = true;
			spaceTwo = (spaceTwo);

		}
		else
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(85) << lightred << "============================================================" << endl;
			cout << setw(85) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
			cout << setw(85) << "============================================================" << endl;
			errorSound();
			cout << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			Sleep(1500);

		}

	}
	promptCheck = false;



}

void displayBlankTwo(string board[][11], string shipsPlaced[][11], bool &happy)
{

	//board is catching shipsPlaced the board string is
	//Erik 11/13/17
	//dragging variables down from, board_intilization(); uncertain when calling the 
	//function to put things inside of it when I dont want to use it inside that function 
	//but just send stuff will do something I do not want it to do. will expirment more with this later.
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	const int ROWS = 11;
	const int COLUMNS = 11;

	cout << setw(115) << darkgrey << div << endl; // divider ' === '
	for (int i = 0; i < ROWS; i++)
	{
		cout << darkgrey << setw(5) << "|";
		for (int s = 0; s < COLUMNS; s++)
		{
			//if else added by Tristan to make our X equal red & 0 equal white.
			if (shipsPlaced[i][s] == "X")
			{
				cout << setw(5) << red << shipsPlaced[i][s] << setw(5) << darkgrey << "|";
			}
			else if (shipsPlaced[i][s] == "O")
			{
				cout << setw(5) << white << shipsPlaced[i][s] << setw(5) << darkgrey << "|";
			}
			//ship colors
			else if (shipsPlaced[i][s] == "d" || shipsPlaced[i][s] == "s" || shipsPlaced[i][s] == "c" || shipsPlaced[i][s] == "b" || shipsPlaced[i][s] == "a")
			{
				cout << setw(5) << lightgreen << shipsPlaced[i][s] << setw(5) << darkgrey << "|"; // using lightgreen, magneta looked bright as well. I want something that is visible and seperate from the border text
			}
			else
			{
				cout << setw(5) << cyan << shipsPlaced[i][s] << setw(5) << darkgrey << "|";
			}
		}
		if (i != ROWS - 1)
		{
			cout << endl << setw(115) << between << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << setw(115) << darkgrey << div << endl;


	shipHPCounter(board, shipsPlaced, happy);
	//cout << victoryScreen;

}

void setPos(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy, string board[][11], string shipName[], bool &promptCheck, string shipsPlaced[][11], bool &happy) // board
{
	promptCheck = false;
	string visualHelper;

	

	do
	{
		visualHelper = " ";

		if (count == 0)
		{
			visualHelper = "Two";
		}
		else if (count == 1 || count == 2)
		{
			visualHelper = "Three";
		}
		else if (count == 3)
		{
			visualHelper = "Four";
		}
		else if (count == 4)
		{
			visualHelper = "Five";
		}

		

		system("cls");
		displayBlankTwo(board, shipsPlaced, happy);  //board
		cout << endl << setw(20) << white << "The " << yellow << shipName[count] << white << " has " << yellow << visualHelper << white << " places it can be placed along the board." << endl;
		cout << white << setw(59) << "Player one, enter your coordinates for the " << yellow << shipName[count] << endl;
		cout << setw(58) << white << "How would you like to place your ship: (" << yellow << "U" << white << "p, " << yellow << "D" << white << "own, " << yellow << "L" << white << "eft or " << yellow << "R" << white << "ight) ";
		cin >> userDirectionalInput;
		//getline(cin, userDirectionalInput);
		//system("pause");
		//get( userDirectionalInput);

		//would like to get, wasd, arrow keys or numpad to correspond with this instead of typing in the direction. Erik, 11/15/2017

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up" || userDirectionalInput == "U" || userDirectionalInput == "u")
		{
			up(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down" || userDirectionalInput == "D" || userDirectionalInput == "d")
		{
			down(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left" || userDirectionalInput == "L" || userDirectionalInput == "l")
		{
			left(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right" || userDirectionalInput == "R" || userDirectionalInput == "r")
		{
			right(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else
		{
			invalidInputRefresh();
		}

	} while (promptCheck == false);

}

void HPsystemOne(string board[][11], string shipsPlaced[][11], int& dCounter, int& sCounter, int& cCounter, int& bCounter, int& aCounter, int y, int x)
 {
	
		if (shipsPlaced[y][x] == "X" && board[y][x] == "d") // not counting correctly
		 {
		dCounter--;
		if (dCounter == 0)
			 {
			shipDestroyed();
			cout << setw(65) << "You have sunk the Destroyer!";
			sinkSound();
			Sleep(2000);
			}
		}
	
		else if (shipsPlaced[y][x] == "X" && board[y][x] == "s")
		 {
		sCounter--;
		if (sCounter == 0)
			 {
			shipDestroyed();
			cout << setw(65) << "You have sunk the Submarine!";
			sinkSound();
			Sleep(2000);
			}
		}
	
		else if (shipsPlaced[y][x] == "X" && board[y][x] == "c")
		 {
		cCounter--;
		if (cCounter == 0)
			 {
			shipDestroyed();
			cout << setw(65) << "You have sunk the Cruiser!";
			sinkSound();
			Sleep(2000);
			}
		}
	
		else if (shipsPlaced[y][x] == "X" && board[y][x] == "b")
		 {
		bCounter--;
		if (bCounter == 0)
			 {
			shipDestroyed();
			cout << setw(65) << "You have sunk the BattleShip!";
			sinkSound();
			Sleep(2000);
			}
		}
	
		else if (shipsPlaced[y][x] == "X" && board[y][x] == "a")
		 {
		aCounter--;
		if (aCounter == 0)
			 {
			shipDestroyed();
			cout << setw(65) << "You have sunk the Carrier!";
			sinkSound();
			Sleep(2000);
			}
		}
	}

void singlePlayerTakeOver() //Simply taken from Erik's function and deleted the word "two" after "Waiting for player " line
{
	string readyStatus;
	bool notReady = false;

	//http://www.cplusplus.com/forum/beginner/6397/ wanted to use current date in the mission report found this. user: Corpus
	char date[9];
	_strdate(date);

	do
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(40) << white << "Mission Report:                  " << date << endl;
		cout << left << darkgrey << "======================================================" << endl;
		cout << left << white << "There are five enemy ships about to enter your border." << endl;
		cout << left << white << "Set a trap for them." << endl;
		cout << left << white << "Don't let them escape!" << endl;
		cout << left << white << "                                  Admiral Gial Ackbar~" << endl;
		cout << left << darkgrey << "======================================================" << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << setw(75) << right << white << "Waiting for player to enter, 'Ready' " << endl << endl;
		cout << setw(55) << right << "Enter: ";
		cin >> readyStatus;
		if (readyStatus == "Ready" || readyStatus == "ready" || readyStatus == "r" || readyStatus == "R")
		{
			notReady = true;
		}

	} while (notReady == false);
	fightSound();
	cout << endl;
	system("cls");
	// beat your last time, score or change message, Erik 11/29/17

}

void Options(int &difficulty, int& boardNum, bool& boardChoose)
{
	bool exitInput = false;
	bool valInput = false;
	bool difInput = false;
	bool boardInput = false;
	int optionSelect;
	int diffSelect;

	system("cls");


	while (!exitInput)
	{
		system("cls");
		cout << white;
		cout << setw(72) << "WELCOME TO THE OPTIONS SCREEN" << endl;
		cout << setw(72) << "-----------------------------" << endl;
		cout << setw(67) << "1. Change Difficulty" << endl;
		cout << setw(67) << "2. Set Board Number " << endl;
		cout << setw(67) << "3. Back to main menu" << endl;

		cout << "Please choose 1-4: ";
		cin >> optionSelect;
		if (optionSelect == 1)
		{
			while (!difInput)
			{
				system("cls");
				cout << white << setw(67) << "1. Easy (70 guesses)\n";
				cout << white << setw(69) << "2. Normal (50 guesses)\n";
				cout << white << setw(67) << "3. Hard (30 guesses)\n";
				cout << setw(70) << white << "4. Extreme (20 guesses)\n";
				cout << setw(65) << white << "5. Back to options\n";


				cout << "Please selct a difficulty: ";
				cin >> diffSelect;
				if (diffSelect == 1)
				{
					difInput = true;
					difficulty = 70;
					cout << "Difficulty set to: " << lightred << "Easy" << endl << endl;
					Sleep(2000);
				}
				else if (diffSelect == 2)
				{
					difInput = true;
					difficulty = 50;
					cout << "Difficulty set to: " << lightred << "Normal" << endl << endl;
					Sleep(2000);
				}
				else if (diffSelect == 3)
				{
					difInput = true;
					difficulty = 30;
					cout << "Difficulty set to: " << lightred << "Hard" << endl << endl;
					Sleep(2000);
				}
				else if (diffSelect == 4)
				{
					difInput = true;
					difficulty = 20;
					cout << "Difficulty set to: " << lightred << "Extreme" << endl << endl;
					Sleep(2000);
				}
				else if (diffSelect == 5)
				{
					Options(difficulty, boardNum, boardChoose);
				}
				else
				{
					invalidInputRefresh();
					Sleep(2000);
					system("cls");
				}
			}
		}
		else if (optionSelect == 2)
		{
			while (!boardInput)
			{
				cout << endl << endl << endl << white << "Enter the board number you wish to play on " << lightred << "(SINGLE-PLAYER ONLY): " << white;
				cin >> boardNum;
				if (boardNum > 10 || boardNum < 1)
				{
					invalidInputRefresh();
					Sleep(2000);
					system("cls");
				}
				else
				{
					cout << endl << "Board number set to: " << lightred << boardNum << endl;
					Sleep(2000);
					boardChoose = true;
					boardInput = true;
				}
			}
		}
		else if (optionSelect == 3)
		{
			exitInput = true;
		}
	}
	mainMenu();
}

//=============================END OF TRISTAN ABOVE=====================================================================