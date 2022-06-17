/*************************************************************************
                           TileAlignment  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TileAlignment> (fichier TileAlignment.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "TileAlignment.h"
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

ostream &operator<<(ostream &stream, const TileAlignment &ta)
{
    
   for (int i = 0; i < (int)ta.alignementVect.size(); i++)
   {
        for (int j = 0; j <  (int)ta.alignementVect[i].size(); j++)
        {
            set<int>::iterator itr;   
            // Displaying set elements
            for (itr = ta.alignementVect[i][j].begin();itr != ta.alignementVect[i][j].end(); itr++)
            {
                stream << *itr << " ";
            }
            stream<<" ||";
        }
        stream<<endl;        
   }
   stream<<"--------------------\n";
   
    return stream;
}


//-------------------------------------------- Constructeurs - destructeur

TileAlignment::TileAlignment (Tile* t, int sizeAlignment){
    this->tile = t;  
    buildAlignments(sizeAlignment);
}


TileAlignment::TileAlignment ()
// Algorithme :
//
{
   
#ifdef MAP
    cout << "Appel au constructeur de <TileAlignment>" << endl;
#endif
} //----- Fin de TileAlignment


TileAlignment::~TileAlignment ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TileAlignment>" << endl;
#endif
} //----- Fin de ~TileAlignment


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void TileAlignment::buildAlignments(int sizeAlignment){
    map<int, int> numTileIndex;
    set<int> unitChecked; 
    int indexSet;
    for (int i=0; i<tile->size; i++){
        for (int j=0; j<tile->size; j++){
            
            if(tile->planingShape[i][j].getTileNumber()==0){
                
                //horizontal
                numTileIndex.clear();
                Alignment a;
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.count(tile->planingShape[i+k][j].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j].getTileNumber()]=a.size();
                        indexSet = a.size();
                        set<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].insert(tile->planingShape[i+k][j].getUnitNumber());
                }
                alignementVect.push_back(a);

                //vertical
                numTileIndex.clear();
                a.clear();
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.count(tile->planingShape[i][j+k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i][j+k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        set<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].insert(tile->planingShape[i][j+k].getUnitNumber());
                }
                alignementVect.push_back(a);

                //diagonal
                numTileIndex.clear();
                a.clear();
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.count(tile->planingShape[i+k][j+k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        set<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].insert(tile->planingShape[i+k][j+k].getUnitNumber());
                }
                alignementVect.push_back(a);
               
            }

            //antiDiagonal  
            if(!unitChecked.contains(tile->planingShape[i+sizeAlignment][j].getUnitNumber())){
                unitChecked.insert(tile->planingShape[i+sizeAlignment][j].getUnitNumber());  
                numTileIndex.clear();
                Alignment a;
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.count(tile->planingShape[i+k][j-k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j-k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j-k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        set<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].insert(tile->planingShape[i+k][j-k].getUnitNumber());
                }
                alignementVect.push_back(a);                
            }
        }
    }

    
    for (int i=tile->size-1; i>tile->size-(sizeAlignment+1); i--){
        for (int j=tile->size-1; j>tile->size-(sizeAlignment+1); j--){
            
            if(!unitChecked.contains(tile->planingShape[i][j].getUnitNumber())){
                unitChecked.insert(tile->planingShape[i][j].getUnitNumber());
                //antiDiagonal    
                numTileIndex.clear();
                Alignment a;
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.count(tile->planingShape[i+k][j].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j].getTileNumber()]=a.size();
                        indexSet = a.size();
                        set<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].insert(tile->planingShape[i+k][j].getUnitNumber());
                }
                alignementVect.push_back(a);                
            }
        }
    }
}