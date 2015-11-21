#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

struct link_struct{

	int node_if_matched;
	vector<int> link;
	vector<int> link_if_matched;
	vector<int> mark;
};

typedef std::vector <vector<link_struct> > link_type;

int result[10000];

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


void read_in_network_link_list (link_type& link, string filename){

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


void read_inverse_network_link_list (link_type& link, string filename){

	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);
    
	int out_node;
	int in_node;

	while(fin >> in_node >> out_node){

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


int BFS(link_type& link, vector<int>& first_layer, vector<set<int> >& node_marked){

	int layer_number = 1;
	int node_number = link[0].size();
	vector<int> node_0_visit(node_number+1);
	vector<int> node_1_visit(node_number+1);
	vector<vector<int> > node_visit;
	node_visit.push_back(node_0_visit);
	node_visit.push_back(node_1_visit);
	vector<int> next_layer;

	node_0_visit.clear();
	node_1_visit.clear();

	for(vector<link_struct>::size_type ix = 0; ix != link[0].size(); ++ix){
		
		if(link[0][ix].node_if_matched == 0 && link[0][ix].link.size() > 0){

			node_visit[0][ix] = 1;
			first_layer.push_back(ix);
			vector<int>& link_to = link[0][ix].link;
			vector<int>& link_match = link[0][ix].link_if_matched;
			vector<int>& link_mark = link[0][ix].mark;
			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){				

				if(link_match[ix2] == 0 ){

				    link_mark[ix2] = 1;
				    node_marked[0].insert(ix);
				    if(node_visit[1][link_to[ix2]] == 0){

					    node_visit[1][link_to[ix2]] = 2;
					    next_layer.push_back(link_to[ix2]);
					}
				}
			}
		}
	}

	int if_new_node_find = 1;
	while(if_new_node_find){

		if_new_node_find = 0;
		vector<int> temp_next_layer;
		int group = layer_number %2;
		int group_connect_to = (layer_number+1) %2;
		if(group == 1){

			for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

				if(link[group][next_layer[ix]].node_if_matched == 0){

					return layer_number;
				}
			}
		}

		layer_number ++;

		for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

			int next_node = next_layer[ix];
			vector<int>& link_to = link[group][next_node].link;
			vector<int>& link_match = link[group][next_node].link_if_matched;
			vector<int>& link_mark = link[group][next_node].mark;
			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){

				if(link_match[ix2] == group && (node_visit[group_connect_to][link_to[ix2]] == 0 || node_visit[group_connect_to][link_to[ix2]]==layer_number + 1) ){

					if(node_visit[group_connect_to][link_to[ix2]] == 0){

						node_visit[group_connect_to][link_to[ix2]]= layer_number + 1;
						temp_next_layer.push_back(link_to[ix2]);
					}										
					link_mark[ix2] = layer_number;
					node_marked[group].insert(next_node);
					if_new_node_find = 1;
				}
			}
		}

		next_layer.clear();
		next_layer = temp_next_layer;		
	}
	return 0;
}

int DFS(link_type& link, int target_layer, int DFS_step, int start_node, int& current_match, vector<vector<int> >& node_visit, int& new_match_node){

	int group = DFS_step %2;
	int group_connect_to = (DFS_step + 1)%2;
	int can_go_further = 0;
	int right_path = 0;

	node_visit[group][start_node] = DFS_step + 1;

	if( DFS_step < target_layer){

		vector<int> next_layer;
		vector<int>& link_to = link[group][start_node].link;
		vector<int>& link_mark = link[group][start_node].mark;
		for(vector<int>::size_type ix = 0; ix != link_to.size(); ++ix){

			if(link_mark[ix] == DFS_step + 1 && node_visit[group_connect_to][link_to[ix]] == 0 ){

				next_layer.push_back(link_to[ix]);				
				link_mark[ix] = 0;
			}
		}

		for(vector<int>::size_type ix = 0; ix != next_layer.size(); ++ix){


			result[start_node] = next_node;



			int next_node = next_layer[ix];
			right_path = DFS(link,target_layer,DFS_step+1,next_node,current_match, node_visit,new_match_node);
			if(right_path){

				link[group][start_node].node_if_matched = 1;
				vector<int>& link_to = link[group][start_node].link;
				vector<int>& link_match = link[group][start_node].link_if_matched;
				for(vector<int>::size_type iy=0; iy != link_to.size(); ++iy){

					if(link_to[iy] == next_node){

						link_match[iy] = group_connect_to;
						break;
					}
				}

				vector<int>& link_to_2 = link[group_connect_to][next_node].link;
				vector<int>& link_match_2 = link[group_connect_to][next_node].link_if_matched;
				for(vector<int>::size_type iy=0; iy != link_to_2.size(); ++iy){

					if(link_to_2[iy] == start_node){

						link_match_2[iy] = group_connect_to;
						break;
					}
				}
				return 1;
			}
		}
	}
	else{

		if(group == 1 && link[group][start_node].node_if_matched == 0){

			current_match ++;
			link[group][start_node].node_if_matched = 1;
			new_match_node = start_node;
			return 1;
		}
	}
	return 0;
}

