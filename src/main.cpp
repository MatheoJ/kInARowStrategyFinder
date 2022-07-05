
#include "TileGenerator.h"
#include "TileAnalyzer.h"
#include "HittingAlignment.h"
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

 

    start = high_resolution_clock::now();
    count = ta.buildHittingset();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    cout<<"Nombre de hitting sets: "<<count<<endl;
    cout<<"________________________________________________________"<<endl;  

    start = high_resolution_clock::now();
    ta.solveGame();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl; 
    cout<<"Vérification de tuiles Gagnantes :"<<duration.count()<<" ms"<<endl; 

 
    /* start = high_resolution_clock::now();
    HittingAlignment ha3(&ta.getVectTileAlignment()[89]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha3.eraseDuplicatesOnHittingSets();
    //cout<< ha3;  

    start = high_resolution_clock::now();
    GameSolver gs3(&ha3);
    gs3.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl;
*/
     

/*     start = high_resolution_clock::now();
    //cout<<ta.getVectTileAlignment()[794];
    HittingAlignment ha(&ta.getVectTileAlignment()[794]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha.eraseDuplicatesOnHittingSets();
    //cout<< ha; 
    
    start = high_resolution_clock::now();
    GameSolver gs(&ha);
    gs.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl; */

    //-----------------------------------------------------------------------------

    /* start = high_resolution_clock::now();
    //cout<<ta.getVectTileAlignment()[794];
    HittingAlignment ha5(&ta.getVectTileAlignment()[894]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha5.eraseDuplicatesOnHittingSets();
    //cout<< ha; 
    
    start = high_resolution_clock::now();
    GameSolver gs5(&ha5);
    gs5.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl; */
     
    /* start = high_resolution_clock::now();
    //cout<<ta.getVectTileAlignment()[1645];
    HittingAlignment ha2(&ta.getVectTileAlignment()[1645]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha2.eraseDuplicatesOnHittingSets();
    cout<< ha2;


     start = high_resolution_clock::now();
    GameSolver gs2(&ha2);
    gs2.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl; */

     
    ///-----------------------------------------------------TILE VALID POUR 9 --------------------------------------------------------------------------//

    /* start = high_resolution_clock::now();
    HittingAlignment ha4(&ta.getVectTileAlignment()[454]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha4.eraseDuplicatesOnHittingSets();
    cout<< ha4; 

     start = high_resolution_clock::now();
    GameSolver gs4(&ha4);
    gs4.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl;


    start = high_resolution_clock::now();
    HittingAlignment ha7(&ta.getVectTileAlignment()[1645]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Génération des hittings sets :"<<duration.count()<<" ms"<<endl;
    ha4.eraseDuplicatesOnHittingSets();
    cout<< ha7; 

    start = high_resolution_clock::now();
    GameSolver gs7(&ha7);
    gs7.solveHittingAlignment();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"Vérification des hittingset Gagnants :"<<duration.count()<<" ms"<<endl;
 */
    
   
} 

