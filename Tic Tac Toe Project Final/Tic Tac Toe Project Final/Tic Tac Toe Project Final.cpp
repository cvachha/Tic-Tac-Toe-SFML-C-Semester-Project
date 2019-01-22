/*
Tic Tac Toe created with SFML
Semester Project
Created by: Mathew Han, Cyrus Vachha, and David Zhu
*/
#include "pch.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <stdlib.h>

using namespace std;
using namespace sf;
const int D = 3;


// Function prototypes
string getCol(string board[D][D], int c);
string getRow(string board[D][D], int r);
string getDiag(string board[D][D], int d);
bool isWinState(string state);
bool isGameOver(string board[D][D]);
int computerTurn(string board[3][3]);

/*
This function returns the contents from a given column from the board
@param Board the string arrray of the board
@int c The column number to return
@return The column contents as a string
*/
string getCol(string board[3][3], int c)
{
	string column = "";
	for (int i = 0; i < 3; i++) column = column + board[i][c];
	return column;
}

/*
This function returns the contents from a given row from the board
@param Board the string arrray of the board
@int r The row number to return
@return The row contents as a string
*/
string getRow(string board[3][3], int r)
{
	string row = "";
	for (int i = 0; i < 3; i++) row += board[r][i];
	return row;
}

/*
This function returns the contents from a given diagonal from the board
@param Board the string arrray of the board
@int d The diagonal number to return
@return The diagonal contents as a string
*/
string getDiag(string board[3][3], int d)
{
	string diagonal = "";
	for (int i = 0; i < 3; i++) diagonal += board[i][2 * d + (1 - 2 * d)*i];
	return diagonal;
}

/*
This function returns boolean indicated whether a player has won
@param state The string input (column, row, or diagonal)
@return A boolean indicating whether a player has won
*/
bool isWinState(string state)
{
	return state[0] == state[1] && state[1] == state[2] && state[0] != ' ';
}

/*
This function returns boolean indicated whether the game has ended
@param board The board
@return A boolean indicating whether the game has ended
*/
bool isGameOver(string board[3][3])
{
	for (int i = 0; i < 3; i++) if (isWinState(getRow(board, i)) || isWinState(getCol(board, i))) return true;
	for (int i = 0; i < 2; i++) if (isWinState(getDiag(board, i))) return true;
	return false;
}

/*
This function creates and draws the game board
@param window The SFML graphics window
*/
void DrawGameBoard(RenderWindow &window)
{
	RectangleShape boardLine1(Vector2f(200.f, 5.f));
	boardLine1.setPosition(250, 250 - 40);
	boardLine1.setOrigin(100.f, 2.5f);
	boardLine1.setFillColor(Color::Black);
	boardLine1.rotate(0.f);

	RectangleShape boardLine2(Vector2f(200.f, 5.f));
	boardLine2.setPosition(250, 250 + 40);
	boardLine2.setOrigin(100.f, 2.5f);
	boardLine2.setFillColor(Color::Black);
	boardLine2.rotate(0.f);

	RectangleShape boardLine3(sf::Vector2f(200.f, 5.f));
	boardLine3.setPosition(250 - 40, 250);
	boardLine3.setFillColor(Color::Black);
	boardLine3.setOrigin(100.f, 2.5f);

	boardLine3.rotate(90.f);

	RectangleShape boardLine4(Vector2f(200.f, 5.f));
	boardLine4.setPosition(250 + 40, 250);
	boardLine4.setFillColor(Color::Black);
	boardLine4.setOrigin(100.f, 2.5f);
	boardLine4.rotate(90.f);

	window.draw(boardLine1);
	window.draw(boardLine2);
	window.draw(boardLine3);
	window.draw(boardLine4);
}


/*
This function creates and draws the markers on the game board
@param window The SFML window
@param boardSymbols The array of symbols on the board
*/
void DrawMarkers(RenderWindow &window, Text *boardSymbols[D][D])
{
	for (int i = 0; i < D; i++)
	{
		for (int j = 0; j < D; j++)
		{
			window.draw(*boardSymbols[i][j]);

		}
	}
}



