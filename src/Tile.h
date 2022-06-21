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
#include <map>
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
    friend class TileAlignment;

    bool BuildTile();
    // Mode d'emploi :
    //Buile the basic shape of the tile with the boundary word

    void buildPlanningShape(int kSize);


    void setBoundaryWord( BoundaryWord *boundWord);

    int getSize();
    int getPlaningShapeSize();

    Unit** getBasicShape();
    Unit** getPlaningShape();

    BoundaryWord * getBoundWord();

    void printPlanningShape();

    void fillTile(int countUnit);
    

    



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
    
    bool dfsFillTile(int i,int j,vector<Unit*>& group, set<Unit*>&checkedUnits,vector<pair<int,int>>& coordGroup );
    pair<int,int> getVector1();
    pair<int,int> getVector2();
    pair<int,int> getVector3(pair<int,int> vect1, pair<int,int> vect2);

    void moveUnitAlongVector(int x,int y,int numUnit,int& countNumTile,map<pair<int,int>,int>& k1k2k3NumTile,int k1,int k2,pair<int, int>& vect1,pair<int, int>&vect2,pair<int, int>&vect3);

   

//----------------------------------------------------- Attributs protégés
    BoundaryWord *boundWord;
    int size;
    int planingShapeSize;
    Unit**  basicShape;
    vector< pair<int,int> > coordBasicUnits; 
    Unit** planingShape;
    

};

//-------------------------------- Autres définitions dépendantes de <Tile>

#endif // TILE_H

