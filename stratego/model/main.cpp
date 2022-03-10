#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Position.h"
#include "Piece.h"
#include <vector>

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

        Game game(redPlayer,bluePlayer);
        cout<<"Avant move ********"<<endl;
        cout<<"taille du vecteur rouge"<<redPlayer.getPieces().size()<<endl;
        cout<<"taille du vecteur bleu"<<bluePlayer.getPieces().size()<<endl;
        cout<<"Pieces joueur rouge : "<<"piece 1 : "<<redPlayer.getPieces().at(0).getPosition().getX()<< " , "<<redPlayer.getPieces().at(0).getPosition().getY()<<endl;
        cout<<"Pieces joueur rouge : "<<"piece 2 : "<<redPlayer.getPieces().at(1).getPosition().getX()<< " , "<<redPlayer.getPieces().at(1).getPosition().getY()<<endl;
        cout<<"Pieces joueur bleu  : "<<"piece 1 : "<<bluePlayer.getPieces().at(0).getPosition().getX()<< " , "<<bluePlayer.getPieces().at(0).getPosition().getY()<<endl;
        cout<<"Pieces joueur bleu  : "<<"piece 2 : "<<bluePlayer.getPieces().at(1).getPosition().getX()<< " , "<<bluePlayer.getPieces().at(1).getPosition().getY()<<endl;
        cout<<"test "<<game.canMinerMove(Position(2,2),Position(2,5),redPlayer,bluePlayer)<<endl;


        game.move(Position(1,2),Position(1,3),redPlayer,bluePlayer);

        cout<<"Avant move ********"<<endl;
        cout<<"taille du vecteur rouge"<<redPlayer.getPieces().size()<<endl;
        cout<<"taille du vecteur bleu"<<bluePlayer.getPieces().size()<<endl;
        cout<<"Pieces joueur rouge : "<<"piece 1 : "<<redPlayer.getPieces().at(0).getPosition().getX()<< " , "<<redPlayer.getPieces().at(0).getPosition().getY()<<endl;
        cout<<"Pieces joueur rouge : "<<"piece 2 : "<<redPlayer.getPieces().at(1).getPosition().getX()<< " , "<<redPlayer.getPieces().at(1).getPosition().getY()<<endl;
        cout<<"Pieces joueur bleu  : "<<"piece 1 : "<<bluePlayer.getPieces().at(0).getPosition().getX()<< " , "<<bluePlayer.getPieces().at(0).getPosition().getY()<<endl;
        cout<<"Pieces joueur bleu  : "<<"piece 2 : "<<bluePlayer.getPieces().at(1).getPosition().getX()<< " , "<<bluePlayer.getPieces().at(1).getPosition().getY()<<endl;


   /* Position pos1(0,0);
    Position pos2(0,1);
    Position pos3(0,0);
    Position pos4(0,1);
    Position pos5(0,0);
    Position pos6(0,1);
    Position pos7(0,0);
    Position pos8(0,1);
    Piece piece(Position(0,1),"m");
    piece.addLastOccupation(pos1);
    piece.addLastOccupation(pos2);
    piece.addLastOccupation(pos3);
    piece.addLastOccupation(pos4);
    piece.addLastOccupation(pos5);
    piece.addLastOccupation(pos6);
    piece.addLastOccupation(pos7);
    if(piece.roundTripCheck(pos8)){
        cout<<"vous effectuer un allez retour"<<endl;
    }else{
        cout<<"PAS allez retour"<<endl;
    }
*/

    return 0;
}
