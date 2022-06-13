/*************************************************************************
                           Unit  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Unit> (fichier Unit.cpp) ------------

//---------------------------------------------------------------- INCLUDE
#include "Unit.h"
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
int Unit::getTileNumber(){
    return tileNumber;
}
    
int Unit::getUnitNumber(){
    return unitNumber;
}


//-------------------------------------------- Constructeurs - destructeur

Unit::Unit (){
    tileNumber =-1;
    unitNumber =-1;
}


Unit::Unit (int tileNb, int unitnb)
// Algorithme :
//
{
    this->unitNumber = unitnb;
    this->tileNumber = tileNb;
#ifdef MAP
    cout << "Appel au constructeur de <Unit>" << endl;
#endif
} //----- Fin de Unit


Unit::~Unit ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Unit>" << endl;
#endif
} //----- Fin de ~Unit


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

