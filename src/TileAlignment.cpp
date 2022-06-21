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
    
    stream<<"Ensemble traces Horizontale :"<<endl;
    for (int i = 0; i < (int)ta.alignementVectHorizontal.size(); i++)
    {
        for (int j = 0; j <  (int)ta.alignementVectHorizontal[i].size(); j++)
        {
                
            // Displaying set elements   
            
            for(int i :ta.alignementVectHorizontal[i][j]){
                stream << i << " ";
            }
            stream<<" ||";
        }
        stream<<endl;        
    }
    stream<<"Ensemble traces Vertical :"<<endl;
    for (int i = 0; i < (int)ta.alignementVectVertical.size(); i++)
    {
        for (int j = 0; j <  (int)ta.alignementVectVertical[i].size(); j++)
        {
                
            // Displaying set elements   
            
            for(int i :ta.alignementVectVertical[i][j]){
                stream << i << " ";
            }
            stream<<" ||";
        }
        stream<<endl;        
    }
    stream<<"Ensemble traces Diagonale :"<<endl;
    for (int i = 0; i < (int)ta.alignementVectDiag.size(); i++)
    {
        for (int j = 0; j <  (int)ta.alignementVectDiag[i].size(); j++)
        {
                
            // Displaying set elements   
            
            for(int i :ta.alignementVectDiag[i][j]){
                stream << i << " ";
            }
            stream<<" ||";
        }
        stream<<endl;        
    }
    stream<<"Ensemble traces Anti-Diagonale :"<<endl;
    for (int i = 0; i < (int)ta.alignementVectAntiDiag.size(); i++)
    {
        for (int j = 0; j <  (int)ta.alignementVectAntiDiag[i].size(); j++)
        {
                
            // Displaying set elements   
            
            for(int i :ta.alignementVectAntiDiag[i][j]){
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
    auto it = a.begin();
    while (it != a.end())
    {
        // remove odd numbers
        if (it->size()==1)
        {
            // `erase()` invalidates the iterator, use returned iterator
            it = a.erase(it);
        }
        // Notice that the iterator is incremented only on the else part (why?)
        else {
            ++it;
        }
    }

    if(a.size()==0)
        return false;
    return true;

}

void eraseDouble(vector<vector<int>>& a){
    auto it = a.begin();
    while (it != a.end()-1)
    {
        // remove odd numbers
        if (*it==*(it+1))
        {
            // `erase()` invalidates the iterator, use returned iterator
            it = a.erase(it);
        }
        // Notice that the iterator is incremented only on the else part (why?)
        else {
            ++it;
        }
    }
}

void addElementToSet(set<int> & vectToEdit,vector<int> & vectTarget ){
    for(int i: vectTarget){
        vectToEdit.insert(i);
    }
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
                if(checkAlignment(a))
                    alignementVectVertical.push_back(a);

                //horizontal
                numTileIndex.clear();
                a.clear();
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i][j+k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i][j+k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i][j+k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        vector<int> s;
                        a.push_back(s);
                    }
                    a[indexSet].push_back(tile->planingShape[i][j+k].getUnitNumber());
                } 

                if(checkAlignment(a))
                    alignementVectHorizontal.push_back(a);
                
                

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
                if(checkAlignment(a))
                    alignementVectDiag.push_back(a);
               
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
                if(checkAlignment(a))
                    alignementVectAntiDiag.push_back(a);              
            }
        }

    }


    if(!checkTileAlignment()){
        return false;
    }
        

    //If the function get's here it means: it hasn't encontered a wrong alignment
    return true;

}


bool TileAlignment::checkTileAlignment(){
    if(alignementVectVertical.size()==0 ||alignementVectHorizontal.size()==0 ||alignementVectDiag.size()==0 ||alignementVectAntiDiag.size()==0  ){
        return false;
    }

    /* set<int> unitTaken;
    //We take every unit wich belong to alignment of two set 
    for(int i; i<alignementVectHorizontal.size(); i++){
        eraseDouble(alignementVectHorizontal[i]);
        if(alignementVectHorizontal[i].size()==1 && alignementVectHorizontal[i][0].size()==2){
            addElementToSet(unitTaken,alignementVectHorizontal[i][0]);
        }       
    } */






    return true;
}
