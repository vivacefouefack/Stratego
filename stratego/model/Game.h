#ifndef GAME_H
#define GAME_H
#include <stdexcept>
#include <iostream>

#include "Player.h"
namespace std
{
class Game {

private:


    /*!
     * \brief the first player
     *
     */
    Player playerOne;
    /*!
     * \brief the second player
     *
     */
    Player playerTwo;


    string message="";



public:

    /*!
      * \brief default constructor
      * default constructor of Board
      */
    inline Game(){}
    /*!
      * \brief  constructor
      * constructor of Game whith players
      */
    inline explicit Game(Player  player1,Player  player2);

    /*!
      * \brief this move method allows you to check all the conditions for moving a piece before performing the move
      * \param current position of the piece to move, new position after move, the player that move the piece
      */
    inline void move( Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent);
    /*!
      * \brief check if the game is over
      * \return true  if a player no longer has a piece or is no longer able to move,
      *  false  if the game can continue
      */
    inline bool gameIsOver();
    /*!
      * \brief give the the winning player
      * \return the winner
      */
    inline Player getWinner();

    /**
     * @brief inWater, this method simply check if at one position there is water
     * @param destination,the position to check
     * @return  true if the position in in the water , false if not
     */
    inline bool inWater(Position destination);

    /**
     * @brief isGoodMove,this method checks if normal movement (not scout movement) is valid.
     * @param currentPosition,the position of the piece that the player is moving
     * @param nextPosition,the position where the player wants to go
     * @return , true if is a good movement , false if not
     */
    inline bool isGoodMove(Position currentPosition,Position nextPosition);

    /**
     * @brief nextCaseMove,  moves the player's piece as a parameter from its current position to a next position
     * after all the conditions have been verified
     * @param currentPosition,the position of the piece that the player is moving
     * @param nextPosition,the position where the player wants to go
     * @param player,the moving player
     * @param opponent,the opponent
     */
    inline void nextCaseMove( Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent);

    /**
     * @brief canMinerMove,this method verifies all the conditions of movement of the scout piece (2)
     * @param currentPosition,the position of the piece that the player is moving
     * @param nextPosition,the position where the player wants to go
     * @param player,the moving player
     * @param opponent,the opponent
     * @return , true if the scout piece can move , false if not
     */
    inline bool canScoutMove(Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent);

    /**
     * @brief getPlayerOne, returns the reference to the first player
     * @return the first player
     */
    inline Player & getPlayerOne();

    /**
     * @brief getPlayerTwo,returns the reference to the second player
     * @return
     */
    inline Player & getPlayerTwo();

    /**
     * @brief canStillMove,this method checks if a player is no longer able to move.
     * @param player,the player to check
     * @return true if the player can still move , false if not
     */
    inline bool canStillMove(Player player);

    /**
     * @brief surrounded,this method checks if a piece is in a situation where it can no longer move
     * @param piece ,the piece to check
     * @return true if the piece is surrounded , false if not
     */
    inline bool surrounded(Player player, Piece piece);

    inline string getMessage();

