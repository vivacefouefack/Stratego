#ifndef POSITION_H
#define POSITION_H
namespace std
{
class Position {
private:

    /*!
     * \brief abscissa position
     */
    int x_;

    /*!
        * \brief ordered position
        */
    int y_;

public:

    /*!
        * \brief default constructor
        * default constructor of one position
        */
    inline Position(){}

    /*!
        * \brief constructor
        * constructor of one position
        *
        * \param x abscissa
        * \param y ordered
        */
    inline Position(int x ,int y);

    /*!
     * \brief abscissa position getter
     * getter for position of a ball
     *
     * \return abscissa position of ball
     */
    inline int getX();

    /*!
     * \brief ordered position getter
     * getter for ordered position of a ball
     *
     * \return orderer position of ball
     */
    inline int getY();
    /*!
     * \brief update x
     * update the value of x
     *\param the new value of y
     */
    inline void setX( int x);
    /*!
     * \brief update y
     * update the value of y
     *\param the new value of y
     */
    inline void setY( int y);



};
Position::Position(int x,int y):
    x_{x},
    y_{y}
{
}
int Position::getX(){
    return this->x_;
}
int Position::getY(){
    return this->y_;
}
void Position::setX(int x){
   this->x_=x;
}
void Position::setY(int y){
    this->y_=y;
}


}
#endif // POSITION_H
