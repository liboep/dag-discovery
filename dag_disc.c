#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct noedges 
{ 
	int no_edge_val; 

	struct noedges *next_ne; 
};

struct noedges *head_ne = NULL;
struct noedges *current_ne = NULL;

struct discov_node
{
    int disc_node;

    struct discov_node *next_d;
};

struct discov_node *head_d = NULL;
struct discov_node *current_d = NULL;

struct edges_map
{
    int from;
    int to;
    struct edges_map * next_m;
};
struct edges_map *head_m = NULL;
struct edges_map *current_m = NULL;


void check_map(int edges_num){
    struct edges_map *curr_m = head_m;
    struct edges_map *prev_m = head_m;

    if(edges_num == 1){
        if((is_in_result(curr_m->to) != 1) && (is_in_no_edges(curr_m->to) != 1)){
            insertNoedges(curr_m->to);
        }


    }else{
        curr_m = curr_m->next_m;
        if((prev_m->to == curr_m->from) && (prev_m->from == prev_m->to)){
            printf("\nThe graph is not DAG.\n\n");
            // printf("No incoming edges nodes not discovered:");
            // printNoedges();
            // printf("\n\n");
            // printf("No incoming edges nodes discovered:");
            // printResult();
            // printf("\n");
            exit(0);
        }else{
            if((is_in_result(curr_m->to) != 1) && (is_in_no_edges(curr_m->to) != 1)){
                insertNoedges(curr_m->to);
            }
            if((is_in_result(prev_m->to) != 1) && (is_in_no_edges(prev_m->to) != 1)){
                insertNoedges(prev_m->to);
            }
            if((is_in_result(curr_m->from) != 1) && (is_in_no_edges(curr_m->from) != 1)){
                insertNoedges(curr_m->from);
            }
            if((is_in_result(prev_m->from) != 1) && (is_in_no_edges(prev_m->from) != 1)){
                insertNoedges(prev_m->from);
            }
        }

    }
    
    
    

}

int is_in_result(int disc_node) {

    struct discov_node* current_d = head_d;
    int found=0;

    //if list is empty
    if(head_d == NULL) {
        return found;
    }

    while(current_d != NULL)
    {
        if(current_d->disc_node == disc_node)
        {
            found = 1;
            return found;
        }

        current_d = current_d->next_d;

    }
    return found;

}

int is_in_no_edges(int no_edge_val) {

    struct noedges* current_ne = head_ne;
    int found=0;

    if(head_ne == NULL) {
        return found;
    }

    while(current_ne != NULL)
    {
        if(current_ne->no_edge_val == no_edge_val)
        {
            
            found = 1;
            return found;
        }

        current_ne = current_ne->next_ne;

    }
    return found;

}

int is_no_edges_empty(){
    struct noedges* current_ne = head_ne;
    int found=0;

    if(head_ne == NULL) {
        found = 1;
        return found;
    }else{
        return found;
    }

}

void search_map_for_ne_nodes (int nodes_num){

    struct edges_map *curr = head_m;
    struct edges_map *prev = head_m;
    int prvs, crnt, diff, flag=0;
    
    prvs = nodes_num;
    curr = curr->next_m;
    crnt = curr->to;

    if((prvs - crnt > 1))
    {

        do
        {
            diff = prvs - crnt - 1;
            if((is_in_result(prvs) != 1) && (is_in_no_edges(prvs) != 1)){
                flag = 1;
                insertNoedges(prvs);
            }
            diff--;
            prvs--;

        }while(diff!=0);
        
    
    }
    

    while(curr != NULL) {

        prvs = prev->to;
        crnt = curr->to;


        if ((crnt - prvs == 1) || (prvs - crnt == 1) || (crnt - prvs == 0)){
            prev = prev->next_m;
            curr = curr->next_m;
        }
        else if((crnt - prvs > 1))
        {
            
            do
            {
                diff = crnt - prvs - 1;
                prvs++;
                if((is_in_result(prvs) != 1) && (is_in_no_edges(prvs) != 1)){
                    flag = 1;
                    insertNoedges(prvs);
                }
                diff--;

            }while(diff!=0);
            
            prev = prev->next_m;
            curr = curr->next_m;
        
        }else if((prvs - crnt > 1))
        {
            

            do
            {
                diff = prvs - crnt - 1;
                prvs--;
                if((is_in_result(prvs) != 1) && (is_in_no_edges(prvs) != 1)){
                    flag = 1;
                    insertNoedges(prvs);
                }
                diff--;

            }while(diff!=0);
            
            prev = prev->next_m;
            curr = curr->next_m;
        
        }



    }

    prvs = crnt;
    crnt = 0;

    
    if((prvs - crnt > 1))
    {

        do
        {
            diff = prvs - crnt - 1;
            prvs--;
            if((is_in_result(prvs) != 1) && (is_in_no_edges(prvs) != 1)){
                flag = 1;
                insertNoedges(prvs);
            }
            diff--;
        }while(diff<0);
        
    
    }     
    
    
    
    if((flag==0) && (is_no_edges_empty() == 1))
    {
        printf("The graph is not DAG.\n\n");
        // printf("No incoming edges nodes not discovered:");
        // printNoedges();
        // printf("\n\n");
        // printf("No incoming edges nodes discovered:");
        // printResult();
        // printf("\n");
        printf("\n");
        printMap();
        printf("\n\n");
        
        exit(0);
    }
    
    

}


