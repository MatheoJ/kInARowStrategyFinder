/*************************************************************************
                           HittingAlignment  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <HittingAlignment> (fichier HittingAlignment.h) ----------------
#if ! defined ( HittingAlignment_H )
#define HittingAlignment_H

//--------------------------------------------------- Interfaces utilisées
#include "TileAlignment.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
    /* struct HittingSet{
        vector< Alignment > alignementVectVertical;
        vector< Alignment > alignementVectHorizontal;
        vector< Alignment > alignementVectDiag;
        vector< Alignment > alignementVectAntiDiag;
    }; */

    using HittingSet = std::vector< Alignment> ;
    using HittingSetFinal = std::vector< vector<int>> ;

//------------------------------------------------------------------------
// Rôle de la classe <HittingAlignment>
//
//
//------------------------------------------------------------------------

class HittingAlignment 
{
//----------------------------------------------------------------- PUBLIC


public:
    friend ostream &operator<<(ostream &stream, const HittingAlignment &ha);
    friend class TileAnalyzer;
    friend class GameSolver;
    friend class main;
//----------------------------------------------------- Méthodes publiques    
    void eraseDuplicatesOnHittingSets();
    vector<HittingSetFinal>& getHittingSetVect();
//-------------------------------------------- Constructeurs - destructeur
    
    

    HittingAlignment (TileAlignment* ta);
    

    virtual ~HittingAlignment ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    void buildHittingSets();
    void recursiveBuildHittingSets(HittingSet hs, map<int,int>& pairTaken, int indexInHS, map<vector<int>,bool> allSetTaken);
    void finishRecursiveBuilding(HittingSet hs, vector<vector<int>>& takenSet, map<int, int>& pairTaken, map<vector<int>,bool> allSetTaken);
    
//----------------------------------------------------- Attributs protégés
    TileAlignment* tileAlign ;
    vector<HittingSetFinal> hittingSetvect;



};

//-------------------------------- Autres définitions dépendantes de <HittingAlignment>

#endif // HittingAlignment_H

