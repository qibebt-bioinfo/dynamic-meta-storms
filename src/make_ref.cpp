// Updated at Oct 14, 2019
// Updated by Gongchao Jing, Xiaoquan Su
// Bioinformatics Group, Single-Cell Research Center, QIBEBT, CAS
// reference built for MetaPhlAn 2

#include <fstream>
#include <set>
#include <stdlib.h>
#include <map>

#include "version.h"
#include "utility.h"
#include "tree.h"

//#define OFFSET MAX
#define OFFSET 70

using namespace std;

string tree_file;
string taxo_file;
string ref_name = "tree";



int printhelp(){
    
    cout << "MS-make-ref version : " << Version << endl;
    cout << "\tMake customized reference for dynamic-meta-storms" << endl;
    cout << "Usage: " << endl;
    cout << "MS-make-ref [Option] Value" << endl;
    cout << "Options: " << endl;
    
    cout << "\t[Input options, required]" << endl;
    cout << "\t  -i Input tree file (newick format)" << endl;
    cout << "\t  -r Input taxonomy annotation file (tabular format)" << endl;
    
    cout << "\t[Output options]" << endl;
     cout << "\t  -o Output reference name, default is \"tree.dms\" "<< endl;
    
    
    cout << "\t  -h Help" << endl;
    
    exit(0);
    
    return 0;
    
    };
    
int Parse_Para(int argc, char * argv[]){
    
    
    
    int i = 1;
      
      if (argc ==1) 
		printhelp();
      
      while(i<argc){
         if (argv[i][0] != '-') {
                           cerr << "Argument # " << i << " Error : Arguments must start with -" << endl;
                           exit(0);
                           };           
         switch(argv[i][1]){
                            
                 
                            case 'i': tree_file = argv[i+1]; break;
                            case 'r': taxo_file = argv[i+1]; break;
							
			    case 'o': ref_name = argv[i+1]; break;         
                            case 'h': printhelp(); break;
                            default : cerr << "Error: Unrec argument " << argv[i] << endl; printhelp(); break; 
                            }
         i+=2;
         }
    
    }

string Read(const char * infilename){
       
       ifstream infile(infilename, ifstream::in);
       if (!infile){
                    
                    cerr << "Cannot openfile : " << infilename << endl;
                    exit(0);
                    
                    }
       
       string buffer;
       
       getline(infile, buffer);
       
       infile.close();
       infile.clear();
       
       return buffer;
       
       }

Node * Make_Tree(string tree_file, int & pos){
     
     
     if (tree_file[pos]!='('){//Leaf node
                           
                           int end = pos + 1;
                           while((tree_file[end]!= ':')&&(tree_file[end]!=',')&&(tree_file[end]!=')')&&(end < tree_file.size()))
                                           end ++;
                           //int id = atoi(tree_file.substr(pos, end-pos).c_str());
                           string id = tree_file.substr(pos, end-pos).c_str();
         
                           pos = ++ end;
                           
                           float dist = 0;
                           
                           if (tree_file[end - 1] == ':'){                                              
                                               while((tree_file[end] != ':')&&(tree_file[end]!=',')&&(tree_file[end]!=')')&&(end < tree_file.size()))
                                                                       end ++;
                                               dist = atof(tree_file.substr(pos, end-pos).c_str());
                                               if (dist >= 1) dist = 0.99;
                                              }
                           //return pos;
 
                           Node * current = new Node(id, dist);
                           
                           lid ++;
                           
                           pos = ++ end;
                           
                           return current;
                           
                           }
     
     else  if (tree_file[pos] == '('){
                              
          pos ++;
          
          Node * c1 = Make_Tree(tree_file, pos);
          
          //pos ++;
          
          Node * c2 = Make_Tree(tree_file, pos);
          
          while ((tree_file[pos] != ':') && (pos < tree_file.size()))
                pos ++;
          
          int end = ++ pos;
          
          float dist = 0;
          
          if (tree_file[end-1] == ':'){                                              
                                               while((tree_file[end]!=':')&&(tree_file[end]!=',')&&(tree_file[end]!=')')&&(end < tree_file.size()))
                                                                       end ++;
                                               dist = atof(tree_file.substr(pos, end-pos).c_str());
                                               if (dist >= 1) dist = 0.99;
                                              }
         
         
          char iid_char[10];
          sprintf(iid_char, "%d", iid);
          string iid_str = iid_char;
          Node * current = new Node(iid_str, dist, c1, c2);
          iid ++;
         
          pos = ++ end;
          
          return current;
          }
          
     else return NULL;
     }

