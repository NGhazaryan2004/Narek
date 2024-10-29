#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
int main(int argc,char** argv){
	if(argc!=2){
		std::cerr<<"argc error";
		exit(errno);
	}
	int fd = open(argv[1],O_CREAT|O_WRONLY|O_TRUNC,0644);
	if(fd == -1){
		std::cerr<<"open error";
		exit(errno);
	}
	int newfd = dup(fd);
	if(newfd == -1){
		std::cerr<<"dup error";
		exit(errno);
	}
	if(write(fd,"First line\n",12)==-1){
		std::cerr<<"write error";
		close(fd);
		close(newfd);
		exit(errno);
	}
	if(write(newfd,"Second line\n",13)== -1){
		std::cerr<<"write error";
		close(fd);
		close(newfd);
		exit(errno);
	}
	return 0;
}

