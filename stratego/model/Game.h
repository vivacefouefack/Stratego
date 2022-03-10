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
      * \brief moves the player's piece as a parameter from its current position to a next position
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

    inline bool inWater(Position destination);

    inline bool isGoodMove(Position currentPosition,Position nextPosition);

    inline void nextCaseMove( Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent);
    inline bool canMinerMove(Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent);
    inline Player & getPlayerOne();
    inline Player & getPlayerTwo();
    inline void fillBoard();
    inline string ** getBoard();

};
Game::Game(Player  player1,Player  player2):
    playerOne{player1},
    playerTwo{player2}
{
}

void Game::move( Position  currentPosition,  Position  nextPosition, Player  & player,Player  & opponent){

    if(!player.isMyPiece(currentPosition)){
        throw std::invalid_argument("vous n'avez pas de piece à cette position");
    }else if(player.getPieceAt(currentPosition).to_string()=="D" || player.getPieceAt(currentPosition).to_string()=="B"){
        throw std::invalid_argument("attention! vous ne pouvez pas déplacer cette pièce");
    }else if(stoi(player.getPieceAt(currentPosition).to_string())!=2 && !isGoodMove(currentPosition,nextPosition)){
         throw std::invalid_argument("mauvais deplacement");
    }else if(player.isMyPiece(nextPosition)){
         throw std::invalid_argument("vous avez déjà une piece à la destination");
    }else if(this->inWater(nextPosition)){
        throw std::invalid_argument("attention! vous allez dans l'eau");
    }else if(player.getPieceAt(currentPosition).to_string()=="2"){

            if(!this->canMinerMove(currentPosition,nextPosition,player,opponent)){
               throw std::invalid_argument("mauvais deplacement du demineur");
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

    if(playerOne.getPieces().size()==7 ||playerTwo.getPieces().size()==7){
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

    if(playerOne.getPieces().size()==7 ){
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
    }
    return true;
}

bool Game::canMinerMove(Position  currentPosition , Position  nextPosition , Player & player,Player  & opponent){

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
    }else if(opponent.getPieceAt(nextPosition).to_string()=="B"){

        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        opponent.getPieceAt(nextPosition).setRevealed();
        player.setMyTurn(false);
        opponent.setMyTurn(true);

    }else if(stoi(player.getPieceAt(currentPosition).to_string())==stoi(opponent.getPieceAt(nextPosition).to_string())){
        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }else if(stoi(player.getPieceAt(currentPosition).to_string())>stoi(opponent.getPieceAt(nextPosition).to_string())){
        player.getPieceAt(currentPosition).setRevealed();
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.getPieceAt(currentPosition).move(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }else if(stoi(player.getPieceAt(currentPosition).to_string())<stoi(opponent.getPieceAt(nextPosition).to_string())){
        opponent.getPieceAt(nextPosition).setRevealed();
        player.addLostPiece(player.getPieceAt(currentPosition));
        player.removePiece(currentPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }else if(stoi(player.getPieceAt(currentPosition).to_string())==1 && stoi(opponent.getPieceAt(nextPosition).to_string())==10){
        player.getPieceAt(currentPosition).setRevealed();
        opponent.addLostPiece(opponent.getPieceAt(nextPosition));
        opponent.removePiece(nextPosition);
        player.getPieceAt(currentPosition).move(nextPosition);
        player.setMyTurn(false);
        opponent.setMyTurn(true);
    }
  }else if(player.getPieceAt(currentPosition).roundTripCheck(nextPosition)){

      throw std::invalid_argument("attention! vous essayez de faire plus de 3 aller retour");

    }else{

      player.emptyLastOccupation(player.getPieceAt(currentPosition));
      player.getPieceAt(currentPosition).move(nextPosition);
     // player.setMyTurn(false);
      //opponent.setMyTurn(true);

  }
}

Player & Game::getPlayerOne(){
    return this->playerOne;
}
Player & Game::getPlayerTwo(){
    return this->playerTwo;
}



}

#endif // GAME_H
