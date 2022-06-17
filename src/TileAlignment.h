/*************************************************************************
                           TileAlignment  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TileAlignment> (fichier TileAlignment.h) ----------------
#if ! defined ( TileAlignment_H )
#define TileAlignment_H

//--------------------------------------------------- Interfaces utilisées
#include "Tile.h"
#include "vector"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using Alignment = vector<set<int>>;


//------------------------------------------------------------------------
// Rôle de la classe <TileAlignment>
//
//
//------------------------------------------------------------------------

class TileAlignment 
{
//----------------------------------------------------------------- PUBLIC


public:

    friend ostream &operator<<(ostream &stream, const TileAlignment &ta);
    friend class TileAnalyzer;
//----------------------------------------------------- Méthodes publiques    
    
//-------------------------------------------- Constructeurs - destructeur
    
    TileAlignment ();
    TileAlignment (Tile * t, int sizeAlignment);
    

    virtual ~TileAlignment ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void buildAlignments(int sizeAlignment);
//----------------------------------------------------- Attributs protégés
    Tile* tile;
    vector<Alignment> alignementVect;



};

//-------------------------------- Autres définitions dépendantes de <TileAlignment>

#endif // TileAlignment_H

