#include<stdio.h>
#include<string.h>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
int n1,n2,m,ans;
vector<int> result;//记录V2中的点匹配的点的编号
vector<int> state;//记录V2中的每个点是否被搜索过
vector<vector<int> > data;//邻接矩阵true代表有边相连

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


void init(){
	int t1,t2;
	data.clear();
	result.clear();
	ans=0;
	scanf("%d%d%d",&n1,&n2,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&t1,&t2);
		//data[t1][t2]=true;
		data[t1].push_back(t2);
	}
	return;
}
bool find(int a){
	for(int i=1;i<=n2;i++){
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
int main()
{
	string filename1, filename2;

	filename1 = "test";
	filename2 = "";

	ofstream fout;
	//fout.open(filename2);

	int number_node = max_node_number_link_list(filename1) +1;   //Warming:maybe err
	init();
	for(int i=1;i<=n1;i++){
		memset(state,0,sizeof(state));//清空上次搜索时的标记
		if(find(i))ans++;//从节点i尝试扩展
	}
	printf("%d\n",ans);
	return 0;
}
