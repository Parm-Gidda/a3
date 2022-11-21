#include "my_malloc.h"
#include "list.h"

int main(){
    printf("sup\n");

    mem_init();

  //  int testing[50] = (int*)my_malloc(200);


    my_malloc(200);
   my_malloc(400);
    int* test = (int*)my_malloc(18400);
   
   my_malloc(200);

   if(my_malloc(2000) == NULL){
       printf("cant put in *************8\n");
   }

    testPrint();

    my_free(test);

     // if(my_malloc(200) == NULL){
       //printf("didnt fit dawg *************8\n");
    // }



    //  testPrint(); 

 

  
}