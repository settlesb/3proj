#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct vnode
{
  int x,y,dist,ix,prnt,visit; 
}vtx;
typedef struct aNode
{
  struct aNode* nxt;
  int weight,ix;
}aNode;
typedef struct alist
{
  struct aNode *hd;  
}alist;
int Dijkstra(vtx v[], alist *alist, int A, int B, int nv);
void rlx(vtx v[], alist *alist, int curr);
aNode* makeNode(int ix, int weight);
void freealist(alist* alist, int n);
void freelist(aNode *anode);
void freealist(alist* alist, int n)
{
  int i = 0;
  for(i=0;i<n;++i)
  {
    if(alist[i].hd != NULL)
    {
      freelist(alist[i].hd);
    } 
  }
  free(alist);
}
void freelist(aNode *anode)
{
  aNode *ptr = anode;
  if(ptr != NULL)
  {
    freelist(ptr->nxt);
    free(ptr);
  }
}
aNode* makeNode(int ix, int weight)
{
  aNode* node = malloc(sizeof(aNode));
  node->nxt  = NULL;
  node->ix = ix;
  node->weight = weight;
  return node;
}
void rlx(vtx v[], alist *alist, int curr)
{
  int ix = 0;
  int weight = 0;
  aNode *listptr = alist[curr].hd;
  while(listptr != NULL)
  {
    ix = listptr->ix;
    weight = listptr->weight;

    if(v[ix].visit == 0 )
    {
      if(v[ix].dist > v[curr].dist + weight)
      {
        v[ix].dist = v[curr].dist + weight;
      }
      v[ix].prnt = curr; 
    }
    listptr = listptr->nxt;
  }
}
int Dijkstra(vtx v[], alist *alist, int A, int B, int nv)
{
  int curr = A; //most recent node extracted
  int n = nv;
  v[A].dist = 0;
  v[curr].visit = 1;
  while(curr != B)
  {
    rlx(v,alist,curr);
    int min = 100000,minix = 0,ctr = 0;
    while(ctr<n)
    {
      if (v[ctr].visit == 0 && v[ctr].dist < min)
      {
        min = v[ctr].dist;
        minix = v[ctr].ix;
      }
      ++ctr;
    }
    curr = minix;
    v[curr].visit = 1;
    --n;
  }
  if(n==0)
  {
    return 0;
  }
  return 1;
}
int main(int argc, char* argv[])
{
  int verti = 0,edges = 0,nquery = 0,A = 0,B = 0, i = 0, j = 0, k=0, aweight = 0;
  FILE* fptr = fopen(argv[1],"r");
  fscanf(fptr,"%d %d",&verti,&edges);
  vtx vertices[verti]; 
  alist *alist = malloc(verti * sizeof(alist));
  while(i<verti)
  {
    alist[i].hd = NULL;
    ++i;
  }
  for(i=0;i < verti;++i) //vtx array
  {
    fscanf(fptr,"%d %d %d",&i,&vertices[i].x,&vertices[i].y);
    vertices[i].dist = 100000;
    vertices[i].prnt = -1;
    vertices[i].ix = i;
    vertices[i].visit = 0;
  }
  while(k<edges) //making list w/ edges
  {
    fscanf(fptr,"%d %d",&i,&j);
    aweight = (sqrt((pow((vertices[j].x - vertices[i].x),2) + pow((vertices[j].y - vertices[i].y),2))));
    aNode* newNode = makeNode(j,aweight);
    newNode->nxt = alist[i].hd;
    alist[i].hd = newNode;
    newNode = makeNode(i,aweight); //point B to point A
    newNode->nxt = alist[j].hd;
    alist[j].hd = newNode;
    ++k;
  }
  fclose(fptr);
  fptr = fopen(argv[2],"r");
  fscanf(fptr,"%d",&nquery);
  for(i = 0;i<nquery;++i)
  {
    fscanf(fptr,"%d %d",&A,&B);
    if(Dijkstra(vertices,alist,A,B,verti) == 1)
  	{
      int u = B; 
      int v = 0; 
      int path[10000] = {0}; 
      printf("%d\n",vertices[B].dist);
      path[v] = B;
      ++v;
      while(u != A)
      {
        path[v] = vertices[u].prnt;
        u = vertices[u].prnt;
        ++v;
      }
      --v; //to account for the extra increment of j done in the previous while loop at the end
      while(v >= 0)
      {
        printf("%d ",path[v]);
        --v;
      }
      printf("\n");
  	}
    int ctr1 = 0;
    while(ctr1 < verti)
    {
      vertices[ctr1].dist = 100000;
      vertices[ctr1].prnt = -1;
      vertices[ctr1].ix = ctr1;
      vertices[ctr1].visit = 0;
      ++ctr1;
    }
  }
  fclose(fptr);
  freealist(alist,verti);
  return 0;
}
