#include <iostream>
#include "../model/Piece.h"
#include "../model/Player.h"
#include "../model/Game.h"
#include "view.h"
#include <fstream>
#include <iostream>

#define BLEUCLAIR "\033[01;34m"
#define ROUGE "\033[00;31m"
#define BLEU "\033[00;34m"
#define SOULIGNE "\033[04m"
#define NORMAL "\033[00m"

#include <windows.h>
using namespace std;

int main()
{


    View view;
    vector<Piece> piecesOne=view.redFilePositioning();
    vector<Piece> piecesTwo=view.blueFilePositioning();
    Player playerOne(piecesOne,"Rouge");
    Player playerTwo(piecesTwo,"Blue");
    Game game(playerOne,playerTwo);
    game.getPlayerOne().setMyTurn(true);
    game.getPlayerTwo().setMyTurn(true);
    view.displayBoard(game);




   return 0;
}
