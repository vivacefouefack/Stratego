#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
namespace std
{
class Game {
private:

    /*!
     * \brief the game board
     *
     */
    Board bord;
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
    inline explicit Game(Player player1,Player player2);

    /*!
      * \brief moves the player's piece as a parameter from its current position to a next position
      * \param current position of the piece to move, new position after move, the player that move the piece
      */
    inline void move(Position currentPosition ,Position nextPosition , Player player);
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


};
}

#endif // GAME_H
