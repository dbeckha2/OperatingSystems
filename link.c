#include <stdio.h>
#include <stdlib.h>

//very simple linked list struct
struct ll {
    int x;
    //Add pointer info
	struct ll *next;
	struct ll *prev;
};
//void print_list(struct ll *list );
//add a node to the list
void add_node(struct ll **list, int y){
   struct ll *nn_ptr;
    struct ll *prevn_ptr;
    struct ll *curn_ptr;
    
    //creat space for the new node using malloc
   nn_ptr = (struct ll *)malloc(sizeof(struct ll ));	
    
    
    //if malloc worked, add data
   nn_ptr->x = y;
 
   curn_ptr = *list;
    prevn_ptr = NULL;
    while( curn_ptr!=NULL && nn_ptr->x>curn_ptr->x ){
       prevn_ptr = curn_ptr;
	 curn_ptr = curn_ptr->next;
        
    }


    //insrt the new node
   //firt if at start of the list
    if (prevn_ptr == NULL && curn_ptr !=NULL) {

	nn_ptr->next = curn_ptr;
	curn_ptr->prev = nn_ptr;
	nn_ptr->prev = NULL;
	//adding to beginnin of the head
	*list = nn_ptr;
    }
    else if(prevn_ptr != NULL && curn_ptr !=NULL){
	prevn_ptr->next  = nn_ptr;
	nn_ptr->next = curn_ptr;
	nn_ptr->prev = prevn_ptr;
	curn_ptr->prev = nn_ptr;
	}
    else if (prevn_ptr!=NULL && curn_ptr == NULL){
	prevn_ptr->next = nn_ptr;
	nn_ptr->prev = prevn_ptr;
	nn_ptr->next = curn_ptr;
    }
    else{
	*list = nn_ptr;
	nn_ptr->next = NULL;
	nn_ptr->prev = NULL;
    }


}

//remove a node containing y
void remove_node(struct ll **list, int y){
  //pointers
    struct ll *prev_n;
    struct ll *cur_n;
    struct ll *temp;
    
    //check if its the first node
   if((*list)->x == y) {
      //remove the first node
	temp = *list;

	*list = (*list)->next;
//cec


   	if((*list)->next == NULL){
	*list ==NULL;
        
        //make sure to free the old node
       }
	 free(temp);
    }
    else{
        //find the correct node
       prev_n = (*list);
     cur_n = (*list)->next;

      while(cur_n->x!=y &&cur_n!=NULL){
	//	printf("%d \n",cur_n->x);
		prev_n= cur_n;
		cur_n = cur_n->next;
	        }
//	printf("%d after while\n",cur_n->x);

	
if (cur_n->next == NULL){
	temp = cur_n;
	cur_n = cur_n->prev;
	cur_n->next = NULL;
	prev_n = cur_n->prev;

free(temp);
	
} 
	else if(cur_n->next!=NULL){
	temp = cur_n;
	prev_n->next= cur_n->next;
	cur_n->next->prev = prev_n;
	cur_n = prev_n->next;


       
       free(temp);
	}
        
       
       
    }

}


//print the list
void print_list(struct ll *list ){

	while(list!=NULL){
		printf("%d", list->x);
		list=list->next;
	}
	printf("\n\n");


}



int main(int argc, const char * argv[]) {
    
    struct ll* test=0;
    add_node(&test, 10);
    add_node(&test, 8);
    add_node(&test, 8);
    add_node(&test, 11);
    add_node(&test, 9);
    print_list(test);
    remove_node(&test, 11);
    print_list(test);
    remove_node(&test, 9);
    print_list(test);
    return 0;
}
