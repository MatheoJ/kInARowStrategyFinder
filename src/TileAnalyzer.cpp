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
                 
            if(vectTile[i].getId()==2263 || vectTile[i].getId()==10060){
                cout<<vectTile[i]<<endl;
                cout<<ta<<endl;
                cout<<"index dans vectTileAlignment : "<<vectTileAlignment.size()-1<<endl;
            }  
                       
        }
    }
    return vectTileAlignment.size();    
}

int TileAnalyzer::buildHittingset(){
    int count = 0 ;
    int count0 = 0;
    for(TileAlignment& ta : vectTileAlignment){
        vectHittingAlignment.emplace_back(&ta);        
        vectHittingAlignment.back().eraseDuplicatesOnHittingSets();

        count+= vectHittingAlignment.back().hittingSetvect.size();
        if (vectHittingAlignment.back().hittingSetvect.size()==0){
            count0++;            
        }
        
        /* if (ta.getTile()->getId()==475){
            cout << vectHittingAlignment.back()<<endl;
        } */
            
    }
    cout<<"Il y a "<< count0<< " pavages qui n'ont pas de hitting set"<<endl;
    return count;
}

vector<TileAlignment>& TileAnalyzer::getVectTileAlignment(){
    return this->vectTileAlignment;
}

vector<HittingAlignment*>& TileAnalyzer::getValidHittingAlignment(){
    return this->validHittingAlignment;
}

void  TileAnalyzer::solveGame(){
    for(HittingAlignment&  ha :vectHittingAlignment ){
        GameSolver gs(&ha);
        if(gs.solveHittingAlignment()){
            validHittingAlignment.push_back(&ha);
            cout<<ha;
        }
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

