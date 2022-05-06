#ifndef MAINSTRATEGO_H
#define MAINSTRATEGO_H

#include <QMainWindow>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainStratego; }
QT_END_NAMESPACE
#include "../controller/Controller.h"
#include "../model/Piece.h"
#include "../model/Player.h"
#include <vector>




class MainStratego : public QMainWindow
{
    Q_OBJECT



public:
    MainStratego(QWidget *parent = nullptr);
    ~MainStratego();
    /**
     * @brief enableRedButton,this method allows you to activate or deactivate the red pieces.
     * @param status,if it is false, the method deactivates the red pieces, and if it is true, the method activates red pieces
     */
    void enableRedButton(bool status);

    /**
     * @brief enableBlueButton,this method allows you to activate or deactivate the blue pieces.
     * @param status,if it is false, the method deactivates the blue pieces, and if it is true, the method activates blue pieces
     */
    void enableBlueButton(bool status);

    /**
     * @brief initGame,allows to initialize the game
     */
    void initGame();

    /**
     * @brief unoccupiedCase,this method allows you to activate the unoccupied squares when starting the game
     */
    void unoccupiedCase();

    /**
     * @brief updateAll,this method makes it possible to update the board during the progress of the game
     * @param message,this argument includes the information to be displayed during the course of the game (example: the bad placement, the winner);
     */
    void updateAll(string message);



private:
    Ui::MainStratego *ui;


private slots:
    /**
     * @brief originPressed,method for associating the action linked to a piece during the stage of positioning the pieces
     */
    void originPressed();

    /**
     * @brief destinationPressed,method for associating the action linked to a box intended to receive a piece previously clicked.
     * it intervenes during the positioning and during the progress of the game
     */
    void destinationPressed();

    /**
     * @brief startPressed,this method will make it possible to associate the action when you click on the "start" button,
     *  by starting the game just after the positioning step
     */
    void startPressed();

    /**
     * @brief cleanPresseButton,this method will make it possible to associate an action with the "init" button
     *  by putting it back to the initial positioning stage
     */
    void cleanPresseButton();

    /**
     * @brief defaulPressetButton,this method will allow you to associate an action with the "default positioning" button
     *  by placing the pieces in a default position
     */
    void defaulPressetButton();

};



#endif // MAINSTRATEGO_H
