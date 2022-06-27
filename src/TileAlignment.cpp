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
bool cleanAlignment(Alignment& a){
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

void addElementToSet(set<int> & vectToEdit,vector<int> & vectTarget ){
    for(int i: vectTarget){
        vectToEdit.insert(i);
    }
}
//----------------------------------------------------- Méthodes publiques


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

void TileAlignment::eraseDuplicatesInAllDirection(){
    eraseDuplicates(alignementVectAntiDiag);
    eraseDuplicates(alignementVectDiag);
    eraseDuplicates(alignementVectHorizontal);
    eraseDuplicates(alignementVectVertical);
}

Tile * TileAlignment::getTile(){
    return this->tile;
}


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
                        a.emplace_back();
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j].getUnitNumber());
                }
                if(cleanAlignment(a)){
                    eraseDuplicates(a);
                    alignementVectVertical.push_back(a);
                }
                else{
                    return false;
                }
                    

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
                        a.emplace_back();
                    }
                    a[indexSet].push_back(tile->planingShape[i][j+k].getUnitNumber());
                } 

                if(cleanAlignment(a)){
                    eraseDuplicates(a);
                    alignementVectHorizontal.push_back(a);
                }
                else{
                    return false;
                }
                

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
                        a.emplace_back();
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j+k].getUnitNumber());
                }
                if(cleanAlignment(a)){
                    eraseDuplicates(a);
                    alignementVectDiag.push_back(a);
                }
                else{
                    return false;
                }
               
            }    


            //antiDiagonal  
            if(!unitChecked.contains(tile->planingShape[i][j+sizeAlignment].getUnitNumber())){
                unitChecked.insert(tile->planingShape[i][j+sizeAlignment].getUnitNumber());  
                numTileIndex.clear();
                Alignment a;
                
                for(int k=0; k<sizeAlignment; k++){
                    if(numTileIndex.contains(tile->planingShape[i+k][j+sizeAlignment-k].getTileNumber())){
                        indexSet = numTileIndex[tile->planingShape[i+k][j+sizeAlignment-k].getTileNumber()];                        
                    }
                    else{
                        numTileIndex[tile->planingShape[i+k][j+sizeAlignment-k].getTileNumber()]=a.size();
                        indexSet = a.size();
                        a.emplace_back();
                    }
                    a[indexSet].push_back(tile->planingShape[i+k][j+sizeAlignment-k].getUnitNumber());
                }
                if(cleanAlignment(a)){
                    eraseDuplicates(a);
                    alignementVectAntiDiag.push_back(a);
                }
                else{
                    return false;
                }            
            }
        }

    }

    

    if(!checkTileAlignment()){
        return false;
    }
   

    //If the function get's here it means: it hasn't encontered a wrong alignment
    return true;

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




template <typename T>
void TileAlignment::eraseDuplicates(std::vector<std::vector<T>> & vecOfElements)
{
    std::map<std::vector<T>, bool> countMap;
   
    // Remove the elements from Map which has 1 frequency count
    for (auto it = vecOfElements.begin() ; it != vecOfElements.end() ;)
    {
        sort((*it).begin(),(*it).end());
        if (countMap.contains(*it))
            it = vecOfElements.erase(it);
        else{
            countMap[*it]=true;
            it++;
        }
            
    }

} 



void TileAlignment::eraseElementTakenByOtherDirection(Alignment& a,set<int>& s1,set<int>& s2,set<int>& s3, map<int, int> pairOfElementTaken){
    
    set<int> elementOfPairAlreadyCheck; 
    
    auto it = a.begin();
    bool toBeDeleted = false;
    while (it != a.end())
    {   
        toBeDeleted = false;
        if((*it).size()==2){
            for(int& i : *it)
            {
                if(s1.contains(i)||s2.contains(i)||s3.contains(i))
                    toBeDeleted=true;
            }
        }
        if((*it).size()==3){
            int count =0;
            elementOfPairAlreadyCheck.clear();
            for(int& i : *it)
            {
                if((s1.contains(i)||s2.contains(i)||s3.contains(i))&& !elementOfPairAlreadyCheck.contains(i)){
                    count++;
                    elementOfPairAlreadyCheck.insert(pairOfElementTaken[i]);
                }                    
            }
            if (count>=2)
                toBeDeleted=true;
        }


        if(toBeDeleted){
            it = a.erase(it);
        } 
        else {            
            ++it;
        }
    }
}   


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


