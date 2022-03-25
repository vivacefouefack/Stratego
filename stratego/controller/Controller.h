#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/Piece.h"
#include "../model/Player.h"
#include "../model/Game.h"
#include "../view/view.h"
namespace std
{
/**
 * @brief The Controller class, this is the class that will connect the view and the model and allow the game to be launched
 */
class Controller{

public:
    /**
     * @brief default controller
     */
    inline Controller(){}

    /**
     * @brief start,this method starts the game
     */
    inline void start();
};

void Controller::start(){
    View view;
    view.displayWelcome();
    vector<Piece> piecesOne;
    vector<Piece> piecesTwo;
    if(view.askPositioningStyle()==1){
        piecesOne=view.redFilePositioning();
        piecesTwo=view.blueFilePositioning();
    }else{
        piecesOne=view.redPiecePositioning();
        piecesTwo=view.bluePiecePositioning();
    }
    Player playerOne(piecesOne,"Rouge");
    Player playerTwo(piecesTwo,"Blue");
    Game game(playerOne,playerTwo);
    game.getPlayerOne().setMyTurn(true);
    view.displayBoard(game);
    view.displayScore(game);
    while(!game.gameIsOver()){
        if(game.getPlayerOne().getIsMyTurn()){
             view.whoIsPlaying(game.getPlayerOne());
             Position current=view.askCurrentPosition();
             Position next=view.askNextPosition();
             game.move(current,next,game.getPlayerOne(),game.getPlayerTwo());
             view.displayBoard(game);
             view.displayScore(game);
        }else{
              view.whoIsPlaying(game.getPlayerTwo());
              Position current=view.askCurrentPosition();
              Position next=view.askNextPosition();
              game.move(current,next,game.getPlayerTwo(),game.getPlayerOne());
              view.displayBoard(game);
              view.displayScore(game);
        }

    }

    view.displayWinner(game);

}
}


#endif // CONTROLLER_H
