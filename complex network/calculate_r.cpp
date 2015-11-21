#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include  <stddef.h>
#include  <dirent.h> 
#include <functional>
#include <cmath>

using namespace std;
struct link_struct{
	vector<int> link;
	int in;
	int out;
};
typedef std::vector <link_struct > link_type;

int reaFileList(char *basePath, vector<string>& file){
	DIR*   dp;
	struct   dirent*   ep;
	char base[100];
	dp   =   opendir(basePath);
	if(dp == NULL){
		perror("Open dir error");
		exit(1);
	}
	while(ep = readdir(dp)) {
		if(strcmp(ep->d_name,".")==0||strcmp(ep->d_name,"..")==0) //current dir OR parrent dir
			continue;
		else if(ep -> d_type ==8) {
			file.push_back(ep->d_name);
		}
	}
	(void)closedir(dp);
	return 1;
}
int max_node_number_link_list(string filename){

	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
	string line;
	int number_node =0;
	int node;
	while(fin >> node){

		if(number_node < node){
			number_node = node;
		}
	}
	return number_node;
}
int max_path_number_link_list(string filename){
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);

	int out_node;
	int in_node;
	int number_path =0;
	while(fin >> out_node >> in_node){
		number_path ++;	
	}
	return number_path;
}
void read_in_network_link_list (link_type& graph, string filename){

	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
    
	int out_node;
	int in_node;

	while(fin >> out_node >> in_node){

		graph[out_node].link.push_back(in_node);
		graph[out_node].out++;
		graph[in_node].in++;
	}
	return;
}

int main()
{
	DIR * dp;
	char basePath[1000];
	memset(basePath, '\0', sizeof(basePath));
	strcpy(basePath,"./BipartiteMatrix");
	vector<string> file;
	file.clear();
	reaFileList(basePath, file);

	for(int k=0;  k < file.size(); k++){
		char* filename1=basePath;
		string filename2 = filename1;
		filename2 = filename2 + "/" + file[k];  
			
	 	int max_number_node = max_node_number_link_list(filename2) +1;
		//cout << max_number_node << endl;
		int number_path = max_path_number_link_list(filename2);
		//cout << number_path << endl;
		link_type graph(max_number_node);
		graph.clear();
		read_in_network_link_list(graph, filename2);
		int j_multi_k =0;
		int j_add_k =0;
		int j_pow2_add_k_pow2 =0;
		 for(int i =0; i < max_number_node; i ++) {
		 	//cout << graph[i].in << endl;
			for(int j =0; j < graph[i].link.size(); j ++) {
				int j_value = graph[i].link[j];
				j_multi_k = j_multi_k + (graph[i].in + graph[i].out) * (graph[j_value].in + graph[j_value].out);
				j_add_k = j_add_k + (graph[i].in + graph[i].out) + (graph[j_value].in + graph[j_value].out);
				j_pow2_add_k_pow2 = j_pow2_add_k_pow2 +  pow((graph[i].in + graph[i].out), 2) + pow((graph[j_value].in + graph[j_value].out) , 2);
			}
		}
		double r;
		double M = 1/(1.0 * number_path);
		r = (M * j_multi_k - pow(M * 0.5 * j_add_k, 2)) / (M * 0.5 * j_pow2_add_k_pow2 - pow(M * 0.5 * j_add_k, 2));
		cout << file[k] << " " << r << endl;
	}
	return 0;
}