using namespace std;

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>


void updatePos(int i, int& horizontalPos, int& verticalPos ){
    switch (i)
    {
    case 0:
        horizontalPos++;
        break;
    case 1:
        verticalPos++;
        break;
    case 2:
        horizontalPos--;
        break;
    case 3:
        verticalPos--;
        break;       
    }
}

void unUpdatePos(int i, int& horizontalPos, int& verticalPos ){
    switch (i)
    {
    case 0:
        horizontalPos--;
        break;
    case 1:
        verticalPos--;
        break;
    case 2:
        horizontalPos++;
        break;
    case 3:
        verticalPos++;
        break;       
    }
}

pair<char,char> getTempPos(int i, int horizontalPos, int verticalPos ){
    switch (i)
    {
    case 0:
        horizontalPos++;
        break;
    case 1:
        verticalPos++;
        break;
    case 2:
        horizontalPos--;
        break;
    case 3:
        verticalPos--;
        break;       
    }
    //cout<<horizontalPos<<" "<< verticalPos<<endl;
    return make_pair(horizontalPos,verticalPos);
}

void printConwayWord(map<char,int>lgth, vector<char>& currentWord){
    int i=0; 
    cout<<"A : ";
    for(; i<lgth['a']; i++){
        cout<<(int)currentWord[i]; 
    }
    cout<<" B : ";
    for(; i<lgth['a']+lgth['b']; i++){
        cout<<(int)currentWord[i]; 
    }
    cout<<" C : ";
    for(; i<lgth['a']+lgth['b']+lgth['c']; i++){
        cout<<(int)currentWord[i]; 
    }

    cout<<" Abis : ";
    for(; i<2*lgth['a']+lgth['b']+lgth['c']; i++){
        cout<<(int)currentWord[i]; 
    }

    cout<<" D : ";
    for(; i<2*lgth['a']+lgth['b']+lgth['c']+lgth['d']; i++){
        cout<<(int)currentWord[i]; 
    }

    cout<<" E : ";
    for(; i<2*lgth['a']+lgth['b']+lgth['c']+lgth['d']+lgth['e']; i++){
        cout<<(int)currentWord[i]; 
    }
    cout<<endl;
    
}

bool genOtherHalfOfPart(int iStart, int iLimit, 
                        map<char,int>lgth, 
                        vector<char>& currentWord,
                        map<pair<char, char>, bool>& pathHaveBeenHere,
                        vector<pair<char,char>>& vectPosToErase,
                        int posHorizontal, int posVertical
                        )
{
    pair<char,char> tempPos;
    bool wordOk = true;
    for (int i= iStart; i>=iLimit; i--){
        tempPos = getTempPos(currentWord[i], posHorizontal, posVertical);
        if(!(pathHaveBeenHere[tempPos]== true) && wordOk){
            updatePos(currentWord[i], posHorizontal, posVertical);
            pathHaveBeenHere[tempPos]= true;
            vectPosToErase.push_back(tempPos);
            currentWord.push_back(currentWord[i]);
        }
        else{
            wordOk = false;            
        }
    }

    return wordOk;
}

void eraseUsedPos(vector<char>& currentWord,
                    map<pair<char, char>, bool>& pathHaveBeenHere,
                    int oldSize, 
                    vector< pair<char,char> >& vectPosToErase)
{
    for(pair<char,char>& p: vectPosToErase){
        pathHaveBeenHere.erase(p);
    }
    while (currentWord.size()!=oldSize)
    {
        currentWord.pop_back();
    }
}

void genE(  map<char,int>lgth, 
            vector<char>& currentWord,
            map<pair<char, char>, bool>& pathHaveBeenHere, 
            int posHorizontal, int posVertical  )
{
    int lengthToMake = abs(posHorizontal) + abs(posVertical);    
    int numLetterToBeAssign = 2*lgth['a']+lgth['b']+lgth['c']+lgth['d']+lgth['e']- currentWord.size();
    int freeLetter = numLetterToBeAssign-lengthToMake;
    pair<char, char> tempPos;
    if (freeLetter>=0){
        int lgthWord = currentWord.size();
        pair<char, char> tempPos;        

        if(lgthWord<2*lgth['a']+lgth['b']+lgth['c']+lgth['d']+lgth['e']/2+lgth['e']%2){
            for (int i = 0; i < 4; i++)
            {
                //If it is not the first letter of the word : check that the letter to add is not the inverse off the last letter
                if(lgthWord==0 || i!=((currentWord.back()+2)%4)){
                    tempPos = getTempPos(i, posHorizontal, posVertical);
                    if(!(pathHaveBeenHere[tempPos]== true)){
                        pathHaveBeenHere[tempPos]= true; 
                        currentWord.push_back(i);
                        updatePos(i, posHorizontal, posVertical);
                        genE(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);              
                        pathHaveBeenHere.erase(tempPos);                
                        currentWord.pop_back();
                        unUpdatePos(i, posHorizontal, posVertical);
                    }                    
                }     
            }
        }
        else{
            int oldSize = currentWord.size();
            int iStart = 2*lgth['a']+lgth['b']+lgth['c']+lgth['d']+lgth['e']/2-1;
            int iLimit =2*lgth['a']+lgth['b']+lgth['c']+lgth['d'];
            vector<pair<char,char> > vectPosToErase;
            if(!genOtherHalfOfPart(iStart, iLimit, lgth, currentWord, pathHaveBeenHere, vectPosToErase, posHorizontal, posVertical)){
                lengthToMake = abs(posHorizontal) + abs(posVertical); 
                if(currentWord.size()==2*lgth['a']+lgth['b']+lgth['c']+lgth['d']+lgth['e']-1 && lengthToMake==1){
                    char c;
                    if (posHorizontal == 1){
                        c=2;
                    }
                    else if(posHorizontal == -1){
                        c=0;
                    }
                    else if(posVertical ==1 ){
                        c=3;
                    }   
                    else if(posVertical == -1){
                        c=1;
                    } 
                    currentWord.push_back(c);
                    printConwayWord(lgth, currentWord);                   
                }
            }
            eraseUsedPos(currentWord,pathHaveBeenHere,oldSize, vectPosToErase);        
        } 
    }
}   


