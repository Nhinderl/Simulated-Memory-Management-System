/*
 * Name: Noah Hinderle
 * Student ID: 1053077
 * Email: nhinderl@uoguelph.ca
 * Date: September 29, 2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

/*creates a file with the name given and of the size given*/
int ds_create(char *filename, long size){

	FILE *fp;
	int i = 1;
	int writeOk = -1;

	if((fp = fopen(filename, "wb")) == NULL){
		printf("There was an error in opening the file");
		return -1;
	}

	ds_file.block[0].start = 0;
	ds_file.block[0].length = size;
	ds_file.block[0].alloced = 0;

	for(i = 1; i < MAX_BLOCKS; i++){

		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;

	}

	writeOk = fwrite(ds_file.block, sizeof(ds_file.block), 1, fp);

	for(i = 1; i <= size; i++){
		fprintf(fp, "%d", 0);
	}
	
	fclose(fp);

	if(writeOk != -1){
		return 0;
	}else{
		return -1;
	}
}

/*reads in the header block from the file*/
int ds_init(char *filename){

	int okFread = 0;

	if((ds_file.fp = fopen(filename, "rb+")) == NULL){
		printf("There was an error in opening the file");
		return -1;
	}

	okFread = fread(ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);

	ds_counts.reads = 0;
	ds_counts.writes = 0;

	if(okFread != 0){
		return 0;
	}else{
		return -1;
	}
}

/*helper function to print out the first 100 malloced blocks of file space*/
void ds_init_test(){

	int i = 0;

	printf("Number:   Start:   Length:   Alloced:\n");

	for(i = 0; i < 100; i++){

		printf("  %d         %ld         %ld         %d   \n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);

	}

}

/*allocates space in the file of requested size and returns the starting point of that block*/
long ds_malloc(long amount){

	int i = 0, found = 0, nextAlloc = 0;
	long tempStart = 0, tempLength = 0;

	for(i = 0; i < MAX_BLOCKS; i++){
		if((ds_file.block[i].length >= amount) && (ds_file.block[i].alloced == 0)){
			tempLength = ds_file.block[i].length;
			ds_file.block[i].length = amount;
			ds_file.block[i].alloced = 1;
			tempStart = ds_file.block[i].start;
			found = 1;
		}
	}

	if(found == 1){
		for(i = 0; i < MAX_BLOCKS; i++){
			if((ds_file.block[i].length == 0) && (nextAlloc == 0)){
				ds_file.block[i].start = tempStart + amount + 1; 
				ds_file.block[i].length = tempLength - amount;
				ds_file.block[i].alloced = 0;
				nextAlloc = 1;
			}
		}
	}


	if(found == 1){
		return tempStart;
	}else{
		return -1;
	}

}

/*frees the block of previously allocated file space*/
void ds_free(long start){

	int i = 0;

	for(i = 0; i < MAX_BLOCKS;i++){
		if(ds_file.block[i].start == start){
			ds_file.block[i].alloced = 0;
		}
	}

}

/*reads bytes bytes in from the start position into ptr*/
void *ds_read(void *ptr, long start, long bytes){

	fseek(ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET);

	fread(ptr, bytes, 1, ds_file.fp);

	ds_counts.reads++;

	if(ptr != NULL){
		return ptr;
	}else{
		return NULL;
	}

}

/*writes bytes bytes into the start position from ptr*/
long ds_write(long start, void *ptr, long bytes){

	long returnVal = 0;

	fseek(ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET);
	returnVal = fwrite(ptr, bytes, 1, ds_file.fp);

	ds_counts.writes++;

	if(returnVal != 0){
		return start;
	}else{
		return -1;
	}
}

/*writes the header block back into the file and prints the number of reads and writes
 *closes the file 
 */
int ds_finish(){

	int fWritten = 0;

	fseek(ds_file.fp, 0, SEEK_SET);
	fWritten = fwrite(ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);
	printf("reads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);
	fclose(ds_file.fp);

	
	if(fWritten != 0){
		return 1;
	}else{
		return 0;
	}
}

/*helper function for the main to get the number of reads*/
int getReads(){
	return ds_counts.reads;
}

/*helper function to get the number of writes*/
int getWrites(){
	return ds_counts.writes;
}

