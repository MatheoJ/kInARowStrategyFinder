using namespace std;

#include <iostream>
#include <set>


int main(){
    int x=1;
    for(int i=2; (i!=0 && i!=10);i+=x ){
        std::cout<<i<<std::endl;
    }
    int startIndex =0;
    int browsingWay =1;
    int wordSize =8;
    
    for(int i=(startIndex+1); (i!=-1 && i!=wordSize); i+=browsingWay){
        std::cout<<"la 1 i="<<i<<std::endl;
              
        
    }
    set<int> s;
    s.contains(2);

}

