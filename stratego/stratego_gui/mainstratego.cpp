#include "mainstratego.h"
#include "ui_mainstratego.h"
#include "../model/Piece.h"
#include "../model/Position.h"
#include "../model/Player.h"
#include "../model/Game.h"
#include <QDebug>



QString permut="";
std::vector<Piece> bluePieces{};
std::vector<Piece> redPieces{};
int blueScore=0;
int redScore=0;
bool accessRedGrid=false;
bool deblocRedGrid=false;
bool PiecePositioning=true;
Position current(-1,-1);
Position nextPos(-2,-2);
QPushButton * buttonInGrid[100];
QPushButton * blueButtons[40];
QPushButton * redButtons[40];
Game game;


MainStratego::MainStratego(QWidget * parent): QMainWindow(parent), ui(new Ui::MainStratego)
{
    ui->setupUi(this);

    for(int i =0; i <40 ; ++i){
        QString buttonName = "piece"+QString::number(i);
        blueButtons[i] =MainStratego::findChild<QPushButton *>(buttonName);
        connect(blueButtons[i], SIGNAL(released()),this,SLOT(originPressed()));
    }

    for(int i =0; i <40 ; ++i){
        QString buttonName = "pieceb"+QString::number(i);
        redButtons[i] =MainStratego::findChild<QPushButton *>(buttonName);
        connect(redButtons[i], SIGNAL(released()),this,SLOT(originPressed()));
    }

    for(int i =0; i <100 ; ++i){
        QString buttonName = "pos"+QString::number(i);

        if(i<10){
            buttonName = "pos0"+QString::number(i);
        }

        buttonInGrid[i] =MainStratego::findChild<QPushButton *>(buttonName);

        if(i==42 || i==43 || i==46 || i==47 || i==52 || i==53 || i==56 || i==57 ){
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color: skyblue; }");
            buttonInGrid[i]->setDisabled(true);
        }else if(i>=40){
            connect(buttonInGrid[i], SIGNAL(released()),this,SLOT(destinationPressed()));
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color:white; }");
            buttonInGrid[i]->setDisabled(true);
        }else{
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color: gray; }");
            connect(buttonInGrid[i], SIGNAL(released()),this,SLOT(destinationPressed()));
        }

    }



    for(unsigned int i = 0; i <=39; i++){
            ui->redPieceGrid->itemAt(i)->widget()->setStyleSheet("QPushButton { background-color: red;color:#c1c1c1;border:5;border-radius: 15px;}");
            ui->redPieceGrid->itemAt(i)->widget()->setDisabled(true);
    }

    for(unsigned int i = 0; i <=39; i++){
            ui->bluePieceGrid->itemAt(i)->widget()->setStyleSheet("QPushButton { background-color: blue;color:#c1c1c1;border:5;border-radius: 15px; }");

    }

    connect(ui->startButton, &QPushButton::clicked,this,&MainStratego::startPressed);
    ui->startButton->setDisabled(true);

    connect(ui->cleanButton, &QPushButton::clicked,this,&MainStratego::cleanPresseButton);
    connect(ui->defaultButton, &QPushButton::clicked,this,&MainStratego::defaulPressetButton);

    initGame();
}


void MainStratego::originPressed(){
    QPushButton *button = (QPushButton *)sender();
    Position pos(button->pos().y()/62,button->pos().x()/75);

    if(permut.size()==0){
        permut=button->text();
        button->hide();

        if(blueScore<=39 && !accessRedGrid){
            blueScore++;

            if(blueScore==40){

                accessRedGrid=true;
            }
        }else if(blueScore==40 && accessRedGrid){
            redScore++;

        }
    }
}