int max_matching(link_type& link, int current_match, int& new_match_node){

	vector<set<int> > node_marked(2);
	vector<int> first_layer;
	int target_layer = BFS(link,first_layer,node_marked);
	int number_node = link[0].size() + 1;

	while(target_layer){

		vector<vector<int> > node_visit;
		vector<int> temp(number_node);
		node_visit.push_back(temp);
		node_visit.push_back(temp);
		temp.clear();

		for(vector<int>::size_type ix = 0; ix != first_layer.size(); ++ix){

			DFS(link,target_layer,0,first_layer[ix],current_match,node_visit,new_match_node);
		}

		for(vector<set<int> >::size_type ix=0; ix != 2; ++ix){

			for(set<int>::iterator it = node_marked[ix].begin(); it != node_marked[ix].end(); ++it){

				int temp_node = *it;
				for(vector<int>::size_type iy =0; iy != link[ix][temp_node].mark.size(); ++iy){

					link[ix][temp_node].mark[iy] = 0;
				}
			}
		}

		first_layer.clear();
		node_marked[0].clear();
		node_marked[1].clear();
		//node_marked.clear();
		//set<int> temp_set;
		//node_marked.push_back(temp_set);
		//node_marked.push_back(temp_set);
		target_layer = BFS(link,first_layer,node_marked);
	}
	return(current_match);
}


void shade_node(link_type& link, int remove_node){

	link[1][remove_node].node_if_matched = 2;
	vector<int> link_to = link[1][remove_node].link;
	vector<int>& link_match = link[1][remove_node].link_if_matched;
	for(vector<int>::size_type ix=0; ix!= link_to.size();++ix){

		int connect_node = link_to[ix];
		if(link_match[ix] == 1){

			link[0][connect_node].node_if_matched = 0;
		}
		link_match[ix] = 2;
		for(vector<int>::size_type ix2 =0; ix2!= link[0][connect_node].link.size(); ++ix2){

			if(link[0][connect_node].link[ix2] == remove_node){

				link[0][connect_node].link_if_matched[ix2] = 2;
				break;
			}
		}
		
	}

}


int find_alternative(link_type& link, int remove_node, int current_match, vector<int>& alternate_node){
		
	link_type new_link = link;
	int new_match_node = -1;
	shade_node(new_link,remove_node);
	int new_match = max_matching(new_link,current_match-1,new_match_node);
	
	while(new_match == current_match){

		int alternative;
		for(vector<link_struct>::size_type ix =0; ix != new_link[1].size(); ++ix){

			if(new_link[1][ix].node_if_matched == 1 && link[1][ix].node_if_matched == 0){

				alternate_node.push_back(ix);
				alternative = ix;
				if(ix != new_match_node){

					cout << "error" << endl;
				}
				break;
			}
		}

		shade_node(new_link,alternative);
		new_match_node = -1;
		new_match = max_matching(new_link,current_match-1,new_match_node);
	}
	
	return 1;
}


void unmatch_A_node(link_type& link, int unmatch_node){

	link[1][unmatch_node].node_if_matched = 0;
	int link_node = -1;
	for(vector<int>::size_type ix=0; ix != link[1][unmatch_node].link.size(); ++ix){

		if(link[1][unmatch_node].link_if_matched[ix] == 1){

			link_node = link[1][unmatch_node].link[ix];
			link[1][unmatch_node].link_if_matched[ix] = 0;
			break;
		}
	}

	if(link_node < 0){

		cout << "error in unmatch_A_node" <<endl;
		return;
	}

	link[0][link_node].node_if_matched = 0;

	for(vector<int>::size_type ix=0; ix != link[0][link_node].link.size(); ++ix){

		if(link[0][link_node].link[ix] == unmatch_node){

			link[0][link_node].link_if_matched[ix] = 0;
		}
	}

}



