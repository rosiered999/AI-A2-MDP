#include<stdio.h>
#include<stdlib.h>

float value[5][6]={0};
float value1[5][6]={0};
char map[5][6];

int cmpfunc(const void* a, const void* b)
{
    float fa = *(const float*) a;
    float fb = *(const float*) b;
    return (fa > fb) - (fa < fb);
}

float max2(float a, float b)
{
    float values[2];
    values[0] = a;
    values[1] = b;

    qsort(values,2,sizeof(float),cmpfunc);
    return values[1];
}

float max(float a, float b, float c, float d)
{
    float values[4];
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;

    qsort(values,4,sizeof(float),cmpfunc);
    return values[3];
}

float find_utility(int i, int j, int dir)
{
    float val;
    if(dir==0)
    {
        if(map[i][j+1]=='w')
            value[i][j+1] = value[i][j];
        if(map[i+1][j]=='w')
            value[i+1][j] = value[i][j];
        if(map[i-1][j]=='w')
            value[i-1][j] = value[i][j];
        val = 0.8*value[i][j+1]+0.1*value[i+1][j]+0.1*value[i-1][j];
    }
    else if(dir==1)
    {
        if(map[i-1][j]=='w')
            value[i-1][j] = value[i][j];
        if(map[i][j+1]=='w')
            value[i][j+1] = value[i][j];
        if(map[i][j-1]=='w')
            value[i][j-1] = value[i][j];
        val = 0.8*value[i-1][j]+0.1*value[i][j+1]+0.1*value[i][j-1];
    }
    else if(dir==2)
    {
        if(map[i][j-1]=='w')
            value[i][j-1] = value[i][j];
        if(map[i+1][j]=='w')
            value[i+1][j] = value[i][j];
        if(map[i-1][j]=='w')
            value[i-1][j] = value[i][j];
        val = 0.8*value[i][j-1]+0.1*value[i+1][j]+0.1*value[i-1][j];
    }
    else if(dir==3)
    {
        if(map[i+1][j]=='w')
            value[i+1][j] = value[i][j];
        if(map[i][j+1]=='w')
            value[i][j+1] = value[i][j];
        if(map[i][j-1]=='w')
            value[i][j-1] = value[i][j];
        val = 0.8*value[i+1][j]+0.1*value[i][j+1]+0.1*value[i][j-1];
    }

    return val;
}

int main()
{
    int i,j,iter=0;
    float a,b,c,d,delta;
    for(i=0;i<5;i++)
    {
        for(j=0;j<6;j++)
        {
            map[i][j] = '-';
        }
    }

    for(i=0;i<5;i++)
    {
        map[0][i] = 'w';
        map[i][0] = 'w';
        map[i][5] = 'w';
        map[4][i] = 'w';
    }

    map[2][2] = 'w';
    map[1][4] = 'g';
    map[2][4] = 'l';
    value[1][4] = 1;
    value[2][4] = -1;
    value1[1][4] = 1; //NEW ONE
    value1[2][4] = -1; //NEW ONE

    float r = -0.04;
    float gamma = 1;
    while(iter<500)
    {
        delta = 0;


        for(i=0;i<5;i++)
        {
            for(j=0;j<6;j++)
            {
                if(map[i][j]!='w'&& map[i][j]!='g'&& map[i][j]!='l')
                {
                    a = find_utility(i,j,0); //right
                    b = find_utility(i,j,1); //up
                    c = find_utility(i,j,2); //left
                    d = find_utility(i,j,3); //down
                    //printf("value[%d][%d] = a %f b %f c %f d %f\n",i,j,a,b,c,d);
                    value1[i][j] = r + gamma*max(a,b,c,d);
                    //delta = max2(delta, fabs(value1[i][j] - value[i][j]));
                }
            }
        }

        for(i=0;i<4;i++)
        {
            for(j=0;j<5;j++)
            {
                value[i][j] = value1[i][j];
            }
        }
        printf("ITERATION #%d\n",iter);
        for(i=1;i<4;i++)
        {
            for(j=1;j<5;j++)
            {
                printf("  %.6f  ", value1[i][j]);
            }
            printf("\n");
        }
        iter++;
    }

    printf("CONVERGING VALUE\n");
    for(i=1;i<4;i++)
    {
        for(j=1;j<5;j++)
        {
            printf("  %.6f  ", value1[i][j]);
        }
        printf("\n");
    }

    /* NOW WE KNOW THAT THE MAP IS CORRECT
    */

    /*  printf("\n");
        for(i=0;i<5;i++)
        {
        for(j=0;j<6;j++)
        {
        printf("  %c  ", map[i][j]);
        }
        printf("\n");
        }*/
}
