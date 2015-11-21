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
#include <map>

using namespace std;

typedef std::vector <vector<int> > link_type;
//typedef NUM 2;
//link_type link;
int n1,m,ans;
int max_number_node;
vector<int> out;
vector<int> in;
vector<string> file;//path file
vector<int> all;
vector<vector<int> > result;
map <int, int> state;
//vector<int> p;
int p[1024];
int sub_p[1024];
int total =0;
int tab =0;
int driver[1024];
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
void read_in_network_link_list (link_type& link, string filename){

	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
    
	int out_node;
	int in_node;

	while(fin >> out_node >> in_node){

		link[out_node].push_back(in_node);
	}
	return;
}
bool equal(pair<int,int> data, int target)  
{  
	if (data.second == target)  {  
	        return   true;  
	}   
	else {  
	        return   false;  
	}  
}  
void sub_fun(int first, link_type& sub_link)
{
	if(first < sub_link.size()){
		if(sub_link[first].size() ==0) sub_fun(first +1, sub_link);
		for(int i =0; i < sub_link[first].size(); i ++){
			sub_p[first] = sub_link[first][i];
			sub_fun(first +1, sub_link);
		}
	}else{
		int num =0;
		for(int i =0; i < sub_link.size(); i ++){
			if(sub_p[i] !=0){
				num ++;
			}
		}
		if(num == 26){
			total ++;
			for(int i =0; i < sub_link.size(); i ++){
				if(sub_p[i] !=0){
					cout << sub_p[i] << " " << i << endl;
					driver[i] ++;
				}
			}
			cout << endl;
		}
	}
}
void fun(int first, link_type& link)
{
	if(first <link.size()){
		if(link[first].size() ==0) fun(first +1, link);
		for(int i =0; i < link[first].size(); i ++){
			p[first] = link[first][i];
			//cout << link[first][i] << " ";
			fun(first +1, link);
		}
	}else{
		link_type sub_link(link.size());

		memset(sub_p,0,sizeof(sub_p));
		for(int i =0; i < link.size(); i ++){
			if(p[i] != 0){
				sub_link[p[i]].push_back(i);
				//cout << i << " " << p[i] << endl;
			}
		}
		//cout << "with" << endl;
		sub_fun(0, sub_link);
		// for(int i =0; i < sub_link.size(); i ++){
		// 	for(int j = 0; j< sub_link[i].size(); j ++){
		// 		if(sub_link[i][j] != 0){
		// 			cout << i << " " << sub_link[i][j] << endl;
		// 		}
		// 	}
		// }
		cout << tab ++ << endl;
	}
}
int main()
{
	string filename = "test";
	max_number_node = max_node_number_link_list(filename) +1;
	cout << max_number_node << endl;
	link_type link(max_number_node);
	read_in_network_link_list(link, filename);
	memset(driver,0,sizeof(driver));
	//cout << link.size() << endl;
	// for(int i =0; i < link.size(); i ++){
	// 	for(int j = 0; j< link[i].size(); j ++){
	// 		if(link[i][j] != 0){
	// 			cout << i << " " << j << endl;
	// 		}
	// 	}
	// }
	fun(0, link);
	cout << "total" << total << endl;
	for(int i = 0; i < max_number_node; i ++){
		cout << i << " " << 1- (double)driver[i] / total << endl;
	}
	return 0;
}