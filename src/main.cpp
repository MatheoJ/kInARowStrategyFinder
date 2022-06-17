
#include "TileGenerator.h"
#include "TileAnalyzer.h"
#include <iostream>
using namespace std;

int main(){
    
    TileGenerator tg;
    vector<char> vect;
    tg.generateBoundWord(4,6, vect);
    vector<BoundaryWord> vectBw = tg.getTileWordVect();
    tg.generateTile();

    tg.generateTilingShape(7);
    
    int size = tg.getTileVect().size();
    tg.getTileVect()[size-1].printPlanningShape();

    TileAna
    /* for(Tile t: vectTile){
        cout<<t;
    }  */ 


    //vectTile[vectTile.size()-1].setPlanningShapesize(10);
    
    /* BoundaryWord *bd = vectTile[38].getBoundWord();
    Tile t(bd);
    t.BuildTile();
    cout<<t; */

    //vectTile[vectTile.size()-1].buildPlanningShape(7);
    //vectTile[vectTile.size()-1].printPlanningShape();

}