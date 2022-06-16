/*************************************************************************
                           TileAlignment  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TileAlignment> (fichier TileAlignment.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "TileAlignment.h"
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


//-------------------------------------------- Constructeurs - destructeur

TileAlignment::TileAlignment (){
    
}


TileAlignment::TileAlignment ()
// Algorithme :
//
{
   
#ifdef MAP
    cout << "Appel au constructeur de <TileAlignment>" << endl;
#endif
} //----- Fin de TileAlignment


TileAlignment::~TileAlignment ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TileAlignment>" << endl;
#endif
} //----- Fin de ~TileAlignment


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

