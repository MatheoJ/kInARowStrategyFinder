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
#include <vector>
#include <queue>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using Alignment = std::vector< std::vector<int> >;


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
    bool buildAlignments(int sizeAlignment);    
    void eraseSubsetAlignment();
    void eraseDuplicatesInAllDirection();
    bool checkTileAlignment();
    bool cleanWithRule();

    Tile * getTile();
    
//-------------------------------------------- Constructeurs - destructeur
    
    TileAlignment ();
    TileAlignment (Tile * t);
    

    virtual ~TileAlignment ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
    template <typename T>
    void eraseDuplicates(std::vector<std::vector<T>> & vecOfElements);
    void eraseElementTakenByOtherDirection(Alignment& a,set<int>& s1,set<int>& s2,set<int>& s3, map<int, int> pairOfElementTaken);
//----------------------------------------------------- Attributs protégés
    Tile* tile;
    vector< Alignment > alignementVectVertical;
    vector< Alignment > alignementVectHorizontal;
    vector< Alignment > alignementVectDiag;
    vector< Alignment > alignementVectAntiDiag;




};

//-------------------------------- Autres définitions dépendantes de <TileAlignment>

#endif // TileAlignment_H

