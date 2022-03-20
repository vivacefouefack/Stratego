#ifndef VIEW_H
#define VIEW_H
#include "../model/Game.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>


namespace std
{
class View{




public:

    inline View(){}

    inline void displayWelcome();

    inline void displayScore(Game game);

    inline void displayWinner(Game game);

    inline void displayBoard(Game & game);

    inline bool columnContaint(char c);

    inline Position askCurrentPosition();

    inline Position askNextPosition();

    inline Position askPosition();

    inline bool symbolContaint(string s);

    inline map<string,int> symboleList();

    inline vector<Piece> bluePiecePositioning();

    inline vector<Piece> redPiecePositioning();





};


void View::displayWelcome(){
    cout<<"    Bienvenu au Jeu STRATEGO !!!!!! "<<endl;
}
void View::displayScore(Game game){
    cout<< "Score : " <<endl;
    cout<<"Joueur Rouge : "<<game.getPlayerOne().getPieces().size()<<endl;
    cout<<"Joueur Bleu : "<<game.getPlayerTwo().getPieces().size()<<endl;
}
void View::displayWinner(Game game){
    cout<<"Le gagnant est : "<<game.getWinner().getColor()<<endl;
}
void View::displayBoard(Game & game){
   vector <char> colonne{'A','B','C','D','E','F','G','H','I','J'};
    cout<<"     "<<colonne.at(0)<<" ";
    for(unsigned u=1;u<colonne.size();u++){
        cout<<"  "<<colonne.at(u)<<" ";
    }
    cout<<endl;
    for(int i=0;i<10;i++){
        if(i==9){
            cout<<i+1<<" ";
        }else {cout<<" "<<i+1<<" ";}
          for(int j=0;j<10;j++){
                if(game.getPlayerOne().isMyPiece(Position(i,j))){
                    if(game.getPlayerOne().getIsMyTurn() || game.getPlayerOne().getPieceAt(Position(i,j)).getRevealed()){
                        if(game.getPlayerOne().getPieceAt(Position(i,j)).to_string()=="10"){
                            cout<<" "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }else{
                        cout<<"  "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }
                    }else{

                            cout<<"  "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_stringHidden()<<" ";

                    }
                }
                else if(game.getPlayerTwo().isMyPiece(Position(i,j))){
                    if(game.getPlayerTwo().getIsMyTurn() || game.getPlayerTwo().getPieceAt(Position(i,j)).getRevealed()){
                        if(game.getPlayerTwo().getPieceAt(Position(i,j)).to_string()=="10"){
                            cout<<" "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }else{
                        cout<<"  "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }
                    }else{

                            cout<<"  "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_stringHidden()<<" ";

                    }
                }else if(game.inWater(Position(i,j))){
                    cout<<"  #  ";
                }else {
                    cout<<"  .  ";
                }
        }
        cout<<""<<endl;
    }
}

bool View::columnContaint(char c){
   vector <char> colonne{'A','B','C','D','E','F','G','H','I','J'};
    for(unsigned u=0;u<colonne.size();u++){
        if(colonne.at(u)==c){
            return true;
        }
    }
    return false;
}

Position View::askCurrentPosition(){

       cout<<"Entrez la Position courante : "<<endl;
       return askPosition();
}

Position View::askNextPosition(){
    cout<<"Entrez la Destination : "<<endl;
    return askPosition();
}


Position View::askPosition(){
    char y;
    int ligne=0;
    int colonne=0;
    cout<<" Entrez La Ligne : ";
    cin>>ligne;
    while(ligne<1 || ligne>10 ){
       cout<<"Ligne Invalide!!"<<endl;
       cout<<" Entrez X : ";
       cin>>ligne;
    }

    cout<<" Entrez La Colonne : ";
    cin>>y;
    while(!columnContaint(y)){
       cout<<"Colonne invalide !!"<<endl;
       cout<<" Entrez La Colonne : ";
       cin>>y;
    }

    switch (y)  {
    case 'A':
        colonne=0;
        break;

    case 'B':
        colonne=1;
        break;

    case 'C':
        colonne=2;
        break;
    case 'D':
        colonne=3;
        break;

    case 'E':
        colonne=4;
        break;

    case 'F':
         colonne=5;
         break;
    case 'G':
        colonne=6;
        break;

    case 'H':
        colonne=7;
        break;

    case 'I':
         colonne=8;
         break;


    case 'J':
         colonne=9;
         break;


    }
    return Position(ligne-1,colonne);
}

map<string,int>View::symboleList(){
    map<string,int> symboles;
    symboles["10"]=1;
    symboles["9"]=1;
    symboles["8"]=2;
    symboles["7"]=3;
    symboles["6"]=4;
    symboles["5"]=4;
    symboles["4"]=4;
    symboles["3"]=5;
    symboles["2"]=8;
    symboles["1"]=1;
    symboles["D"]=1;
    symboles["B"]=6;

    return symboles;
}

bool View::symbolContaint(string s){
    vector <string> colonne{"10","9","8","7","6","5","4","3","2","1","D","B"};
     for(unsigned u=0;u<colonne.size();u++){
         if(colonne.at(u)==s){
             return true;
         }
     }
     return false;
}

vector<Piece> View::bluePiecePositioning(){

    map<string,int> symbols=this->symboleList();
    vector<Piece> pieces;
    cout<<"Joueur Bleu positionnez vos pieces dans l'ordre suivant : de gauche à droite en allant du haut vers le bas"<<endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<10;j++){
            map<string, int>::iterator it;
            cout<<"Symbole => Quantite"<<endl;
               for(it=symbols.begin(); it!=symbols.end(); ++it){

                   cout <<"  "<< it->first <<"     =>    " << it->second << '\n';
               }

            string symbole;
            cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
            cin>>symbole;
            while(symbols[symbole]<=0 || !symbolContaint(symbole)){
                if(!symbolContaint(symbole)){
                    cout<<"Entrez un symbole valide !!"<<endl;
                    cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                    cin>>symbole;
                }else{
                     cout<<"le maximum de "<<symbole<<" sur le plateau été atteint !!"<<endl;
                     cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                     cin>>symbole;
                }
            }
            Piece piece(Position(i,j),symbole);
            pieces.push_back(piece);
            symbols[symbole]=symbols[symbole]-1;

        }
    }
     return pieces;
}

vector<Piece> View::redPiecePositioning(){
    map<string,int> symbols=this->symboleList();
    vector<Piece> pieces;
    cout<<"Joueur Rouge positionnez vos pieces dans l'ordre suivant : de gauche à droite en allant du haut vers le bas"<<endl;
    for(int i=6;i<10;i++){
        for(int j=0;j<10;j++){
            map<string, int>::iterator it;
            cout<<"Symbole => Quantite"<<endl;
               for(it=symbols.begin(); it!=symbols.end(); ++it){

                   cout <<"  "<< it->first <<"     =>    " << it->second << '\n';
               }

            string symbole;
            cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
            cin>>symbole;
            while(symbols[symbole]<=0 || !symbolContaint(symbole)){
                if(!symbolContaint(symbole)){
                    cout<<"Entrez un symbole valide !!"<<endl;
                    cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                    cin>>symbole;
                }else{
                     cout<<"le maximum de "<<symbole<<" sur le plateau été atteint !!"<<endl;
                     cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                     cin>>symbole;
                }
            }
            Piece piece(Position(i,j),symbole);
            pieces.push_back(piece);
            symbols[symbole]=symbols[symbole]-1;

        }
    }
     return pieces;
}

}


#endif // VIEW_H
