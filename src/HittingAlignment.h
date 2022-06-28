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
//----------------------------------------------------- Méthodes publiques    
    
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
    void recursiveBuildHittingSets(HittingSet hs, map<int,int>& pairTaken, int indexInHS);
//----------------------------------------------------- Attributs protégés
    TileAlignment* tileAlign ;
    vector<HittingSet> hittingSetvect;



};

//-------------------------------- Autres définitions dépendantes de <HittingAlignment>

#endif // HittingAlignment_H

