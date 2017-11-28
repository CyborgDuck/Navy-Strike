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
#include "vector"

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


//==================Function Prototypes==============
void intro(int&);
int mainMenu(); //In order to display the main menu, and not the ENTIRE intro every time, we need the menu part in a different function

//void board_intilization();

void onePlayer();
void TwoPlayer();
void Options(int&);
void firstCoordOne(string, int&, string[][11], bool&);
void firstCoordTwo(string, int&, bool&, string[], int&, string[][11], string[][11]); //Needed to change this to "firstCoordTwo" because you use more variables than Single Player
void secCoord(int&, bool&, string[][11], string[], int&, string[][11]);
void secCoordOne(int&, bool&, string[][11]);
bool refresh(int&, string[][11], string[][11], int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, string[][11], string[][11], string[][11], string[][11], string[][11], bool&, string[][11], string[][11]);
void displayBlank(string[][11]);
void displayMiss(int);
void displayHit(int);

//movement positions.
void setPos(int&, int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, string[][11], string[], bool&, string[][11]);
void up(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void down(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void left(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void right(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);

//ship Hp
void destroyerHP(int&, int&, int&, int&, string[][11], string&, string[][11]);
void submarineHP(int&, int&, int&, int&, int&, string[][11], string&);
void cruiserHP(int&, int&, int&, int&, int&, string[][11], string&);
void battleshipHP(int&, int&, int&, int&, int&, int&, string[][11], string&);
void carrierHP(int&, int&, int&, int&, int&, int&, int&, string[][11], string&);
void shipDestroyed();

//ship Placement
//bool chkPlacement(bool&, string[][11], int&, int&, int&, int&, string[][11]); //obsolete I believe, 11/28/17 Erik.

//Happy with the placement? or reset/redo > then turn controls to player two
bool happyPlacement(bool&, string[][11]); 
void boardRESET(string[][11]);

//start of missile strikes / player2
void cleaningSlate(string[][11]);
void missiles();

//sounds
void startSound();
void missSound();
void hitSound();
void sinkSound();

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

	//intro(players);  //currently to test deeper code comment this out, set players = 2;
	mainMenu(); //Skip past the intro straight into the main menu;

	//board_intilization(); //board intilization will go into the functions OnePlayer(), TwoPlayer() // board intilization is completely replaced with, displayBlank.
	
	system("pause");
	return 0;
}

//============================== ALL Functions=================




//================================ERIK'S FUNCTIONS BELOW==============================================================================

//void board_intilization()
//{
//
//	//this function is being used to give the player a prompt on where they should place the board.
//	//May be possible to use this one to highlight the color of the letter that is currently being selected and then the number, Erik 11/15/2017
//
//	//const int victorVec = 2; // possible idea for a 3d array
//	const int ROWS = 11;
//	const int COLUMNS = 11;
//
//	//variables
//	string div = "===============================================================================================================";
//	string between = "---------------------------------------------------------------------------------------------------------------";
//	
//	//       \/ [victorVec] 3d array
//	char board[ROWS][COLUMNS] = {	{ ' ',  '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '0'  },
//									{ 'A',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'B',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'C',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'D',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'E',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'F',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'G',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'H',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'I',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'J',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' } };
//
//
//
//	//This will be the board that the player uses to place and will look similar to the player guessing. except will be rewritten over the hidden spots
//	//2 for loops for making the board
//	cout << setw(115) << darkgrey << div << endl; // divider ' === '
//	for (int i = 0; i < ROWS; i++)
//	{
//		cout << darkgrey << setw(5) << "|";
//		for (int s = 0; s < COLUMNS; s++)
//		{
//			cout << setw(5) << lightcyan << board[i][s] << setw(5) << darkgrey << "|";
//		}
//		if (i != ROWS - 1)
//		{
//			cout << endl << setw(115) << between << endl;
//		}
//		else
//		{
//			cout << endl;
//		}
//	}
//	cout << setw(115) << darkgrey << div << endl;
//
//	//was considering sending a few variables to displayblank.. but wouldnt this also call displayBlank within the current function? I dont want that.
//	//displayBlank();
//
//
//}

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

	//This, 'do while' was for changing color on one of the splash screens but i dont like it.
	//May be able to use this in options though. - Erik

	/*do
	{

	if (v == 0)
	{
	cout << white;
	}
	else if (v == 1)
	{
	cout << cyan;
	}
	else if (v == 2)
	{
	cout << blue;
	}
	else if (v == 3)
	{
	cout << white;
	}
	else if (v == 4)
	{
	cout << blue;
	}
	else if (v == 5)
	{
	cout << cyan;
	}
	else if (v == 6)
	{
	cout << white;
	}
	else
	{
	cout << white;
	}*/


	//title
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
		Sleep(10);
	}


	//cout << endl << endl << endl; //part of the above color switch turned off the timer on endl;s

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
	Sleep(5500);  //if returning to the color switch change the timer to something less than 5.5seconds
	system("cls");
	// very sensitive to spaces and tabs do not change.

	//both the v and the while is the end of the do while color change. again leaving for possible changes in options
	//v++;
	//} while (v != 6);


	//authors
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
		Sleep(10);
	}

	cout << setw(65) << white << "Created By," << endl << setw(70) << "Erik, Tristan and Chuck" << endl << setw(65) << "Version 0.02" << endl; //update version count, for every day in class? we will be at 0.08 on Dec 6, 2017 	
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
	int players = 0;
	int difficulty = 30; //How many guesses the player has before losing the game
	bool menuNumber = false;
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




		cout << endl << endl << endl << endl << endl;
		cout << setw(76) << white << "Choose how you would like to play. \n";
		cout << endl << setw(65) << "1. ONE PLAYER \n";
		cout << setw(66) << "2. TWO PLAYERS \n"; //Only two player will work for the time being, 1 player will require an ai.
		cout << setw(62) << "3. OPTIONS \n"; //If time allows, come back to try to edit colors.





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

		cout << endl << setw(62) << white << "Enter 1 - 3: ";

		//keep running until the player gives an appropriate number
		cin >> players;

		//players has to equal 1-3 if it does not, run it again.
		if (players == 1 || players == 2 || players == 3)//HERE doesnt seem to want to loop for some reason also need an array for the player choice since this is staying a void function to pass on the choice 1 or 2 Maybe an OPTION button to change the colors? that would be cool. maybe a few presets
		{
			menuNumber = true;
		}
		else
		{
			cout << "Your trying to break my program, are you? I can do that myself, try again." << endl;
		}


	} while (menuNumber != true);
	system("cls");

	if (players == 1)//1 player vs ai.
	{
		//need to make a function to place the ship in a random location on the board.
		//cout << "Look forward to this feature in a new update! We require an A.I. to hire, know any around?" << endl;
		onePlayer();

		//Sleep(3000);
		//and back to intro(); until we decide to tackle that	
		//system("cls");
		//intro(); // ****game seems to break and default to press any key if going through the intro function more than once?**** why does it do this.

		//OnePlayer();

	}
	else if (players == 2)//2 players - Primary Focus
	{

		TwoPlayer();
		// need when the ship is being placed to be across more than one position on the board.
		//Possible idea, a max amount of shots you can shoot before you lose? could also manipulate in options to unlimited or limited

	}
	else if (players == 3)//Options
	{

		// cout << "Future development is required here, look forward to changing colors of the game board!" << endl; colors and board size? we may be able to manipulate sound still looking into it.
		Options(difficulty);

	}
	else
	{
		cout << "How'd you get here? Your not supposed to be here." << endl;


	}

	return players;
}

