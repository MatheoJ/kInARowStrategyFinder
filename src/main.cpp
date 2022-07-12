
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

