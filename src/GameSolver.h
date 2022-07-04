/*************************************************************************
                           GameSolver  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <GameSolver> (fichier GameSolver.h) ----------------
#if ! defined ( GameSolver_H )
#define GameSolver_H

//--------------------------------------------------- Interfaces utilisées
#include "HittingAlignment.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


enum PlayedBy {noONe, maker, breaker};
enum GameState {stillGoing, winMaker, winBreaker};
//------------------------------------------------------------------------
// Rôle de la classe <GameSolver>
//
//
//------------------------------------------------------------------------

class GameSolver 
{
//----------------------------------------------------------------- PUBLIC


public:
  
//----------------------------------------------------- Méthodes publiques   
    bool solveHittingAlignment();
    bool solveHittingSet(HittingSetFinal& hsf);
 
//-------------------------------------------- Constructeurs - destructeur
    
   

    GameSolver (HittingAlignment* ha);
    

    virtual ~GameSolver ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    
    bool doABreakerMove(HittingSetFinal hsf, vector<int>& unitTotake, map<vector<PlayedBy>, bool>& mapOfMoovDone,vector<PlayedBy>& mooveDone,int unitTaken =-1);
    bool doAMakerMove(HittingSetFinal hsf, vector<int>& unitTotake, map<vector<PlayedBy>, bool>& mapOfMoovDone,vector<PlayedBy>& mooveDone,int unitTaken =-1);
    GameState eraseUnitTakenByBreaker(HittingSetFinal& hsf, int uniTaken);
    GameState eraseUnitTakenByMaker(HittingSetFinal& hsf, int uniTaken, int& unitForcedToTake);

//----------------------------------------------------- Attributs protégés
    HittingAlignment* ha;

};

//-------------------------------- Autres définitions dépendantes de <GameSolver>

#endif // GameSolver_H

