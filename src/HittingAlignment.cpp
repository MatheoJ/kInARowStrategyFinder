/*************************************************************************
                           HittingAlignment  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <HittingAlignment> (fichier HittingAlignment.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "HittingAlignment.h"
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include "Utils.h"

//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


void eraseSubsetHitting(HittingSet& hittingSet){
   
    //erase a ligne if it exist another which a subset of the first one
    for (auto it = hittingSet.begin() ; it != hittingSet.end() ;)
    {    
                
        for (auto it2 = hittingSet.begin(); it2 != hittingSet.end();)
        {
            if(*it2!=*it){
                if (includes((*it2).begin(),(*it2).end(),(*it).begin(),(*it).end())){
                    it2 = hittingSet.erase(it2);
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


    //erase a ligne if it has only one set and there is another line with only one set as well which is a sebset of the first one 
    for (auto it = hittingSet.begin() ; it != hittingSet.end() ;)
    {    
        if(it->size()==1){
            for (auto it2 = hittingSet.begin(); it2 != hittingSet.end();)
            {
                if(*it2!=*it && it2->size()==1){
                    if (includes((*it2)[0].begin(),(*it2)[0].end(),(*it)[0].begin(),(*it)[0].end())){
                        it2 = hittingSet.erase(it2);
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
        }  
        it++;                 
    }    
   
}


bool eraseTakenPair(Alignment& a, map<int,int>& pairOfElementTaken){
    bool toBeDeleted;
    bool canHaveBeenTaken = (a.size()==1);

    for (auto it = a.begin() ; it != a.end() ;)
    {
        
        toBeDeleted = false;
        if((*it).size()==2){
            if((pairOfElementTaken.contains((*it)[0]) && pairOfElementTaken[(*it)[0]]!=(*it)[1])
                || 
                (pairOfElementTaken.contains((*it)[1]) && pairOfElementTaken[(*it)[1]]!=(*it)[0]))
            {
                toBeDeleted=true;
            } 
            //If the pair is identical to one of the taken pair we need to check if it can be the one which we took in order not to delete the wrong one
            else if((pairOfElementTaken.contains((*it)[0]) && pairOfElementTaken[(*it)[0]]==(*it)[1] )){
                if(!canHaveBeenTaken){
                    a.clear();
                    return true;
                }
            }
        }        
        if (toBeDeleted){
            it=a.erase(it);
            if(a.size()==0){
                return false;
            }
        }            
        else{
            it++;
        }            
    }
    
    return true;
}


bool eraseTakenSet(Alignment& a, 
                    vector<vector<int>>& takenSet,
                    map<int, int>& pairOfElementTaken)
{
    bool toBeDeleted;
    bool canHaveBeenTaken = (a.size()==1);

    for (auto it = a.begin() ; it != a.end() ;)
    {        
        toBeDeleted = false;
        if((*it).size()==2){
            if((pairOfElementTaken.contains((*it)[0]) && pairOfElementTaken[(*it)[0]]!=(*it)[1])
                || 
                (pairOfElementTaken.contains((*it)[1]) && pairOfElementTaken[(*it)[1]]!=(*it)[0]))
            {
                toBeDeleted=true;
            }            
        }         
        if(!toBeDeleted  ){             
            for(int i = 0; i<takenSet.size(); i++){
                if((*it) == takenSet[i] ){
                    if(!canHaveBeenTaken){
                        a.clear();
                        return true;  
                    }                      
                }
                else if(includes((*it).begin(), (*it).end(),takenSet[i].begin(), takenSet[i].end())){                    
                    a.clear();
                    return true;
                }
                /* else if(includes(takenSet[i].begin(), takenSet[i].end(),(*it).begin(), (*it).end()) && canHaveBeenTaken ){                      
                   takenSet[i]=(*it);
                }  */
            }  
        }       
        if (toBeDeleted){
            it=a.erase(it);
            if(a.size()==0){
                return false;
            }            
        }            
        else{
            it++;
        }            
    }
    
    return true;
}

bool hasOnlySetSizeTwo(Alignment a){

     
    for (vector<int>& v : a){
        if(v.size()!=2){
            return false;
        }
    }
    return true;
}



ostream &operator<<(ostream &stream, const HittingAlignment &ha)
{
    //stream<<"MinVertical ="<<t.boundWord->getMinVertical()<<" MaxVertical ="<<t.boundWord->getMaxVertical()<<" |MinHorizontal ="<<t.boundWord->getMinHorizontal()<<" MaxHorizontal ="<<t.boundWord->getMaxHorizontal()<<endl;
    
   stream<<*(ha.tileAlign->getTile());
   for (int i = 0; i < ha.hittingSetvect.size(); i++)
   {
        for (int j = 0; j <  (int)ha.hittingSetvect[i].size(); j++)
        { 
            for (int k = 0; k <  (int)ha.hittingSetvect[i][j].size(); k++)
            {
                // Displaying set elements            
                for(int i :ha.hittingSetvect[i][j][k]){
                    stream << i << " ";
                }
                stream<<" ||";
            }
            stream<<endl; 
        } 
        stream<<"------------------------"<<endl;        
   }

    stream<<"Il y a "<<ha.hittingSetvect.size()<<" Hitting sets pour ce pavage"<<endl; 

   
    return stream;
}

