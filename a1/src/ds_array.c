/*
 * Name: Noah Hinderle
 * Student ID: 1053077
 * Email: nhinderl@uoguelph.ca
 * Date: September 29, 2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ds_array.h"
#include "ds_memory.h"

long elements;

/*allocates file space for the long that holds the amount of elements in the array*/
int ds_create_array(){

    long start, zeroNum = 0, writeOk = -1, initOk = -1;

    initOk = ds_init("array.bin");
    start = ds_malloc(sizeof(long));

    ds_malloc(sizeof(int) * MAX_ELEMENTS);

    writeOk = ds_write(start, &zeroNum, sizeof(long));

    ds_finish();

    if((writeOk != -1) && (initOk != -1)){
        return 0;
    }else{
        return -1;
    }

}

/*reads in the number of elements that were previously stored in the first long value*/
int ds_init_array(){

    int initOk = -1;
    
    initOk = ds_init("array.bin");

    ds_read(&elements, 0, sizeof(long));

    if(initOk != -1){
        return 0;
    }else{
        return -1;
    }

}

/*replaces the values at index with value*/
int ds_replace(int value, long index){

    long returnVal = -1;

    returnVal = ds_write((index * sizeof(int)) + sizeof(long) + 1, &value, sizeof(value));

    if(returnVal != -1){
        return 0;
    }else{
        return -1;
    }
}

/*inserts the value given into location index and shifts the rest of the array up by 1 element*/
int ds_insert(int value, long index){

    int tempVal = 0, writeOk = -1;
    long tempIndex = (index * sizeof(int)) + sizeof(long) + 1;

    if(index == elements){
        ds_write(tempIndex, &value, sizeof(value));
        elements++;
        return 0;
    }else{
        ds_read(&tempVal, tempIndex, sizeof(value));
        ds_write(tempIndex, &value, sizeof(value));
        index++;
        ds_insert(tempVal, index);
    }

    if(writeOk != -1){
        return 0;
    }else{
        return -1;
    }

}

/*deletes the value found and index and shifts the rest of the array backwards by 1 element*/
int ds_delete(long index){

    int tempVal = 0, writeOk = -1;
    long tempInd = (index * sizeof(int)) + sizeof(long) + 1;

    if(index == elements){
        elements--;
        return 0;
    }else{
        ds_read(&tempVal, tempInd + sizeof(int), sizeof(int));
        writeOk = ds_write(tempInd, &tempVal, sizeof(int));
        index++;
        ds_delete(index);
    }

    if(writeOk != -1){
        return 0;
    }else{
        return -1;
    }
    

}

/*swaps the values at the given indices*/
int ds_swap(long index1, long index2){

    int tempInt1 = 0, tempInt2 = 0;
    long success1 = 0, success2 = 0;
    long tempInd1 = (index1 * sizeof(int)) + sizeof(long) + 1;
    long tempInd2 = (index2 * sizeof(int)) + sizeof(long) + 1;
    
    ds_read(&tempInt1, tempInd1, sizeof(int));
    ds_read(&tempInt2, tempInd2, sizeof(int));

    success1 = ds_write(tempInd1, &tempInt2, sizeof(tempInt2));
    success2 = ds_write(tempInd2, &tempInt1, sizeof(tempInt1));

    if((success1 != -1) && (success2 != -1)){
        return 0;
    }else{
        return -1;
    }

}

/*finds the target value and returns its index*/
long ds_find(int target){

    int i = 0, num = 0;
    long index = -1, start = 0;

    for(i = 0; i < elements; i++){
        start = (i * sizeof(int)) + sizeof(long) + 1;
        ds_read(&num, start, sizeof(target));
        if(num == target){
            index = i;
        }
    }
    return index;
}

/*reads elements into the array from a txt file*/
int ds_read_elements(char *filename){

    int num = 0, i = 0;
    FILE *fp;
    if((fp = fopen(filename, "r")) == NULL){
        return -1;
    }

    fseek(fp, 0, SEEK_SET);

    while(fscanf(fp, "%d\n", &num) != EOF){

        ds_insert(num, i);
        i++;
        
    }

    return 0;
}

/*calls the ds_finish function and writes the number of elements of the array back into the first spot*/
int ds_finish_array(){

    int success = 0;

    success = ds_write(0, &elements, sizeof(long));
    ds_finish();

    if(success != 0){
        return 0;
    }else{
        return -1;
    }

}

/*helper function to print out the array's elements and indices*/
void ds_show_array(int value){

    long index = -1;

    index = ds_find(value);

    printf("Elements: %ld\nIndex: %ld\nValue: %d\n", elements, index, value);

}