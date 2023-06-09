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
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  int *numero = calloc(sizeof(int), 10);
  int i,j,k,l;
  for(i=0 ; i<9 ; i++)
    {
      for(j=0 ; j<9 ; j++)
        {
          if(n->sudo[i][j] != 0)
          {
            if(numero[n->sudo[i][j]] == 1) return 0;
            else numero[n->sudo[i][j]] = 1;
          }
        }
      free(numero);
      numero = calloc(sizeof(int), 10);
      for(j=0 ; j<9 ; j++)
        {
          if(n->sudo[j][i] != 0)
          {
            if(numero[n->sudo[j][i]] == 1) return 0;
            else numero[n->sudo[j][i]] = 1;
          }
        }
      free(numero);
      numero = calloc(sizeof(int), 10);
    }

  free(numero);
  for(k=0 ; k<9 ; k++)
    {
      numero = calloc(sizeof(int), 10);
      for(l=0; l<9 ; l++)
        {
          i=3*(k/3) + (l/3);
          j=3*(k%3) + (l%3);
          if(n->sudo[i][j] != 0)
          {
            if(numero[n->sudo[i][j]] == 1) return 0;
            else numero[n->sudo[i][j]] = 1;
          }
        }
    }
  
  return 1;
}
  
List* get_adj_nodes(Node* n) 
{ 
  List* list=createList();
  for(int i=0; i<9 ; i++)  
    { 
      for(int j=0 ; j<9 ; j++)
        {
          if(n->sudo[i][j]==0)
            {
              for(int k=1 ; k<=9 ; k++)
                {
                  Node* nuevo_nodo=copy(n);
                  nuevo_nodo->sudo[i][j]=k;
                  if(is_valid(nuevo_nodo))
                  pushBack(list,nuevo_nodo);
                }
              return list;
            }
        }
    }
  return list;
}

int is_final(Node* n)
{
  int i,j;
  for(i=0 ; i<9 ; i++)
    {
      for(j=0 ; j<9 ; j++)
        {
          if(n->sudo[i][j]==0) return 0;
        }
    }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* S = createStack();
  push(S, initial);
  while(top(S) != NULL)
  {
    Node* nAux = top(S);
    pop(S);
    if (is_final(nAux)) return nAux;
    
    List* listaNodosAdj = get_adj_nodes(nAux);
    Node* nCurrent = first(listaNodosAdj);

    while(nCurrent)
    {
      push(S, nCurrent);
      nCurrent = next(listaNodosAdj);
    }
    
    free(listaNodosAdj);
  }

  
  (*cont)++;
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