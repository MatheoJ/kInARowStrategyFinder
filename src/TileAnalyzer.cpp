/*************************************************************************
                           TileAnalyzer  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TileAnalyzer> (fichier TileAnalyzer.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "TileAnalyzer.h"
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
int TileAnalyzer::analyzeTileVect(vector<Tile *>& vectTile ){
    for(int i =0; i<(int)vectTile.size(); i++){
        TileAlignment ta(vectTile[i]);
        if(ta.buildAlignments(sizeAlignment)){            
            ta.eraseDuplicatesInAllDirection();
            ta.eraseSubsetAlignment();
            ta.eraseDuplicatesInAllDirection();
            if(ta.cleanWithRule()){
                vectTileAlignment.push_back(ta);
            }     
        }
    }
    return vectTileAlignment.size();    
}

void TileAnalyzer::analyzeTileVectMemorySave(vector<Tile *>& vectTile, ThreadPool* pool){
    for(int i =0; i<(int)vectTile.size(); i++){
        pool->enqueueVoid([&](Tile* t) {this->analyzeTile(t);}, vectTile[i]);        
    }
}

void TileAnalyzer::analyzeBwVectMemorySave(vector<BoundaryWord *>& vectBW, ThreadPool* pool, int kSize){
   /*  for(int i =0; i<(int)vectBW.size(); i++){
        pool->enqueueVoid([&](BoundaryWord* b) {this->analyzeBoundaryWord(b, kSize);},vectBW[i]);        
    } */

    while(vectBW.size()!=0){
        sem_wait(&(pool->semaphore));
        pool->enqueueVoid([&](BoundaryWord* b) {this->analyzeBoundaryWord(b, kSize);},vectBW.back()); 
        vectBW.pop_back();
    }
}

void  TileAnalyzer::analyzeBounDaryWordMemorySave(BoundaryWord* bw, ThreadPool* pool, int kSize){
    pool->enqueueVoid([&](BoundaryWord* b) {this->analyzeBoundaryWord(b, kSize);}, bw);  
}



void TileAnalyzer::analyzeBoundaryWord(BoundaryWord* bw, int kSize){
    Tile * t = new Tile(bw);
    if(t->BuildTile()){
        t->buildPlanningShape(kSize);
        TileAlignment ta(t);
        if(ta.buildAlignments(sizeAlignment)){            
            ta.eraseDuplicatesInAllDirection();
            ta.eraseSubsetAlignment();
            ta.eraseDuplicatesInAllDirection();
            if(ta.cleanWithRule()){
                //vectTileAlignment.push_back(ta);
                HittingAlignment ha (&ta);
                ha.eraseDuplicatesOnHittingSets();
                GameSolver gs(&ha);
                if(gs.solveHittingAlignment()){                    
                    mutexPrint.lock();
                    ha.printValidHittingSet();
                    this->numValidTile++;
                    mutexPrint.unlock();
                }
            }     
        }
    }
    //delete bw;
    delete t;
}

void TileAnalyzer::analyzeTile(Tile* t){
    TileAlignment ta(t);
    if(ta.buildAlignments(sizeAlignment)){            
        ta.eraseDuplicatesInAllDirection();
        ta.eraseSubsetAlignment();
        ta.eraseDuplicatesInAllDirection();
        if(ta.cleanWithRule()){
            //vectTileAlignment.push_back(ta);
            HittingAlignment ha (&ta);
            ha.eraseDuplicatesOnHittingSets();
            GameSolver gs(&ha);
            if(gs.solveHittingAlignment()){                    
                mutexPrint.lock();
                ha.printValidHittingSet();
                this->numValidTile++;
                mutexPrint.unlock();
            }
        }     
    }
}

void TileAnalyzer::buildHittingset(ThreadPool* pool){
    
    //int size = vectTileAlignment.size();
    for(TileAlignment& ta : vectTileAlignment){

        pool->enqueueVoid([&](TileAlignment* t) {this->makeHittingAlignement(t);}, &ta);
       
    
       /*  vectHittingAlignment.emplace_back(&ta);        
        vectHittingAlignment.back().eraseDuplicatesOnHittingSets();

        countHittingSet+= vectHittingAlignment.back().hittingSetvect.size();
        cout<<"\r"<<count++<<" / "<<size<<flush; */            
    }
}

vector<TileAlignment>& TileAnalyzer::getVectTileAlignment(){
    return this->vectTileAlignment;
}

vector<HittingAlignment*>& TileAnalyzer::getValidHittingAlignment(){
    return this->validHittingAlignment;
}

int TileAnalyzer::getNumValidTile(){
    return this->numValidTile;
}

void  TileAnalyzer::solveGame(ThreadPool* pool){
    for(HittingAlignment&  ha :vectHittingAlignment ){
        pool->enqueueVoid([&](HittingAlignment* h) {this->solveHitAlignment(h);}, &ha);
        //this->solveHitAlignment(&ha);
    }
}

int TileAnalyzer::countHittingSets(){
    int count =0;
    for(HittingAlignment& ha: vectHittingAlignment){
        count += ha.hittingSetvect.size();
    }
    return count;
}

//-------------------------------------------- Constructeurs - destructeur



TileAnalyzer::TileAnalyzer (int sizeAlignment)
// Algorithme :
//
{
    this->sizeAlignment=sizeAlignment;
    this->numValidTile=0; 
    
#ifdef MAP
    cout << "Appel au constructeur de <TileAnalyzer>" << endl;
#endif
} //----- Fin de TileAnalyzer

TileAnalyzer::TileAnalyzer ()
// Algorithme :
//
{
    this->sizeAlignment=0;
    this->numValidTile=0; 
    
#ifdef MAP
    cout << "Appel au constructeur de <TileAnalyzer>" << endl;
#endif
} //----- Fin de TileAnalyzer


TileAnalyzer::~TileAnalyzer ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TileAnalyzer>" << endl;
#endif
} //----- Fin de ~TileAnalyzer


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void TileAnalyzer::solveHitAlignment(HittingAlignment* ha){
    GameSolver gs(ha);
    static int count = 1;
    static int size = vectHittingAlignment.size();
    if(gs.solveHittingAlignment()){
        mutexValidHittingAlignment.lock();
        validHittingAlignment.push_back(ha);
        mutexValidHittingAlignment.unlock();
        
        mutexPrint.lock();
        ha->printValidHittingSet();
        mutexPrint.unlock();
    }
    mutexPrint.lock();    
    cout<<"\r"<<count++<<" / "<<size<<flush;
    mutexPrint.unlock();
}


void TileAnalyzer::makeHittingAlignement (TileAlignment* ta){
    static int count = 1;
    static int size = vectTileAlignment.size();

    HittingAlignment ha (ta);
    ha.eraseDuplicatesOnHittingSets();
    mutexHittingAlignment.lock();
    vectHittingAlignment.push_back(ha);
    mutexHittingAlignment.unlock();


    mutexPrint.lock();    
    cout<<"\r"<<count++<<" / "<<size<<flush;
    mutexPrint.unlock();

}
