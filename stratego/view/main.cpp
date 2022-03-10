#include <iostream>
#include "../model/Piece.h"
#include "../model/Player.h"
#include "../model/Game.h"
#include "view.h"

using namespace std;

int main()
{
    Piece piece1(Position(1,2),"5");
    Piece piece2(Position(2,5),"2");
    Piece piece3(Position(6,7),"1");
    Piece piece4(Position(8,9),"8");
    Piece bombe(Position(8,2),"B");
    Piece bombe1(Position(2,4),"B");
    Piece drapeau(Position(9,1),"D");

    vector<Piece>playerOne{piece1,piece2,bombe,bombe1};
    vector<Piece>playerTwo{piece3,piece4,drapeau};

    Player redPlayer(playerOne);
    Player bluePlayer(playerTwo);
    redPlayer.setMyTurn(false);
    bluePlayer.setMyTurn(true);

    Game game(redPlayer,bluePlayer);


    View view;

    view.displayBoard(game);
    cout<<"*********************************"<<endl;
    game.move(Position(6,7),Position(7,7),game.getPlayerTwo(),game.getPlayerOne());
    view.displayBoard(game);

    return 0;
}
