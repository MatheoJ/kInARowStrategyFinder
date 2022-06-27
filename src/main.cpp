
#include "TileGenerator.h"
#include "TileAnalyzer.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
    
    int KSIZE = 7;
    int minHPer =4;
    int maxHPer =6;

    if(argc>1){
        minHPer=atoi(argv[1]);
        maxHPer= minHPer;
    }

    if(argc>2){
        KSIZE=atoi(argv[2]);        
    }

    TileGenerator tg;
    vector<char> vect;




    auto start = high_resolution_clock::now();
    tg.generateBoundWord(minHPer,maxHPer, vect);
    auto stop = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des boundary word :"<<duration.count()<<" ms"<<endl;

    start = high_resolution_clock::now();
    tg.generateTile();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des tuiles :"<<duration.count()<<" ms"<<endl;

    int nb = tg.getTileVect().size();

    start = high_resolution_clock::now();
    tg.generateTilingShape(KSIZE);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des formes de pavages :"<<duration.count()<<" ms"<<endl;


    start = high_resolution_clock::now();
    TileAnalyzer ta(KSIZE);
    int count = ta.analyzeTileVect(tg.getTileVect());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des alignements :"<<duration.count()<<" ms"<<endl;
    cout<<endl;
    cout<<"Nombre pavages traités: "<<nb<<endl;
    cout<<"Nombre de pavages gardés aprés analyse de leurs traces: "<<count<<endl;
    cout<<"________________________________________________________"<<endl;

 
    cout<<*(ta.getVectTileAlignment()[89].getTile())<<endl;
    cout<<(ta.getVectTileAlignment()[89])<<endl;


    cout<<*(ta.getVectTileAlignment()[1426].getTile())<<endl;
    cout<<(ta.getVectTileAlignment()[1426])<<endl;

    cout<<*(ta.getVectTileAlignment()[694].getTile())<<endl;
    cout<<(ta.getVectTileAlignment()[694])<<endl;

    cout<<*(ta.getVectTileAlignment()[962].getTile())<<endl;
    cout<<(ta.getVectTileAlignment()[962])<<endl;  
     

    
    
}

