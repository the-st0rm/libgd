#include <stdio.h>
#include <stdlib.h>
#include "gd.h"
#include <string.h>


/*
   This file fuzzes webp function in libgd
   reading an image converting it to webp and write the output to a file.
   gdImageWebp
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


int read_extenstion(char* buffer, size_t size, char* ext)
{
	strncpy(ext, (char *)(buffer+size-5), 5);
	ext[5] = 0;
	if (strcmp(ext, ".pngX") == 0)
		return 1;
	if (strcmp(ext, ".gifX") == 0)
		return 2;
	if (strcmp(ext, ".jpgX") == 0)
		return 3;
	if (strcmp(ext, ".tgaX") == 0)
		return 4;
	if (strcmp(ext, ".tiff") == 0)
		return 5;
	if (strcmp(ext, ".webp") == 0)
		return 6;
	return -1;
}


int fuzz_png()
{
	return 0;
}

int fuzz_gif()
{
	return 0;
}

int fuzz_jpg()
{
	return 0;
}

int fuzz_tga()
{
	return 0;
}

int fuzz_tiff()
{
	return 0;
}

int fuzz_webp()
{
	return 0;
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

	char ext[6];
	res = read_extenstion(buffer, size, ext);
	if (res < 0)
	{
		//printf("ext: %s\n", ext);
		//printf("extention not correct\n");
		exit(0);
	}

	
	switch (res)
	{
		case 1:
		//open png
			printf("openning png\n");
			ptr = gdImageCreateFromPngPtr(size-5, (void *)buffer);
			break;
		case 2:
		//open gif
			printf("openning gif\n");
			ptr = gdImageCreateFromGifPtr(size-5, (void *)buffer);
			break;
		case 3:
		//open jpg
			printf("openning jpg\n");
			ptr = gdImageCreateFromJpegPtr(size-5, (void *)buffer);
			break;
		case 4:
		//open tga
			printf("openning tga\n");
			ptr = gdImageCreateFromTgaPtr(size-5, (void *)buffer);
			break;
		case 5:
		//open tiff
			printf("openning tiff\n");
			ptr = gdImageCreateFromTiffPtr(size-5, (void *)buffer);
			break;
		// case 6:
		// //open webp
		// 	printf("openning webp\n");
		// 	exit(0);
		// 	//gdImageWebpPtr()
		// 	break;
		default:
			printf("error!\n");
			exit(0);
	}
	printf("ptr: %p\n", ptr);
	//gdImagePtr ptr2;
	int new_size;
	FILE *output;
	output = fopen("/dev/null", "wb");
	gdImageWebp(ptr, output); 
	
	return 0;

	// char * filename = argv[1];
	// printf("opening: %s\n", filename);
	// FILE *in;
	// in = fopen(filename, "r");
	// if (in!=NULL)
	// {
	// 	im = gdImageCreateFromPng(in);
	// 	printf("imageptr: %p\n", im);
	// }
	//printf("Main\n");




	return 0;
}
