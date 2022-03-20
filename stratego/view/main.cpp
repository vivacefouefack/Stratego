#include <iostream>
#include "../model/Piece.h"
#include "../model/Player.h"
#include "../model/Game.h"
#include "view.h"

using namespace std;

int main()
{





    View view;
    vector<Piece> piecesOne=view.redPiecePositioning();
    vector<Piece> piecesTwo=view.bluePiecePositioning();
    Player playerOne(piecesOne);
    Player playerTwo(piecesTwo);
    Game game(playerOne,playerTwo);
    game.getPlayerOne().setMyTurn(true);
    game.getPlayerTwo().setMyTurn(true);
    view.displayBoard(game);

}
