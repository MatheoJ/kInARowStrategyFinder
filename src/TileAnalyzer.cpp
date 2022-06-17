/*************************************************************************
                           TileAnalyzer  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TileAnalyzer> (fichier TileAnalyzer.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "TileAnalyzer.h"
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void TileAnalyzer::analyzeTileVect(vector<Tile>& vectTile){
    for(int i =0; i<(int)vectTile.size(); i++){
        TileAlignment ta(&vectTile[i], sizeAlignment);
        vectTileAlignment.push_back(ta);        
    }
}

//-------------------------------------------- Constructeurs - destructeur



TileAnalyzer::TileAnalyzer (int sizeAlignment)
// Algorithme :
//
{
    this->sizeAlignment=sizeAlignment;
    
#ifdef MAP
    cout << "Appel au constructeur de <TileAnalyzer>" << endl;
#endif
} //----- Fin de TileAnalyzer


TileAnalyzer::~TileAnalyzer ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TileAnalyzer>" << endl;
#endif
} //----- Fin de ~TileAnalyzer


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
