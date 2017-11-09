#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int route[10000];
typedef struct vnode
{
  int ix,prnt,x,y,dist,visit; 
}vtx;
typedef struct aNode
{
  struct aNode* nxt;
  int wght,ix;
}aNode;
typedef struct aList
{
  struct aNode *hd;  
}aList;
int Dijkstra(vtx v[], aList *alist, int A, int B, int verti);
void freealist(aList* alist, int j);
void freelist(aNode *anode);
void call(vtx *vertices, int count1);
void freealist(aList* alist, int j)
{
	int i = 0;
	while(i<j)
	{
	  if(alist[i].hd != NULL)
		{
			freelist(alist[i].hd);
		} 
		++i;
	}
	free(alist);
}
void freelist(aNode *anode)
{
  if(anode != NULL)
  {
		freelist(anode->nxt);
		free(anode);
  }
}
int Dijkstra(vtx v[], aList *alist, int A, int B, int verti)
{
	int curr = A,test=verti;
	v[curr].dist = 0;
	v[curr].visit = 1;
	while(curr != B)
	{
		aNode *tmp = alist[curr].hd;
		while(tmp != NULL)
		{
			if(!v[tmp->ix].visit)
			{
				if(v[tmp->ix].dist > v[curr].dist + tmp->wght)
				{
				  v[tmp->ix].dist = v[curr].dist + tmp->wght;
				}
				v[tmp->ix].prnt = curr; 
			}
			tmp = tmp->nxt;
		} 
		int min = 100000,minix = 0,count; // max number = 100000
		for(count=0;count<verti;++count)
		{
			if (v[count].visit == 0 && v[count].dist < min)
			{
				min = v[count].dist;
				minix = v[count].ix;
			}
		}
		curr = minix;
	  v[curr].visit = 1;
	  --test;
	}
	if(test==0)
	{
	  return 0;
	}
	return 1;
}
void call(vtx *vertices, int count1)
{
  vertices[count1].dist = 100000;
  vertices[count1].prnt = -1;
  vertices[count1].ix = count1;
  vertices[count1].visit = 0;
}
int main(int argc, char* argv[])
{
	int verti,edges,nq, A,B,count1,i, j,awght;
	FILE* fptr = fopen(argv[1],"r");
	fscanf(fptr,"%d %d",&verti,&edges);
	vtx vertices[verti]; 
	aList *alist = malloc(verti * sizeof(aList));
	for (i=0; i<verti; ++i)
	{
	  alist[i].hd = NULL;
	}
	for(count1=0;count1 < verti;++count1)
  {
    fscanf(fptr,"%d %d %d",&i,&vertices[count1].x,&vertices[count1].y);
    call(vertices,count1);
  }
 	for(count1 = 0;count1<edges;++count1)
  {
  	fscanf(fptr,"%d %d",&i,&j);
    awght = (sqrt((pow((vertices[i].x - vertices[j].x),2) + pow((vertices[j].y - vertices[i].y),2))));
  	aNode* newNode = malloc(sizeof(aNode));
		newNode->ix = j;
		newNode->wght = awght;
		newNode->nxt  = NULL;
    newNode->nxt = alist[i].hd;
    alist[i].hd = newNode;
  	newNode = malloc(sizeof(aNode));
		newNode->ix = i;
		newNode->wght = awght;
		newNode->nxt  = NULL;
	  newNode->nxt = alist[j].hd;
	  alist[j].hd = newNode;
  }
	fclose(fptr);
	fptr = fopen(argv[2],"r");
	fscanf(fptr,"%d",&nq);
	for(count1 = 0;count1<nq;++count1)
	{
		fscanf(fptr,"%d %d",&A,&B);
    if(Dijkstra(vertices,alist,A,B,verti))
		{
			int i = B,j=0;
			printf("%d\n",vertices[B].dist);
			route[j] = B;
			++j;
			while(i != A)
			{
			  route[j] = vertices[i].prnt;
			  i = vertices[i].prnt;
			  ++j;
			}
			--j; 
			while(j >= 0)
			{
			  printf("%d ",route[j]);
			  --j;
			}
			printf("\n");
		}
		for(count1 = 0; count1 < verti; ++count1)
		{
			call(vertices,count1);
		}
  }
	fclose(fptr);
	freealist(alist,verti);
	return 0;
}


