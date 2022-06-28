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
    int  analyzeTileVect(vector<Tile>& vectTile);
    int  buildHittingset();
    vector<TileAlignment>& getVectTileAlignment();  
    
    
//-------------------------------------------- Constructeurs - destructeur
    
    

    TileAnalyzer (int sizeAnalyzing);
    

    virtual ~TileAnalyzer ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<TileAlignment> vectTileAlignment;
    vector<HittingAlignment> vectHittingAlignment;
    int sizeAlignment;


};

//-------------------------------- Autres définitions dépendantes de <TileAnalyzer>

#endif // TileAnalyzer_H

 

