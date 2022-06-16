
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
    cout<<vectTile[38];
    vectTile[38].fillTile(6);
    cout<<vectTile[38];
    /* BoundaryWord *bd = vectTile[38].getBoundWord();
    Tile t(bd);
    t.BuildTile();
    cout<<t; */

    //vectTile[vectTile.size()-1].buildPlanningShape(7);
    //vectTile[vectTile.size()-1].printPlanningShape();

}