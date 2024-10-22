#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "arg sxal" <<std::endl;
        	return 1;        }
	int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
	{
        	std::cout << "sxal" << std::endl;
        	return 1;
   	 }
    	 char arr[32];
    	 ssize_t count;
	 while ((count = read(fd, arr, sizeof(arr))) > 0)
	 {
        	 std::cout.write(arr,count);
   	 }
	 if (count == -1)
	 {
         	std::cout << "read sxal"<< std::endl;
         	return 1;
   	 }
    	 if (close(fd) == -1)
	 {
        	 std::cout << "close sxal" << std::endl;
        	 return 1;
    	 }

	 return 0;
}

