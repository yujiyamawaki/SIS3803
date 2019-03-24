#include "../header/define.h"
#include "../header/module.h"
#include "../header/include.h"

void option(int argc,char *argv[],bool flag[]){
    int oval;
    opterr = 0;
    while((oval=getopt(argc,argv,"n:j:p:c:"))!=-1){
        switch(oval){
            case 'n':
                flag[0]=1;
                setStoptime = atoi(optarg);
                break;
            case 'j':
                flag[1]=1;
                setStoptime = atoi(optarg);
                break;
            case 'c':
                flag[1]=1;
                flag[2]=1;
                setStoptime = atoi(optarg);
                break;
            case 'p':
                flag[1]=1;
                flag[3]=1;
                setStoptime = atoi(optarg);
                break;
            default:
                fprintf(stdout,"Error. Need arguments\n");
                exit(1);
                break;
        }
    }
    return;
}