void genD(  map<char,int>lgth, 
            vector<char>& currentWord,
            map<pair<char, char>, bool>& pathHaveBeenHere, 
            int posHorizontal, int posVertical  )
{
    int lgthWord = currentWord.size();
    pair<char, char> tempPos;

    if(lgth['d']==0){
        genE(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
    }
    else{
        if(lgthWord<2*lgth['a']+lgth['b']+lgth['c']+lgth['d']/2+lgth['d']%2){
            for (int i = 0; i < 4; i++)
            {
                //If it is not the first letter of the word : check that the letter to add is not the inverse off the last letter
                if(lgthWord==0 || i!=((currentWord.back()+2)%4)){
                    tempPos = getTempPos(i, posHorizontal, posVertical);
                    if(!(pathHaveBeenHere[tempPos]== true)){
                        pathHaveBeenHere[tempPos]= true; 
                        currentWord.push_back(i);
                        updatePos(i, posHorizontal, posVertical);
                        genD(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);              
                        pathHaveBeenHere.erase(tempPos);                
                        currentWord.pop_back();
                        unUpdatePos(i, posHorizontal, posVertical);
                    }
                    
                }     
            }
        }
        else{
            int oldSize = currentWord.size();
            int iStart = 2*lgth['a']+lgth['b']+lgth['c']+lgth['d']/2-1;
            int iLimit = 2*lgth['a']+lgth['b']+lgth['c'];
            vector<pair<char,char> > vectPosToErase;
            if(genOtherHalfOfPart(iStart, iLimit, lgth, currentWord, pathHaveBeenHere, vectPosToErase, posHorizontal, posVertical)){
                genE(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
            }
            eraseUsedPos(currentWord,pathHaveBeenHere,oldSize, vectPosToErase);       
        }    
    }
    
}



void genA_bis(map<char,int>lgth, vector<char>& currentWord,map<pair<char, char>, bool>& pathHaveBeenHere, 
        int posHorizontal, int posVertical  ){

    vector<pair<char,char>> vectPosToErase;
    bool wordOk;
    pair<char,char> tempPos;
    for(int i =  lgth['a']-1;i>=0;i--){
        char newC = (currentWord[i]+2)%4;
        tempPos = getTempPos(newC, posHorizontal, posVertical);
        if(!(pathHaveBeenHere[tempPos]== true) && wordOk){
            updatePos(newC, posHorizontal, posVertical);
            pathHaveBeenHere[tempPos]= true;
            vectPosToErase.push_back(tempPos);
            currentWord.push_back(newC);
        }
        else{
            wordOk = false;
        }
    }
    if(wordOk){
        genD(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
    }
    for(pair<char,char>& p: vectPosToErase){
        pathHaveBeenHere.erase(p);
    }
    while (currentWord.size()!=lgth['a']+lgth['b']+lgth['c'])
    {
        currentWord.pop_back();
    }   
}       



void genC(map<char,int>lgth, vector<char>& currentWord,map<pair<char, char>, bool>& pathHaveBeenHere, 
        int posHorizontal, int posVertical  ){
    int lgthWord = currentWord.size();
    pair<char, char> tempPos;

    if(lgth['c']==0){
        genA_bis(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
    }
    else{
        if(lgthWord<lgth['a']+lgth['b']+lgth['c']/2+lgth['c']%2){
            for (int i = 0; i < 4; i++)
            {
                //If it is not the first letter of the word : check that the letter to add is not the inverse off the last letter
                if(lgthWord==0 || i!=((currentWord.back()+2)%4)){
                    tempPos = getTempPos(i, posHorizontal, posVertical);
                    if(!(pathHaveBeenHere[tempPos]== true)){
                        pathHaveBeenHere[tempPos]= true; 
                        currentWord.push_back(i);
                        updatePos(i, posHorizontal, posVertical);
                        genC(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);              
                        pathHaveBeenHere.erase(tempPos);                
                        currentWord.pop_back();
                        unUpdatePos(i, posHorizontal, posVertical);
                    }
                    
                }     
            }
        }
        else{
            int oldSize = currentWord.size();
            int iStart = lgth['a']+lgth['b']+lgth['c']/2-1;
            int iLimit = lgth['a']+lgth['b'];
            vector<pair<char,char> > vectPosToErase;
            if(genOtherHalfOfPart(iStart, iLimit, lgth, currentWord, pathHaveBeenHere, vectPosToErase, posHorizontal, posVertical)){
                genA_bis(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
            }
            eraseUsedPos(currentWord,pathHaveBeenHere,oldSize, vectPosToErase);       
        }    
    }    
}

void genB(map<char,int>lgth, vector<char>& currentWord,map<pair<char, char>, bool>& pathHaveBeenHere, 
        int posHorizontal, int posVertical  ){
    int lgthWord = currentWord.size();
    pair<char, char> tempPos;
    

    if(lgthWord<lgth['a']+lgth['b']/2+lgth['b']%2){
        for (int i = 0; i < 4; i++)
        {
            //If it is not the first letter of the word : check that the letter to add is not the inverse off the last letter
            if(lgthWord==0 || i!=((currentWord.back()+2)%4)){
                tempPos = getTempPos(i, posHorizontal, posVertical);
                if(!(pathHaveBeenHere[tempPos]== true)){
                    pathHaveBeenHere[tempPos]= true; 
                    currentWord.push_back(i);
                    updatePos(i, posHorizontal, posVertical);
                    genB(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);              
                    pathHaveBeenHere.erase(tempPos);                
                    currentWord.pop_back();
                    unUpdatePos(i, posHorizontal, posVertical);
                }
                
            }     
        }
    }
    else{
        int oldSize = currentWord.size();
        int iStart = lgth['a']+lgth['b']/2-1;
        int iLimit =lgth['a'];
        vector<pair<char,char>> vectPosToErase;
        if(genOtherHalfOfPart(iStart, iLimit, lgth, currentWord, pathHaveBeenHere, vectPosToErase, posHorizontal, posVertical)){
            genC(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
        }
        eraseUsedPos(currentWord,pathHaveBeenHere,oldSize, vectPosToErase);        
    } 
}

void genA(map<char,int>&lgth, vector<char>& currentWord,map<pair<char, char>, bool>& pathHaveBeenHere, 
        int posHorizontal, int posVertical  ){
    pathHaveBeenHere[make_pair(0,0)]=true;
    int lgthWord = currentWord.size()+1;
    pair<char, char> tempPos;
    for (int i = 0; i < 4; i++)
    {
        //If it is not the first letter of the word : check that letter to add is not the inverse off the last letter
        if(lgthWord==1 || i!=((currentWord.back()+2)%4)){
            tempPos = getTempPos(i, posHorizontal, posVertical);
            if(!(pathHaveBeenHere[tempPos]== true)){
                pathHaveBeenHere[tempPos]= true; 
                currentWord.push_back(i);
                updatePos(i, posHorizontal, posVertical);
                if (lgthWord<lgth['a']){
                    genA(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical);
                }
                else{
                    genB(lgth, currentWord, pathHaveBeenHere, posHorizontal, posVertical  );
                }                
                pathHaveBeenHere[tempPos]=false;                
                currentWord.pop_back();
                unUpdatePos(i, posHorizontal, posVertical);

                /* if(lgthWord==2 && i!=((currentWord.back()))){
                cout<<"laaaaa";
                } */
            }
            
        }     
    }
}                                                                                       

void generateConWayBondaryWord(int halfPeremiter){
    int length = 2*halfPeremiter;

    for (int a=1; a<halfPeremiter;a++){
        for (int b = 1; b < (length-2*a); b++){
            for(int c=0; c< (length-2*a-b); c++){
                for(int d =0 ;d<(length-2*a-b-c); d++){
                    int e = length-2*a-b-c-d;
                    map<char,int>lgth;
                    lgth['a']=a;
                    lgth['b']=b;
                    lgth['c']=c;
                    lgth['d']=d;
                    lgth['e']=e;
                    cout<<"A= "<<a<<", B= "<<b<<", C= "<<c<<", D= "<<d<<", E= "<<e<<endl;
                    vector<char> word;
                    map<pair<char, char>, bool> pathHaveBeenHere;
                    genA(lgth,word, pathHaveBeenHere, 0,0);
                }
            }
        }
        
    }
}

int main(){

   generateConWayBondaryWord(7);
    int a =7;
    int b = 2;
    cout<<a/b;

   
}

