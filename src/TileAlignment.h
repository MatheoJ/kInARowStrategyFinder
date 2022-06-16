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
using Alignement = vector<set<int>>;


//------------------------------------------------------------------------
// Rôle de la classe <TileAlignment>
//
//
//------------------------------------------------------------------------

class TileAlignment 
{
//----------------------------------------------------------------- PUBLIC


public:
    friend class Tile;
//----------------------------------------------------- Méthodes publiques    
    
//-------------------------------------------- Constructeurs - destructeur
    
    TileAlignment ();
    TileAlignment ();
    

    virtual ~TileAlignment ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Tile* tile;
    vector<Alignement> alignementVect;

};

//-------------------------------- Autres définitions dépendantes de <TileAlignment>

#endif // TileAlignment_H

