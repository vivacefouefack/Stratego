#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include <vector>
namespace std
{
class Board{
private:

    /*!
     * \brief two-dimensional array representing the game board
     *
     */
    Piece tab[10][10];

public:

    /*!
      * \brief default constructor
      * default constructor of Board
      */
    inline Board(){}

    /*!
      * \brief fill the table with the pieces of the different players
      * default constructor of a Player
      * \param pieces of player one and pieces of player two
      */
    inline void fillBoard(vector<Piece> playerOne,vector<Piece> playerTwo);

};
}

#endif // BOARD_H
