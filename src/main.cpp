
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
    cout<<"Nombre de threads utilisés : "<<num_threads<<endl;

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
    cout<<"Nombre de boundary word :"<<tg.getTileWordVect().size()<<endl;

    startTimeMeasurment();   
    ThreadPool* pool = new ThreadPool(num_threads);
    TileAnalyzer *ta = new TileAnalyzer (KSIZE);
    ta->analyzeBwVectMemorySave(tg.getTileWordVect(), pool, KSIZE);
    delete pool;   
    cout<<"Analyse des tuiles :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<"Nombre de tuiles Gagnantes :"<<ta->getNumValidTile()<<endl;
    cout<<"Nombre de boundary word restant:"<<tg.getTileWordVect().size()<<endl;
    cout<<"________________________________________________________"<<endl;
    delete ta;


    /* ==============================Pour ne PAS STCOKER LES BOUNDARY WORD========================*/

    /* startTimeMeasurment();   
    ThreadPool* pool = new ThreadPool(num_threads);
    TileAnalyzer *ta = new TileAnalyzer (KSIZE);
    tg.generateAndAnalyzeBoundWord(minHPer,maxHPer, vect, pool, KSIZE, ta);
    delete pool;    
    cout<<"Analyse des tuiles :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<"Nombre de tuiles Gagnantes :"<<ta->getNumValidTile()<<endl;
    cout<<"________________________________________________________"<<endl;
    delete ta; */

    /* HittingSetFinal hsf;
    hsf.push_back(vector<int> {6, 11, 13, 16});
    hsf.push_back(vector<int> {5, 12, 14, 15 });
    hsf.push_back(vector<int> {0, 1 ,2, 3 });
    hsf.push_back(vector<int> {7, 8, 9, 10});
    hsf.push_back(vector<int> {0, 10, 11, 12 });
    hsf.push_back(vector<int> {1, 9, 13, 14});
    hsf.push_back(vector<int> {2, 8, 15, 16});
    hsf.push_back(vector<int> {3, 5, 6, 7});
    hsf.push_back(vector<int> {2, 11, 14});
    hsf.push_back(vector<int> {13, 15});
    hsf.push_back(vector<int> {5, 9, 16 });
    hsf.push_back(vector<int> {1, 6, 15});
    hsf.push_back(vector<int> {14, 16 });
    hsf.push_back(vector<int> {8, 12, 13});

    GameSolver gs;
    cout<<"le hs est :"<<gs.solveHittingSet(hsf)<<endl; */


    /* startTimeMeasurment();
    tg.generateBoundWord(minHPer,maxHPer, vect);

    cout<<"Génération des boundary word :"<<stopTimeMeasurment().count()<<" ms"<<endl;


    startTimeMeasurment();
    tg.generateTile();
    int nb = tg.getTileVect().size();

    cout<<"Génération des tuiles :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<"Nombre de tuiles :"<<nb<<endl;

    

    startTimeMeasurment();
    tg.generateTilingShape(KSIZE);

    cout<<"Génération des formes de pavages :"<<stopTimeMeasurment().count()<<" ms"<<endl;

    startTimeMeasurment();
    TileAnalyzer ta(KSIZE);    
    ThreadPool* pool = new ThreadPool(num_threads);
    ta.analyzeTileVectMemorySave(tg.getTileVect(), pool);
    delete pool;
    cout<<"Analyse des tuiles :"<<stopTimeMeasurment().count()<<" ms"<<endl;
    cout<<"Nombre de tuiles Gagnantes :"<<ta.getNumValidTile()<<endl;
    cout<<"________________________________________________________"<<endl;
 */
    /*
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
    cout<<"Nombre de tuiles Gagnantes :"<<ta.getValidHittingAlignment().size()<<endl;  */

 
   
} 

