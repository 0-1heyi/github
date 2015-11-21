#include  <stddef.h>
#include  <sys/types.h>
#include  <dirent.h> 
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n1,m,ans;
int result[10000];//记录V2中的点匹配的点的编号
bool state[10000];//记录V2中的每个点是否被搜索过
bool data[10000][10000];//邻接矩阵true代表有边相连
vector<int> out;
vector<int> in;
vector<string> file;//path file
vector<int> all;
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
void init(string filename){
	char* fname = (char*) filename.c_str();
	ifstream fin(fname, ios_base::in);

	int t1,t2;
	memset(data,0,sizeof(data));
	memset(result,0,sizeof(result));
	ans=0;
	//scanf("%d%d",&n1,&m);
	fin >> n1 >> m;
	for(int i=1;i<=m;i++){
		//scanf("%d%d",&t1,&t2);
		fin >> t1 >> t2;
		all.push_back(t1);
		all.push_back(t2);
		data[t1][t2]=true;
	}
	return;
}
bool find(int a){
	for(int i=1;i<=n1;i++){
		if(data[a][i]==1&&!state[i]){//如果节点i与a相邻并且未被查找过
			state[i]=true;//标记i为已查找过
			if(result[i]==0//如果i未在前一个匹配M中
				||find(result[i])){//i在匹配M中，但是从与i相邻的节点出发可以有增广路
					result[i]=a;//记录查找成功记录
				return true;//返回查找成功
			}
		}
	}
	return false;
}
int main(){
	DIR * dp;
	char basePath[1000];
	file.clear();
	memset(basePath, '\0', sizeof(basePath));
	strcpy(basePath,"./BipartiteMatrix_add_nodenum_pathnum");
	reaFileList(basePath);

	for(int j=0;  j < file.size(); j++){
		out.clear();
		in.clear();
		all.clear();
		char* filename1=basePath;
		string filename = filename1;
		filename = filename + "/" + file[j];    //strcat(filename,"/");
		string ofile = "./DFS_MAX_MATCHING_RESULT/" + file[j];
		char* name = (char*) ofile.c_str();
		ofstream fout(name);
		string ofil = "./DFS_DRIVERNODE_RESULT/" + file[j];
		char* nam = (char*) ofil.c_str();
		ofstream ou(nam);

		init(filename);
		for(int i=1;i<=n1;i++){
			memset(state,0,sizeof(state));//清空上次搜索时的标记
			if(find(i))ans++;//从节点i尝试扩展
		}
		printf("%d\n",ans);
		for(int i=1;i<=n1;i++){
			if(result[i]!=0){
				fout << result[i] << "\t" << i << "\n";
				out.push_back(result[i]);
				in.push_back(i);
			}
		}

		// sort(out.begin(),out.end());
		// sort(in.begin(),in.end());
		// for(int i =0; i< out.size()-1; i++){
		// 	if(out[i] == out[i+1]){
		// 		cout << file[j] << "\n" <<  "out" << out[i];
		// 		cout << "error" << endl;
		// 		break;
		// 	}
		// }
		// for(int i =0; i< in.size()-1; i++){
		// 	if(in[i] == in[i+1]){
		// 		cout << file[j] << "\n" <<  "in" << in[i];
		// 		cout << "error" << endl;
		// 		break;
		// 	}
		// }

		//driver nodes
		//vector<int> all;
		//all.clear();
		//unique_copy(all1.begin(), all1.end(), all);
		sort(all.begin(), all.end());
		all.erase(unique(all.begin(), all.end()), all.end());
		for(int i = 0; i < in.size(); i++){
			for(int k = 0; k < all.size(); k++){
				if(in[i] == all[k]){
					all[k] = 0;
					//break;
				}
			}
		}
		for(int k = 0; k < all.size(); k++){
			if(all[k] !=0){
				ou << all[k] << "\n"; 
			}
		}
	}
	return 0;
}