void TwoPlayer()
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



	string cleanSlate[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10"  },
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


	string board[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10"  },
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

	string destroyerBOARD[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
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

	string subBOARD[ROWS][COLUMNS] = {		{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
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

	string cruiserBOARD[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
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

	string battleshipBOARD[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
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

	string carrierBOARD[ROWS][COLUMNS] = {	{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
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



	string shipHits[ROWS][COLUMNS] = {		{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
											{ "A",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "B",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "C",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "D",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "E",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "F",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "G",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "H",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "I",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" },
											{ "J",  "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" } };

	


	//come back to this if i can figure out the position marker.
	//Still want to try to make this go back and forth like a real battleship game, player one goes then player two for placing ships and taking turns.
	//work on player 2 after player one is fully working, will be easier. Erik 11/15/2017

	//for (int x = 0; x < 2; x++)
	//{
	//	if (x == 0)
	//	{
	//		PlayerX = "One ";
	//	}
	//	else if (x == 1)
	//	{
	//		PlayerX = "Two ";
	//	}
	//	cout << "Enter your positions player " << PlayerX;
	//	Sleep(3000);
	//	system("cls");
	//	board_intilization();
	//}






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
					firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
					secCoord(spaceTwo, promptCheck, board, shipName, count, shipsPlaced);


					setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck, shipsPlaced);
					cout << endl << endl;
					validInput = refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, destroyerBOARD, subBOARD, cruiserBOARD, battleshipBOARD, carrierBOARD, validInput, cleanSlate, shipHits);
				} while (validInput == false);

			}
		

		redoShipsPlace++;
			happy = happyPlacement(happy, shipsPlaced);

		} while (happy == false);

		
			//destroyerHP(); // idea to break this up so that each ship has its own function...
			//if this doesnt work break the if else chain keep the functions within this, 'for loop'.

		//}
		/*else if (count == 1)
		{
			firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipName, count);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			//submarineHP();

		}
		else if (count == 2)
		{
			firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipName, count);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			//cruiserHP();

		}
		else if (count == 3)
		{
			firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipName, count);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			//battleshipHP();

		}
		else if (count == 4)
		{
			firstCoordTwo(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipName, count);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board, shipName, promptCheck);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			//carrierHP();

		}*/
		//replacing the shipsplaced on to the board making it visible to player one to see where their placed.
		//This does not update with every placed ship though. perhaps make this a function. Erik - 11/15/2017
		//maybe can use board intilization to refresh. what the board looks like, from placement to placement.


	

	//a prompt here confirming player 1s ship placement? or something to let player two to take over
	// player two starts to set ships? 11/26/17 Erik.

	//player two starts to attack
	//system("cls");  // class 11/27/17
	//cleaningSlate(cleanSlate);
		system("cls");
		displayBlank(board);
		missiles();
	





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


bool refresh(int &spaceOneNum, string board[][11], string shipsPlaced[][11], int &spaceTwo, int &destroy1, int &count, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy, string destroyerBOARD[][11], string subBOARD[][11], string cruiserBOARD[][11], string battleshipBOARD[][11], string carrierBOARD[][11], bool &validInput, string cleanSlate[][11], string shipHits[][11])
{
	
	//rows and columns may be obsolete now.
	//There may be an excessive amount of 'validInput = true;' may need only 1 per direction?
	//Erik 11.27.17
	const int ROWS = 11;
	const int COLUMNS = 11;
	bool continu3 = true;
	
			//initial ship placement idea by Tristan
			//board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];


			if (count == 0) // 0 is the destroyer, 2 spots
			{
				continu3 = true;
				


				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					//older version of code to place ships. Erik, 11/27/17
					//board[spaceOneNum][spaceTwo] = destroyerBOARD[destroy][spaceTwo];
					//board[destroy1][spaceTwo] = destroyerBOARD[destroy1][spaceTwo];

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true) // if theirs an "O" at this location procede to mark shipsPlaced and write shiphits to destroyerBOARD.
					{

						//might be bloat since we found a side-step to this way.
						//destroyerBOARD[spaceOneNum][spaceTwo] = shipHits[destroy][spaceTwo]; //setting an X marker from the shipHits[][] board onto DestroyerBOARD[][]
						
						shipsPlaced[spaceOneNum][spaceTwo] = "X"; // visualizing the placement of the ship for player 1.
						//validInput = true;

					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{
						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;
						Sleep(1500);
						validInput = false;
						continu3 = false;
					}


					if (shipsPlaced[destroy1][spaceTwo] == "O" && continu3 == true)
					{

						shipsPlaced[destroy1][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[destroy1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;
						
						Sleep(1500);

						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}
					
					destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput, destroyerBOARD);
				}


				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;

					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}


					if (shipsPlaced[destroy1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[destroy1][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[destroy1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}

					destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput, destroyerBOARD);
				}

				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X"; 
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}


					if (shipsPlaced[spaceOneNum][destroy1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][destroy1] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][destroy1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}


					destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput, destroyerBOARD);
				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][destroy1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][destroy1] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][destroy1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}

					destroyerHP(destroy, destroy1, spaceOneNum, spaceTwo, board, userDirectionalInput, destroyerBOARD);
				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}

			else if (count == 1) // 1 is the submarine, 3 spots
			{
				continu3 = true;
				//what if the board isnt updating the position of the ship because spaceonenum / space two arent updating to the right number..

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[sub1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[sub1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[sub1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[sub2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[sub2][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[sub2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						shipsPlaced[sub1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[sub1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[sub1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[sub1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O"; //reset
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[sub2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[sub2][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[sub2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[sub1][spaceTwo] = "O"; //reset
						shipsPlaced[spaceOneNum][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][sub1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][sub1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][sub1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][sub2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][sub2] = "X";
						validInput = true;
					}
					else if(shipsPlaced[spaceOneNum][sub2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[spaceOneNum][sub1] = "O";
						validInput = false;
						continu3 = false;
					}

					submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][sub1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][sub1] = "X";
						//validInput = true;
					}
					else if(shipsPlaced[spaceOneNum][sub1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][sub2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][sub2] = "X";
						validInput = true;
					}
					else if(shipsPlaced[spaceOneNum][sub2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[spaceOneNum][sub1] = "O";
						validInput = false;
						continu3 = false;
					}

					submarineHP(sub, sub1, sub2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 2) // 2 is the cruiser, 3 spots
			{
				continu3 = true;

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[cruis1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[cruis1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[cruis1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[cruis2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[cruis2][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[cruis2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[cruis1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[cruis1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[cruis1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[cruis1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[cruis2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[cruis2][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[cruis2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[cruis1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][cruis1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][cruis1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][cruis1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][cruis2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][cruis2] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][cruis2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";					//reset
						shipsPlaced[spaceOneNum][cruis1] = "O";
						validInput = false;
						continu3 = false;
					}

					cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][cruis1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][cruis1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][cruis1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][cruis2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][cruis2] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][cruis2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[spaceOneNum][cruis1] = "O";
						validInput = false;
						continu3 = false;
					}

					cruiserHP(cruis, cruis1, cruis2, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 3) // 3 is the battleship, 4 spots
			{
				continu3 = true;

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[battleship1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship2][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[battleship2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[battleship1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship3][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship3][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[battleship3][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[battleship1][spaceTwo] = "O";	//reset
						shipsPlaced[battleship2][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[battleship1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship2][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[battleship2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[battleship1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[battleship3][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[battleship3][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[battleship3][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[battleship1][spaceTwo] = "O";	//reset
						shipsPlaced[battleship2][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship2] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[spaceOneNum][battleship1] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship3] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship3] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship3] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][battleship1] = "O";	//reset
						shipsPlaced[spaceOneNum][battleship2] = "O";
						validInput = false;
						continu3 = false;
					}

					battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship2] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][battleship1] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][battleship3] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][battleship3] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][battleship3] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][battleship1] = "O";	//reset
						shipsPlaced[spaceOneNum][battleship2] = "O";
						validInput = false;
						continu3 = false;
					}

					battleshipHP(battleship, battleship1, battleship2, battleship3, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 4) // 4 is the airship carrier, 5 spots
			{
				continu3 = true;

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier2][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";	//reset
						shipsPlaced[carrier1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier3][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier3][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier3][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[carrier1][spaceTwo] = "O";			//reset
						shipsPlaced[carrier2][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier4][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier4][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[carrier4][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[carrier1][spaceTwo] = "O";			//reset
						shipsPlaced[carrier2][spaceTwo] = "O";			//reset
						shipsPlaced[carrier3][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier1][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier1][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier1][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier2][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier2][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier2][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[carrier1][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier3][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier3][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[carrier3][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[carrier1][spaceTwo] = "O";			//reset
						shipsPlaced[carrier2][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[carrier4][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[carrier4][spaceTwo] = "X";
						validInput = true;
					}
					else if (shipsPlaced[carrier4][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[carrier1][spaceTwo] = "O";			//reset
						shipsPlaced[carrier2][spaceTwo] = "O";			//reset
						shipsPlaced[carrier3][spaceTwo] = "O";
						validInput = false;
						continu3 = false;
					}

					carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset

						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier2] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier3] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier3] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier3] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier2] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier4] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier4] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier4] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier2] = "O";						//reset
						shipsPlaced[spaceOneNum][carrier3] = "O";
						validInput = false;
						continu3 = false;
					}

					carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					if (shipsPlaced[spaceOneNum][spaceTwo] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][spaceTwo] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][spaceTwo] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						validInput = false;
						continu3 = false;
					}


					if (shipsPlaced[spaceOneNum][carrier1] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier1] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier1] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset

						validInput = false;
						continu3 = false;
					}


					if (shipsPlaced[spaceOneNum][carrier2] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier2] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier2] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier3] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier3] = "X";
						//validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier3] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier2] = "O";
						validInput = false;
						continu3 = false;
					}

					if (shipsPlaced[spaceOneNum][carrier4] == "O" && continu3 == true)
					{
						shipsPlaced[spaceOneNum][carrier4] = "X";
						validInput = true;
					}
					else if (shipsPlaced[spaceOneNum][carrier4] != "O" && continu3 == true)
					{

						system("cls");
						cout << setw(65) << red << "-----------------------------------------------" << endl;
						cout << setw(65) << "Theirs a ship here already, redo your ship placement." << endl;
						cout << setw(65) << "-----------------------------------------------" << endl;

						Sleep(1500);
						shipsPlaced[spaceOneNum][spaceTwo] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier1] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier2] = "O";		//reset
						shipsPlaced[spaceOneNum][carrier3] = "O";
						validInput = false;
						continu3 = false;
					}

					carrierHP(carrier, carrier1, carrier2, carrier3, carrier4, spaceOneNum, spaceTwo, board, userDirectionalInput);
				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}

	
	return validInput;

}


void destroyerHP(int &destroy, int &destroy1, int &spaceOneNum, int &spaceTwo, string board[][11], string &userDirectionalInput, string destroyerBOARD[][11])
{
	int destHP = 2;

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{
		if (board[spaceOneNum][spaceTwo] == "X")  //before i get ahead of myself destroyerBOARD possibly rewrite in board.
		{
			destHP = destHP - 1;
		}
		else if (board[destroy1][spaceTwo] == "X")
		{
			destHP = destHP - 1;
		}

	}
	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{
		if (board[spaceOneNum][spaceTwo] == "X")
		{
			destHP = destHP - 1;
		}
		else if (board[destroy1][spaceTwo] == "X")
		{
			destHP = destHP - 1;
		}

	}
	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{
		if (board[spaceOneNum][spaceTwo] == "X")
		{
			destHP = destHP - 1;
		}
		else if (board[spaceOneNum][destroy1] == "X")
		{
			destHP = destHP - 1;
		}

	}
	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{
		if (board[spaceOneNum][spaceTwo] == "X")
		{
			destHP = destHP - 1;
		}
		else if (board[spaceOneNum][destroy1] == "X")
		{
			destHP = destHP - 1;
		}

	}

	if (destHP == 0)
	{
		
		shipDestroyed();
		cout << "You lost your destroyer." << endl;
		Sleep(1500);
	}

}

void submarineHP(int &sub, int &sub1, int &sub2, int &spaceOneNum, int &spaceTwo, string board[][11], string &userDirectionalInput)
{
	int subHP = 3;

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{
		if(board[spaceOneNum][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}
		else if(board[sub1][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}
		else if(board[sub2][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}
	
	}

	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}
		else if(board[sub1][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}
		else if(board[sub2][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}

	}

	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}

		else if(board[spaceOneNum][sub1] == "X")
		{
			subHP = subHP - 1;
		}

		else if(board[spaceOneNum][sub2] == "X")
		{
			subHP = subHP - 1;
		}


	}

	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{

	if(board[spaceOneNum][spaceTwo] == "X")
		{
			subHP = subHP - 1;
		}

		else if(board[spaceOneNum][sub1] == "X")
		{
			subHP = subHP - 1;
		}

		else if(board[spaceOneNum][sub2] == "X")
		{
			subHP = subHP - 1;
		}

	}

	if (subHP == 0)
	{

	shipDestroyed();
	cout << "You lost your submarine." << endl;
	Sleep(1500);
	}

}


void cruiserHP(int &cruis, int &cruis1, int &cruis2, int &spaceOneNum, int &spaceTwo, string board[][11], string &userDirectionalInput)
{
	int cruisHP = 3;

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[cruis1][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[cruis2][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}


	}

	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{

	if(board[spaceOneNum][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[cruis1][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[cruis2][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}

	}

	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[spaceOneNum][cruis1] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[spaceOneNum][cruis2] == "X")
		{
			cruisHP = cruisHP - 1;
		}

	}

	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{

	if(board[spaceOneNum][spaceTwo] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[spaceOneNum][cruis1] == "X")
		{
			cruisHP = cruisHP - 1;
		}
		else if(board[spaceOneNum][cruis2] == "X")
		{
			cruisHP = cruisHP - 1;
		}


	}

	if (cruisHP == 0)
	{

	shipDestroyed();
	cout << "You lost your cruiser." << endl;
	Sleep(1500);
	}

}

void battleshipHP(int &battleship, int &battleship1, int &battleship2, int &battleship3, int &spaceOneNum, int &spaceTwo, string board[][11], string &userDirectionalInput)
{
	int battleHP = 4;

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship1][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship2][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship3][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}

	}

	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{

	if(board[spaceOneNum][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship1][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship2][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[battleship3][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}

	}

	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{

		if (board[spaceOneNum][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship1] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship2] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship3] == "X")
		{
			battleHP = battleHP - 1;
		}

	}

	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{

		if (board[spaceOneNum][spaceTwo] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship1] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship2] == "X")
		{
			battleHP = battleHP - 1;
		}
		else if(board[spaceOneNum][battleship3] == "X")
		{
			battleHP = battleHP - 1;
		}

	}

	if (battleHP == 0)
	{

	shipDestroyed();
	cout << "You lost your battleship." << endl;
	Sleep(1500);
	}

}

void carrierHP(int &carrier, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &spaceOneNum, int &spaceTwo, string board[][11], string &userDirectionalInput)
{
	int carriHP = 5;

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[carrier1][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[carrier2][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[carrier3][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[carrier4][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}

	}

	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{

	if(board[spaceOneNum][spaceTwo] == "X")
	{
		carriHP = carriHP - 1;
	}
	else if(board[carrier1][spaceTwo] == "X")
	{
		carriHP = carriHP - 1;
	}
	else if(board[carrier2][spaceTwo] == "X")
	{
		carriHP = carriHP - 1;
	}
	else if(board[carrier3][spaceTwo] == "X")
	{
		carriHP = carriHP - 1;
	}
	else if(board[carrier4][spaceTwo] == "X")
	{
		carriHP = carriHP - 1;
	}

	}

	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier1] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier2] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier3] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier4] == "X")
		{
			carriHP = carriHP - 1;
		}

	}

	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{

		if(board[spaceOneNum][spaceTwo] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier1] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier2] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier3] == "X")
		{
			carriHP = carriHP - 1;
		}
		else if(board[spaceOneNum][carrier4] == "X")
		{
			carriHP = carriHP - 1;
		}

	}

	if (carriHP == 0)
	{

	shipDestroyed();
	cout << "You lost your carrier." << endl;
	Sleep(1500);
	}

}

/*bool chkPlacement(bool &validInput, string board[][11], int &destroy, int &destroy1, int &spaceOneNum, int &spaceTwo, string cleanSlate[][11])
{

	//checks the placement with all the ships that they are okay to be placed where the user says, otherwise redo that ship placement.
	const int ROWS = 11;
	const int COLS = 11;
	

		if (board[spaceOneNum][spaceTwo] == "~" || board[spaceOneNum][spaceTwo] == "O") // or "O"
		{
			

			validInput = true;
		}
		else
		{
			system("cls");
			cout << "There's a ship here already, redo your ship placement." << endl;
			Sleep(1000);

			for (int i = 0; i < ROWS; i++)
			{
				for (int y = 0; y < COLS; y++)
				{
					board[i][y] = cleanSlate[i][y];

				}

			}
		
			validInput = false;
		}
		
		
		

	

	return validInput;

}*/

bool happyPlacement(bool &happy, string shipsPlaced[][11])
{
	string yesNo;

	system("cls");
	displayBlank(shipsPlaced);
	cout << endl << endl << setw(65) << white << "Are you happy with your ships placement? (y/n): ";
	cin >> yesNo;

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
	for (int i = 0; i < 11; i++)
	{
		for (int e = 0; e < 11; e++)
		{
			shipsPlaced[i][e] = "O";

		}
	}

}

void cleaningSlate(string cleanSlate[][11])
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
			//if else added by Tristan to make our X equal red & O equal white.
			if (cleanSlate[i][s] == "X")
			{
				cout << setw(5) << red << cleanSlate[i][s] << setw(5) << darkgrey << "|";
			}
			else if (cleanSlate[i][s] == "O")
			{
				cout << setw(5) << white << cleanSlate[i][s] << setw(5) << darkgrey << "|";
			}
			else
			{
				cout << setw(5) << cyan << cleanSlate[i][s] << setw(5) << darkgrey << "|";
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

void missiles()
{


}

//ascii art

//Erik 11/13/17
//           ascii art place holder until we get to it.
//if things look off center its because \\ is required for one 
//backslash to be recognized in cout. if things are not lining 
//up in the command prompt it may be because i missed a backslash
//game over / you won! with x amount of shots left. time left? or with a total time.

void displayHit(int count) // not set to anything yet.
{ 
	/*((((
	*)    ()\)  (*)     ((()\))\))\ )
	` ) / ()\    (() / ()\)    (`) / ()\       )\  ()\      ((() / ((() / (((() / (
	()(_))((((_)(/ (_))(() / ()\   ()(_)) ((((_)((((_))((_))\ / (_)) / (_)))\ / (_))
	(_(_()))\ _)\ (_)) / (_))_((_)(_(_()))\ _)\)\___((_)_   _((_)(_)) (_)) ((_)(_))_
	| _   _ | (_)_\(_) | _ \ (_)) __ || __ || _   _ | (_)_\(_)((/ __|/ _ \ | | | ||_ _ || _ \ | __ || \
	| |     / _ \  |   /   | (_ || _|   | |      / _ \ | (__ | (_) || |_| | | | |   /| _| | |) |
	|_|    /_ / \_\ | _ | _\    \___ || ___|  |_|     /_ / \_\   \___ | \__\_\ \___/ |___ || _ | _\ | ___ || ___ /


	//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php


	*/
}

void displayMiss(int count) //Still unable to get displayed properly in command window
{
	//collaberated on by both tristan and erik.
	system("cls");
	//when shot was missed trigger this
	//green?
	cout << endl << endl << endl << endl << endl << endl;
	cout << setw(82) << " __   _____  _   _   __  __ ___ ____ ____  _____ ____  " << endl;
	cout << setw(82) << " \\ \\ / / _ \\| | | | |  \\/  |_ _/ ___/ ___|| ____|  _ \\ " << endl;
	cout << setw(82) << "  \\ \V / | | | | | | | |\\/| || |\\___ \\___ \\|  _| | | | |" << endl;
	cout << setw(82) << "   | || |_| | |_| | | |  | || | ___) |__) | |___| |_| |" << endl;
	cout << setw(82) << "   |_| \\___/ \\___/  |_|  |_|___|____/____/|_____|____/ " << endl;

	//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php
	count = 29 - count; // change 30 to 'difficulty' and adjust difficulty to amount of shots

	cout << endl << setw(55) << "You have, " << count << " shots left." << endl;
	cout << endl << endl << endl << endl;
}

void shipDestroyed()
{
	//this needs to be tested if it needs to be formated still, and colorized. Erik 11/27/17
	system("cls");
	//ship blows up use this,
	//red and orange black/grey
	cout << endl << endl << endl << endl << endl << endl;
	cout << setw(82) << "			 \\         .  ./" << endl;
	cout << setw(82) << " \\      .:; '.:..   / " << endl;
	cout << setw(82) << " (M^^.^~~:.')." << endl;
	cout << setw(82) << " -   (/  .    . . \\ \\)  -" << endl;
	cout << setw(82) << " ((| :. ~ ^  :. .|))" << endl;
	cout << setw(82) << " -   (\\- |  \\ /  |  /)  -" << endl;
	cout << setw(82) << " -\\  \\     /  /-" << endl;
	cout << setw(82) << " \\  \\   /  /" << endl;
	//Made with the help of this site, SOURCE:	 http://www.chris.com/ascii/index.php?art=objects/explosives

	// you blew up // you lost your // x ship.				 
}

//================================ERIK'S FUNCTIONS ABOVE==============================================================================




//===========================CHUCK'S FUNCTIONS BELOW===================================================
void startSound()
{


}

void missSound()
{


}

void hitSound()
{

}

void sinkSound()
{

}

//===========================CHUCK'S FUNCTIONS ABOVE===================================================




//=====================TRISTAN'S FUNCTIONS BELOW=========================================
void onePlayer()
{
	srand(time(NULL));
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	bool promptCheck = false;
	const int size = 11;
	string spaceOne = " "; //letter that player enters for coordinate 1
	int spaceTwo = 0;    //Number that player enters for coordinate 2
	int spaceOneNum = 0; //Number conversion between char and int for spaceOne
	int random;          //variable that determines which board the user uses
	int maxNum = 10;     //Setting the random number not to exceed 10
	int allShips = 0;    //Variable used to count how many hits have been detected. There are a total of 17 hits before all ships are sunk. So, if this number reaches 17, the game is won. Most likely a placeholder for whenever we get
						 //Hit detection properly
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

	string boardOne[11][11] = {		{ " ",  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A",  "X" , "O" , "O" , "O" , "O" , "X" , "X" , "X" , "O" , "O" },
									{ "B",  "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C",  "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D",  "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E",  "O" , "O" , "X" , "O" , "X" , "X" , "X" , "X" , "X" , "O" },
									{ "F",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "G",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H",  "O" , "X" , "X" , "X" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "I",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J",  "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardTwo[11][11] = {		{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "O" , "O" }, //C3-5 is a 3-spot ship
									{ "D", "O" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "X" , "O" , "O" , "O" , "X" , "X" , "X" , "X" , "O" },
									{ "F", "O" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "X" , "X" , "X" , "X" , "X" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardThree[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "X" , "X" , "X" , "O" , "O" },
									{ "C", "O" , "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" },
									{ "F", "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" },
									{ "G", "X" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "X" , "O" },
									{ "H", "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" },
									{ "I", "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardFour[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "X" , "X" , "X" , "X" , "X" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "X" , "X" , "X" , "O" , "X" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardFive[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "X" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "X" , "O" },
									{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "X" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "X" , "X" , "X" , "X" , "O" },
									{ "J", "O" , "X" , "X" , "X" , "X" , "X" , "O" , "O" , "O" , "O" } };

	string boardSix[11][11] = {		{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "X" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "X" },
									{ "C", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "X" },
									{ "D", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "X" },
									{ "E", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "X" , "X" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "X" , "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardSeven[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "X" , "X" , "X" , "X" , "O" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "X" , "X" , "X" , "X" , "X" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardEight[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "X" , "X" , "O" , "O" , "O" , "X" , "X" , "X" , "X" },
									{ "D", "O" , "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "X" , "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "X" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "X" , "X" , "O" , "O" , "X" , "O" , "O" , "O" } };

	string boardNine[11][11] = {	{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "O" , "O" , "O" , "X" , "X" , "O" , "O" , "O" , "O" , "O" },
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "X" , "O" , "O" , "X" , "X" , "X" , "O" , "O" , "O" , "O" },
									{ "D", "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "X" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "X" , "X" , "X" , "X" , "X" , "O" , "O" , "O" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "X" , "X" , "X" , "X" , "O" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	string boardTen[11][11] = {		{ " ", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10" },
									{ "A", "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" , "X" }, // 2, 3, 5 
									{ "B", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "C", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "D", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "E", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "F", "O" , "O" , "X" , "X" , "X" , "O" , "X" , "X" , "X" , "X" },
									{ "G", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "H", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "I", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" },
									{ "J", "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" , "O" } };

	//do
	//{
	random = 1; //(rand() % maxNum); 
	//} while (random == 0);

	for (int count = 0; count < 3; count++)
	{
		cout << setw(67) << endl << endl << endl << endl << endl << endl << "Your board number is: " << random << "." << endl << endl;
		Sleep(1000);
		system("cls");
		Sleep(100);
	}

	if (random == 1)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardOne[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(2000);						 //}
			}
			if (blank[spaceOneNum][spaceTwo] == "X")
			{
				allShips++;
				displayHit(count);
				Sleep(2000);
			}

			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}

	else if (random == 2)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardTwo[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 3)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardThree[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);		
				Sleep(1500);							// }    //TO DISPLAY PROPERLY
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 4)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardFour[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);
				Sleep(1500);							// }    //TO DISPLAY PROPERLY
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 5)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardFive[spaceOneNum][spaceTwo];

			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);
				Sleep(1500);								// }    //TO DISPLAY PROPERLY
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 6)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardSix[spaceOneNum][spaceTwo];
			
			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 7)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardSeven[spaceOneNum][spaceTwo];
			
			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 8)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardEight[spaceOneNum][spaceTwo];
			
			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 9)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardNine[spaceOneNum][spaceTwo];
			
			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}
	else if (random == 10)
	{
		for (int count = 0; count < 30; count++)
		{
			firstCoordOne(spaceOne, spaceOneNum, blank, promptCheck);
			secCoordOne(spaceTwo, promptCheck, blank);
			blank[spaceOneNum][spaceTwo] = boardTen[spaceOneNum][spaceTwo];
			
			if (blank[spaceOneNum][spaceTwo] == "O")     //}
			{											// } //STILL CANNOT GET ASCII ART 
				displayMiss(count);							// }    //TO DISPLAY PROPERLY
				Sleep(1500);
				//system("pause");						 //}
			}
			
			
			system("cls");
			displayBlank(blank);
			if (allShips == 17)
			{
				system("cls");
				count = 29;
				cout << white << "==========================================" << endl;
				cout << white << "ALL TARGETS ELIMINATED, MISSION SUCCESSFUL" << endl;
				cout << white << "==========================================" << endl;
			}
		}
		if (allShips != 17)
		{
			cout << white << "=====================================" << endl;
			cout << white << "Sorry, you have taken too many turns.\n" << setw(20) << red << "YOU LOSE" << endl;
			cout << white << "=====================================" << endl;
		}
	}

}

void firstCoordOne(string spaceOne, int& spaceOneNum, string blank[][11], bool& promptCheck)
{
	
	const int ROWS = 11;
	string sletter =  "a";
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
			displayBlank(blank);
			cout << endl;
			//cout << setw(75) << white << "Using letters A-J, and then a number 1-10, enter your coordinates: ";
			cout << setw(75) << white << "Using letters A-J, enter your coordinates: ";
			cin >> spaceOne;
		} while (spaceOne.length() != 1);
		

		//check to see if input is a-j or A-J before sending it on.
		if (spaceOne.length() > 1)
		{
			cout << endl;
			cout << setw(74) << red << "=========================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(74) << "=========================================================" << endl;
			Sleep(1500);
			system("cls");
		}
		else if ((spaceOne >= "a" && spaceOne <= "j") || (spaceOne >= "A" && spaceOne <= "J"))
		{
			promptCheck = true;



		}
		else
		{
			cout << endl;
			cout << setw(74) << red << "=========================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(74) << "=========================================================" << endl;
			Sleep(1500);
			system("cls");

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
void firstCoordTwo(string spaceOne, int &spaceOneNum, bool &promptCheck, string shipName[], int &count, string board[][11], string shipsPlaced[][11])
{
	//variables
	const int ROWS = 11;
	string sletter = "a";
	string sLETTER = "A";
	char letter;
	char cLETTER;

	//===========FOR TWO PLAYER==========================================================================
	do
	{
		do {
			//board_intilization(spaceOneNum, spaceTwo);
			system("cls");
			displayBlank(shipsPlaced); //board // lets you visualize the board when placing the ships cord on the X - ROWS axis
			cout << endl;
			cout << white << setw(55) << "Player one, enter coordinates for the " << shipName[count] << endl;
			//cout << setw(75) << white << "Using letters A-J, and then a number 1-10, enter your coordinates: ";
			cout << setw(75) << white << "Using letters A-J, enter your coordinates: ";
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
			cout << setw(74) << red << "=========================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(74) << "=========================================================" << endl;
			Sleep(1500);
			system("cls");

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

		//old conversion that worked with the char boards.
		//letter++;
		//cLETTER++;
	}

	//cout << spaceOneNum; //testing to see if it counts right.

}

void secCoord(int &spaceTwo, bool &promptCheck, string board[][11], string shipName[], int &count, string shipsPlaced[][11])
{

	promptCheck = false;
	while (!promptCheck)
	{
		
			system("cls");
			//board_intilization(spaceOneNum, spaceTwo);
			displayBlank(shipsPlaced); //board // lets you visualize the board when placing the ships cord on the Y - COlS axis
			cout << endl;
			cout << white << setw(55) << "Player one, enter coordinates for the " << shipName[count] << endl;
			cout << setw(75) << white << "Using numbers 1-10, enter your second coordinate: ";
			cin >> spaceTwo;
		

		if (spaceTwo >= 1 && spaceTwo <= 10)
		{
			promptCheck = true;
			spaceTwo = (spaceTwo);

		}
		else
		{
			cout << endl;
			cout << setw(75) << red << "============================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
			cout << setw(75) << "============================================================" << endl;
			//cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
			cout << endl;
			Sleep(1500);
			system("cls");

		}

	}
	promptCheck = false;



}

void secCoordOne(int &spaceTwo, bool &promptCheck, string board[][11])
{

	promptCheck = false;
	while (!promptCheck)
	{
		
			system("cls");
			//board_intilization(spaceOneNum, spaceTwo);
			displayBlank(board);
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
			cout << endl;
			cout << setw(75) << red << "============================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
			cout << setw(75) << "============================================================" << endl;
			//cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
			cout << endl;
			Sleep(1500);
			system("cls");

		}

	}
	promptCheck = false;



}

void displayBlank(string board[][11])
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

void setPos(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy, string board[][11], string shipName[], bool &promptCheck, string shipsPlaced[][11]) // board
{
	promptCheck = false;

	do
	{
		system("cls");
		displayBlank(shipsPlaced);  //board
		cout << endl;
		cout << white << setw(55) << "Player one, enter coordinates for the " << shipName[count] << endl;
		cout << setw(75) << white << "How would you like to place your ship: (Up, Down, Left or Right) ";
		cin >> userDirectionalInput;
		//getline(cin, userDirectionalInput);
		//system("pause");
		//get( userDirectionalInput);

		//would like to get, wasd, arrow keys or numpad to correspond with this instead of typing in the direction. Erik, 11/15/2017

		if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
		{
			up(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;
		
		}
		else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
		{
			down(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
		{
			left(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
		{
			right(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			promptCheck = true;

		}
		else
		{
			//need to test if setw is correct still.
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl;
			cout << setw(65) << red << "--------------------------" << endl;
			cout << setw(65) << "Invalid input. Try again." << endl;
			cout << setw(65) << "--------------------------" << endl;
			Sleep(1500);
		}
	
	} while (promptCheck == false);

}
void Options(int &difficulty)
{
	bool exitInput = false;
	bool valInput = false;
	int optionSelect;
	int diffSelect;


	cout << cyan;
	cout << setw(72) << "WELCOME TO THE OPTIONS SCREEN" << endl;
	cout << setw(67) << "1. Change Difficulty" << endl;
	cout << setw(67) << "4. Back to main menu" << endl;

	while (!exitInput)
	{

		cout << "Please choose 1-*: ";
		cin >> optionSelect;
		if (optionSelect == 1)
		{
			cout << white << setw(67) << "1. Easy (40 guesses)\n";
			cout << white << setw(69) << "2. Normal (30 guesses)\n";
			cout << white << setw(67) << "3. Hard (20 guesses)\n";
			cout << setw(69) << white << "4. Extreme (17 guesses;" << red << " ALL GUESSES MUST BE HITS)\n";
			while (!valInput)
			{
				cout << cyan << "Please selct a difficulty: ";
				cin >> diffSelect;
				if (diffSelect == 1)
				{
					valInput = true;
					difficulty = 40;
				}
				else if (diffSelect = 2)
				{
					valInput = true;
					difficulty = 30;
				}
				else if (diffSelect = 3)
				{
					valInput = true;
					difficulty = 20;
				}
				else if (diffSelect = 4)
				{
					valInput = true;
					difficulty = 17;
				}
				else
				{
					cout << red << "========================" << endl;
					cout << red << "INVALID INPUT, TRY AGAIN" << endl;
					cout << red << "========================" << endl;
					Sleep(2000);
				}
			}
		}
		else if (optionSelect == 4)
		{
			exitInput = true;
		}
	}
	mainMenu();
}

//=============================END OF TRISTAN ABOVE=====================================================================