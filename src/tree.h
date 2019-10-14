// Updated at Oct 10, 2019
// Updated by Gongchao Jing, Xiaoquan Su
// Bioinformatics Group, Single-Cell Research Center, QIBEBT, CAS
// reference built for MetaPhlAn 2

#include <iostream>
#include <sstream>
#include "utility.h"


using namespace std;

#define MAX 1000000
int lid = 0;
int iid = 0;
int oid = 0;

ofstream orderout;
ofstream idout;
ofstream distout;


#ifndef _DB_H
#define _DB_H



class Node{
      
      public:
             Node(){
                    id ="";
                    dist = 0;
                    oid = -1;
                    c1 = NULL;
                    c2 = NULL;
                    };
             Node(string _id, float _dist){
                      
                      id = _id;
                      dist = _dist;
                      oid = -1;
                      
                      c1 = NULL;
                      c2 = NULL;
                      }  
             Node(string _id, float _dist, Node * _c1, Node * _c2){
                      
                      id = _id;
                      dist = _dist;
                      oid = -1;
                      
                      c1 = _c1;
                      c2 = _c2;
                      
                      }       
             
             bool Is_leaf(){
                  
                  return ((c1 == NULL) && (c2 == NULL));
                  }
             
             bool Is_ban(){
                  
                  return (((c1 == NULL) && (c2 == NULL)) || ((c1 != NULL) && (c2 != NULL)));
                  
                  }
             
             string id;
             float dist; 
             
             int oid;                
             
             Node * c1;
             Node * c2;                      
};

class Reg{
      
      public:
             
      Reg(){
            min = 0;
            size = 0;
            //hash.clear();
            };
      
      int Get(){
          
          //cout << "min " << min << endl;
          
          int i = min;
          
          for (int i = min; i < MAX; i ++)
              if (hash.count(i) == 0){                                
                                hash.insert(i);
                                
                                if (hash.size() > size)
                                   size = hash.size();
                                
                                min = i;
                                return i;
                                }
                                     
          /*
          while(hash.count(i) != 0)
                              i ++;
          */
          
          return -1;
          }
      
      int Free(int i){                    
          
          if (hash.count(i) != 0){
             
             set<int>::iterator siter= hash.find(i);
             
             hash.erase(siter);
             
             //cout << "Free " << i << endl;
                       
             if (i < min) 
                min = i;
             }
          return 0;
        }
      
      int Size(){
          
          return size;
          
          }
      
      private:
      
      set <int> hash;
      int min;
      int size;
      };

       
#endif
