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
#include <queue>

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
              
            // Displaying set elements   
            for(int i :ta.alignementVect[i][j]){
                stream << i << " ";
            }
            stream<<" ||";
        }
        stream<<endl;        
   }
   stream<<"--------------------\n";
   
    return stream;
}


//-------------------------------------------- Constructeurs - destructeur

TileAlignment::TileAlignment (Tile* t){
    this->tile = t;  
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


bool checkAlignment(Alignment& a){
    for(int i =0; i<(int)a.size(); i++){
        if(a[i].size()==1)
            return false;
    }
    return true;

}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool TileAlignment::buildAlignments(int sizeAlignment){
    map<int, int> numTileIndex;
    set<int> unitChecked; 
    int indexSet;
   


    for (int i=0; i<tile->size; i++){

        for (int j=0; j<tile->size; j++){
            
            if(tile->planingShape[i][j].getTileNumber()==0){
                
                //vertical
                numTileIndex.clear();
                Alignment a;
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i+k][j].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j].getTileNumber()]=a.size();
                        indexSet = a.size();
                        vector<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j].getUnitNumber());
                }
                if(!checkAlignment(a))
                    return false;
                
                alignementVect.push_back(a);

                //horizontal
                numTileIndex.clear();
                a.clear();
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i][j+k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i][j+k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        vector<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].push_back(tile->planingShape[i][j+k].getUnitNumber());
                }
                if(!checkAlignment(a))
                    return false;
                alignementVect.push_back(a);
                

                //diagonal
                numTileIndex.clear();
                a.clear();
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i+k][j+k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j+k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        vector<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j+k].getUnitNumber());
                }
                if(!checkAlignment(a))
                    return false;
                alignementVect.push_back(a);
               
            }    


            //antiDiagonal  
            if(!unitChecked.contains(tile->planingShape[i+sizeAlignment][j].getUnitNumber())){
                unitChecked.insert(tile->planingShape[i+sizeAlignment][j].getUnitNumber());  
                numTileIndex.clear();
                Alignment a;
                
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i+k][j-k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j-k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j-k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        vector<int> s;

                        a.push_back(s);
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j-k].getUnitNumber());
                }
                if(!checkAlignment(a))
                    return false;
                alignementVect.push_back(a);                
            }
        }

    }

    //If the function get's here it means: it hasn't encontered a wrong alignment
    return true;

} 
