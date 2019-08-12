// Updated at July 31, 2019
// Bioinformatics Group, Single-Cell Research Center, QIBEBT, CAS
// Updated by Xiaoquan Su
// For MetaPhlAn2 sp table

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stdlib.h>

#include "table_format.h"
#include "utility.h"
#include "version.h"

using namespace std;

string Infilename;
string Outpath;
string Outprefix;
bool Reverse_table = false;

int Output_Single_Format(const char * outfilename, vector <string> sp, vector <float> abd){
    
    ofstream outfile(outfilename, ios::out);
    if(!outfile){
                 cerr << "Error: Cannot open output file: " << outfilename << endl; 
                 return 0;                
                 }
    
    outfile << "#Species output" << endl;
    
    int count = 0;
    
    for (int i = 0; i < sp.size(); i ++)
        if (abd[i] > 0){
           outfile << sp[i] << "\t" << abd[i] << endl;
           count ++;
           }
    
    outfile.close();
    outfile.clear();
    
    return count;
    }

void Gen_Single_Format(){
     
    _Table_Format sp_table(Infilename.c_str(), Reverse_table); 
    
    vector <string> sp = sp_table.Get_Feature_Names();
    vector <string> samples = sp_table.Get_Sample_Names();
    
    string sample_list = Outpath + ".Single_Sample.list";
    
    ofstream outfile(sample_list.c_str(), ios::out);
    if(!outfile){
                 cerr << "Error: Cannot open output file: " << sample_list << endl; 
                 return;                
                 }
    
    
    for (int i = 0; i < sp_table.Get_Sample_Size(); i ++){
        
        vector <float> abd = sp_table.Get_Abd(i);
        Check_Path(Outpath.c_str(), 1);
        string outfilename = Outpath + "/" + Outprefix + samples[i] + ".sp.out";
        
        int count = Output_Single_Format(outfilename.c_str(), sp, abd);
        
        outfile << samples[i]  << "\t" << outfilename << endl;
        cout << samples[i] << ":\t" << count << " taxa" << endl;
        }
    
    outfile.close();
    outfile.clear();
    
    cout << sp_table.Get_Sample_Size() << " Samples output" << endl;
    }

void printhelp(){
    
    cout << "Table2single version: " << Version << endl;
    cout << "\tSplit table to single files" << endl;
    cout << "Usage : " << endl;
    cout << "MS-table-to-single [-option] value" << endl;
    cout << "\toption : " << endl;
   
    cout << "\t[Input options, required]" << endl;
    cout << "\t  -i or -T Input species table [Required]" << endl;
    cout << "\t  -R If the input table is reversed, T(rue) or F(alse), default is false [Optional]" << endl;
    
    cout << "\t[Output options]" << endl;
    cout << "\t  -o Output file directory, default is \"result\"" << endl;
    cout << "\t  -p Prefix name of output"<<endl;
    
    cout << "\t[Other options]" << endl;
    cout << "\t  -h Help" << endl;
    
    exit(0);
}

void Parse_Para(int argc, char *argv[]){
     Outpath = "result";
     int i = 1;
     if (argc == 1) printhelp();
     while (i<argc){
           if (argv[i][0] != '-'){
              cout << "Argument ::" << i;
              cout <<" Error : Arguments must start with -\n"<<endl;
              exit(0);
              }
           switch (argv[i][1]){
                  case 'i': 
                  case 'T': Infilename  =argv[i+1];break;
                  case 'R': if ((argv[i+1][0] == 't') || (argv[i+1][0] == 'T')) Reverse_table = true; break;
                  case 'o': Outpath = argv[i+1];break;
                  case 'p': Outprefix = argv[i+1]; break;           
                  case 'h': printhelp();
                  }
                  i+=2;
          }
     Check_Path(Outpath.c_str(), 1);
          return;
}

int main(int argc, char * argv[]){
    
    Parse_Para(argc, argv);
        
    Gen_Single_Format();
            
    return 0;
    }
