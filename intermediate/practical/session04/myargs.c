#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//int main(int argc, char** argv)
int main(int argc, char* argv[])
{
	printf("Num of args = %d\n", argc);

	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	return 0;
}
