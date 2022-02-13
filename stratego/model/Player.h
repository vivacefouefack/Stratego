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
    inline std::vector <Piece> getPieces();

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


};
}
#endif // PLAYER_H