bool TileAlignment::checkTileAlignment(){
    

    if(alignementVectVertical.size()==0 ||alignementVectHorizontal.size()==0 ||alignementVectDiag.size()==0 ||alignementVectAntiDiag.size()==0  ){
        return false;
    }

    set<int> unitTakenByHorizontal, unitTakenByVertical, unitTakenByDiag, unitTakenByAntiDiag;
    map<int, int> pairOfElementTaken;
    bool unitTaken = true;

    while (unitTaken)
    {
        unitTaken = false;
        //We take every unit wich belong to alignment of two set 
        //horizontal
        for(Alignment& a: alignementVectHorizontal){
            this->eraseElementTakenByOtherDirection(a,unitTakenByVertical,unitTakenByDiag,unitTakenByAntiDiag, pairOfElementTaken);
            if(a.size()==0){
                return false;
            }
            if(a.size()==1 && a[0].size()==2){
                if(!unitTakenByHorizontal.contains(a[0][0])||!unitTakenByHorizontal.contains(a[0][1])){
                    addElementToSet(unitTakenByHorizontal,a[0]);
                    pairOfElementTaken[a[0][0]]=a[0][1];
                    pairOfElementTaken[a[0][1]]=a[0][0];
                    unitTaken = true;
                }
            } 
        }
        //Vertical
        for(Alignment& a: alignementVectVertical){
            this->eraseElementTakenByOtherDirection(a,unitTakenByHorizontal,unitTakenByDiag,unitTakenByAntiDiag, pairOfElementTaken);
            if(a.size()==0){
                return false;
            }
            if(a.size()==1 && a[0].size()==2){
                if(!unitTakenByVertical.contains(a[0][0])||!unitTakenByVertical.contains(a[0][1])){
                    addElementToSet(unitTakenByVertical,a[0]);
                    pairOfElementTaken[a[0][0]]=a[0][1];
                    pairOfElementTaken[a[0][1]]=a[0][0];
                    unitTaken = true;
                }
            } 
        }
        //Diagonal
        for(Alignment& a: alignementVectDiag){
            this->eraseElementTakenByOtherDirection(a,unitTakenByVertical,unitTakenByHorizontal,unitTakenByAntiDiag, pairOfElementTaken);
            if(a.size()==0){
                return false;
            }
            if(a.size()==1 && a[0].size()==2){
                if(!unitTakenByDiag.contains(a[0][0])||!unitTakenByDiag.contains(a[0][1])){
                    addElementToSet(unitTakenByDiag,a[0]);
                    pairOfElementTaken[a[0][0]]=a[0][1];
                    pairOfElementTaken[a[0][1]]=a[0][0];
                    unitTaken = true;
                }
            } 
        }
        //AntiDiagonal
        for(Alignment& a: alignementVectAntiDiag){
            this->eraseElementTakenByOtherDirection(a,unitTakenByVertical,unitTakenByDiag,unitTakenByHorizontal, pairOfElementTaken);
            if(a.size()==0){
                return false;
            }
            if(a.size()==1 && a[0].size()==2){
                if(!unitTakenByAntiDiag.contains(a[0][0])||!unitTakenByAntiDiag.contains(a[0][1])){
                    addElementToSet(unitTakenByAntiDiag,a[0]);
                    pairOfElementTaken[a[0][0]]=a[0][1];
                    pairOfElementTaken[a[0][1]]=a[0][0];
                    unitTaken = true;
                }                
            } 
        }           
    }

    return true;
}


//erase Subset inside an Alignment AND between the alignment them selves
void TileAlignment::eraseSubsetAlignment(){
    vector< Alignment >* tabVect[4] = {&alignementVectVertical,  &alignementVectHorizontal, &alignementVectDiag, &alignementVectAntiDiag};
    for (int i =0; i<4; i++){
        vector< Alignment >* vect = tabVect[i];
         
         for (auto it = vect->begin() ; it != vect->end() ;)
        {    
                    
            for (auto it2 = vect->begin(); it2 != vect->end();)
            {
                if(*it2!=*it){
                    if (includes((*it2).begin(),(*it2).end(),(*it).begin(),(*it).end())){
                        it2 = vect->erase(it2);
                        if(it2<it){
                            it--;
                        }
                    }
                    else{                            
                        it2++;
                    }
                }  
                else{
                   it2++; 
                }
            }
            it++;                    
        }

        for(Alignment& a: *vect){
            for (auto it = a.begin() ; it != a.end() ;)
            {                
                for (auto it2 = a.begin() ; it2 != a.end() ;)
                {
                    if(*it2!=*it){
                        if (includes((*it).begin(),(*it).end(),(*it2).begin(),(*it2).end())){
                            it2 = a.erase(it2);
                            if(it2<it){
                                it--;
                            }
                        }    
                        else{                            
                            it2++;
                        }
                    }
                    else{
                        it2++; 
                    }
                   
                        
                }
                it++;                    
            }            
        }      
    }
   
}