int BFS_A_node(link_type& link, vector<int>& first_layer, vector<set<int> >& node_marked, int target_node){

	int layer_number = 1;
	int node_number = link[0].size();
	vector<int> node_0_visit(node_number+1);
	vector<int> node_1_visit(node_number+1);
	vector<vector<int> > node_visit;
	node_visit.push_back(node_0_visit);
	node_visit.push_back(node_1_visit);
	vector<int> next_layer;

	node_0_visit.clear();
	node_1_visit.clear();

	for(vector<link_struct>::size_type ix = 0; ix != link[0].size(); ++ix){
		
		if(link[0][ix].node_if_matched == 0 && link[0][ix].link.size() > 0){

			node_visit[0][ix] = 1;
			first_layer.push_back(ix);
			vector<int>& link_to = link[0][ix].link;
			vector<int>& link_match = link[0][ix].link_if_matched;
			vector<int>& link_mark = link[0][ix].mark;
			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){				

				if(link_match[ix2] == 0 ){

				    link_mark[ix2] = 1;
				    node_marked[0].insert(ix);
				    if(node_visit[1][link_to[ix2]] == 0){

					    node_visit[1][link_to[ix2]] = 2;
					    next_layer.push_back(link_to[ix2]);
					}
				}
			}
		}
	}

	int if_new_node_find = 1;
	while(if_new_node_find){

		if_new_node_find = 0;
		vector<int> temp_next_layer;
		int group = layer_number %2;
		int group_connect_to = (layer_number+1) %2;
		if(group == 1){

			for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

				if(next_layer[ix] == target_node){

					return layer_number;
				}
			}
		}

		layer_number ++;

		for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

			int next_node = next_layer[ix];
			vector<int>& link_to = link[group][next_node].link;
			vector<int>& link_match = link[group][next_node].link_if_matched;
			vector<int>& link_mark = link[group][next_node].mark;
			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){

				if(link_match[ix2] == group && (node_visit[group_connect_to][link_to[ix2]] == 0 || node_visit[group_connect_to][link_to[ix2]]==layer_number + 1) ){

					if(node_visit[group_connect_to][link_to[ix2]] == 0){

						node_visit[group_connect_to][link_to[ix2]]= layer_number + 1;
						temp_next_layer.push_back(link_to[ix2]);
					}										
					link_mark[ix2] = layer_number;
					node_marked[group].insert(next_node);
					if_new_node_find = 1;
				}
			}
		}

		next_layer.clear();
		next_layer = temp_next_layer;
		
	}

	return 0;
}



int DFS_A_node(link_type& link, int target_layer, int target_node, int DFS_step, int start_node, vector<vector<int> >& node_visit){

	int group = DFS_step %2;
	int group_connect_to = (DFS_step + 1)%2;
	int can_go_further = 0;
	int right_path = 0;

	node_visit[group][start_node] = DFS_step + 1;

	if( DFS_step < target_layer){

		vector<int> next_layer;
		vector<int>& link_to = link[group][start_node].link;
		vector<int>& link_mark = link[group][start_node].mark;
		for(vector<int>::size_type ix = 0; ix != link_to.size(); ++ix){

			if(link_mark[ix] == DFS_step + 1 && node_visit[group_connect_to][link_to[ix]] == 0 ){

				next_layer.push_back(link_to[ix]);				
				link_mark[ix] = 0;
			}
		}

		for(vector<int>::size_type ix = 0; ix != next_layer.size(); ++ix){

			int next_node = next_layer[ix];
			right_path = DFS_A_node(link,target_layer,target_node, DFS_step+1,next_node, node_visit);
			if(right_path){

				link[group][start_node].node_if_matched = 1;
				vector<int>& link_to = link[group][start_node].link;
				vector<int>& link_match = link[group][start_node].link_if_matched;
				for(vector<int>::size_type iy=0; iy != link_to.size(); ++iy){

					if(link_to[iy] == next_node){

						link_match[iy] = group_connect_to;
						break;
					}
				}

				vector<int>& link_to_2 = link[group_connect_to][next_node].link;
				vector<int>& link_match_2 = link[group_connect_to][next_node].link_if_matched;
				for(vector<int>::size_type iy=0; iy != link_to_2.size(); ++iy){

					if(link_to_2[iy] == start_node){

						link_match_2[iy] = group_connect_to;
						break;
					}
				}
				return 1;
			}
		}
	}
	else{

		if(group == 1 && start_node == target_node){

			link[group][start_node].node_if_matched = 1;
			return 1;
		}
	}
	return 0;
}