void insertMap(int from, int to) {
   //create a link
   struct edges_map *link = (struct edges_map*) malloc(sizeof(struct edges_map));
	
   link->from = from;
   link->to = to;
	
   //point it to old first node
   link->next_m = head_m;
	
   //point first to new first node
   head_m = link;
}


void insertNoedges(int no_edge_val) {

   struct noedges *link_ne = (struct noedges*) malloc(sizeof(struct noedges));
	
   link_ne->no_edge_val = no_edge_val;
   
   link_ne->next_ne = head_ne;
	
   head_ne = link_ne;
}


void insertResult(int disc_node) {

   struct discov_node *link_d = (struct discov_node*) malloc(sizeof(struct discov_node));
	
   link_d->disc_node = disc_node;
   
   link_d->next_d = head_d;
	
   head_d = link_d;
}


void printMap() {
   struct edges_map *ptr = head_m;

   //start from the beginning
   while(ptr != NULL) {
      printf("%d %d\n",ptr->from,ptr->to);
      ptr = ptr->next_m;
   }
	
   printf("\n");
}


void printNoedges() {
    struct noedges *ptr_ne = head_ne;
    if(ptr_ne == NULL)
    {
        printf(" 'List empty.'\n");
    }
    while(ptr_ne != NULL) 
    {
        printf(" %d",ptr_ne->no_edge_val);
        ptr_ne = ptr_ne->next_ne;
    }

}


void printResult() {
    struct discov_node *ptr_d = head_d;
    if(ptr_d == NULL)
    {
        printf("List empty.\n");
    }
    while(ptr_d != NULL) 
    {
        printf(" %d",ptr_d->disc_node);
        ptr_d = ptr_d->next_d;
    }

}


int deleteMap(int from, int edges_num) {
        
    struct edges_map *previous, *current;

    if(head_m == NULL) {
        return NULL;
    }
    
     while (head_m != NULL && head_m->from == from)
    {
        // Get reference of head_m node
        previous = head_m;

        // Adjust head_m node link
        head_m = head_m->next_m;
        
        edges_num--;
        // Delete prev since it contains reference to head_m node
        free(previous);

    }
    
    current = head_m;
    previous = NULL;

    while (current != NULL)
    {
        if (current->from == from)
        {
            // Adjust links for previous node
            if (previous != NULL) 
            {
                previous->next_m = current->next_m;
                edges_num--;
            }
            
            // Delete current node
            free(current);

            current = previous->next_m;
        } 
        else
        {
            previous = current;
            current = current->next_m;
        }        

    }
    

    return edges_num;
}


int delLast()
{
    struct noedges *toDelete, *secondLastNode;
    int del_node;

    if(head_ne == NULL)
    {
        printf("List is already empty.");
    }
    else
    {
        toDelete = head_ne;
        secondLastNode = head_ne;

        // Traverse to the last node of the list
        while(toDelete->next_ne != NULL)
        {
            secondLastNode = toDelete;
            toDelete = toDelete->next_ne;
        }

        if(toDelete == head_ne)
        {
            head_ne = NULL;
        }
        else
        {
            // Disconnect link of second last node with last node
            secondLastNode->next_ne = NULL;
        }
        
        del_node = toDelete->no_edge_val;
        // Delete the last node
        free(toDelete);
        return del_node;
    }
}


    

int main(void)
{    
    struct timeval start, end;
    
    char OneLine[100], fname[50];
    int u, v, e, tmp=1, diff, flag=0, edges_num, nodes_num;
    long int pos;
    FILE *fp;
    int no_edges_vert_del;
    
    printf("Give file name: ");
    scanf("%s",fname);
    fp = fopen(fname, "r");
    
    gettimeofday(&start, NULL);	
	
    if (!fp)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    while (fgets(OneLine, 99, fp) != NULL){
        if (OneLine[0] == '%')
        {
            pos = ftell(fp);  
        }
    }

    fseek(fp, pos, SEEK_SET);
    fscanf(fp, "%d %d %d", &u, &v, &e);
    edges_num = e;
    nodes_num = u;
    
    while (fscanf(fp, "%d %d", &u, &v) == 2)
    {
        insertMap(u, v);
    }
    
    fclose(fp);
    
    
    while(edges_num > 2)
    {
        // printf("\n......................................................................................................\n");
        search_map_for_ne_nodes (nodes_num);

        // printf("\n");
        // printf("No incoming edges nodes not discovered:");
        // printNoedges();
        // printf("\n\n");
    
        no_edges_vert_del = delLast();
        edges_num = deleteMap(no_edges_vert_del, edges_num);
        insertResult(no_edges_vert_del);
        
        // printf("\n");
        // printf("No incoming edges nodes not discovered:");
        // printNoedges();
        // printf("\n");
        
        // printf("\n");
        // printf("No incoming edges nodes discovered:");
        // printResult();
        // printf("\n");

    }

    check_map(edges_num);
    
    struct noedges *finish_ne = head_ne;

    while(finish_ne != NULL){
        // printf("\n......................................................................................................\n");
        no_edges_vert_del = delLast();
        insertResult(no_edges_vert_del);
        finish_ne = head_ne;
    }
    gettimeofday(&end, NULL);
    // printf("\n......................................................................................................\n");

    printf("\nAll edges discovered.\n");
    printf("Nodes discovered:");
    printResult();
    printf("\n\n");

    printf("\nTime taken: %ld micro seconds\n",
    ((end.tv_sec * 1000000  + end.tv_usec) -
    (start.tv_sec * 1000000  + start.tv_usec)));

}
