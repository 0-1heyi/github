#include  <stddef.h>
#include  <stdio.h>   
#include  <sys/types.h>   
#include  <dirent.h> 
#include <string.h>  
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> file;

int reaFileList(char *basePath){
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
		else if(ep -> d_type ==8) {        //file
			//puts(ep->d_name);
			file.push_back(ep->d_name);
		}//else if(ep -> d_type ==10)     //link file
			//puts(ep->d_name);
		// else if(ep -> d_type ==4){       //dir
		// 	memset(base, '\0', sizeof(base));
		// 	strcpy(base, basePath);
		// 	strcat(base,"/");
		// 	strcat(base,ep->d_name);
		// 	reaFileList(base);
		// }
	}
	(void)closedir(dp);
	return 1;
}

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

int   main(void)   
{   
	DIR * dp;
	char basePath[1000];
	file.clear();
	memset(basePath, '\0', sizeof(basePath));
	strcpy(basePath,"./BipartiteMatrix");
	reaFileList(basePath);

	for(int i=0;  i < file.size(); i++){
		char* filename1=basePath;
		string filename2 = filename1;
		filename2 = filename2 + "/" + file[i];    //strcat(filename2,"/");
		//cout << filename2 << endl;
		string ofile = "./BipartiteMatrix_add_nodenum_pathnum/" + file[i];
		char* name = (char*) ofile.c_str();
		ofstream fout(name);

		int number_node = max_node_number_link_list(filename2) + 1;
		int number_path = max_path_number_link_list(filename2);
		fout << number_node << "\t" << number_path << "\n";

		//node read in file
		char* fname = (char*) filename2.c_str();
		ifstream fin(fname, ios_base::in);

		int out_node;
		int in_node; 
		while(fin >> out_node >> in_node){
			fout << out_node << "\t" << in_node << "\n";
		}


		cout << file[i] << " down" << endl;
	}
	return   0;
}  