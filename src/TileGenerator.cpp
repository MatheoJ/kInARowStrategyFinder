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


//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

vector<BoundaryWord *>& TileGenerator::getTileWordVect(){
    return this->tileWordVect;
}

vector<Tile *>& TileGenerator::getTileVect(){
    return this->tileVect;
}

void TileGenerator::generateBoundWord(int minHalfPerimeter,int maxHAlfPerimeter, vector<char>& currentHalfWord)
// Algorithme :
// La méthode s'appel récursivement pour faire toute les combinaisons possible de chiffre pour la première moitier du mot, 
// Puis quand la longueur du mot est comprise entre 4 et le demi prérimètre max on appel generateOtherHalf pour générer toutes
// les combinaisons possibles de l'autre moitié et ajouter les mots à l'attributs tileWordVect
{
    static int lgthWord = 0;
    for (int i = 0; i < 4; i++)
    {
        //If it is not the first letter of the word : check that letter to add is not the inverse off the last letter
        if(lgthWord==0 || i!=((currentHalfWord.back()+2)%4)){
            currentHalfWord.push_back(i);
            
            lgthWord++;
            if (lgthWord>=minHalfPerimeter && lgthWord<=maxHAlfPerimeter){
                generateFullWord(currentHalfWord);
            }
            if (lgthWord<=maxHAlfPerimeter){
                generateBoundWord(minHalfPerimeter,maxHAlfPerimeter,currentHalfWord);
            }
            currentHalfWord.pop_back();
            lgthWord--;
        }      
    }    
} //----- Fin de Méthode

void TileGenerator::generateAndAnalyzeBoundWord(int minHalfPerimeter,int maxHAlfPerimeter, vector<char>& currentHalfWord, ThreadPool *pool, int kSize, TileAnalyzer* ta)
// Algorithme :
// La méthode s'appel récursivement pour faire toute les combinaisons possible de chiffre pour la première moitier du mot, 
// Puis quand la longueur du mot est comprise entre 4 et le demi prérimètre max on appel generateOtherHalf pour générer toutes
// les combinaisons possibles de l'autre moitié et ajouter les mots à l'attributs tileWordVect
{

    static int lgthWord = 0;
    for (int i = 0; i < 4; i++)
    {
        //If it is not the first letter of the word : check that letter to add is not the inverse off the last letter
        if(lgthWord==0 || i!=((currentHalfWord.back()+2)%4)){
            currentHalfWord.push_back(i);
            
            lgthWord++;
            if (lgthWord>=minHalfPerimeter && lgthWord<=maxHAlfPerimeter){
                generateFullWord(currentHalfWord, pool, kSize, ta);
            }
            if (lgthWord<=maxHAlfPerimeter){
                generateAndAnalyzeBoundWord(minHalfPerimeter,maxHAlfPerimeter,currentHalfWord, pool, kSize, ta);
            }
            currentHalfWord.pop_back();
            lgthWord--;
        }      
    }    
} //----- Fin de Méthode


void TileGenerator::generateTile(){
    for(int i=0; i<(int)tileWordVect.size(); i++){
        Tile * t = new Tile(tileWordVect[i]);
        if(t->BuildTile()){
            this->tileVect.push_back(t);
        }  
        else{
            delete t;
        }      
    }
}

void TileGenerator::generateTilingShape(int kSize){
    for(int i=0; i<(int)this->tileVect.size(); i++){
        this->tileVect[i]->buildPlanningShape(kSize);
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
    for(Tile * t: this->tileVect){
        delete t;
    }
#ifdef MAP
    cout << "Appel au destructeur de <TileGenerator>" << endl;
#endif
} //----- Fin de ~TileGenerator

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

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

void TileGenerator::generateFullWord(vector<char>& firstHalf, ThreadPool *pool, int kSize, TileAnalyzer* ta ){   
    
    int length = firstHalf.size();
    
    for(int xSize=1; xSize<length-1;xSize++){
        for(int ySize=1; ySize<length-xSize; ySize++){
            int zSize = length-xSize-ySize;
            vector<char> otherHalf;
            buildOtherHalf(firstHalf,otherHalf,xSize,ySize,zSize);

            BoundaryWord * bw = new BoundaryWord (firstHalf, otherHalf, xSize, ySize, zSize); 

            if(bw->isSelfAvoiding()){
                if(kSize ==0){
                    this->tileWordVect.push_back(bw);
                }
                else{
                    ta->analyzeBounDaryWordMemorySave(bw, pool, kSize);
                }
                                 
            }
            else{
                delete bw;
            }                               
        }       
    }    
}//----- Fin de Méthode
