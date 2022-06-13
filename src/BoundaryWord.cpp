/*************************************************************************
                           BoundaryWord  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <BoundaryWord> (fichier BoundaryWord.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "BoundaryWord.h"
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel

#include <map>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
ostream &operator<<(ostream &stream, const BoundaryWord &bw)
{
    for (int x : bw.word)
        stream << x << " ";
    stream<<"#X ="<<bw.xSize<<" #Y ="<<bw.ySize<<" #Z ="<<bw.zSize;
    stream<<endl;
    return stream;
}

bool BoundaryWord::isSelfAvoiding(){

    map<pair<char,char>,bool>  pathHaveBeenHere; 
    int horizontalPos=0, maxH=0, minH=0;
    int verticalPos=0, maxV=0, minV=0;
    bool res = true;
    pathHaveBeenHere[make_pair(horizontalPos,verticalPos)]=true;
    for(int i=0; i<this->word.size()-1;i++){
        switch (this->word[i])
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
        if(pathHaveBeenHere[make_pair(horizontalPos,verticalPos)]==true){
            res = false;
        }
        else{
            pathHaveBeenHere[make_pair(horizontalPos,verticalPos)]=true;
        }

        maxH=max(horizontalPos, maxH);
        minH=min(horizontalPos, minH);
        maxV=max(verticalPos, maxV);
        minV=min(verticalPos, minV);
    }

    this->maxHorizontal = maxH;
    this->minHorizontal = minH;
    this->maxVertical = maxV;
    this->minVertical = minV;

    return res;
}//----- Fin de Méthode
int BoundaryWord:: getMaxHorizontal(){ 
    return this->maxHorizontal;
}
int BoundaryWord:: getMaxVertical(){
    return this->maxVertical;
}
int BoundaryWord:: getMinHorizontal(){ 
    return this->minHorizontal;
}
int BoundaryWord:: getMinVertical(){ 
    return this->minVertical;
} 


//-------------------------------------------- Constructeurs - destructeur

BoundaryWord::BoundaryWord (vector<char>& firstHalf, vector<char>& otherHalf,int x,int y,int z)
: xSize(x), ySize(y), zSize(z)
// Algorithme :
//
{
    this->word=vector<char>(firstHalf);
    word.insert(word.end(),otherHalf.begin(),otherHalf.end()); 
#ifdef MAP
    cout << "Appel au constructeur de <BoundaryWord>" << endl;
#endif
} //----- Fin de BoundaryWord


BoundaryWord::~BoundaryWord ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <BoundaryWord>" << endl;
#endif
} //----- Fin de ~BoundaryWord


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

