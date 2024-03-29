#ifndef VIEW_H
#define VIEW_H
#include "../model/Game.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>


namespace std
{
class View{


public:

    /**
     * @brief View, default controller
     */
    inline View(){}

    /**
     * @brief displayWelcome, this method just displays a welcome at the start of the game
     */
    inline void displayWelcome();

    /**
     * @brief displayScore,this method displays the current score of the game
     * @param game, represents the facade of the game which allows us to recover the score
     */
    inline void displayScore(Game game);

    /**
     * @brief displayWinner,show the winner after the game is over
     * @param game,represents the facade of the game which allows us to recover the winner player
     */
    inline void displayWinner(Game game);

    /**
     * @brief displayBoard, this method displays the game board
     * @param game,represents the facade of the game which allows us to recover informations to display the board
     */
    inline void displayBoard(Game & game);

    /**
     * @brief columnContaint,this method checks if a column entered by the user
     * falls within the accepted values (from A to J)
     * @param c, column entered by the user
     * @return true if the input column is valid and false if not
     */
    inline bool columnContaint(char c);

    /**
     * @brief askCurrentPosition,this method asks for the position of the piece the player wants to move
     * @return the position of the piece the player wants to move
     */
    inline Position askCurrentPosition();

    /**
     * @brief askNextPosition,this method asks the player the destination position to which he would like to move
     * @return the destination position
     */
    inline Position askNextPosition();

    /**
     * @brief askPosition, this method asks the player a position
     * @return the position
     */
    inline Position askPosition();

    /**
     * @brief symbolContaint,this method makes it possible to check if an entered symbol
     * is part of the valid symbols when positioning the pieces by interaction
     * @param s, the input symbol
     * @return , true if the input symbol is valid and false if not
     */
    inline bool symbolContaint(string s);

    /**
     * @brief symboleList,this method just gives the list of valid symbols and their maximum sizes
     * the key will be the symbol and the value the size
     * @return the list of valid symbols and their maximum sizes
     */
    inline map<string,int> symboleList();

    /**
     * @brief bluePiecePositioning,this method allows the positioning by interaction for the blue player
     * @return,all the pieces of the blue player already positioned
     */
    inline vector<Piece> bluePiecePositioning();

    /**
     * @brief bluePiecePositioning,this method allows the positioning by interaction for the blue player
     * @return,all the pieces of the blue player already positioned
     */
    inline vector<Piece> redPiecePositioning();

    /**
     * @brief blueFilePositioning,this method positions the pieces of the blue player by file reading
     * @return all the pieces of the blue player already positioned
     */
    inline vector<Piece> blueFilePositioning();

    /**
     * @brief blueFilePositioning,this method positions the pieces of the red player by file reading
     * @return all the pieces of the blue player already positioned
     */
    inline vector<Piece> redFilePositioning();

    /**
     * @brief askPositioningStyle,this method asks the players what means of positioning they would like to use
     * @return (1) for file reading or (2) for interaction
     */
    inline int askPositioningStyle();

    /**
     * @brief whoIsPlaying ,this method just displays the player who has the turn
     * @param player,the player who has the turn
     */
    inline void whoIsPlaying(Player player);

