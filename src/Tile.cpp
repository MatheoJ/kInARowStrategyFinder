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
                stream<<t.basicShape[i][j].getUnitNumber()<<"|";
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

void Tile::printPlanningShape(){
    for (int i = 0; i < this->planingShapeSize; i++)
    {
            for (int j = 0; j < this->planingShapeSize; j++)
            {
                if(this->planingShape[i][j].getTileNumber()!=-1){
                    cout<<this->planingShape[i][j].getTileNumber()<<" |";
                }
                else{
                    cout<<" ";
                }
            }
            cout<<endl;        
    }
    cout<<"--------------------\n";
}

bool Tile::BuildTile ()
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

    bool res = true;
    if(browsingWay ==-1){
        res = false;
    }
    
    return res;
    
} //----- Fin de Méthode

void Tile::buildPlanningShape(int kSize){

    this->planingShapeSize = this->size+kSize;

    this->planingShape = new Unit* [this->planingShapeSize];
    for(int i=0; i<this->planingShapeSize; i++){
        this->planingShape[i]= new Unit[this->planingShapeSize];
    }

    //find the two vector for planning

    pair<int,int> vect1 = this->getVector1();
    pair<int,int> vect2 = this->getVector2();
    pair<int,int> vect3 = this->getVector3(vect1,vect2);

    //cout<<"vect 1 : x="<<vect1.first<<", y="<<vect1.second<<endl;
    //cout<<"vect 2 : x="<<vect2.first<<", y="<<vect2.second<<endl;

    //Move the basics shape trhought the plan with first vector until every unit is of the gridd
    //Then move once with the second vector and repeate the first step

    map<pair<int,int>,int> k1k2NumTile;
    int x, y, k1, numUnit, numTile, countNumTile;
    countNumTile=1;

    k1k2NumTile[make_pair(0,0)]=0;

    for(int i=0;i<this->size;i++)
    {
        for (int j = 0; j < this->size; j++)
        {            
            
            numUnit = this->basicShape[i][j].getUnitNumber();
            if(numUnit!=-1){
                
                x = i;
                y = j;
                k1=0;
                int k2=0;
                this->planingShape[x][y]=Unit(0, numUnit);

                this->moveUnitAlongVector(x,y,numUnit,countNumTile,k1k2NumTile, k1,k2, vect1, vect2,vect3);
                
/* 
                
                while(x<this->planingShapeSize && x>=0 && y<this->planingShapeSize && y>=0){

                    moveUnitAlongSecondVector(x,y,numUnit,countNumTile, k1, vect2, k1k2NumTile, 1 );
                    moveUnitAlongSecondVector(x,y,numUnit,countNumTile, k1, vect2, k1k2NumTile,-1 );
                    x+=vect1.first;
                    y+=vect1.second;
                    k1++;
                }
                x = i;
                y = j;
                k1=0;
                while(x<this->planingShapeSize && x>=0 && y<this->planingShapeSize && y>=0){
                    
                    moveUnitAlongSecondVector(x,y,numUnit,countNumTile, k1, vect2, k1k2NumTile, 1 );
                    moveUnitAlongSecondVector(x,y,numUnit,countNumTile, k1, vect2, k1k2NumTile,-1 );
                    x-=vect1.first;
                    y-=vect1.second;
                    k1--;
                } */
            }       
        }
    }   
}

void Tile::setBoundaryWord( BoundaryWord *boundWord){
    this->boundWord=boundWord;
}

int Tile::getSize(){
    return this->size;
}

int Tile::getPlaningShapeSize(){
    return this->planingShapeSize;
}

Unit** Tile::getBasicShape(){
    return this->basicShape;
}

