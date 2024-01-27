//
//  main.c
//  20240129.Bio.Coop&Conflict.Evo.MRSA simulation.normal+normal variation
//
//  Created by Shi Michael on 2024/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    long times = 1000000000;
    int days = 80;
    int anti_kill=5;//amount of bacteria killed by the antibiotics
    int rep=1;//reproduction
    int prob=5;//probability of eating antibiotics = (prob-1)/prob
    //int total[times][days+1];
    long surv_sum=0;
    long three_sum[days][7];
    long dom_sum[2];//dominant set as 50% and 80%
    dom_sum[0]=0;dom_sum[1]=0;
    for (int i=0;i<days+1;i++){three_sum[i][6]=0;three_sum[i][1]=0;three_sum[i][2]=0;three_sum[i][3]=0;three_sum[i][4]=0;three_sum[i][5]=0;}
    for (long tt = 0; tt<times; tt++){
        if (tt%(times/100)==0){printf("%ld/100;%ld\n", tt*100/times, tt);}
        int number[days][5];
        for (int i=0;i<days+1;i++){number[i][0]=0;number[i][1]=0;number[i][2]=0;number[i][3]=0;number[i][4]=0;}
        //setting
        for (int i=0;i<20;i++){
            int random = rand()%3;
            number[0][random]+=1;}
        number[0][3]=number[0][0]+number[0][1]+number[0][2];
        //total[tt][0]=20;
        three_sum[0][4]+=number[0][0];
        three_sum[0][5]+=number[0][1];
        three_sum[0][6]+=number[0][2];
        three_sum[0][3]+=number[0][3];
        int end=0;
        //printf("0: %d, %d, %d; %d\n",number[0][0],number[0][1],number[0][2],number[0][3]);
        //printf("0,%d\n", number[0][3]);
        int sum_end[2];
        sum_end[0]=0;
        sum_end[1]=0;
        for (int i=1;i<days+1;i++){
            number[i][0]=number[i-1][0];
            number[i][1]=number[i-1][1];
            number[i][2]=number[i-1][2];
            int pre =rand()%prob;
            number[i][4]=1;
            if (pre!=prob-1){number[i][0]-=anti_kill;number[i][4]=0;}
            for (int j =0;j<2;j++){if (number[i][j]<0){number[i][j+1]+=number[i][j];number[i][j]=0;}}
            for (int j=0;j<3;j++) {
                if (number[i][j]!=0){number[i][j]+=rep;}
            }
            if (number[i][2]<1&&end==0){number[i][2]=0;number[i][2]=0;surv_sum+=i;end=1;}
            else if (number[i][2]<1&&end!=0){number[i][2]=0;end=1;}
            number[i][3]=number[i][0]+number[i][1]+number[i][2];
            three_sum[i][4]+=number[i][0];
            three_sum[i][5]+=number[i][1];
            three_sum[i][6]+=number[i][2];
            three_sum[i][3]+=number[i][3];
            //printf("%d: %d, %d, %d; %d, %d\n", i, number[i][0], number[i][1], number[i][2], number[i][3], number[i][4]);
            //printf("%d,%d\n", i, number[i][3]);
            //printf("%d, %d, %d\n", tt, i, total[tt][i]);
            //printf("%d\n", total[tt][i]);
            if (sum_end[0]==0&&(number[i][3]/2<number[i][2])){dom_sum[0]+=i;sum_end[0]=1;
                //printf("end1, %ld, %d\n", dom_sum[0], i);
            }
            if (sum_end[1]==0&&(number[i][2]>number[i][3]*0.8)){dom_sum[1]+=i;sum_end[1]=1;
                //printf("end2, %ld, %d\n", dom_sum[1], i);
            }
        }
        //printf("\n");
    }
    //for (int i=0;i<times;i++){for (int j=0;j<days+1;j++){printf ("%d,", total[i][j]);}}printf("\n");
    //day,low,mid,high,total\n
    printf("%ld; %d; %d; 1/%d\n", times, anti_kill, rep, prob);
    printf("%lf,", surv_sum*1.0/times);
    printf("%lf,%lf\n", dom_sum[0]*1.0/times,dom_sum[1]*1.0/times);
    for (int i=0;i<days;i++){printf("%d,%lf,%lf,%lf,%lf\n", i, three_sum[i][4]*1.0/times, three_sum[i][5]*1.0/times, three_sum[i][6]*1.0/times,three_sum[i][3]*1.0/times);}
    //printf("\n\n");
    //for (int i=0;i<times;i++){for (int j=0;j<days+1;j++){printf("%d, %d, %d\n", i, j, total[i][j]);}printf("\n");}
    return 0;
}