    /**
     * @brief checkFile ,this method checks if the file containing the player's pieces respects the requested specificities
     * @param url,the file path
     * @return true if it respect and false if not.
     */
    inline bool checkFile(string url);





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
    cout<<"      "<<colonne.at(0)<<" ";
    for(unsigned u=1;u<colonne.size();u++){
        cout<<"   "<<colonne.at(u)<<" ";
    }
    cout<<endl;
    cout<<endl;
    for(int i=0;i<10;i++){
        if(i==9){
            cout<<i+1<<"  ";
        }else {cout<<" "<<i+1<<"  ";}
          for(int j=0;j<10;j++){
                if(game.getPlayerOne().isMyPiece(Position(i,j))){
                    if(game.getPlayerOne().getIsMyTurn() || game.getPlayerOne().getPieceAt(Position(i,j)).getRevealed()){
                        if(game.getPlayerOne().getPieceAt(Position(i,j)).to_string()=="10"){
                            cout<<" "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }else{
                        cout<<"  "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_string()<<"  ";
                        }
                    }else{

                            cout<<"  "<<game.getPlayerOne().getPieceAt(Position(i,j)).to_stringHidden()<<"  ";

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

                            cout<<"  "<<game.getPlayerTwo().getPieceAt(Position(i,j)).to_stringHidden()<<"  ";

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
            while(!symbolContaint(symbole)){

                    cout<<"Entrez un symbole valide !!"<<endl;
                    cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                    cin>>symbole;
                  }
                 if(symbols[symbole]<=0){
                     cout<<"le maximum de "<<symbole<<" sur le plateau été atteint !!"<<endl;
                     j--;
                }else{

                     Piece piece(Position(i,j),symbole);
                     pieces.push_back(piece);
                     symbols[symbole]=symbols[symbole]-1;
                 }

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
            while(!symbolContaint(symbole)){

                    cout<<"Entrez un symbole valide !!"<<endl;
                    cout<<"Entrez le Symbole à la Position ("<<i<<", "<<j<<"):";
                    cin>>symbole;
                  }
                 if(symbols[symbole]<=0){
                     cout<<"le maximum de "<<symbole<<" sur le plateau été atteint !!"<<endl;
                     j--;
                }else{

                     Piece piece(Position(i,j),symbole);
                     pieces.push_back(piece);
                     symbols[symbole]=symbols[symbole]-1;
                 }


        }
    }
     return pieces;
}

vector<Piece> View::blueFilePositioning(){

    string chemin;
    cout<<"Joueur bleu entrez le chemin du fihier texte à lire pour positionner les pieces (ex: '../positions.txt'"<<endl;
    cin>>chemin;
    while(!checkFile(chemin)){
        cout<<"La structure du fichier donné ne respecte pas les specificité du jeu"<<endl;
        cout<<"Joueur bleu entrez le chemin du fihier texte à lire pour positionner les pieces (ex: '../positions.txt'"<<endl;
        cin>>chemin;
    }
    ifstream fichier(chemin, ios::in);  // on ouvre en lecture
    string line;
    vector<Piece> pieces;
    int i=0;
    while (getline(fichier, line)){
            int start = 0;
            string delimiter = " ";
            int end = line.find(delimiter);

            int j=0;
            while (end != -1) {

                    Piece piece(Position(i,j),line.substr(start, end - start));
                    pieces.push_back(piece);
                    start = end + delimiter.size();
                    end = line.find(delimiter, start);
                    j++;
                }
            Piece piece(Position(i,j),line.substr(start, end - start));
            pieces.push_back(piece);

            i++;
        }
    return pieces;

}
vector<Piece> View::redFilePositioning(){
    string chemin;
    cout<<" Joueur Rouge entrez le chemin du fihier texte à lire  (ex: 'positions.txt' si dans le dossier courant "<<endl;
    cin>>chemin;
    while(!checkFile(chemin)){
        cout<<"La structure du fichier donné ne respecte pas les specificité du jeu"<<endl;
        cout<<"Joueur bleu entrez le chemin du fihier texte à lire (ex: 'positions.txt' si dans le dossier courant "<<endl;
        cin>>chemin;
    }
    ifstream fichier(chemin, ios::in);
    string line;
    vector<Piece> pieces;
    int i=9;
    while (getline(fichier, line)){
            int start = 0;
            string delimiter = " ";
            int end = line.find(delimiter);

            int j=0;
            while (end != -1) {

                    Piece piece(Position(i,j),line.substr(start, end - start));
                    pieces.push_back(piece);
                    start = end + delimiter.size();
                    end = line.find(delimiter, start);
                    j++;
                }
            Piece piece(Position(i,j),line.substr(start, end - start));
            pieces.push_back(piece);

            i--;
        }
    return pieces;
}

int View::askPositioningStyle(){
    cout<<"Quel Style de Positionnement preferez vous ? "<<endl;
    cout<<"(1):Lecture Fichier         (2):Interaction"<<endl;
    int style;
    cin>>style;
    while(style!=1 && style !=2){
        cout<<"Entrez 1 ou 2 ! "<<endl;
        cout<<"(1):Lecture Fichier         (2):Interaction"<<endl;
        cin>>style;
    }
    return style;
}

void View::whoIsPlaying(Player player){
    cout<<"Au tour du Joueur "<<player.getColor()<<endl;
}

bool View::checkFile(string url){

    map<string,int> symbols=this->symboleList();
    ifstream fichier(url, ios::in);
    string line;
    vector<Piece> pieces;
    int i=9;
    while (getline(fichier, line)){
            int start = 0;
            string delimiter = " ";
            int end = line.find(delimiter);

            int j=0;
            while (end != -1) {
                    if(!symbolContaint(line.substr(start, end - start))){
                        return false;
                    }
                    symbols[line.substr(start, end - start)]=symbols[line.substr(start, end - start)]-1;
                    Piece piece(Position(i,j),line.substr(start, end - start));
                    pieces.push_back(piece);
                    start = end + delimiter.size();
                    end = line.find(delimiter, start);
                    j++;
                }
            Piece piece(Position(i,j),line.substr(start, end - start));
            pieces.push_back(piece);

            i--;
        }
    if(pieces.size()>40 || pieces.size()<40){
        return false;
    }
    map<string, int>::iterator it;
       for(it=symbols.begin(); it!=symbols.end(); ++it){
           if( it->second<0) {
               return false;
           }
       }
    return true;
}

}


#endif // VIEW_H
