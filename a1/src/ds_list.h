/*
 * Name: Noah Hinderle
 * Student ID: 1053077
 * Email: nhinderl@uoguelph.ca
 * Date: September 29, 2019
 *
 */

struct ds_list_item_struct{
    int item;
    long next;
};

int ds_create_list();
int ds_init_list();
int ds_replace(int, long);
int ds_insert(int, long);
int ds_delete(long);
int ds_swap(long, long);
long ds_find(int);
int ds_read_elements(char *);
int ds_finish_list();

void show_list();