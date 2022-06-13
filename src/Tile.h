/*************************************************************************
                           Tile  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Tile> (fichier Tile.h) ----------------
#if ! defined ( TILE_H )
#define TILE_H

//--------------------------------------------------- Interfaces utilisées
#include "BoundaryWord.h"
#include "Unit.h"
#include <algorithm>
#include <set>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Tile>
//
//
//------------------------------------------------------------------------

class Tile 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    friend ostream &operator<<(ostream &stream, const Tile &t);

    void BuildTile();
    // Mode d'emploi :
    //Buile the basic shape of the tile with the boundary word


    void setBoundaryWord( BoundaryWord *boundWord);

    int getSize();

    Unit** getBasicShape();

    BoundaryWord * getBoundWord();

    



//-------------------------------------------- Constructeurs - destructeur
    
    Tile (BoundaryWord *);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Tile ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void fillTile(int countUnit);
    bool dfsFillTile(int i,int j,vector<Unit*> group, set<Unit*>checkedUnits );

//----------------------------------------------------- Attributs protégés
    BoundaryWord *boundWord;
    int size;
    Unit**  basicShape;
    Unit** planingShape;

};

//-------------------------------- Autres définitions dépendantes de <Tile>

#endif // TILE_H

