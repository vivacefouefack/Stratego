#ifndef PLAYER_H
#define PLAYER_H
#include "Piece.h"
#include <vector>
#include "Position.h"
#include <string>
namespace std
{
/*!
 * \class Player
 * it's class to represent a instance of player
 */
class Player
{
private:

    /*!
     * \brief pieces of player
     * list of all pieces of a player
     */
    std::vector<Piece> pieces_;
    /*!
     * \brief lost pieces of player
     * list of lost pieces of a player
     */
    std::vector<Piece> lostPieces_;

    bool isMyTurn=false;

    string color="";




public:

    /*!
      * \brief default constructor
      * default constructor of a Player
      */
    inline Player(){}

    /*!
        * \brief constructor of player
        * constructor of a Player with his list of pieces
        *
        *  \param pieces,  pieces of player
        */
    inline explicit Player(std::vector <Piece> pieces);

    /*!
        * \brief pieces getter
        * getter for all pieces of player
        *
        * \return list of pieces
        */
    inline std::vector <Piece> & getPieces();


    inline void addLostPiece(Piece piece);

    /*!
        * \brief remove the piece
        * removes the piece that's dead
        *
        * \param position of the piece that has to be removed
        */
    inline void removePiece(Position position);

    /*!
        * \brief
        * says if the player has his piece at the position in parameter
        *
        * \param the position that we have to test if it's for this player
        * \return  true if yes and false if not
        */
    inline bool isMyPiece(Position position);


    inline std::vector<Piece> & getLostPiece();

    inline Piece & getPieceAt(Position position);

    inline void emptyLastOccupation(Piece piece);

    inline void setMyTurn(bool tour);
    inline bool getIsMyTurn();
    inline void setColor(string color);
    inline string getColor();
    inline void hideAllPiece();



};
Player::Player(std::vector<Piece> pieces):
    pieces_{pieces}
{

}
vector<Piece> & Player::getPieces(){
    return this->pieces_;
}
void Player::addLostPiece(Piece piece){
    this->lostPieces_.push_back(piece);
}
void Player::removePiece(Position position){
    for(unsigned u=0;u<this->pieces_.size();u++){
        if(this->pieces_.at(u).getPosition().getX()==position.getX()
           && this->pieces_.at(u).getPosition().getY()==position.getY() ){
            this->addLostPiece(this->pieces_.at(u));
             this->pieces_.erase(this->pieces_.begin()+u);
        }
    }
}
bool Player::isMyPiece(Position position){
    for(unsigned u=0;u<this->pieces_.size();u++){
        if(this->pieces_.at(u).getPosition().getX()==position.getX()
           && this->pieces_.at(u).getPosition().getY()==position.getY() ){
            return true;
        }
    }
    return  false;
}
vector<Piece> & Player::getLostPiece(){
    return this->lostPieces_;
}
Piece & Player::getPieceAt(Position position){
    unsigned index=0;//???????????????
    for(unsigned u=0;u<this->pieces_.size();u++){
            if(this->pieces_.at(u).getPosition().getX()==position.getX()
               && this->pieces_.at(u).getPosition().getY()==position.getY() ){
                index=u;
            }
        }
    return this->pieces_.at(index);

}
void Player::emptyLastOccupation(Piece piece){
    for(unsigned u=0;u<this->pieces_.size();u++){
            if(this->pieces_.at(u).getPosition().getX()!=piece.getPosition().getX()
               || this->pieces_.at(u).getPosition().getY()!=piece.getPosition().getY() ){
                this->pieces_.at(u).emptyLastOccup();
        }
    }
}
void Player::setMyTurn(bool tour){
    this->isMyTurn=tour;
}
bool Player::getIsMyTurn(){
    return this->isMyTurn;
}
void Player::setColor(string color){
    this->color=color;
}
string Player::getColor(){
    return this->color;
}



}
#endif // PLAYER_H
