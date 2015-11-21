#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
using namespace std;
struct link_struct{
	vector<int> link;
	int dist;
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
		graph[in_node].dist = -1;
		graph[out_node].dist = -1;
	}
}
void unweighted(link_type& graph, int k) {
	queue<int> q;
	while(!q.empty()) q.pop();
	q.push(k);
	graph[k].dist =0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i =0; i < graph[v].link.size(); i ++) {
			int j_val = graph[v].link[i];
			if(graph[j_val].dist ==-1) {
				graph[j_val].dist = graph[v].dist +1;
				q.push(j_val);
			}
		}
	}
}
double cal_sum_d_reciprocal(link_type& graph, string filename, int max_number_node) {
	double dreciprocal;
	for(int k =1; k < max_number_node; k ++) {
		read_in_network_link_list(graph, filename);
		unweighted(graph, k);
		for(int i =1; i < max_number_node; i ++) {
			//cout << graph[i].dist << " ";
			if(graph[i].dist >0)
				dreciprocal += 1.0/graph[i].dist;
		}
		//cout << endl;
	}
	return dreciprocal;
}
int main()
{
	string filename = "test";
	int max_number_node = max_node_number_link_list(filename) +1;
	cout << max_number_node << endl;
	link_type graph(max_number_node);
	double dreciprocal = cal_sum_d_reciprocal(graph, filename, max_number_node);
	cout << "dreciprocal " << dreciprocal << endl;
	cout << "efficiency " << 1.0/(max_number_node -1)/(max_number_node -2) * dreciprocal;
	cout << endl;
	return 0;
}