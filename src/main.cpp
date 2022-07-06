
#include "TileGenerator.h"
#include "TileAnalyzer.h"
#include "HittingAlignment.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


auto start = high_resolution_clock::now(); 


auto stop = high_resolution_clock::now(); 


void startTimeMeasurment(){
    start = high_resolution_clock::now();
}

std::chrono::duration<double, std::milli> stopTimeMeasurment(){
    stop = high_resolution_clock::now();
    
    return duration_cast<microseconds>(stop - start);
}




int main(int argc, char** argv){
    
    int KSIZE = 7;
    int minHPer =4;
    int maxHPer =6;

    const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports

    if(argc>1){
        minHPer=atoi(argv[1]);
        maxHPer= minHPer;
    }

    if(argc>2){
        KSIZE=atoi(argv[2]);        
    }

    TileGenerator tg;
    vector<char> vect;


    startTimeMeasurment();
    tg.generateBoundWord(minHPer,maxHPer, vect);

    cout<<"Génération des boundary word :"<<stopTimeMeasurment().count()<<" ms"<<endl;


    startTimeMeasurment();
    tg.generateTile();

    cout<<"Génération des tuiles :"<<stopTimeMeasurment().count()<<" ms"<<endl;

    int nb = tg.getTileVect().size();

    startTimeMeasurment();
    tg.generateTilingShape(KSIZE);

    cout<<"Génération des formes de pavages :"<<stopTimeMeasurment().count()<<" ms"<<endl;


    startTimeMeasurment();
    TileAnalyzer ta(KSIZE);
    int count = ta.analyzeTileVect(tg.getTileVect());

    cout<<"Génération des alignements :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<endl;
    cout<<"Nombre pavages traités: "<<nb<<endl;
    cout<<"Nombre de pavages gardés aprés analyse de leurs traces: "<<count<<endl;
    cout<<"________________________________________________________"<<endl;

 

    startTimeMeasurment();
    ThreadPool* poolHs = new ThreadPool(num_threads);
    ta.buildHittingset(poolHs);
    delete poolHs;
    cout<<"Génération des hittings sets :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<"Nombre de hitting sets: "<<ta.countHittingSets()<<endl;
    cout<<"________________________________________________________"<<endl;  

    startTimeMeasurment();    
    ThreadPool* poolSolveGame = new ThreadPool(num_threads);
    ta.solveGame(poolSolveGame);
    delete poolSolveGame;
    cout<<endl<<"Vérification des hittingset Gagnants :"<<stopTimeMeasurment().count()<<" ms"<<endl; 
    cout<<"Nombre de tuiles Gagnantes :"<<ta.getValidHittingAlignment().size()<<endl; 

 
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

