#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <algorithm>
using namespace std;
struct link_struct{
	vector<int> link;
	int know;
};
typedef std::vector <link_struct > link_type;

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
void read_in_network_link_list (link_type& graph, string filename){
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
	int out_node;
	int in_node;
	while(fin >> out_node >> in_node){
		graph[out_node].link.push_back(in_node);
		graph[in_node].know = 0;
		graph[out_node].know =0;
	}
}
void dfs(link_type& graph, int k, int& num) {
	graph[k].know =1;
	for(int i =0; i < graph[k].link.size(); i ++) {
		int j_val = graph[k].link[i];
		if(!graph[j_val].know) {
			//cout << num;
			dfs(graph, j_val, ++num);
			// return num;
		}
	}
}
int main()
{
	string filename = "test";
	int max_number_node = max_node_number_link_list(filename) +1;
	cout << max_number_node << endl;
	link_type graph(max_number_node);
	read_in_network_link_list(graph, filename);
	vector<int> result(max_number_node, 0);
	for(int i =1; i < max_number_node; i ++) {
		if(!graph[i].know) {
			int num =1;
			dfs(graph, i, num);
			result[i] = num;
			cout << num << " ";
		}
	}
	sort(result.begin(), result.end());
	//cout << result[max_number_node -1];
}