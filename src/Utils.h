/*************************************************************************
                           Unit  -  description
                             -------------------
    début                : 09/06/2022
    e-mail               : matheo.joseph@insa-lyon.fr
*************************************************************************/

#if ! defined ( Utils_H )
#define Utils_H

#include <vector>

class Utils 
{
//----------------------------------------------------------------- PUBLIC


public:
    template <typename T>
    static void eraseDuplicates(std::vector<std::vector<T>> & vecOfElements)
    {
        std::map<std::vector<T>, bool> countMap;
    
        // Remove the elements from Map which has 1 frequency count
        for (auto it = vecOfElements.begin() ; it != vecOfElements.end() ;)
        {
            sort((*it).begin(),(*it).end());
            if (countMap.contains(*it))
                it = vecOfElements.erase(it);
            else{
                countMap[*it]=true;
                it++;
            }
                
        }

    } 
   

protected:
    

};
#endif 

