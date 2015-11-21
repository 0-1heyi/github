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

int main()
{
	return 0;
}