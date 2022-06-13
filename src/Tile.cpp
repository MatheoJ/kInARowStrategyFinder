/*************************************************************************
                           Tile  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Tile> (fichier Tile.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "Tile.h"
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>


//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

ostream &operator<<(ostream &stream, const Tile &t)
{
    stream<<"This is the tile of size :"<< t.size<<endl;
    //stream<<"MinVertical ="<<t.boundWord->getMinVertical()<<" MaxVertical ="<<t.boundWord->getMaxVertical()<<" |MinHorizontal ="<<t.boundWord->getMinHorizontal()<<" MaxHorizontal ="<<t.boundWord->getMaxHorizontal()<<endl;
    
   stream<<*(t.boundWord);
   for (int i = 0; i < t.size; i++)
   {
        for (int j = 0; j < t.size; j++)
        {
            if(t.basicShape[i][j].getTileNumber()!=-1){
                stream<<"█";
            }
            else{
                stream<<" ";
            }
        }
        stream<<endl;        
   }
   stream<<"--------------------\n";
   
    return stream;
}

void Tile::BuildTile ()
// Algorithme :
//
{
    //search for the bottom left point of the boundWord
    int startIndex=0;
    int minVerticalStart=9999;
    int horizontalPos=0, verticalPos=0;

    

    for(int i=0; i<(int)this->boundWord->word.size();i++){
        if(horizontalPos==this->boundWord->minHorizontal && minVerticalStart>verticalPos){
            minVerticalStart=verticalPos; 
            startIndex =i;
        } 
        //cout<<"horizontalPos =:"<<horizontalPos<<" |verticalPos = "<<verticalPos<<endl;
        switch (this->boundWord->word[i])
        {
        case 0:
            horizontalPos++;
            break;
        case 1:
            verticalPos++;
            break;
        case 2:
            horizontalPos--;
            break;
        case 3:
            verticalPos--;
            break;       
        }
        //cout<<"dir ="<<(int)this->boundWord->word[i]<<" |";

    }
    //We start from the bottom left point
    //We find the browsing way for the vector in order to start with a right direction.

    int browsingWay = 1;
    if(startIndex==0){
        if(this->boundWord->word[this->boundWord->word.size()-1]==2){
            browsingWay=-1;
        }
    }
    else{
        if(this->boundWord->word[startIndex-1]==2){
            browsingWay=-1;
        }
    }
    //If the browsing way is not the natural way, we inverse the direction in the word
    if(browsingWay==-1){
        startIndex--;
        for (int i = 0; i <(int)this->boundWord->word.size() ; i++)
        {
            this->boundWord->word[i]=(this->boundWord->word[i]+2)%4;
        }
        
    }

   
    //We place the tile on the bottom left of the grid
    //We konw that we start at the left
    int y = 0;
    //We find at wath y is the start
    int x = (this->size-1-abs(this->boundWord->minVertical-minVerticalStart));
    //cout<<"startIndex = "<<startIndex<<" |browsingWay ="<<browsingWay<<" |Minvertical ="<<minVerticalStart<<endl;
    int countUnit=0;
    //We iterate through the word from the start point to the end or the begining depending on the way of brosing
    for(int i=(startIndex); (i!=-1 && i!=(int)this->boundWord->word.size()); i+=browsingWay){
        //cout<<" x="<<x<<" y="<<y<<endl;
        switch (this->boundWord->word[i])
        {
        case 0:
            y++;
            if(this->basicShape[x][y-1].tileNumber==-1){
                this->basicShape[x][y-1]= Unit(0,countUnit);
                countUnit++;
            }
            break;
        case 1:
            x--;
            if(this->basicShape[x+1][y-1].tileNumber==-1){
                this->basicShape[x+1][y-1]= Unit(0,countUnit);
                countUnit++;
            }
            
            break;
        case 2:
            y--;
            if(this->basicShape[x+1][y].tileNumber==-1){
                this->basicShape[x+1][y]= Unit(0,countUnit);
                countUnit++;
            }
            break;
        case 3:
            x++;
            if(this->basicShape[x][y].tileNumber==-1){
                this->basicShape[x][y]= Unit(0,countUnit);
                countUnit++;
            }            
            break;       
        }
    }

    //Then we iterate through the word from the end or the begining depending on the way of brosing to the start point  
    
    int i=0;
    //if the Browsing way is the not natural way, we begin at the end
    if(browsingWay ==-1){
        i=(int)this->boundWord->word.size()-1;
    }

    for( ;i!=startIndex;i+=browsingWay){
        //cout<<" x="<<x<<" y="<<y<<endl;
       switch (this->boundWord->word[i])
        {
        case 0:
            y++;
            if(this->basicShape[x][y-1].tileNumber==-1){
                this->basicShape[x][y-1]= Unit(0,countUnit);
                countUnit++;
            }
            break;
        case 1:
            x--;
            if(this->basicShape[x+1][y-1].tileNumber==-1){
                this->basicShape[x+1][y-1]= Unit(0,countUnit);
                countUnit++;
            }
            
            break;
        case 2:
            y--;
            if(this->basicShape[x+1][y].tileNumber==-1){
                this->basicShape[x+1][y]= Unit(0,countUnit);
                countUnit++;
            }
            break;
        case 3:
            x++;
            if(this->basicShape[x][y].tileNumber==-1){
                this->basicShape[x][y]= Unit(0,countUnit);
                countUnit++;
            }            
            break;       
        }
    }
    
    this->fillTile(countUnit);
    
} //----- Fin de Méthode

void Tile::setBoundaryWord( BoundaryWord *boundWord){
    this->boundWord=boundWord;
}

int Tile::getSize(){
    return this->size;
}

Unit** Tile::getBasicShape(){
    return this->basicShape;
}

BoundaryWord * Tile::getBoundWord(){
    return this->getBoundWord();
}


//-------------------------------------------- Constructeurs - destructeur

Tile::Tile (BoundaryWord *boundWord )
// Algorithme :
//
{
    this->boundWord=boundWord;
    this->size= max((boundWord->maxHorizontal-boundWord->minHorizontal),(boundWord->maxVertical-boundWord->minVertical));
    this->basicShape = new Unit* [this->size];
    for(int i=0; i<this->size; i++){
        this->basicShape[i]= new Unit[this->size];
    }
    this->BuildTile();
#ifdef MAP
    cout << "Appel au constructeur de <Tile>" << endl;
#endif
} //----- Fin de Tile


Tile::~Tile ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Tile>" << endl;
#endif
} //----- Fin de ~Tile


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool Tile::dfsFillTile(int i,int j,vector<Unit*> group, set<Unit*>checkedUnits ){
    bool inTile = true;

    // If we are at a nonFile Tile in the border it means that the all group does not belong to the tile
    if(i==0||j==0||i==this->size-1||j==this->size-1){
        inTile = false;
    }
    // If we are not at border we have to check all four neighbours
    else{
        if(this->basicShape[i+1][j].getTileNumber()==-1 && !checkedUnits.contains(&(this->basicShape[i+1][j]))){
            group.push_back(&(this->basicShape[i+1][j]));
            checkedUnits.insert(&(this->basicShape[i+1][j]));
            inTile = inTile && dfsFillTile(i+1,j,group,checkedUnits);
        }
        if(this->basicShape[i-1][j].getTileNumber()==-1 && !checkedUnits.contains(&(this->basicShape[i-1][j]))){
            group.push_back(&(this->basicShape[i-1][j]));
            checkedUnits.insert(&(this->basicShape[i-1][j]));
            inTile = inTile && dfsFillTile(i-1,j,group,checkedUnits);
        }
        if(this->basicShape[i][j+1].getTileNumber()==-1 && !checkedUnits.contains(&(this->basicShape[i][j+1]))){
            group.push_back(&(this->basicShape[i][j+1]));
            checkedUnits.insert(&(this->basicShape[i][j+1]));
            inTile = inTile && dfsFillTile(i,j+1,group,checkedUnits);
        }
        if(this->basicShape[i][j-1].getTileNumber()==-1 && !checkedUnits.contains(&(this->basicShape[i][j-1]))){
            group.push_back(&(this->basicShape[i][j-1]));
            checkedUnits.insert(&(this->basicShape[i][j-1]));
            inTile = inTile && dfsFillTile(i,j-1,group,checkedUnits);
        }        
    }
    return inTile;    
}

void Tile::fillTile(int countUnit){
    set<Unit*> checkedUnits;

    for(int i=1;i<this->size-1;i++){
        for (int j = 1; j < this->size-1; j++)
        {
            vector<Unit*> group;
            bool inTile=false;
            if(this->basicShape[i][j].getTileNumber()==-1 && !checkedUnits.contains(&(this->basicShape[i][j]))){           
                group.push_back(&(this->basicShape[i][j]));
                checkedUnits.insert(&(this->basicShape[i][j]));
                inTile = dfsFillTile(i,j,group,checkedUnits);
            } 
            if(inTile){
                for(Unit* u:group){
                    *u=Unit(0,countUnit);
                    countUnit ++;
                }                
            }
        }        
    }
}