Node * Trav(Node * node, Reg & reg){
    
    if (node == NULL) return NULL;
    
    if (!(node->Is_ban()))
                        cerr << "Im ban : " << node->id << endl; 
    
    if (node->Is_leaf()){
                     
                     idout << node->id << endl;
                     
                     // node->oid = node->id;
                     
                     node->oid = oid ++;

                     return node;
                     }
    else {
         
         Node * c1 = Trav(node->c1, reg);
         Node * c2 = Trav(node->c2, reg);
         
         //orderout << c1->oid << "\t" << c2->oid << "\t";
         //distout << c1->dist << "\t" << c2->dist << endl;
         
         if (c1->oid < 0) reg.Free( c1->oid + OFFSET);
         if (c2->oid < 0) reg.Free( c2->oid + OFFSET);
         
         //int current_id = reg.Get();         
         int current_id = reg.Get() - OFFSET;
         
         node->oid = current_id;
         
         //orderout << " -> " << current_id  << endl;
         
         orderout << c1->oid << "\t" << c1->dist << "\t" << c2->oid << "\t" << c2->dist << "\t" << current_id << endl;
         
         return node;
         }
    
    return NULL;
    }

void output_id_order(){
	
    int pos = 0;
    Reg reg;
    char command[BUFFER_SIZE];
    string out_ref_name = ref_name + ".dms";
    /*
    sprintf(command, "mkdir %s", out_ref_name.c_str());
    system(command);
    
    sprintf(command, "mkdir %s/tree", out_ref_name.c_str());
    system(command);
    */
    
    Check_Path(out_ref_name.c_str(), 1);
    Check_Path((out_ref_name + "/tree").c_str(), 1);
    
    sprintf(command, "Rscript %s/Rscript/config.R", Check_Env().c_str());
    system(command);


    sprintf(command, "Rscript %s/Rscript/MS_new_tree.R -i %s -o %s", Check_Env().c_str(), tree_file.c_str(), (out_ref_name + "/tree/" + "tree.nwk").c_str());
    system(command);

    string tree_file2 = Read((out_ref_name  + "/tree/tree.nwk").c_str());
    Node * root = Make_Tree(tree_file2, pos);
    
    cout << lid << " leaf nodes in total" << endl;
    cout << iid << " intern nodes in total" << endl;
 
    string database_path = out_ref_name + "/tree/" ;
   
    orderout.open((database_path+"order.txt").c_str(), ofstream::out);
    idout.open((database_path+"id.txt").c_str(), ofstream::out);
    //distout.open((database_path+"dist.txt").c_str(), ofstream::out);
    
    Trav(root, reg);
    
    cout << oid << " leaf nodes in total" << endl;
    cout << reg.Size() << " intern reg used" << endl;
    
    orderout.close();
    orderout.clear();
    
    idout.close();
    idout.clear();
    
    //distout.close();
    //distout.clear();
 
	
} 

void output_id_taxon(){
	ifstream infile(taxo_file.c_str(), ios::in);
	if(!infile){
		cerr << "Cannot openfile : " << taxo_file << endl;
        exit(0);
	}
	string buffer;
	string species_name;
	string out_ref_name = ref_name + ".dms";
	string taxo_path = out_ref_name + "/taxonomy_annotation.txt";
	ofstream outfile_taxo(taxo_path.c_str(), ios::out);
	if(!outfile_taxo){
		cerr << "Cannot openfile : " << taxo_path << endl;
        exit(0);
	}
	map<string, string> map_taxo;
	getline(infile, buffer);
	outfile_taxo << "Species\tKingdom\tPhylum\t\tClass\t\t\tOrder\t\t\tFamily\t\tGenus\t\t\tSpecies"<< endl;
	while(getline(infile, buffer)){
		string name_temp;
		stringstream str_buf(buffer);
		string temp;
	    temp = "";
	    string temp_total = "";
		str_buf >> name_temp;
		temp_total += name_temp;
		for(int i = 0; i < 5; i++){
			str_buf >> name_temp;
			temp_total += "\t";
			temp_total += name_temp;
			name_temp = name_temp.substr(3, name_temp.size()-3);
			temp += name_temp + "\t";
		}
		str_buf >> species_name;
		temp_total += "\t";
		temp_total += species_name;
		temp_total = species_name + "\t" + temp_total; 
		map_taxo[species_name] = temp; 
		outfile_taxo << temp_total << endl;
	}
	
	string id_path = out_ref_name + "/tree/id.txt";
	ifstream infile_id(id_path.c_str(), ios::in);
	if(!infile_id){
		cerr << "Cannot openfile : " << id_path << endl;
        exit(0);
	}
	
	string outfile_name = out_ref_name + "/tree/id_taxon.txt";
	ofstream outfile(outfile_name.c_str(), ios::out);
	if(!infile_id){
		cerr << "Cannot openfile : " << outfile_name << endl;
        exit(0);
	}
	
	while(getline(infile_id, buffer)){
		outfile << map_taxo[buffer] << endl;
	}
	
	 
	
	infile.close();
	infile_id.close();
	outfile.close();
	outfile_taxo.close();
}



int main(int argc, char * argv[]){
    
    Parse_Para(argc, argv);  
    output_id_order();
    output_id_taxon();            
    
    return 0;
    }