void max_matching_A_node (link_type& link, int target_node){

	vector<set<int> > node_marked(2);
	vector<int> first_layer;
	int target_layer = BFS_A_node(link,first_layer,node_marked,target_node);
	int number_node = link[0].size() + 1;

	vector<vector<int> > node_visit;
	vector<int> temp(number_node);
	node_visit.push_back(temp);
	node_visit.push_back(temp);
	temp.clear();

	for(vector<int>::size_type ix = 0; ix != first_layer.size(); ++ix){

		if(DFS_A_node(link,target_layer,target_node,0,first_layer[ix],node_visit)==1){

			break;
		}
	}

	for(vector<set<int> >::size_type ix=0; ix != 2; ++ix){

		for(set<int>::iterator it = node_marked[ix].begin(); it != node_marked[ix].end(); ++it){

			int temp_node = *it;
			for(vector<int>::size_type iy =0; iy != link[ix][temp_node].mark.size(); ++iy){

				link[ix][temp_node].mark[iy] = 0;
			}
		}
	}


}



int BFS_simple(link_type& link){

	int layer_number = 1;
	int node_number = link[0].size();
	vector<int> node_0_visit(node_number+1);
	vector<int> node_1_visit(node_number+1);
	vector<vector<int> > node_visit;
	node_visit.push_back(node_0_visit);
	node_visit.push_back(node_1_visit);
	vector<int> next_layer;
	vector<int> first_layer;

	node_0_visit.clear();
	node_1_visit.clear();

	for(vector<link_struct>::size_type ix = 0; ix != link[0].size(); ++ix){
		
		if(link[0][ix].node_if_matched == 0 && link[0][ix].link.size() > 0){

			node_visit[0][ix] = 1;
			first_layer.push_back(ix);
			vector<int>& link_to = link[0][ix].link;
			vector<int>& link_match = link[0][ix].link_if_matched;

			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){				

				if(link_match[ix2] == 0 ){

				    if(node_visit[1][link_to[ix2]] == 0){

					    node_visit[1][link_to[ix2]] = 2;
					    next_layer.push_back(link_to[ix2]);
					}
				}
			}
		}
	}

	int if_new_node_find = 1;
	while(if_new_node_find){

		if_new_node_find = 0;
		vector<int> temp_next_layer;
		int group = layer_number %2;
		int group_connect_to = (layer_number+1) %2;
		if(group == 1){

			for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

				if(link[group][next_layer[ix]].node_if_matched == 0){

					return layer_number;
				}
			}
		}

		layer_number ++;

		for(vector<int>::size_type ix =0; ix != next_layer.size(); ++ix){

			int next_node = next_layer[ix];
			vector<int>& link_to = link[group][next_node].link;
			vector<int>& link_match = link[group][next_node].link_if_matched;

			for(vector<int>::size_type ix2 =0; ix2 != link_to.size(); ++ix2){

				if(link_match[ix2] == group && node_visit[group_connect_to][link_to[ix2]] == 0 ){

					node_visit[group_connect_to][link_to[ix2]]= layer_number + 1;
					temp_next_layer.push_back(link_to[ix2]);
					if_new_node_find = 1;
				}
			}
		}

		next_layer.clear();
		next_layer = temp_next_layer;
		//temp_next_layer.clear();
	}

	return 0;
}


void find_always_match(link_type& link, vector<int>& always_match){

	link_type new_link = link;
	for(vector<link_struct>::size_type ix=0; ix != link[1].size(); ++ix){
				
		if(link[1][ix].node_if_matched == 1){
						
			shade_node(new_link,ix);
			int if_augmentpath = BFS_simple(new_link);
			//cout << if_augmentpath << " "<< ix << endl;
			if(if_augmentpath == 0){

				always_match.push_back(ix);
			}

			new_link[1][ix] = link[1][ix];
			vector<int>& link_to = link[1][ix].link;
			for(vector<int>::size_type iy=0; iy!= link_to.size(); ++iy){

				int connect_node = link_to[iy];
				new_link[0][connect_node] = link[0][connect_node];
			}

		}
	}
}




void remove_A_node(link_type& link, int remove_node){

	for(vector<int>::size_type ix=0; ix != link[1][remove_node].link.size(); ++ix){

		int link_node = link[1][remove_node].link[ix];
		
		int iy; 
		for(iy=0; iy != link[0][link_node].link.size(); ++iy){

			if(link[0][link_node].link[iy] == remove_node){

				break;
			}
		}
		link[0][link_node].link.erase(link[0][link_node].link.begin()+iy);		
	}

	link[1][remove_node].link.clear();

}


void reshape_network(link_type& link){

	for(int ix=0; ix != 2; ++ix){

		for(int iy=0; iy!= link[ix].size(); ++iy){

			link[ix][iy].node_if_matched=0;
			link[ix][iy].link_if_matched.clear();
			link[ix][iy].mark.clear();
			if(link[ix][iy].link.size() != 0){

				vector<int> temp(link[ix][iy].link.size());
				link[ix][iy].link_if_matched = temp;
				link[ix][iy].mark = temp;
			}
		}
	}
}


