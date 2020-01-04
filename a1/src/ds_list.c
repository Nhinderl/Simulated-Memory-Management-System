/*
 * Name: Noah Hinderle
 * Student ID: 1053077
 * Email: nhinderl@uoguelph.ca
 * Date: September 29, 2019
 *
 */

#include <stdio.h>
#include "ds_memory.h"
#include "ds_list.h"

/*writes the head pointer to the first index in the file*/
int ds_create_list(){

    long negOne = -1, start = 0;
    int fails = 0, init = -1, written = -1;

    init = ds_init("list.bin");

    start = ds_malloc(sizeof(negOne));

    written = ds_write(start, &negOne, sizeof(long));

    fails = ds_finish();

    if((fails != 0) && (init == 0) && (written != -1)){
        return 0;
    }else{
        return -1;
    }

}

/*calls ds_init function to initialize the list*/
int ds_init_list(){

    int init = 0;
    
    init = ds_init("list.bin");

    if(init != -1){
        return 0;
    }else{
        return -1;
    }

}

/*replaces the value at the given index with value*/
int ds_replace(int value, long index){

    int i = 0, wroteProper = 0;
    struct ds_list_item_struct previous_struct, replace_struct;

    ds_read(&previous_struct.next, 0, sizeof(long));

    while((previous_struct.next != -1) && (i < index)){
        ds_read(&previous_struct, previous_struct.next, sizeof(previous_struct));
        i++;
    }

    if((i == index) && (previous_struct.next != -1)){

        previous_struct.item = value;
        ds_write(previous_struct.next - sizeof(previous_struct) - 1, &previous_struct, sizeof(previous_struct));
        return 0;

    }else if(previous_struct.next == -1){
        
        replace_struct.item = value;
        replace_struct.next = previous_struct.next;

        previous_struct.next = ds_malloc(sizeof(struct ds_list_item_struct));

        wroteProper = ds_write(previous_struct.next, &replace_struct, sizeof(replace_struct));

        if(index == 0){

            wroteProper = ds_write(0, &previous_struct.next, sizeof(long));

        }else{

            wroteProper = ds_write(previous_struct.next - sizeof(previous_struct) - 1, &previous_struct, sizeof(previous_struct));

        }

        if(wroteProper != -1){
            return 0;
        }else{
            return -1;
        }

    }else{
        return -1;
    }

}

/*inserts value into the given index*/
int ds_insert(int value, long index){

    int wroteProper = 0, i = 0;
    struct ds_list_item_struct previous_struct, replace_struct;

    ds_read(&previous_struct.next, 0, sizeof(long));

    while((previous_struct.next != -1) && (i < index)){
        ds_read(&previous_struct, previous_struct.next, sizeof(previous_struct));
        i++;
    }

    replace_struct.item = value;
    replace_struct.next = previous_struct.next;

    previous_struct.next = ds_malloc(sizeof(struct ds_list_item_struct));

    wroteProper = ds_write(previous_struct.next, &replace_struct, sizeof(replace_struct));

    if(index == 0){

        wroteProper = ds_write(0, &previous_struct.next, sizeof(long));

    }else{

        wroteProper = ds_write(previous_struct.next - sizeof(previous_struct) - 1, &previous_struct, sizeof(previous_struct));

    }

    if(wroteProper != -1){
        return 0;
    }else{
        return -1;
    }
}

/*deletes the value at the given index*/
int ds_delete(long index){

    int i = 0;
    struct ds_list_item_struct previous_struct, delete_struct;

    ds_read(&previous_struct.next, 0, sizeof(long));

    while((previous_struct.next != -1) && (i < index)){
        ds_read(&previous_struct, previous_struct.next, sizeof(previous_struct));
        i++;
    }

    if(i == index){

        ds_read(&delete_struct, previous_struct.next, sizeof(delete_struct));
        previous_struct.next = delete_struct.next;
        ds_write(previous_struct.next - (2 * sizeof(previous_struct)) - 2, &previous_struct, sizeof(previous_struct));
        return 0;

    }else{

        return -1;
    
    }

}

/*swaps the values at the two indices given*/
int ds_swap(long index1, long index2){

    int i = 0, j = 0, temp = 0;

    struct ds_list_item_struct item1, item2;

    ds_read(&item1.next, 0, sizeof(long));

    if(index1 > index2){

        while((item1.next != -1) && (i < index1 + 1)){

            ds_read(&item1, item1.next, sizeof(item2));
            i++;

        }

        ds_read(&item2.next, 0, sizeof(long));

        while((item2.next != -1) && (j < index2 + 1)){

            ds_read(&item2, item2.next, sizeof(item2));
            j++;

        }

    }else if(index1 < index2){

        while((item1.next != -1) && (i < index1 + 1)){

            ds_read(&item1, item1.next, sizeof(item2));
            i++;

        }

        if(item1.next == -1){

            return -1;

        }else{

            item2 = item1;

            while((item2.next != -1) && (i < index2 + 1)){

                ds_read(&item2, item2.next, sizeof(item2));
                i++;

            }
            
        }

    }else{

        return -1;

    }
        
    temp = item1.item;
    item1.item = item2.item;
    item2.item = temp;

    ds_write(item1.next + ((index2 - index1 - 1) * (sizeof(item2) + 1)), &item2, sizeof(item2));
    /*fix this write statement*/
    ds_write(item1.next - sizeof(item1) - 1, &item1, sizeof(item1));

    return 0;

}

/*finds the target and returns its index*/
long ds_find(int target){

    int i = 0;
    struct ds_list_item_struct next_struct;

    ds_read(&next_struct.next, 0, sizeof(long));
    ds_read(&next_struct.item, next_struct.next, sizeof(int));

    while((next_struct.next != -1) && (next_struct.item != target)){
        ds_read(&next_struct, next_struct.next, sizeof(next_struct));
        i++;
    }

    if(next_struct.next == -1){
        if(next_struct.item == target){
            return i - 1;
        }else{
            return -1;
        }
    }else{
        return i - 1;
    }

}

/*reads values into the list from a txt file*/
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

/*calls ds_finish function to print reads and writes and end the list*/
int ds_finish_list(){

    int finished = 0;

    finished = ds_finish();

    if(finished == 1){
        return 0;
    }else{
        return -1;
    }

}

/*helper function to print out the values in the list and their indices*/
void show_list(){

    long loc;
    struct ds_list_item_struct li;

    /*ds_init_test();*/

    ds_read(&loc, 0, sizeof(long));

    while(loc != -1){
        ds_read(&li, loc, sizeof(li));
        printf("Location: %ld\nItem: %d\nNext: %ld\n", loc, li.item, li.next);
        loc = li.next;
    }

}