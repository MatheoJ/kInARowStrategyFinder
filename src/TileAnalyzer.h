/*************************************************************************
                           TileAnalyzer  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TileAnalyzer> (fichier TileAnalyzer.h) ----------------
#if ! defined ( TileAnalyzer_H )
#define TileAnalyzer_H

//--------------------------------------------------- Interfaces utilisées
#include "TileAlignment.h"
#include "HittingAlignment.h"
#include "GameSolver.h" 
#include "../include/ThreadPool.h"
#include <mutex>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TileAnalyzer>
//
//
//------------------------------------------------------------------------

class TileAnalyzer 
{
//----------------------------------------------------------------- PUBLIC


public:
//----------------------------------------------------- Méthodes publiques 
    int  analyzeTileVect(vector<Tile *>& vectTile);
    void  analyzeTileVectMemorySave(vector<Tile *>& vectTile, ThreadPool* pool);
    void  analyzeBwVectMemorySave(vector<BoundaryWord *>& vectBW, ThreadPool* pool, int kSize);
    void  analyzeBounDaryWordMemorySave(BoundaryWord * bw, ThreadPool* pool,int kSize);
    void analyzeTile(Tile* t);
    void analyzeBoundaryWord(BoundaryWord* bw, int kSize);
    void  buildHittingset(ThreadPool* pool);
    void  solveGame(ThreadPool* pool);

    int countHittingSets();
    int getNumValidTile();

    vector<TileAlignment>& getVectTileAlignment();  
    vector<HittingAlignment*>& getValidHittingAlignment();
    
    
//-------------------------------------------- Constructeurs - destructeur
    
    

    TileAnalyzer (int sizeAnalyzing);
    TileAnalyzer ();
    

    virtual ~TileAnalyzer ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void solveHitAlignment(HittingAlignment* ha);
    void makeHittingAlignement (TileAlignment* ta);
//----------------------------------------------------- Attributs protégés
    vector<TileAlignment> vectTileAlignment;
    vector<HittingAlignment*> validHittingAlignment;    
    vector<HittingAlignment> vectHittingAlignment;
    int sizeAlignment;
    int numValidTile; 

    std::mutex mutexValidHittingAlignment;
    std::mutex mutexHittingAlignment;   
    std::mutex mutexPrint;


};

//-------------------------------- Autres définitions dépendantes de <TileAnalyzer>

#endif // TileAnalyzer_H

 

