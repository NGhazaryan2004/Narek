#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;


int main(int argc,char** argv){
	if(argc != 2){
		cout<<"argc sxal"<<endl;
		return 1;
	}
	int fd = open(argv[1],O_RDWR);
	if(fd == -1){
		cout<<"open sxal"<<endl;
		return 1;
	}
	char arr[2048];
	ssize_t count;
	while((count = read(fd,arr,sizeof(arr)))>0){
		lseek(fd,-count,SEEK_CUR);
		if(write(fd,"\0",count) == -1){
			cout<<"write scal"<<endl;
			return 1;
		}
	}

	if(count == -1){
		cout<<"read sxal"<<endl;
	}

	close(fd);

	if(unlink(argv[1]) == -1){
		cout<<"unlink sxal"<<endl;
		return 1;		
	}
	return 0;
}
