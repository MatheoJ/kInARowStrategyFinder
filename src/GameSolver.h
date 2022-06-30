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
 
//-------------------------------------------- Constructeurs - destructeur
    
   

    GameSolver ();
    

    virtual ~GameSolver ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    bool solveHittingSet();
    void makeABreakerMove();
    void makeAMakerMove();

//----------------------------------------------------- Attributs protégés
    HittingAlignement* ha;

};

//-------------------------------- Autres définitions dépendantes de <GameSolver>

#endif // GameSolver_H

