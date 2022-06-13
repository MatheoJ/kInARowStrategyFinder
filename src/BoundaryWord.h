/*************************************************************************
                           BoundaryWord  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <BoundaryWord> (fichier BoundaryWord.h) ----------------
#if ! defined ( BoundaryWord_H )
#define BoundaryWord_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <BoundaryWord>
//
//
//------------------------------------------------------------------------

class BoundaryWord 
{
    
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    friend class Tile;
    friend ostream &operator<<(ostream &stream, const BoundaryWord &bw);

    bool isSelfAvoiding();

    int getMaxHorizontal();
    int getMinHorizontal();
    int getMaxVertical();
    int getMinVertical();



//-------------------------------------------- Constructeurs - destructeur
    
    BoundaryWord (vector<char>& firstHalf, vector<char>& otherHalf,int xSize,int ySize,int Zsize);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~BoundaryWord ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<char>  word;
    int xSize;
    int ySize;
    int zSize;
    int maxHorizontal; 
    int minHorizontal;
    int maxVertical;
    int minVertical;


};

//-------------------------------- Autres définitions dépendantes de <BoundaryWord>

#endif // BoundaryWord_H

