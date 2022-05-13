#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          printf("%d ", n->sudo[i][j]);
          if(j%3==2 && j!=8)printf("| ");
        }
       printf("\n");
       if(i%3==2 && i!=8)printf("---------------------\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  int numero,k,p;
  int contS=0,contH=0,contV=0;
  
  for(k=0;k<9;k++){
    for(numero=1;numero<10;numero++){
      for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        if(n->sudo[i][j]==numero)contS++;
        if(contS>1)return 0;

      }
      for(p=0;p<9;p++){
        if(n->sudo[p][k]==numero)contV++;
        if(n->sudo[k][p]==numero)contH++;
        if(contV>1|| contH>1)return 0;
      }
      contS=0;
      contV=0;
      contH=0;
    }
    
  }

  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i,j,k; 
  
  for(i=0;i<9;i++){
    
   for(j=0;j<9;j++){
     
     if(n->sudo[i][j]==0){
       
       for(k=1;k<10;k++){
         n->sudo[i][j]=k;
         
         if(is_valid(n)){
           Node* adj=copy(n);
           pushBack(list,adj);
         }
          
       }
       n->sudo[i][j]=0;
       return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[i][j]==0)return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while (get_size(S)!=0){
    Node* n=top(S);
    if(is_final(n))return n;
    pop(S);
    List* adj=get_adj_nodes(n);
    Node* aux=first(adj);
    while (aux){
      push(S,aux);
      aux=next(adj);
    }
    
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/