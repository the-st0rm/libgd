#include <stdio.h>
#include <stdlib.h>
#include "gd.h"
#include <string.h>


/*
   This file fuzzes webp function in libgd
   reading an image converting it to webp in memory.
   gdImageWebpPtr
*/

int read_file(char *file_name, char** buffer)
{
	FILE *fp;
	size_t size;
	int result;

	fp = fopen(file_name, "rb");
	//printf("openning: %s\n", file_name);
	if (fp == NULL)
	{
		printf("Failed to open: %s\n", file_name);
		return -1;
	}
	fseek(fp, 0L, SEEK_END);
	size=ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	if (size>0)
	{
		*buffer = malloc(size);
		result = fread(*buffer,1,size,fp);
  		if (result!=size) 
  		{
			printf("Reading error\n"); 
			fclose(fp);
			return -1;
		}
		else
		{
			fclose(fp);
			return result;
		}		
	}
	return -1;
}


int main(int argc, char **argv)
{
	gdImagePtr ptr;
	char* buffer;
	int size;
	int res;

	if (argc<2)
	{
		printf("Usage: %s <input_file>\n", argv[0]);
		return 0;
	}

	size = read_file(argv[1], &buffer);
	if (size <= 0)
	{
		return 0;
	}



	
	printf("openning jpg\n");
	ptr = gdImageCreateFromJpegPtr(size, (void *)buffer);
	printf("ptr: %p\n", ptr);
	//gdImagePtr ptr2;
	int new_size;
	if (ptr == NULL)
	{
		return 0;
	}

	gdImageWebpPtr(ptr, &new_size); 
	return 0;
}
