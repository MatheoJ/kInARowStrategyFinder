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
int TileAnalyzer::analyzeTileVect(vector<Tile>& vectTile ){
    for(int i =0; i<(int)vectTile.size(); i++){
        TileAlignment ta(&vectTile[i]);
        if(ta.buildAlignments(sizeAlignment)){            
            ta.eraseDuplicatesInAllDirection();
            ta.eraseSubsetAlignment();
            ta.eraseDuplicatesInAllDirection();
            if(ta.cleanWithRule()){
                vectTileAlignment.push_back(ta);
            }
                 
            if(vectTile[i].getId()==2263){
                cout<<vectTile[i]<<endl;
                cout<<ta<<endl;
            }            
        }
    }
    return vectTileAlignment.size();    
}

vector<TileAlignment>& TileAnalyzer::getVectTileAlignment(){
    return this->vectTileAlignment;
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

