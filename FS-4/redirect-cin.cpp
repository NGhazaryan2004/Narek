#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cerrno>
void initialize(int argc,char** argv){
	if(argc!=2){
		std::cerr<<"argc error";
		exit(errno);
	}
	int fd = open(argv[1],O_RDONLY);
	if(fd == -1){
		std::cerr<<"open error";
		exit(errno);
	}
	if(dup2(fd,0) > 0){
		std::cout << "cant dup file";
		close(fd);
		exit(errno);
	}
	close(fd);
}

int main(int argc,char** argv){

	initialize(argc,argv);
	
	std::string input;
	std::cin >> input;
	std::string reversed(input.rbegin(),input.rend());
	std::cout<<reversed<< std::endl;

	return 0;
		
}
