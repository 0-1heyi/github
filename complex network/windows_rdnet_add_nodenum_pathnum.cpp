#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <dir.h>
using namespace std;
void getAllFiles(string path, vector<string>& files) 
{ 
  	//文件句柄 
 	long  hFile  =  0; 
  	//文件信息 
	struct _finddata_t fileinfo; 
  	string p; 
  	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {	 
    		do{      
    			if((fileinfo.attrib & _A_SUBDIR)) { 
        				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) {
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					getFilesall( p.assign(path).append("\\").append(fileinfo.name), files ); 
				}
			} 
			else{ 
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			} 
		}while(_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile); 
	} 
}
int main()
{
	char* filePath = "//home//heyaoji//Documents//complex network//BipartiteMatrix";
	vector<string> files;
	char* distAll = "AllFiles.txt";
	getFilesall(filePath, files);
	ofstream ofn(distAll);
	int size = file.size();
	for(int i=0; i<size; i++){
		ofn << files[i] << endl;
	}
	ofn.close();
}