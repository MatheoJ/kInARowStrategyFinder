/*************************************************************************
                           GameSolver  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <GameSolver> (fichier GameSolver.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "GameSolver.h"
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

bool GameSolver::solveHittingAlignment(){
    bool res = false;
    int count = 0; 
    for(HittingSetFinal& hsf: ha->hittingSetvect ){
       
        bool isHittingSetVAlid = solveHittingSet(hsf);

         res=res||isHittingSetVAlid;

        if(isHittingSetVAlid)
            count++;  
    }
    cout<<"Il y a "<<count<<" hitting set permettant de trouver une stratégie"<<endl;
    return res;
}

//-------------------------------------------- Constructeurs - destructeur

GameSolver::GameSolver (HittingAlignment* ha){
    this->ha = ha;
}




GameSolver::~GameSolver ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GameSolver>" << endl;
#endif
} //----- Fin de ~GameSolver


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool GameSolver::solveHittingSet(HittingSetFinal& hsf){
    map<int, bool> checkedUnit;
    vector<int> unitToTake;
    for(vector<int>& v :hsf){
        for(int& i :v){
            if(checkedUnit[i]==false){
                checkedUnit[i]=true;
                unitToTake.push_back(i);
            }
        }
    }

    bool res = doAMakerMove(hsf, unitToTake);

    return res;
}

bool GameSolver::doAMakerMove(HittingSetFinal hsf, vector<int>& unitTotake, int unitTaken){
    if(unitTaken != -1){
        GameState currentState = eraseUnitTakenByBreaker(hsf, unitTaken);
        if(currentState == winMaker){
            return false;
        }
        if(currentState == winBreaker){
            return true;
        }        
    }

    bool res = true;

    for(auto it = unitTotake.begin(); it!=unitTotake.end(); it++){

        if(res){
            unitTaken = (*it);
            it = unitTotake.erase(it);
            res =  res && doABreakerMove(hsf,unitTotake,unitTaken);
            unitTotake.insert(it,unitTaken );
        }
        
    }

    return res;
}


bool GameSolver::doABreakerMove(HittingSetFinal hsf, vector<int>& unitTotake, int unitTaken ){
    int unitForcedToTake = -1;
    if(unitTaken != -1){

        GameState currentState = eraseUnitTakenByMaker(hsf, unitTaken, unitForcedToTake);
        if(currentState == winMaker){
            return false;
        }
        if(currentState == winBreaker){
            return true;
        }        
    }

    bool res = false;
    for(auto it = unitTotake.begin(); it!=unitTotake.end(); it++){

        if(unitForcedToTake == -1 || *it == unitForcedToTake ){
            unitTaken = (*it);
            it = unitTotake.erase(it);
            res =  res || doABreakerMove(hsf,unitTotake,unitTaken);
            unitTotake.insert(it,unitTaken );
        }
    }

    return res;
}



GameState GameSolver::eraseUnitTakenByBreaker(HittingSetFinal& hsf, int uniTaken){
    
    GameState resState = stillGoing;

    for(auto it = hsf.begin(); it != hsf.end(); ){
        if(find((*it).begin(), (*it).end(), uniTaken) != (*it).end()){
            it = hsf.erase(it);
        }
        else{
            if((*it).size()==1){
                return winMaker;
            }
            it++;
        }
    }

    if(hsf.size()==0){
        resState = winBreaker;
    }

    return resState; 
}


GameState GameSolver::eraseUnitTakenByMaker(HittingSetFinal& hsf, int uniTaken, int& unitForcedToTake){
    
    GameState resState = stillGoing;
    for(vector<int>& v: hsf){
        for(auto it = v.begin(); it != v.end();){
            if((*it)== uniTaken ){
                it = v.erase(it);
            }
            else{                               
                it++;
            }
        }
        if(v.size()==0){
            return winMaker;
        }
        if(v.size()==1){
            if(unitForcedToTake==-1){
                unitForcedToTake=v[0];
            }
            else if(v[0]!=unitForcedToTake){
                return winMaker;
            }
            
        }  

    }
    
    if(hsf.size()==0){
        resState = winBreaker;
    }

    return resState; 
}
