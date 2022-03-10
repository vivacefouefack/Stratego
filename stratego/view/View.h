#ifndef VIEW_H
#define VIEW_H
#include "../model/Game.h"

namespace std
{
class View{




public:

    inline View(){}

    inline void displayBoard(Game & game);

    inline void displayScore(Game game);

    inline void displayWinner(Game game);

    inline void displayWelcome();

    inline Position askCurrentPosition();

    inline Position askNextPosition();

    inline vector<Piece> piecePositioning();

};


void View::displayWelcome(){
    cout<<"    Bienvenu au Jeu STRATEGO !!!!!! "<<endl;
}
void View::displayScore(Game game){
    cout<< "Score : " <<endl;
    cout<<"Joueur Rouge : "<<game.getPlayerOne().getPieces().size()<<endl;
    cout<<"Joueur Bleu : "<<game.getPlayerTwo().getPieces().size()<<endl;
}
void View::displayWinner(Game game){
    cout<<"Le gagnant est : "<<game.getWinner().getColor()<<endl;
}
void View::displayBoard(Game & game){

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
                if(game.getPlayerOne().isMyPiece(Position(i,j))){
                    if(game.getPlayerOne().getIsMyTurn() || game.getPlayerOne().getPieceAt(Position(i,j)).getRevealed()){
                        cout<<" "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_string()<<" ";
                    }else{

                            cout<<" "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_stringHidden()<<" ";

                    }
                }
                else if(game.getPlayerTwo().isMyPiece(Position(i,j))){
                    if(game.getPlayerTwo().getIsMyTurn() || game.getPlayerTwo().getPieceAt(Position(i,j)).getRevealed()){
                        cout<<" "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_string()<<" ";
                    }else{

                            cout<<" "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_stringHidden()<<" ";

                    }
                }else if(game.inWater(Position(i,j))){
                    cout<<" # ";
                }else {
                    cout<<" . ";
                }
        }
        cout<<""<<endl;
    }
}
}

#endif // VIEW_H
