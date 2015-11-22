#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
using namespace std;
struct link_struct{
	vector<int> link;
	int know;
	int dist;
	int in;
	int out;
};
typedef std::vector <link_struct > link_type;

int max_node_number_link_list(string filename) {
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
	string line;
	int number_node =0;
	int node;
	while(fin >> node) {
		if(number_node < node) {
			number_node = node;
		}
	}
	return number_node;
}
void read_in_network_link_list (link_type& graph, string filename) {
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
	int out_node;
	int in_node;
	while(fin >> out_node >> in_node) {
		graph[out_node].link.push_back(in_node);
		graph[out_node].out ++;
		graph[in_node].in ++;
		graph[out_node].know =0;
		graph[in_node].know =0;
		graph[in_node].dist = -1;
		graph[out_node].dist = -1;
	}
}
void graph_init(link_type& graph, int max_number_node) {
	for(int i =0; i < max_number_node; i ++) {
		graph[i].out =0;
		graph[i].in =0;
		graph[i].dist = -1;
		graph[i].dist = -1;
	}
}
void copy_graph(link_type& dest, link_type& src, int max_number_node) {
	for(int i =0; i < max_number_node; i ++) {
		dest[i].link = src[i].link;
		dest[i].dist = src[i].dist;
		dest[i].in = src[i].in;
		dest[i].out = src[i].out;
	}
}
int cal_onenode_two_hop_degree(link_type& graph, int k, int level) {
	queue<int> q, p;
	while(!q.empty()) q.pop();
	while(!p.empty()) p.pop();
	q.push(k);
	graph[k].dist =0;
	int sum =0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i =0; i < graph[v].link.size(); i ++) {
			int j_val = graph[v].link[i];
			if(graph[j_val].dist ==-1) {
				graph[j_val].dist = graph[v].dist +1;
				p.push(j_val);
			}
		}
	}//cout << k << "\'s one_hop size: " << p.size() << endl;
	//cout << k << "\'s two_hop nodes: ";
	while(!p.empty()) {
		int v = p.front(); p.pop();
		for(int i =0; i < graph[v].link.size(); i ++) {
			int j_val = graph[v].link[i];
			if(graph[j_val].dist ==-1) {
				//cout << j_val << " in degree:" << graph[j_val].in << " out degree:" << graph[j_val].out << " ";
				graph[j_val].dist = graph[v].dist +1;
				sum += graph[j_val].in + graph[j_val].out;
			}
		}
		//cout << endl;
	}
	//cout << k << "\'s two_hop nodes degree sum: " << sum << endl;
	return sum;
}
void cal_allnode_two_hop_degree(link_type& graph, int max_number_node, vector<int>& twohot_dgree) {
	for(int k =1; k < max_number_node; k ++) {
		link_type flag_graph(max_number_node);
		copy_graph(flag_graph, graph, max_number_node);
		int level =2;
		cout << cal_onenode_two_hop_degree(flag_graph, k, level) << " ";
		// twohot_dgree[k] = cal_onenode_two_hop_degree(graph, k, level);
	}
}
void dfs(link_type& graph, int k, int& num) {
	graph[k].know =1;
	for(int i =0; i < graph[k].link.size(); i ++) {
		int j_val = graph[k].link[i];
		if(!graph[j_val].know) {
			dfs(graph, j_val, ++num);
		}
	}
}
void cal_maximum_connected_subgraph(link_type& graph, int max_number_node) {
	vector<int> result(max_number_node, 0);
	for(int i =1; i < max_number_node; i ++) {
		int num =1;
		if(!graph[i].know) {
			dfs(graph, i, num);
			result[i] = num;
			cout << num << " ";
		}
	}
}
int main()
{
	string filename = "test";
	int max_number_node = max_node_number_link_list(filename) +1;
	cout << max_number_node << endl;
	link_type graph(max_number_node);
	vector<int> twohot_dgree(max_number_node);
	twohot_dgree.clear();
	twohot_dgree[0] =0;
	read_in_network_link_list(graph, filename);
	cal_allnode_two_hop_degree(graph, max_number_node, twohot_dgree);
	cal_maximum_connected_subgraph(graph, max_number_node);
	return 0;
}