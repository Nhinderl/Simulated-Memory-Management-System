/*
 * Name: Noah Hinderle
 * Student ID: 1053077
 * Email: nhinderl@uoguelph.ca
 * Date: September 29, 2019
 *
 */

#define MAX_BLOCKS 4096

struct ds_counts_struct {
	int reads;
	int writes;
};

struct ds_blocks_struct {
	long start;
	long length;
	char alloced;
};

struct ds_file_struct {
	FILE *fp;
	struct ds_blocks_struct block[MAX_BLOCKS];
};

int ds_create(char *, long);
int ds_init(char *);
long ds_malloc(long);
void ds_free(long);
void *ds_read(void *, long, long);
long ds_write(long, void *, long);
void ds_init_test();
int ds_finish();
int getReads();
int getWrites();