void HittingAlignment::eraseSubSetOnHittingSets(){
    for(HittingSet& hs: hittingSetvect){
        eraseSubsetHitting(hs);
    }
}

void HittingAlignment::eraseDuplicatesOnHittingSets(){
    for(HittingSet& hs: hittingSetvect){
        Utils::eraseDuplicates(hs);
    }
}


//-------------------------------------------- Constructeurs - destructeur

HittingAlignment::HittingAlignment (TileAlignment* ta){
   this->tileAlign = ta;   
   buildHittingSets();
}




HittingAlignment::~HittingAlignment ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <HittingAlignment>" << endl;
#endif
} //----- Fin de ~HittingAlignment


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void HittingAlignment::buildHittingSets(){
    HittingSet  hs;
    
    hs.insert(hs.end(), this->tileAlign->alignementVectHorizontal.begin(), this->tileAlign->alignementVectHorizontal.end());    
    hs.insert(hs.end(), this->tileAlign->alignementVectVertical.begin(), this->tileAlign->alignementVectVertical.end());    
    hs.insert(hs.end(), this->tileAlign->alignementVectDiag.begin(), this->tileAlign->alignementVectDiag.end());
    hs.insert(hs.end(), this->tileAlign->alignementVectAntiDiag.begin(), this->tileAlign->alignementVectAntiDiag.end());

    map<int,int> pairTaken;
    recursiveBuildHittingSets(hs,pairTaken,0);

} 

void HittingAlignment::recursiveBuildHittingSets(HittingSet hs, map<int,int>& pairTaken , int indexInHS ){
    int i = indexInHS;
    bool finalSet = true;
    for(auto it = hs.begin(); it!=hs.end();){

        //if the alignment has been deleted
        if(!eraseTakenPair(*it,pairTaken)){
            return;
        }
        //if the alignement has been cleared because it has been validated by a taken pair
        else if((*it).size()!=0){
            //if the alignment has 2 or more sets and they are only of size 2
            if(hasOnlySetSizeTwo(*it)){
                if((*it).size()>1||!pairTaken.contains((*it)[0][0])){
                    Alignment a = *it;
                    finalSet = false;
                    for(int i =0; i<a.size(); i++){
                        (*it).clear();
                        (*it).push_back(a[i]);
                        pairTaken[a[i][0]]=a[i][1];
                        pairTaken[a[i][1]]=a[i][0];
                        recursiveBuildHittingSets(hs, pairTaken, i+1);
                        pairTaken.erase(a[i][0]);
                        pairTaken.erase(a[i][1]);
                    }  
                    return;
                }                 
            }
            it++;
            i++; 
        } 
        else{
            it = hs.erase(it);
        }
    }
    if(finalSet){
        //hittingSetvect.push_back(hs);
        eraseSubsetHitting(hs);
        Utils::eraseDuplicates(hs);
        vector<vector<int>> v;
        map<int, int> m;
        finishRecursiveBuilding(hs, v, m);
    }
}


void HittingAlignment::finishRecursiveBuilding(HittingSet hs, vector<vector<int>>& takenSet, map<int, int>& pairTaken )
{
    bool finalSet = true;
    for(auto it = hs.begin(); it!=hs.end();){

        //if the alignment has been deleted
        if(!eraseTakenSet(*it,takenSet,pairTaken)){
            return;
        }
        else if((*it).size()!=0){
            //if the alignment has 2 or more sets 
            if((*it).size()>1){
                Alignment a = *it;
                finalSet = false;
                for(int i =0; i<a.size(); i++){
                    (*it).clear();
                    (*it).push_back(a[i]);
                    takenSet.push_back(a[i]);
                    if((a[i]).size()==2){
                        pairTaken[a[i][0]]=a[i][1];
                        pairTaken[a[i][1]]=a[i][0];
                    }
                    finishRecursiveBuilding(hs, takenSet, pairTaken);
                    if((a[i]).size()==2){
                        pairTaken.erase(a[i][0]);
                        pairTaken.erase(a[i][1]);
                    }
                    takenSet.pop_back();
                }  
                return;    
            }
            it++;
        }
        
        //if the alignement has been cleared because it has been validated by a taken set
        else{
            it = hs.erase(it);
        }
    }
    if(finalSet){
        if(hittingSetvect.size()==0 || hittingSetvect.back()!=hs )
            hittingSetvect.push_back(hs);
    }  
}