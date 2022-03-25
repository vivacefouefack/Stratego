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

    /**
     * @brief isMyTurn, a boolean which will allow to give the hand to a player
     */
    bool isMyTurn=false;

    /**
     * @brief color_,represents the color of a player
     */
    string color_;




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
    inline explicit Player(std::vector <Piece> pieces,string color);

    /*!
        * \brief pieces getter
        * getter for all pieces of player
        *
        * \return list of pieces
        */
    inline std::vector <Piece> & getPieces();

    /**
     * @brief addLostPiece,the method adds a piece among the lost pieces
     * @param piece, the lost piece
     */
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

    /**
     * @brief getLostPiece,gives all the lost pieces.
     * @return return lost pieces
     */
    inline std::vector<Piece> & getLostPiece();

    /**
     * @brief getPieceAt,this method makes it possible to obtain the piece which is at a position
     * @param position,the position where the piece you are looking for is located
     * @return , the piece at the position
     */
    inline Piece & getPieceAt(Position position);

    /**
     * @brief emptyLastOccupation, this method empties all the history of movements
     * of each of its pieces except the piece enters in parameter
     * @param piece,the room whose movement history will not be deleted.
     */
    inline void emptyLastOccupation(Piece piece);

    /**
     * @brief setMyTurn,this method allows us to give or remove the hand to the player
     * @param tour, true to give hand to the player, false to remove hand to the player
     */
    inline void setMyTurn(bool tour);

    /**
     * @brief getIsMyTurn, simple getter of isMyTurn.
     * @return isMyTurn
     */
    inline bool getIsMyTurn();

    /**
     * @brief getColor, simple getter of the player color
     * @return the player color
     */
    inline string getColor();




};
Player::Player(std::vector<Piece> pieces,string color):
    pieces_{pieces},
    color_{color}
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
    unsigned index=0;
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
string Player::getColor(){
    return this->color_;
}



}
#endif // PLAYER_H
