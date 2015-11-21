#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

struct link_struct{
	int node_if_matched;
	vector<int> link;
	vector<int> link_if_matched;
	vector<int> mark;
};

typedef std::vector <vector<link_struct> > link_type;

int max_node_number_link_list(string filename){
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
	string line;
	int number_node = 0;
	int in_number;

	while(fin >> in_number){
		if(number_node < in_number){
			number_node = in_number;
		}
	}	
	return number_node;
}

void read_in_network_link_list(link_type& link, string filename){
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);

	int out_node;
	int in_node;
	while(fin >> out_node >> in_node){
		
		link[0][out_node].link.push_back(in_node);
		link[1][in_node].link.push_back(out_node);
	}

	for(int ix=0; ix!=2; ++ix){
		for(int iy=0; iy!= link[ix].size(); ++iy){
			if(link[ix][iy].link.size() != 0){
				vector<int> temp(link[ix][iy].link.size());
				link[ix][iy].link_if_matched = temp;
				link[ix][iy].mark = temp;
			}
		}
	}
}

int max_matching(link_type &link, int current_match, int& new_match_node){
	
}


int main()
{
	string filename1, filename2;

	filename1 = "test";
	filename2 = "";

	ofstream fout;
	//fout.open(filename2);

	int number_node = max_node_number_link_list(filename1) +1;   //Warming:maybe err
	link_type link(2);
	vector<link_struct> link_col(number_node);
	vector<link_struct> link_row(number_node);
	link[0] = link_col;
	link[1] = link_row;
	link_row.clear();
	link_col.clear();
	vector<int> out_degree(number_node);
	vector<int> in_degree(number_node);

	for(int ix=0; ix!= link[0].size(); ++ix){
		link[0][ix].node_if_matched = 0;
		link[1][ix].node_if_matched = 0;
	}
	read_in_network_link_list(link, filename1);

	cout << number_node << " " << filename1 << endl;

	vector<int> matching_fraction(number_node);
	int new_match_node = -1;
	int current_match = max_matching(link, 0, new_match_node);
}