void MainStratego::destinationPressed(){
    QPushButton *button = (QPushButton *)sender();
    if(PiecePositioning){

        if(permut.size()!=0 && button->text().size()==0){
            button->setText(permut);
            if(accessRedGrid && deblocRedGrid){
                button->setStyleSheet("QPushButton {background-color: red;  color: red; }");
                Position pos(button->pos().y()/62,button->pos().x()/75);
                game.getPlayerTwo().getPieces().push_back(Piece(pos,button->text().toStdString()));
                 ui->labelRedScore->setText(QString::number(redScore));
                if(blueScore==redScore){
                    PiecePositioning=false;
                    ui->startButton->setDisabled(false);
                    ui->startButton->setStyleSheet("QPushButton { background-color:green; }");
                }
            }else{
                button->setStyleSheet("QPushButton {background-color:blue;  color: blue; }");
                Position pos(button->pos().y()/62,button->pos().x()/75);             
                game.getPlayerOne().getPieces().push_back(Piece(pos,button->text().toStdString()));
                ui->labelBlueScore->setText(QString::number(blueScore));
            }
            permut="";
        }


        if(accessRedGrid && !deblocRedGrid){
            for(unsigned int i = 0; i <=39; i++){
                    ui->redPieceGrid->itemAt(i)->widget()->setDisabled(false);
            }
            enableRedButton(false);
            deblocRedGrid=true;
        }

    }else{

        Position pos(button->pos().y()/62,button->pos().x()/75);

        if(current.getX()==-1 &&current.getY()){
            current.setX(pos.getX());
            current.setY(pos.getY());
            game.setMessage("");
        }else{
            nextPos.setX(pos.getX());
            nextPos.setY(pos.getY());
        }

        if(current.getX()!=-1 && current.getY()!=-1 && nextPos.getX()!=-2 &&nextPos.getY()!=-2){

            if(game.getPlayerOne().getIsMyTurn()){
                game.move(current,nextPos,game.getPlayerOne(),game.getPlayerTwo());
                updateAll(game.getMessage());
            }else{
                game.move(current,nextPos,game.getPlayerTwo(),game.getPlayerOne());
                updateAll(game.getMessage());
            }
            current.setX(-1);
            current.setY(-1);
            nextPos.setX(-2);
            nextPos.setY(-2);
        }

    }


}

void MainStratego::enableRedButton(bool status){

    if(status){
        for(int i =40; i <100 ; ++i){
            if(i!=42 && i!=43 && i!=46 && i!=47 && i!=52 && i!=53 && i!=56 && i!=57){
                buttonInGrid[i]->setStyleSheet("QPushButton { background-color: white; }");
                buttonInGrid[i]->setText("");
                buttonInGrid[i]->setDisabled(true);
            }
            if(i>=60){
                buttonInGrid[i]->setStyleSheet("QPushButton { background-color: white; }");
                buttonInGrid[i]->setText("");
                buttonInGrid[i]->setDisabled(true);
            }

        }
    }else{
        for(int i =60; i <100 ; ++i){
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color: gray; }");
            buttonInGrid[i]->setDisabled(false);
        }
    }

}

void MainStratego::enableBlueButton(bool status){

    if(status){
        for(int i =0; i <40 ; ++i){
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color: gray; }");
            buttonInGrid[i]->setDisabled(true);
            buttonInGrid[i]->setText("");
        }
    }else{
        for(int i =0; i <40 ; ++i){
            buttonInGrid[i]->setStyleSheet("QPushButton { background-color: gray; }");
            buttonInGrid[i]->setDisabled(false);
            buttonInGrid[i]->setText("");
        }
    }

}

void MainStratego::initGame(){
    blueScore=0;
    redScore=0;
    accessRedGrid=false;
    deblocRedGrid=false;
    PiecePositioning=true;
    Player playerOne(bluePieces,"Blue");
    Player playerTwo(redPieces,"Red");
    Game gameIn(playerOne,playerTwo);
    game=gameIn;

}


void MainStratego::defaulPressetButton(){
    int cpt=0;
    initGame();
    accessRedGrid=true;
    deblocRedGrid=true;
    PiecePositioning=false;

    for(int i =0; i <40 ; ++i){
        Position pos(buttonInGrid[i]->pos().y()/62,buttonInGrid[i]->pos().x()/75);
        game.getPlayerOne().getPieces().push_back(Piece(pos,blueButtons[i]->text().toStdString()));
    }

    for(int j =60; j <100 ; ++j){
        Position pos(buttonInGrid[j]->pos().y()/62,buttonInGrid[j]->pos().x()/75);
        game.getPlayerTwo().getPieces().push_back(Piece(pos,redButtons[cpt]->text().toStdString()));
        cpt++;
    }

    for(int i =0; i <40 ; ++i){
        blueButtons[i]->setHidden(true);
        redButtons[i]->setHidden(true);
    }

    enableRedButton(true);
    enableBlueButton(true);
    updateAll("");
    PiecePositioning=false;
    ui->startButton->setStyleSheet("QPushButton { background-color:green; }");
    ui->startButton->setDisabled(false);

}