Unit** Tile::getPlaningShape(){
    return this->planingShape;
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
    this->planingShapeSize = 0;    
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

bool Tile::dfsFillTile(int i,int j,vector<Unit*>& group, set<Unit*>& checkedUnits ){
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


void Tile::moveUnitAlongSecondVector(int x, int y,int numUnit,int& countNumTile, int k1, pair<int, int>vect2, map<pair<int,int>,int>& k1k2NumTile, int sens){
    int numTile;
    int x2,y2,k2;
    x2 =x ;
    y2 =y ;
    k2 =0 ;
    while(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        
        if(planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(k1,k2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            if (numTile==0)
                cout<< " |x2: "<<x2<<" |y2: "<<y2<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            this->planingShape[x2][y2]=Unit(numTile, numUnit);                        
        }
        x2+=sens*vect2.first;
        y2+=sens*vect2.second;
        k2+=sens;
    }    
}

pair<int,int>  Tile::getVector1(){

    int y=0, x=0;
    for(int i=0; i<this->boundWord->xSize+this->boundWord->ySize;i++){
        
        switch (this->boundWord->word[i])
        {
        case 0:
            y++;
            break;
        case 1:
            x--;
            break;
        case 2:
            y--;
            break;
        case 3:
            x++;
            break;       
        }
    }
    return make_pair(x,y);

}
pair<int,int>  Tile::getVector2(){
    int y=0, x=0;
    int startindex = this->boundWord->word.size()-(this->boundWord->zSize+this->boundWord->ySize);
    for(int i=startindex; i<this->boundWord->word.size();i++){
        
        switch (this->boundWord->word[i])
        {
        case 0:
            y++;
            break;
        case 1:
            x--;
            break;
        case 2:
            y--;
            break;
        case 3:
            x++;
            break;       
        }
    }
    return make_pair(-x,-y);
}

pair<int,int>  Tile::getVector3(pair<int,int> vect1, pair<int,int> vect2){
 
    return make_pair(vect1.first-vect2.first,vect1.second-vect2.second);
}


void Tile::moveUnitAlongVector(int x, int y, int numUnit, int& countNumTile, map<pair<int,int>,int>& k1k2NumTile, int k1, int k2, pair<int, int>& vect1, pair<int, int>&vect2,pair<int, int>&vect3){
    int x2,y2,numTile,newk1, newk2;
    x2=x+vect1.first;
    y2=y+vect1.second;
    newk1=k1+1;
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(newk1,k2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,newk1,k2,vect1,vect2,vect3);
        }
    }
    x2=x-vect1.first;
    y2=y-vect1.second;
    newk1=k1-1;
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(newk1,k2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,newk1,k2,vect1,vect2,vect3);
        }
    }
    x2=x-vect2.first;
    y2=y-vect2.second;
    newk2 = k2-1;
    
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(k1,newk2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,k1,newk2,vect1,vect2,vect3);
        }
    }
    x2=x+vect2.first;
    y2=y+vect2.second;
    newk2 = k2+1;
    
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(k1,newk2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,k1,newk2,vect1,vect2,vect3);
        }
    }
    x2=x-vect3.first;
    y2=y-vect3.second;
    newk2 = k2+1;
    newk1 = k1-1;
    
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(newk1,newk2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,newk1,newk2,vect1,vect2,vect3);
        }
    }

    x2=x+vect3.first;
    y2=y+vect3.second;
    newk2 = k2-1;
    newk1 = k1+1;
    
    if(x2<this->planingShapeSize && x2>=0 && y2<this->planingShapeSize && y2>=0){
        if(this->planingShape[x2][y2].getTileNumber()==-1){
            pair<int,int> xyPair= make_pair(newk1,newk2);
            //If the pair of vector factor as not been asigned a number of tile
            if (k1k2NumTile.count(xyPair)){
                numTile = k1k2NumTile[xyPair];
            }
            else{
                numTile = countNumTile;
                k1k2NumTile[xyPair]= countNumTile;
                countNumTile++;
                //cout<<"countNumTile : "<<countNumTile<< " |k1: "<<k1<<" |k2: "<<k2<< " |sens :"<<sens<<endl;
            }
            this->planingShape[x2][y2]=Unit(numTile, numUnit);
            this->moveUnitAlongVector(x2,y2,numUnit,countNumTile,k1k2NumTile,newk1,newk2,vect1,vect2,vect3);
        }
    }
    
}

