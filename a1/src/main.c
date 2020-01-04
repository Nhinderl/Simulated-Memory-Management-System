#include <stdio.h>
#include <stdlib.h>
#include "ds_memory.h"
#include "ds_list.h"

int main(){

  FILE *fp, *fp2;
  int i = 0, j = 0, randNum1, randNum2;
  int k = 0, reads[30][10], writes[30][10];

  fp2 = fopen("ds_delete_list.csv", "w");

  /*prints the headings of the file*/
  for(i = 10; i <= 100; i += 10){
    if(i != 10){
      fprintf(fp2, ",");
    }
    fprintf(fp2, "\"Reads=%d\",\"Writes=%d\"", i, i);
  }
  fprintf(fp2, "\n");

  for(j = 10; j <= 100; j += 10){

    fp = fopen("Test.txt", "w");

    for(i = 0; i < j; i ++){

      randNum1 = (rand() % j) + 1;
      fprintf(fp, "%d\n", randNum1);

    }

    fclose(fp);
    
    for(i = 0; i < 30; i++){

      ds_create("list.bin", 2048);

      ds_create_list();

      ds_init_list();

      ds_read_elements("Test.txt");
      ds_finish_list();
      ds_create_list();
      ds_init_list();

      randNum2 = (rand() % j) + 1;
      randNum1 = (rand() % j) + 1;

      ds_delete(randNum1);

      reads[i][(j / 10) - 1] = getReads();
      writes[i][(j / 10) - 1] = getWrites();

      ds_finish_list();

    }

    printf("End of %d values\n", j);

  }

  for(i = 0; i < 30; i++){
    for(k = 0; k < 10; k++){
      if(k != 0){
        fprintf(fp2, ",");
      }
      fprintf(fp2, "\"%d\",\"%d\"", reads[i][k], writes[i][k]);
    }
    fprintf(fp2, "\n");
  }

  fclose(fp2);
    
return 0;

}