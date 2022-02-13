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
    bool revealed_;
    /*!
     * \brief last occupied positions of the piece
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
    inline  bool roundTripCheck();
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

};
}

#endif // PIECE_H
