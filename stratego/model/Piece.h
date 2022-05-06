#ifndef PIECE_H
#define PIECE_H
#include "Position.h"
#include <vector>
#include <string>
namespace std
{
class Piece {

private:

    /*!
     * \brief position of the piece
     *
     */
    Position  position_;
    /*!
     * \brief rank of the piece
     *
     */
    string symbole_;
    /*!
     * \brief indicates if the piece is revealed.
     * a piece remains revealed if it emerges victorious from a combat
     *
     */
    bool revealed_=false;
    /*!
     * \brief this vector will make it possible to record the movement history of the piece
     *
     */
    vector<Position> lastOccupation ;
public:

    /*!
      * \brief default constructor
      * default constructor of a Piece
      */
    inline Piece(){}

    /*!
        * \brief constructor of piece
        * constructor of a Piece with his position and his symbole
        *
        *  \param pieces,  pieces of player
        */
    inline explicit Piece(Position position,string symbole);

    /*!
        * \brief move the piece
        * moves the piece to the next position given as a parameter
        *
        *  \param the next position of the piece
        */
    inline  void move(Position nextPosition);

    /*!
        * \brief checks with lastOccupation if the piece
        * has made more than three round trips
        *  \return  true if yes and false if not
        */
    inline  bool roundTripCheck(Position nextPosition);

    /**
     * @brief getPosition, simple getter of position of the piece
     * @return position of the piece
     */
    inline Position & getPosition();

    /*!
        * \brief piece in string .
        * a piece will be represented on the board by its symbol
        *\return  the string value
        */

    string to_string();
    /*!
        * \brief when a player plays the opponent pieces will be represented by this string
        *  \return  the string value
        */
    string to_stringHidden();

    /**
     * @brief getRevealed, simple getter of revealed
     * @return revealed
     */
    inline bool getRevealed();

    /**
     * @brief setRevealed,modify the revealed status of a piece
     */
    inline void setRevealed();

    /**
     * @brief addLastOccupation,adds a position in the movement history of the piece
     * @param position,the position to add
     */
    inline void addLastOccupation(Position position);

    /**
     * @brief emptyLastOccup,this method empties the movement history of the piece.
     */
    inline void emptyLastOccup();


};
Piece::Piece(Position position,string symbole):
    position_{position},
    symbole_{symbole}
{
}
Position & Piece::getPosition(){
    return this->position_;
}
void Piece::move(Position nextPosition){
    this->position_.setX(nextPosition.getX());
    this->position_.setY(nextPosition.getY());
    this->addLastOccupation(nextPosition);
}
inline string Piece::to_string(){
    return this->symbole_;
}
inline string Piece::to_stringHidden(){
    return "?";
}
bool Piece::getRevealed(){
    return this->revealed_;
}
void Piece::setRevealed(){
    this->revealed_=true;
}
void Piece::addLastOccupation(Position position){
        this->lastOccupation.push_back(position);
}
bool Piece::roundTripCheck(Position nextPosition)
{
    if(this->lastOccupation.size()<7){
        return false;
    }
    this->addLastOccupation(nextPosition);
    for(unsigned u=0;u<this->lastOccupation.size()-2;u++){
        if(lastOccupation.at(u).getX()!=lastOccupation.at(u+2).getX()
                || lastOccupation.at(u).getY()!=lastOccupation.at(u+2).getY() ){
            return false;
        }
    }

    return true;
}
void Piece::emptyLastOccup(){
    this->lastOccupation.clear();
}

}

#endif // PIECE_H
