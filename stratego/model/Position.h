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
        * \param x , the line
        * \param y ,the column
        */
    inline Position(int x ,int y);

    /*!
     * \brief line getter
     * \return the line
     */
    inline int getX();

    /*!
     * \brief column getter
     * \return the column
     */
    inline int getY();
    /*!
     * \brief update line
     * update the value of line
     *\param the new value of line
     */
    inline void setX( int x);
    /*!
     * \brief update column
     * update the value of column
     *\param the new value of column
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
