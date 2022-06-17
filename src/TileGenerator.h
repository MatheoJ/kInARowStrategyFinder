/*************************************************************************
                           TileGenerator  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TileGenerator> (fichier TileGenerator.h) ----------------
#if ! defined ( TILEGEN_H )
#define TILEGEN_H

//--------------------------------------------------- Interfaces utilisées

using namespace std;
#include <vector>
#include <string>
#include <map>
#include "Tile.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TileGenerator>
// Génère des polyominos qui plannent le plan et sont auto évidant
//
//------------------------------------------------------------------------

class TileGenerator
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    vector<BoundaryWord>& getTileWordVect();

    vector<Tile>& getTileVect();

    void generateBoundWord(int minHalfPerimeter, int maxHalfPerimeter, vector<char>& currentHalfWord);
    // Mode d'emploi :
    // Appeler cette methode pour remplir l'attribut tileWordVect avec de polyomino qui plannent le plan

    void generateTile();
    // Mode d'emploi :
    // Appeler cette methode pour remplir l'attribut tileVect

    void generateTilingShape(int kSize);



    

    
    

//-------------------------------------------- Constructeurs - destructeur

    TileGenerator();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TileGenerator();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE
private:
    void generateFullWord(vector<char>& firstHalf);
    void buildOtherHalf(vector<char>& firstHalf,vector<char>& otherHalf,int xSize,int ySize,int zSize);
    bool isSelfAvoiding(BoundaryWord& fullVector);
    void buildTile(BoundaryWord& bw);

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<BoundaryWord>  tileWordVect;
    vector<Tile> tileVect;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // TILEGEN_H