    inline void setMessage(string s);
};
Game::Game(Player  player1,Player  player2):
    playerOne{player1},
    playerTwo{player2}
{
}

void Game::move( Position  currentPosition,  Position  nextPosition, Player  & player,Player  & opponent){

    if(!player.isMyPiece(currentPosition)){
        cout<<"vous n'avez pas de piece à cette position"<<endl;
        this->message="vous n'avez pas de piece à cette position";
    }else if(player.getPieceAt(currentPosition).to_string()=="D" || player.getPieceAt(currentPosition).to_string()=="B"){

        cout<<"attention! vous ne pouvez pas déplacer cette pièce"<<endl;
        this->message="attention! vous ne pouvez pas déplacer cette pièce";
    }else if(stoi(player.getPieceAt(currentPosition).to_string())!=2 && !isGoodMove(currentPosition,nextPosition)){
        cout<<"mauvais deplacement"<<endl;
        this->message="mauvais deplacement";
    }else if(player.isMyPiece(nextPosition)){
        cout<<"vous avez déjà une piece à la destination"<<endl;
        this->message="vous avez déjà une piece à la destination";
    }else if(this->inWater(nextPosition)){
        cout<<"attention! vous allez dans l'eau"<<endl;
         this->message="attention! vous allez dans l'eau";
    }else if(player.getPieceAt(currentPosition).to_string()=="2"){

            if(!this->canScoutMove(currentPosition,nextPosition,player,opponent)){
                cout<<"mauvais deplacement de l'eclaireur"<<endl;
                this->message="mauvais deplacement de l'eclaireur";
            }else{
                this->nextCaseMove(currentPosition,nextPosition,player,opponent);

            }

    }else {

        nextCaseMove(currentPosition, nextPosition,player,opponent);

    }


}
bool Game::inWater(Position destination){
    if((destination.getX()==4 && destination.getY()==2) ||(destination.getX()==4 && destination.getY()==3)
           || (destination.getX()==4 && destination.getY()==6) ||(destination.getX()==4 && destination.getY()==7)
            ||(destination.getX()==5 && destination.getY()==2) ||(destination.getX()==5 && destination.getY()==3)
            || (destination.getX()==5 && destination.getY()==6) ||(destination.getX()==5 && destination.getY()==7)){
        return true;
    }
    return false;
}
bool Game::gameIsOver(){
    for(unsigned u=0;u<this->playerOne.getPieces().size();u++){
        if(playerOne.getPieces().at(u).to_string()=="D" && playerOne.getPieces().at(u).getRevealed()==true){
            return true;
        }
    }

    for(unsigned u=0;u<this->playerTwo.getPieces().size();u++){
        if(playerTwo.getPieces().at(u).to_string()=="D" && playerTwo.getPieces().at(u).getRevealed()==true){
            return true;
        }
    }
    if(!canStillMove(playerOne)||!canStillMove(playerTwo)){
        return true;
    }



    return false;
}

Player Game::getWinner(){
    for(unsigned u=0;u<this->playerOne.getPieces().size();u++){
        if(playerOne.getPieces().at(u).to_string()=="D" && playerOne.getPieces().at(u).getRevealed()==true){
            return playerTwo;
        }
    }
    if(!canStillMove(playerOne)){
        return playerTwo;
    }


    return playerOne;
}
inline bool Game::isGoodMove(Position currentPosition,Position nextPosition){
    if(nextPosition.getX()-currentPosition.getX()>1 || nextPosition.getX()-currentPosition.getX()<-1){
        return false;
    }else if(nextPosition.getY()-currentPosition.getY()>1 || nextPosition.getY()-currentPosition.getY()<-1){
        return false;
    }else if(nextPosition.getY()!=currentPosition.getY() && nextPosition.getX()!=currentPosition.getX()){
        return false;
    }else if(currentPosition.getX()<0 || currentPosition.getX()>9 || currentPosition.getY()<0 || currentPosition.getY()>9){
        return false;
    }else if(nextPosition.getX()<0 || nextPosition.getX()>9 || nextPosition.getY()<0 || nextPosition.getY()>9){
        return false;
    }
    return true;
}

bool Game::canScoutMove(Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent){

    if(nextPosition.getY()!=currentPosition.getY() && nextPosition.getX()!=currentPosition.getX()){
            return false;
    }
    if(currentPosition.getX()<=nextPosition.getX()){
       for(int i=currentPosition.getX()+1;i<nextPosition.getX();i++){
           if(player.isMyPiece(Position(i,currentPosition.getY())) || opponent.isMyPiece(Position(i,currentPosition.getY())) ){
              return false;

               }else if(this->inWater(Position(i,currentPosition.getY()))){
                     return false;
                 }
         }
    }else{
       for(int i=currentPosition.getX()-1;i>nextPosition.getX();i--){
            if(player.isMyPiece(Position(i,currentPosition.getY())) || opponent.isMyPiece(Position(i,currentPosition.getY())) ){
                 return false;
                 }else if(this->inWater(Position(i,currentPosition.getY()))){
                     return false;
                    }
        }
    }

    if(currentPosition.getY()<=nextPosition.getY()){
     for(int i=currentPosition.getY()+1;i<nextPosition.getY();i++){
       if(player.isMyPiece(Position(currentPosition.getX(),i)) || opponent.isMyPiece(Position(currentPosition.getX(),i)) ){
                 return false;
           }else if(this->inWater(Position(i,currentPosition.getX()))){
                return false;
             }
        }
   }else{
       for(int i=currentPosition.getY()-1;i>nextPosition.getY();i--){
         if(player.isMyPiece(Position(currentPosition.getX(),i)) || opponent.isMyPiece(Position(currentPosition.getX(),i)) ){
                   return false;
             }else if(this->inWater(Position(currentPosition.getX(),i))){
                  return false;
               }
          }
   }
    return true;
}

void Game::nextCaseMove( Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent){
  if (opponent.isMyPiece(nextPosition)){

    if(opponent.getPieceAt(nextPosition).to_string()=="D"){
        opponent.getPieceAt(nextPosition).setRevealed();
    }
        else if(stoi(player.getPieceAt(currentPosition).to_string())==3 && opponent.getPieceAt(nextPosition).to_string()=="B"){

        player.getPieceAt(currentPosition).setRevealed();
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.getPieceAt(currentPosition).move(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
        else if(opponent.getPieceAt(nextPosition).to_string()=="B"){

        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        opponent.getPieceAt(nextPosition).setRevealed();
        player.setMyTurn(false);
        opponent.setMyTurn(true);

    }
        else if(stoi(player.getPieceAt(currentPosition).to_string())==stoi(opponent.getPieceAt(nextPosition).to_string())){

        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
        else if(stoi(player.getPieceAt(currentPosition).to_string())>stoi(opponent.getPieceAt(nextPosition).to_string())){

        player.getPieceAt(currentPosition).setRevealed();
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.getPieceAt(currentPosition).move(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
        else if(stoi(player.getPieceAt(currentPosition).to_string())<stoi(opponent.getPieceAt(nextPosition).to_string())){

        opponent.getPieceAt(nextPosition).setRevealed();
        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
        else if(stoi(player.getPieceAt(currentPosition).to_string())==1 && stoi(opponent.getPieceAt(nextPosition).to_string())==10){

        player.getPieceAt(currentPosition).setRevealed();
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.getPieceAt(currentPosition).move(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
  }

  else if(player.getPieceAt(currentPosition).roundTripCheck(nextPosition)){
        cout<<"attention! vous essayez de faire plus de 3 aller retour"<<endl;
        this->message="attention! vous essayez de faire plus de 3 aller retour";


    }else{

      player.emptyLastOccupation(player.getPieceAt(currentPosition));
      player.getPieceAt(currentPosition).move(nextPosition);
      player.setMyTurn(false);
      opponent.setMyTurn(true);

  }
}

Player & Game::getPlayerOne(){
    return this->playerOne;
}
Player & Game::getPlayerTwo(){
    return this->playerTwo;
}
bool Game::canStillMove(Player player){
    for(unsigned u=0;u<player.getPieces().size();u++){
        if(player.getPieces().at(u).to_string()!="D" && playerOne.getPieces().at(u).to_string()!="B"){
            if(!surrounded(player,player.getPieces().at(u))){
                return true;
            }
        }
    }

    return false;
}

bool Game::surrounded(Player player,Piece piece){
    if(isGoodMove(piece.getPosition(),Position(piece.getPosition().getX()+1,piece.getPosition().getY()))){
        if(!player.isMyPiece(Position(piece.getPosition().getX()+1,piece.getPosition().getY()))){
            if(!inWater(Position(piece.getPosition().getX()+1,piece.getPosition().getY()))){
                return false;
            }
        }
    }
    if(isGoodMove(piece.getPosition(),Position(piece.getPosition().getX()-1,piece.getPosition().getY()))){
        if(!player.isMyPiece(Position(piece.getPosition().getX()-1,piece.getPosition().getY()))){
            if(!inWater(Position(piece.getPosition().getX()-1,piece.getPosition().getY()))){
                   return false;
            }
        }
    }
    if(isGoodMove(piece.getPosition(),Position(piece.getPosition().getX(),piece.getPosition().getY()+1))){
        if(!player.isMyPiece(Position(piece.getPosition().getX(),piece.getPosition().getY()+1))){
            if(!inWater(Position(piece.getPosition().getX(),piece.getPosition().getY()+1))){
                return false;
            }
        }
    }
    if(isGoodMove(piece.getPosition(),Position(piece.getPosition().getX(),piece.getPosition().getY()-1))){
        if(!player.isMyPiece(Position(piece.getPosition().getX(),piece.getPosition().getY()-1))){
            if(!inWater(Position(piece.getPosition().getX(),piece.getPosition().getY()-1))){
                return false;
            }
        }
    }
    return true;
}

string Game::getMessage(){
    return this->message;
}
void Game::setMessage(string s){
    this->message=s;
}


}

#endif // GAME_H
