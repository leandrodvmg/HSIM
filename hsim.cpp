/* L. Galvão and L. Merschmann. HSIM: A Supervised Imputation Method for Hierarchical Classification Scenario.
In International Conference on Discovery Science. */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <sstream>

using namespace std;

char easytolower(char in){
  return tolower(in);
}

static inline std::string &str_lower(std::string &data) {
        transform(data.begin(), data.end(), data.begin(), easytolower);
        return data;
}

vector<string> explode(string str, char delimiter){				
	vector<string> out;
	size_t found = str.find(delimiter);
	while(found != string::npos){
		string sub_str = str.substr(0,found);		
		out.push_back(sub_str);
		str = str.substr(found+1);		
		found = str.find(delimiter);
	}
	// add the last one
	out.push_back(str);			
	return out;
}

int in_array_string(string v_class, vector< string > &f_class){
	for(unsigned int j=0; j < f_class.size(); ++j){
		if(v_class.compare(f_class[j]) == 0){
			return j;
		}
	}
	
	return -1;
}

int in_array(double value, vector< double > &v_value){
	for(unsigned int j=0; j < v_value.size(); ++j){
		if(value == v_value[j]){
			return j;
		}
	}
	
	return -1;
}

bool is_descendant(string classA, string classB){
	if(classA.find(classB) == 0) return true;
	return false;
}

bool is_ascendant(string classA, string classB){
	if(classB.find(classA) == 0) return true;
	return false;
}

double mode(vector< double > v_values){
	vector< double > v_distinct, f_distinct;
	int position;
	
	for(unsigned int k = 0; k < v_values.size(); ++k){		
		position = in_array(v_values[k], v_distinct);
		if(position == -1){
			v_distinct.push_back(v_values[k]);
			f_distinct.push_back(1);
		} else {
			f_distinct[position]++;
		}
	}
	
	double max = LONG_MIN;
	int id;
	for(unsigned int k = 0; k < f_distinct.size(); ++k){
		if(f_distinct[k] > max){
			max = f_distinct[k];
			id = k;
		}
	}
		
	return v_distinct[id];
}

int main(int argc, char *argv[]) {
	
	unsigned int opt;  	
	string input_file;
	string output_file;		
	
	while((opt = getopt(argc, argv, "i:o:")) != EOF){
		switch(opt)
		{  
			 case 'i': input_file = optarg; break;
			 case 'o': output_file = optarg; break;         
			 default: fprintf(stderr, "Usage: -i [Name of input file]\t -o [Name of output file]\n"); return (1);
		}
	}
	
	if(argc != 5){
		fprintf(stderr, "Usage: -i [Name of input file]\t -o [Name of output file]\n");
		return (1);
	}		

	ifstream file(input_file.c_str());	
    string str,line;  
        
    vector< vector< double > >  data, new_data;
    vector< string > a_class, dist_class;
    vector< int > numeric_attr;
    string header = "", attr_class = "";
    
    getline(file, str);
    str_lower(str);
    while(str.find("@data") == string::npos)
    {
		if(str.find("@attribute class") != string::npos){
			attr_class = str;
			while(str.find("@data") == string::npos){
				getline(file, str);
				str_lower(str);
			}
			break;
		}
			
		if(str.find("@attribute") != string::npos){
			if(str.find("numeric") != string::npos){
				numeric_attr.push_back(1);
			} else {
				numeric_attr.push_back(0);
			}
		}
		
		header = header + str + "\n";
		getline(file, str);
		str_lower(str);
	}
	
    while(getline(file, str))
    {
		
		if(!str.empty()){
			vector< double > v_value;
			vector< string > v_str = explode(str,',');
			int tam = v_str.size();
			for(int i = 0; i < (tam-1); ++i){
				if(v_str[i].compare("?") != 0)
					v_value.push_back(atof(v_str[i].c_str()));
				else
					v_value.push_back(DBL_MAX);
			}
					
			string classe = v_str[tam-1];
			if(in_array_string(classe, dist_class) == -1){
				dist_class.push_back(classe);
			}
			
			a_class.push_back(classe);
			data.push_back(v_value);			
		}
	
    }
    
    file.close();	
	
	new_data = data;
		
	int num_att = data[0].size(), num_inst = data.size();	
	for(int j = 0; j < num_att; ++j){
		vector< string > impute_class;
		vector< double > impute_value;			
		for(int i = 0; i < num_inst; ++i){
			if(data[i][j] == DBL_MAX){
				vector< double > equal, descendant, ascendant, different;				
				int pos = in_array_string(a_class[i], impute_class);
				if(pos == -1){
					for(int k = 0; k < num_inst; ++k){
						if(i != k){							
							if(data[k][j] != DBL_MAX){								
								if(a_class[k].compare(a_class[i]) == 0){									
									equal.push_back(data[k][j]);
								} else if(is_descendant(a_class[k],a_class[i])){									
									descendant.push_back(data[k][j]);
								} else if(is_ascendant(a_class[k],a_class[i])){
									ascendant.push_back(data[k][j]);
								} else {									
									different.push_back(data[k][j]);
								}
							}							
						}						
					}
					
					if(equal.size() || descendant.size() || ascendant.size() || different.size()){
						if(numeric_attr[j]){
							double mean = 0;
							if(equal.size() > 0){						
								for(unsigned int m=0; m < equal.size(); ++m){
									mean += equal[m];
								}
								mean = (mean/equal.size());
							} else if(descendant.size() > 0){
								for(unsigned int m=0; m < descendant.size(); ++m){
									mean += descendant[m];
								}
								mean = (mean/descendant.size());
							}  else if(ascendant.size() > 0){
								for(unsigned int m=0; m < ascendant.size(); ++m){
									mean += ascendant[m];
								}
								mean = (mean/ascendant.size());
							} else {
								for(unsigned int m=0; m < different.size(); ++m){
									mean += different[m];
								}
								mean = (mean/different.size());
							}
							
							impute_class.push_back(a_class[i]);
							impute_value.push_back(mean);
							new_data[i][j] = mean;
						} else {
							double mode_value;
							if(equal.size() > 0){						
								mode_value = mode(equal);								
							} else if(descendant.size() > 0){
								mode_value = mode(descendant);
							} else if(ascendant.size() > 0){
								mode_value = mode(ascendant);
							} else {
								mode_value = mode(different);
							}
							
							impute_class.push_back(a_class[i]);
							impute_value.push_back(mode_value);
							new_data[i][j] = mode_value;
						}
						
					} else {						
						cout << "All values of attribute " << j << " are missing.\n Method do not support this scenario\n";												
					}
				} else {										
					new_data[i][j] = impute_value[pos];
				}
			}
		}			
	}		
	
	ofstream file2;		
	file2.open(output_file.c_str());
		
	header = (header + attr_class + "\n@data\n");
	file2 << header;	
	for(int i = 0; i < num_inst; ++i){
		string v_line = "";		
		for(int j = 0; j < num_att; ++j){							
			ostringstream num_str;
			num_str << new_data[i][j];
			v_line = v_line + num_str.str() +  ",";						
		}	
		v_line = v_line + a_class[i] + "\n";
		file2 << v_line;				
	}	
	
	file2.close();
	
	return 0;
}