void node_sampling(link_type& link, int repeat_time, int transient_time, vector<int>& matching_fraction){

	int new_match_node = -1;
   	int current_match = max_matching(link,0,new_match_node);
	vector<int> matching_set;

    	for(vector<int>::size_type ix=0; ix != link[1].size(); ++ix){

    		if(link[1][ix].node_if_matched == 1){

			matching_set.push_back(ix);
		}
	}

	for(int iix = 0; iix != transient_time; ++iix){
	
		int pick = rand() % matching_set.size();

		int pick_node = matching_set[pick];

		vector<int> alternate_node;

		find_alternative(link, pick_node, current_match,alternate_node);

		int pick2 = rand() % alternate_node.size();
		int pick_node_2 = alternate_node[pick2];
		matching_set[pick] = pick_node_2;
		unmatch_A_node(link,pick_node);
		max_matching_A_node(link,pick_node_2);

	}

	cout << "transient time done" << endl;

	for(int iix = 0; iix != repeat_time; ++iix){
	
	    	int pick = rand() % matching_set.size();

		int pick_node = matching_set[pick];

	    	vector<int> alternate_node;

	    	find_alternative(link, pick_node, current_match,alternate_node);

        		int pick2 = rand() % alternate_node.size();
		int pick_node_2 = alternate_node[pick2];
		matching_set[pick] = pick_node_2;

		/*
		georgios, matching_set is the vector contains the nodes that are matched. You can integrate your function starting here.
		*/

		unmatch_A_node(link,pick_node);
		max_matching_A_node(link,pick_node_2);

		for(vector<int>::size_type iiy=0; iiy != matching_set.size(); ++iiy){

			matching_fraction[matching_set[iiy]] += 1;
		}
		//cout << "replacing node " << pick_node << " to " << pick_node_2 << endl;
	}

	cout << "one sampling done" << endl;
}





int main()
{
	srand( time( NULL ) );



	string filename1, filename2;
	
	filename1 = "/home/heyaoji/Documents/complex network/BipartiteMatrix";
	filename2 = "test.txt";


	ofstream fout;
	fout.open(filename2);

	int number_node = max_node_number_link_list(filename1) +1;
	link_type link(2);
	vector<link_struct> link_col(number_node);
	vector<link_struct> link_row(number_node);
	link[0] = link_col;
	link[1] = link_row;
	link_col.clear();
	link_row.clear();
	vector<int> out_degree(number_node);
	vector<int> in_degree(number_node);

	for(int ix=0; ix!= link[0].size(); ++ix){

		link[0][ix].node_if_matched = 0;
		link[1][ix].node_if_matched = 0;
	}
	read_in_network_link_list(link,filename1);
	//read_inverse_network_link_list(link,filename1);
	cout << number_node << " " << filename1 << endl;

	vector<int> matching_fraction(number_node);
	int new_match_node = -1;
	int current_match = max_matching(link,0,new_match_node);
	for(int i=1;i<=10000;i++){
			if(result[i]!=0){
				cout << result[i] << "\t" << i << "\n";
			}
		}
	vector<int> always_match;
	find_always_match(link,always_match);

	int nc = 0;
	for(int ix=0; ix != link[1].size(); ++ix){

		if(link[1][ix].link.size() == 0){

			nc ++;
			//cout << ix << endl;
		}

		in_degree[ix] = link[1][ix].link.size();
		out_degree[ix] = link[0][ix].link.size();
	}




	cout << current_match <<" " << always_match.size() << " " << nc << endl;

	int sample_time = 5*(current_match - always_match.size());
	int transient_time = 2*(current_match - always_match.size());

	for(int ix=0; ix != always_match.size(); ++ix){

		matching_fraction[always_match[ix]] = sample_time;
		remove_A_node(link, always_match[ix]);
	}

	reshape_network(link);
	node_sampling(link, sample_time, transient_time, matching_fraction);

	for(int ix=0; ix != matching_fraction.size(); ++ix){

		if(matching_fraction[ix] == sample_time){

			fout << ix << " " << 0 << " " << out_degree[ix] << " " << in_degree[ix] << endl;
		}
		else{

			double temp = 1- matching_fraction[ix]*1.0/sample_time;
			fout << ix << " " << temp << " " << out_degree[ix] << " " << in_degree[ix] << endl;
		}
	}


	int temmmmp;
	cin >> temmmmp;

	return 1;
}