/*
This function returns the computer's chosen position
@param board The string array of the board
@return The computer's chosen position
*/
int computerTurn(string board[3][3])
{
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
		{

			if (board[i][j] == board[i][(j + 1) % 3] && isdigit(board[i][(j + 2) % 3][0]))
			{
				return 3 * i + ((j + 2) % 3) + 1; //horizontal ones
			}
			if (board[i][j] == board[(i + 1) % 3][j] && isdigit(board[(i + 2) % 3][j][0]))
			{
				return 3 * ((i + 2) % 3) + j + 1; //vertical
			}
		}

		if (board[i][i] == board[(i + 1) % 3][(i + 1) % 3] && isdigit(board[(i + 2) % 3][(i + 2) % 3][0]))
		{

			return 4 * ((i + 2) % 3) + 1; //top left -> bottom right diagonals
		}
		if (board[i][2 - i] == board[(i + 1) % 3][2 - (i + 1) % 3] && isdigit(board[(i + 2) % 3][2 - (i + 2) % 3][0]))
		{

			return 2 * ((i + 2) % 3) + 3; //top right -> bottom left diagonal
		}
	}

	int position;

	do
	{
		position = rand() % 9;
	} while (position > 8 || position < 0 || !isdigit(board[position / 3][position % 3][0]));

	return position + 1;

}

