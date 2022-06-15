
#include "TileGenerator.h"
#include <iostream>
using namespace std;

int main(){
    
    TileGenerator tg;
    vector<char> vect;
    tg.generateBoundWord(6, vect);
    vector<BoundaryWord> vectBw = tg.getTileWordVect();
    tg.generateTile();

    vector<Tile> vectTile= tg.getTileVect();
    /* for(Tile t: vectTile){
        cout<<t;
    }  */ 


    //vectTile[vectTile.size()-1].setPlanningShapesize(10);
    cout<<vectTile[vectTile.size()-1];
    vectTile[vectTile.size()-1].buildPlanningShape(7);
    vectTile[vectTile.size()-1].printPlanningShape();

}