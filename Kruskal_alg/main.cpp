#include <iostream>
using namespace std;
/*
 * Code by Armando Aguirre
 */
typedef struct Edge{
    int v0;
    int v1;
    int cost;
    bool operator<(const Edge temp) const {
        return (this->cost<temp.cost); }
    bool operator>(const Edge temp) const {
        return (this->cost>temp.cost); }
};
int compare(const void * x,const void * y) {
    if(*(Edge*)x < *(Edge*)y){
        return -1;}
    else if( *(Edge*)x > *(Edge*)y) {
        return 1; } else {
        return 0; }}
typedef struct SetUnion{
    int ID;
    SetUnion(const int x){
        ID=-1; }
}* ptr_Union;
int MST(const int n, int *cost, const int limit) {
    Edge edges[n*n];
    size_t z=0;
    int temp=0;
    for(int b=0;b<n;b++) {
        for(int a=temp;a<n;a++) {
            if((*(cost + a*n+b))<limit) {
                edges[z].cost=(*(cost + a*n+b));
                edges[z].v0=b;
                edges[z].v1=a;

                z++;
            }
        }
        temp++;
    }
    qsort(edges,z,sizeof(Edge),compare);
    ptr_Union mst[n];
    for(int i=0;i<n;i++) {
    ptr_Union temp0=new SetUnion(n);
        *(mst+i)=temp0;
         }
    int a=0; //edge number
    int SETID=0; //the first set
    int min=0;
    while(a<z){
        if(mst[edges[a].v0]->ID==-1 && mst[edges[a].v1]->ID==-1) {
            mst[edges[a].v0]->ID=SETID;
            mst[edges[a].v1]->ID=SETID;
            min+=edges[a].cost;
            SETID++;
        }//checking if we can merge any of the sets
        //both vertices are not equal to -1 so they are part of a set
       else if(mst[edges[a].v0]->ID!=-1 && mst[edges[a].v1]->ID!=-1) {
            if(mst[edges[a].v0]->ID<mst[edges[a].v1]->ID) {
                int tempID=mst[edges[a].v0]->ID;
                int oldID=mst[edges[a].v1]->ID;
                for(int i=0;i<n;i++) {
                    if(oldID==mst[i]->ID) {
                        mst[i]->ID=tempID;
                    }
                }
                min+=edges[a].cost;
             }
            else if(mst[edges[a].v0]->ID>mst[edges[a].v1]->ID) {
                int tempID=mst[edges[a].v1]->ID;
                int oldID=mst[edges[a].v0]->ID;
                for(int i=0;i<n;i++) {
                    if(oldID==mst[i]->ID) {
                        mst[i]->ID=tempID;
                    }
                }
                min+=edges[a].cost;
             }


        } //one of the vertices is part of a set while the other one is not
          else  if(mst[edges[a].v1]->ID==-1 && mst[edges[a].v0]->ID!=-1) {
                int tempID=mst[edges[a].v0]->ID;
                mst[edges[a].v1]->ID=tempID;
            min+=edges[a].cost;
            }
            else if(mst[edges[a].v1]->ID!=1 && mst[edges[a].v0]->ID==-1) {
                int tempID=mst[edges[a].v1]->ID;

                mst[edges[a].v0]->ID=tempID;
            min+=edges[a].cost;
            }
        a++;
    }
return min;
}

int main(void)
{  int cost[512][512];
    int d[9] = {1, 3, 4, 8, 12, 13, 20, 195, 198};
    int i,j, result1, result2;
    for(i=0; i< 512; i++ )
    {  for( j=0; j< 512; j++ )
        {
            if(i==j)
                cost[i][j] = 0;
            else if ( (i^j) == 1 )
                cost[i][j] = d[0];
            else if ( (i^j) == 2 )
                cost[i][j] = d[1];
            else if ( (i^j) == 4 )
                cost[i][j] = d[2];
            else if ( (i^j) == 8 )
                cost[i][j] = d[3];
            else if ( (i^j) == 16 )
                cost[i][j] = d[4];
            else if ( (i^j) == 32 )
                cost[i][j] = d[5];
            else if ( (i^j) == 64 )
                cost[i][j] = d[6];
            else if ( (i^j) == 128 )
                cost[i][j] = d[7];
            else if ( (i^j) == 256 )
                cost[i][j] = d[8];
            else
                cost[i][j] = 201;
        }
    }
#ifdef DEBUG
    for(i=0; i<11; i++)
   {  for( j=0; j< 11; j++)
         printf("%d  ", cost[i][j]);
      printf("\n");
   }
#endif
    result1 = 256*d[0] + 128*d[1] + 64*d[2] + 32*d[3]
              + 16* d[4] +   8*d[5] +  4*d[6] +  2*d[7] + d[8];
    result2 = MST(512, &(cost[0][0]), 200);
    if( result1 == result2 )
        printf("test PASSED\n");
    else
        printf("test FAILED\n should be %d, is %d.\n", result1, result2);
    exit(0);
}



/*

int main() {
    int cost[6][6]={{8,4,2,8,8,8},
                    {4,8,5,6,8,8},
                    {2,5,8,1,8,4},
                    {8,6,1,8,3,8},
                    {8,8,8,3,8,2},
                    {8,8,4,8,2,8}};

    int cost2[6][6]= {
            {8,3,8,1,8,8},
            {3,8,1,3,8,8},
            {8,1,8,1,5,4},
            {1,2,1,8,6,8},
            {8,8,5,6,8,2},
            {8,8,4,8,2,8},
    };

    printf("min=%d \n",MST(6,&cost2[0][0],7));

    return 0;
}
*/