void MainStratego::unoccupiedCase(){
    for(int i =40; i <60 ; ++i){
        if(i!=42 && i!=43 && i!=46 && i!=47 && i!=52 && i!=53 && i!=56 && i!=57){
            buttonInGrid[i]->setEnabled(true);
        }
    }
    game.getPlayerOne().setMyTurn(true);
    ui->informUser->setText("");
}

void MainStratego::startPressed(){

    unoccupiedCase();

    if(ui->startButton->text()=="restart"){
        initGame();
        defaulPressetButton();
        unoccupiedCase();
    }
    enableRedButton(false);
    enableBlueButton(false);
    updateAll(game.getMessage());
    ui->startButton->setDisabled(true);
}

void MainStratego::cleanPresseButton(){
    initGame();
    ui->informUser->setText("");
    ui->startButton->setText("start");
    ui->startButton->setDisabled(true);

    for(int i =0; i <40 ; ++i){
        if( blueButtons[i]->isHidden()){
            blueButtons[i]->setHidden(false);
        }
        if(redButtons[i] ->isHidden()){
             redButtons[i]->setHidden(false);
        }
    }

    enableRedButton(true);
    enableBlueButton(false);
    updateAll("");
}

void MainStratego::updateAll(string message){
    QString textButton="";
    ui->informUser->setStyleSheet("QLabel {  color:red;  }");
    ui->informUser->setText(QString::fromStdString(message));
    for(int i =0; i <10 ; ++i){
         for(int j =0; j <10 ; ++j){
             Position pos(i,j);
             if(game.getPlayerOne().isMyPiece(pos)){

                 if(game.getPlayerOne().getIsMyTurn()){
                     textButton=QString::fromStdString(game.getPlayerOne().getPieceAt(pos).to_string());
                     qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                     textButton="";
                     ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color: blue;  color:#c1c1c1; }");
                 }else{
                     if(game.getPlayerOne().getPieceAt(pos).getRevealed()){
                         textButton=QString::fromStdString(game.getPlayerOne().getPieceAt(pos).to_string());
                         qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                         textButton="";
                         ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color: blue;  color:#c1c1c1; }");

                     }else{
                     textButton=QString::fromStdString(game.getPlayerOne().getPieceAt(pos).to_stringHidden());
                     qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                     textButton="";
                     ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color: blue;  color:blue; }");
                    }
                }

             }else if(game.getPlayerTwo().isMyPiece(pos)){

                 if(game.getPlayerTwo().getIsMyTurn()){
                     textButton=QString::fromStdString(game.getPlayerTwo().getPieceAt(pos).to_string());
                     qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                     textButton="";
                     ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color:red;  color:#c1c1c1; }");
                 }else{
                     if(game.getPlayerTwo().getPieceAt(pos).getRevealed()){
                         textButton=QString::fromStdString(game.getPlayerTwo().getPieceAt(pos).to_string());
                         qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                         textButton="";
                         ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color:red;  color:#c1c1c1; }");

                     }else{
                     textButton=QString::fromStdString(game.getPlayerTwo().getPieceAt(pos).to_stringHidden());
                     qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText(textButton);
                     textButton="";
                     ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color:red;  color:red; }");
                    }
                }
             }
             else{
                 if(qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->isEnabled()){
                     qobject_cast<QPushButton*>(ui->grid->itemAtPosition(i,j)->widget())->setText("");
                      ui->grid->itemAtPosition(i,j)->widget()->setStyleSheet("QPushButton {background-color: gray}");
                 }
             }

         }
    }

    ui->labelRedScore->setText(QString::number(game.getPlayerTwo().getPieces().size()));
    ui->labelBlueScore->setText(QString::number(game.getPlayerOne().getPieces().size()));

    if(game.gameIsOver() && !PiecePositioning){
        for(int i =0; i <100 ; ++i){
            if(i!=42 && i!=43 && i!=46 && i!=47 && i!=52 && i!=53 && i!=56 && i!=57){
                buttonInGrid[i]->setEnabled(false);
            }
        }

        ui->informUser->setStyleSheet("QLabel {color:green; }");
        ui->informUser->setText(QString::fromStdString("Game over the winner is player "+game.getWinner().getColor()));
        ui->startButton->setText("restart");
        ui->startButton->setDisabled(false);
    }
}


MainStratego::~MainStratego()
{
    delete ui;
}

