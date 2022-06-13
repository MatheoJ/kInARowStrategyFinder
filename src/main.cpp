
#include "TileGenerator.h"
#include <iostream>
using namespace std;

int main(){
    string s ="test";
    s+= 1;
    cout<<s;
    TileGenerator tg;
    vector<char> vect;
    tg.generateBoundWord(6, vect);
    vector<BoundaryWord> vectBw = tg.getTileWordVect();
    for(int i =0; i<(int)tg.getTileWordVect().size(); i++){
        Tile t(&vectBw[i]);
        cout<<t;
    }
    

}