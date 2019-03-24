#include "../header/include.h"
#include "../header/define.h"
#include "../header/module.h"

int build(int runnum)
{
    int i=0, j=0, k=0, ret;
    unsigned long int buf[16]={0}, offset[16]={0};
    double start=0, time=0, sec=0;
    char raw[50]={0}, build[50]={0}, str[18][14];
    FILE *fp1, *fp2;

    //sprintf(raw,"../beamtime2017/raw%04d.csv",runnum);
    sprintf(raw,"../data/raw%04d.csv",runnum);
    sprintf(build,"../data/build%04d.csv",runnum);
    fprintf(stdout,"Info. Edit %s to %s.\n",raw,build);
    if((fp1 = fopen(raw, "r"))== NULL){
        fprintf(stdout,"failed to open rawdata\n");
        return -1;
    }
    if((fp2 = fopen(build, "w"))== NULL){
        fprintf(stdout,"failed to open build data\n");
        return -1;
    }

    for(i=0;i<17;i++){
        fscanf(fp1,"%s",str[i]);
    }

    while( (ret=fscanf(fp1, "%lf,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu",&time,&buf[0],&buf[1],&buf[2],&buf[3]
        ,&buf[4],&buf[5],&buf[6],&buf[7],&buf[8],&buf[9],&buf[10],&buf[11],&buf[12],&buf[13],&buf[14],&buf[15]))!=EOF){
        if(j!=0){
            sec = time - start;
            fprintf(fp2,"%lf,%.3lf",time,sec);
            for(i=0;i<16;i++){
                int  count=0;
                count = buf[i]-offset[i];
                fprintf(fp2,",%d",count);
            }
            fprintf(fp2,"\n");
        }
        if(j==0)start = time;
        for(k=0;k<16;k++)offset[k]=buf[k];
        j++;
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