int main()
{

	//SFML window
	RenderWindow window(sf::VideoMode(500, 500), "Tic Tac Toe");


	Vector2u windowSize = window.getSize();
	int width = windowSize.x;
	int height = windowSize.y;


	Texture bgTexture;
	bgTexture.loadFromFile("menuScreen.png", sf::IntRect(0, 0, 500, 500));

	string gameMode = "";
	int turn = 0;
	bool isGameOverBool = false;
	bool isTie = false;
	bool computersTurn = false;
	Font font;
	font.loadFromFile("ariblk.ttf");
	string displayText = "";
	string board[D][D] = { { "1", "2", "3" }, { "4", "5", "6" }, { "7", "8", "9" } };

	Text *boardSymbols[D][D];
	Text text;
	text.setFont(font);
	text.setString(displayText);
	text.setCharacterSize(24);
	text.setFillColor(Color::Black);


	FloatRect textRect = text.getLocalBounds();
	text.setPosition(Vector2f(width / 2.0f - 100, 30));

	//background
	RectangleShape bg(Vector2f(width, height));
	Color bgColor(211, 211, 211);

	bg.setFillColor(bgColor);

	RectangleShape mainMenuScreen(Vector2f(width, height));
	mainMenuScreen.setTexture(&bgTexture);

	Text promptText;
	promptText.setFont(font);
	promptText.setString("");
	promptText.setCharacterSize(16);
	promptText.setFillColor(Color::Black);
	FloatRect promptTextRect = promptText.getLocalBounds();
	promptText.setOrigin(promptTextRect.left + promptTextRect.width / 2.0f, promptTextRect.top + promptTextRect.height / 2.0f);
	promptText.setPosition(Vector2f(width / 2.0f - 40, height / 2.0f));

	string xo = "X";

	bool isPlaying = false;

	//This creates the markers for the board
	for (int i = 0; i < D; i++)
	{
		for (int j = 0; j < D; j++)
		{

			boardSymbols[i][j] = new Text;
			boardSymbols[i][j]->setPosition(160 + 75 * j, 150 + 75 * i);

			//marker
			boardSymbols[i][j]->setFont(font);
			boardSymbols[i][j]->setFillColor(Color::Black);

			string numString = to_string(i * 3 + j + 1);
			boardSymbols[i][j]->setString(numString);

			boardSymbols[i][j]->setCharacterSize(36);

		}
	}

	while (window.isOpen())
	{
		Event event;

		CircleShape mark(20.f);

		while (window.pollEvent(event))
		{

			if (!isPlaying &&event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (event.mouseButton.x < width / 2.0f)
					{
						if (!isPlaying)
						{
							//2 player version
							gameMode = "twoPlayer";
							isPlaying = true;
							mainMenuScreen.setFillColor(Color::Transparent);
							promptText.setPosition(90, 100);
							promptText.setString("Please enter in a valid position (1-9)");
						}
					}

					if (event.mouseButton.x > width / 2.0f)
					{
						//AI version
						if (!isPlaying)
						{
							isPlaying = true;
							mainMenuScreen.setFillColor(Color::Transparent);
							promptText.setPosition(120, 100);
							gameMode = "AI";

						}
					}
				}

			}


			if (isPlaying) {

				if (!isGameOverBool) {
					//Still playing
					if (gameMode == "twoPlayer")
					{
						displayText = "Player " + to_string(turn % 2 + 1) + "'s turn: ";
					}
					else if (gameMode == "AI")
					{
						displayText = "Your Move:";
					}

					text.setString(displayText);

					if ((event.type == Event::TextEntered) || (computersTurn)) {
						//handle number input
						int position;
						if (gameMode == "twoPlayer" || (gameMode == "AI" && turn % 2 == 0))
						{

							position = static_cast<char>(event.text.unicode) - 49;
							if (gameMode == "AI")
							{
								computersTurn = true;
							}


						}
						if ((gameMode == "AI" && turn % 2 == 1)) {
							//Computer choses position
							position = computerTurn(board) - 1;
							computersTurn = false;
						}

						if (turn >= 9) {
							//Tie
							isGameOverBool = true;
							isTie = true;
							promptText.setString("");

						}
						if (position > 8 || position < 0 || !isdigit(board[position / 3][position % 3][0]))
						{
							//invalid input
							displayText = "Player " + to_string(turn % 2 + 1) + "'s turn: ";

							text.setString(displayText);
							promptText.setString("Invalid Input: Enter in a valid position (1-9)");
							promptText.setFillColor(Color::Red);

						}

						else
						{
							//valid input
							if (gameMode == "twoPlayerMode")
							{
								string displayText = "Player " + to_string(turn % 2 + 1) + "'s turn: ";
							}
							else if (gameMode == "AI")
							{
								displayText = "Your Move:";
							}

							text.setString(displayText);
							promptText.setString("Please enter in a valid position (1-9)");


							promptText.setFillColor(Color::Black);

							if (turn % 2 == 0)
							{
								xo = "X";

								int i = position / 3;
								int j = position % 3;
								boardSymbols[i][j]->setString(xo);


							}
							else
							{
								xo = "O";
								int i = position / 3;
								int j = position % 3;
								boardSymbols[i][j]->setString(xo);
							}
							board[position / 3][position % 3] = xo;

							if (turn >= 9) {
								isGameOverBool = true;
								isTie = true;
								promptText.setString("");

							}

							//check if someone won
							if (!isTie) {
								isGameOverBool = isGameOver(board);
							}

							if (!isGameOverBool)
							{
								turn++;

								if (turn >= 9) {
									isGameOverBool = true;
									isTie = true;
									promptText.setString("");

								}
							}

						}

					}
				}

				else
				{
					//GAME OVER
					isPlaying = false;

					if (!isTie) {
						string displayText = "Player " + to_string(turn % 2 + 1) + " Wins!";
						text.setString(displayText);
						promptText.setString("");
					}
					else {
						//Tie
						string displayText = "A Tie!";
						text.setPosition(Vector2f(width / 2.0f - 30, 30));
						text.setString(displayText);
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}

		window.clear();

		//Elements are drawn
		window.draw(bg);
		DrawGameBoard(window);

		//Markers are drawn
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				window.draw(*boardSymbols[i][j]);
			}
		}

		DrawMarkers(window, boardSymbols);
		window.draw(mainMenuScreen);
		window.draw(text);
		window.draw(promptText);
		window.display();
	}

	return 0;
}