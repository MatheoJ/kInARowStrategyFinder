/*************************************************************************
                           TileGenerator  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TileGenerator> (fichier TileGenerator.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TileGenerator.h"
//------------------------------------------------------------- Constantes
const int MINHALFPERIMETER = 4;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

vector<BoundaryWord> TileGenerator::getTileWordVect()const{
    return this->tileWordVect;
}

vector<Tile> TileGenerator::getTileVect()const{
    return this->tileVect;
}

void TileGenerator::generateBoundWord(int maxHAlfPerimeter, vector<char>& currentHalfWord)
// Algorithme :
// La méthode s'appel récursivement pour faire toute les combinaisons possible de chiffre pour la première moitier du mot, 
// Puis quand la longueur du mot est comprise entre 4 et le demi prérimètre max on appel generateOtherHalf pour générer toutes
// les combinaisons possibles de l'autre moitié et ajouter les mots à l'attributs tileWordVect
{
    static int lgthWord = 0;
    for (int i = 0; i < 4; i++)
    {
        if(lgthWord==0 || i!=currentHalfWord.back()){
            currentHalfWord.push_back(i);
            
            lgthWord++;
            if (lgthWord>=MINHALFPERIMETER){
                generateFullWord(currentHalfWord);
            }
            if (lgthWord<=maxHAlfPerimeter){
                generateBoundWord(maxHAlfPerimeter,currentHalfWord);
            }
            currentHalfWord.pop_back();
            lgthWord--;
        }      
    }    
} //----- Fin de Méthode

void TileGenerator::buildOtherHalf(vector<char>& firstHalf,vector<char>& otherHalf,int xSize,int ySize,int zSize){
    for(char i : firstHalf){
        otherHalf.push_back((i+2)%4); //Make the invers move
    }
    for(int i=0; i<xSize/2; i++){
        char temp = otherHalf[i];
        otherHalf[i] = otherHalf[xSize-1-i];
        otherHalf[xSize-1-i] = temp;
    }
    for(int i=0; i<ySize/2; i++){
        char temp = otherHalf[xSize+i];
        otherHalf[xSize+i] = otherHalf[xSize+ySize-1-i];
        otherHalf[xSize+ySize-1-i] = temp;
    }
    for(int i=0; i<zSize/2; i++){
        char temp = otherHalf[xSize+ySize+i];
        otherHalf[xSize+ySize+i] = otherHalf[xSize+ySize+zSize-1-i];
        otherHalf[xSize+ySize+zSize-1-i] = temp;
    }
}//----- Fin de Méthode

void TileGenerator::generateFullWord(vector<char>& firstHalf){   
    
    int length = firstHalf.size();
    
    for(int xSize=1; xSize<length-1;xSize++){
        for(int ySize=1; ySize<length-xSize; ySize++){
            int zSize = length-xSize-ySize;
            vector<char> otherHalf;
            buildOtherHalf(firstHalf,otherHalf,xSize,ySize,zSize);

            BoundaryWord bw(firstHalf, otherHalf, xSize, ySize, zSize); 

            if(bw.isSelfAvoiding()){
                this->tileWordVect.push_back(bw); 
                //cout<<bw;
            }                               
        }       
    }    
}//----- Fin de Méthode

void TileGenerator::generateTile(){
    for(int i=0; i<(int)tileWordVect.size(); i++){
        Tile t(&tileWordVect[i]);
        this->tileVect.push_back(t);
    }
}


//-------------------------------------------- Constructeurs - destructeur

TileGenerator::TileGenerator ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <TileGenerator>" << endl;
#endif
} //----- Fin de TileGenerator


TileGenerator::~TileGenerator ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <TileGenerator>" << endl;
#endif
} //----- Fin de ~TileGenerator

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

