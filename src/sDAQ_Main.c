#include "../header/include.h"
#include "../header/define.h"
#include "../header/module.h"

int main(int argc, char *argv[])
{
    if(argc > 3){
        fprintf(stdout,"Error. Too many arguments.\n");
        exit(1);
    }

    option(argc,argv,flag);
    CVBoardTypes VMEBoard = cvV1718;

    req.tv_sec = 0;
    req.tv_nsec = 1000000;

    if(SIG_ERR == signal(SIGINT, (void*)quit)){
        fprintf(stdout,"Error. Failed to set signal handler.\n");
        exit(1);
    }

    if(flag[0] == 1){
        if((fp = fopen("../data/raw0000.csv","w"))== NULL){
            fprintf(stdout,"Error. Failed to open raw0000.csv\n");
            exit(1);
        }
        fprintf(stdout,"Info. Writting data to raw0000.csv.\n");
    }

    if(flag[1] == 1){
        if((daqlog = fopen("./misc/daq.csv","a"))== NULL){
            fprintf(stdout,"Error. Failed to open daq.csv\n");
            exit(1);
        }
        if((runcounter = fopen("./misc/runcounter.log","r"))== NULL){
            fprintf(stdout,"Error. Failed to open runcounter.csv.\n");
            exit(1);
        }
        fscanf(runcounter,"%d", &runnumber);
        fclose(runcounter);
        runnumber++;
        char filename[30];
        sprintf(filename,"../data/raw%04d.csv",runnumber);
        if((fp = fopen(filename,"w"))== NULL){
            fprintf(stdout,"Error. Failed to open build%d.csv.\n",runnumber);
            exit(1);
        }
        fprintf(stdout,"Info. Writting data to %s\n",filename);
        fprintf(daqlog,"%04d",runnumber);
        if((runcounter = fopen("./misc/runcounter.log","w"))== NULL){
            fprintf(stdout,"Error. Failed to update runcounter.log\n");
            exit(1);
        }
        fprintf(runcounter,"%d",runnumber);
        fclose(runcounter);
    }

    if((config = fopen("./misc/config.txt","r"))== NULL){
        fprintf(stdout,"Error. Failed to open config.txt.\n");
        exit(1);
    }

    for(j=0;j<19;j++){
        if(j==0)fscanf(config,"%d" , &CLKch);
        if(j==1)fscanf(config,"%lf", &CLKrate);
        if(j> 1)fscanf(config,"%s", str[j-2]);
    }
    fclose(config);
    fprintf(stdout,"Info. CLK ch.%01d rate %.1lf Hz\n",CLKch,CLKrate);
/*
    for(j=0;j<17;j++){
        if(j==0)fprintf(fp,"%14s",str[j]);
        if(j>0)fprintf(fp,",%10s",str[j]);
    }
    fprintf(fp,"\n");
*/
    CVErrorCodes result = CAENVME_Init( VMEBoard, Link, Device, &Handle);
    if(result != cvSuccess){
        fprintf(stdout,"CAEN1718 Init %s\n", CAENVME_DecodeError(result));
        fprintf(stdout,"*************************************************\n");
        fprintf(stdout,"!!!!!!!!!! Error. Failed to open V1718 !!!!!!!!!!\n");
        fprintf(stdout,"*************************************************\n");
        exit(-1);
    }

    fprintf(stdout,"Info. Init Success!\n");
    fprintf(stdout,"Info. Starting SIS3803 setup function.\n");
    sis3803_clear();
    nanosleep(&req, NULL);
    fprintf(stdout,"Info. SIS3803 clear.\n");
    sis3803_inhi_on();
    nanosleep(&req, NULL);
    fprintf(stdout,"Info. SIS3803 inhi on.\n");

    gettimeofday(&tv, NULL);
    sis3803_enable();
    fprintf(stdout,"Info. SIS3803 enable.\n");
    initialTime = tv.tv_sec + ((double)tv.tv_usec/1000000);

    while(1)
    {
        CAENVME_ReadCycle( Handle, SIS3803AD+0x200+(0x4*CLKch), &Buffer[CLKch], cvA32_U_DATA, cvD32);

        if(Buffer[CLKch]!=sumCLK){
            for(i=0;i<16;i++)CAENVME_ReadCycle( Handle, SIS3803AD+0x200+(0x4*i), &Buffer[i], cvA32_U_DATA, cvD32);

            sumCLK = Buffer[CLKch];
            measurementTime = initialTime + sumCLK/CLKrate;
            if(counter == 0){
                startTime = measurementTime;
                time_t t = startTime;
                localtime_r(&t, &tm);
                fprintf(stdout,"Info. sDAQ START :%04d/%02d/%02d %02d:%02d:%02d JST\n",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                if(flag[1]==1)fprintf(daqlog,",%04d/%02d/%02d-%02d:%02d:%02d",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            }
            fprintf(fp,"%10.3lf,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu\n"
                    ,measurementTime,Buffer[0],Buffer[1],Buffer[2],Buffer[3],Buffer[4],Buffer[5],Buffer[6],Buffer[7]
                              ,Buffer[8],Buffer[9],Buffer[10],Buffer[11],Buffer[12],Buffer[13],Buffer[14],Buffer[15]);
            if(counter % 600 == 0){
                if(counter != 0){
                    fprintf(stdout,"Info. %10.1lfsec passed.\n",(float)counter/10);
                }else{
                    fprintf(stdout,"Info. Loading data ...\n");
                }
            }

            if(measurementTime - startTime >= setStoptime)break;
            if(endflag == 1)break;

            counter++;
        }
    }

    fclose(fp);

    if(endflag==1)fprintf(stdout,"\n");
    t = measurementTime;
    localtime_r(&t, &tm);
    fprintf(stdout,"Info. sDAQ STOP  :%04d/%02d/%02d %02d:%02d:%02d JST\n",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    sis3803_disable();
    nanosleep(&req, NULL);
    fprintf(stdout,"Info. SIS3803 disable.\n");
    sis3803_clear();
    nanosleep(&req, NULL);
    fprintf(stdout,"Info. SIS3803 clear.\n");
    fprintf(stdout,"Info. Total Measurement Time : %8.3lf sec.\n",(float)counter/10);

    if(flag[1]==1){
        fprintf(daqlog,",%04d/%02d/%02d-%02d:%02d:%02d",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        if(flag[2]==1)fprintf(stdout,"Info. calibration\n");
        if(flag[2]==1)fprintf(daqlog,",calibration");
        if(flag[3]==1)fprintf(stdout,"Info. physics    \n");
        if(flag[3]==1)fprintf(daqlog,",physics    ");
        if(flag[2]==0&&flag[3]==0)fprintf(stdout,"Info. junk       \n");
        if(flag[2]==0&&flag[3]==0)fprintf(daqlog,",junk       ");
        fprintf(daqlog,",%10.3lf,%10.3lf,%8.3lf,%8.3lf\n", startTime, measurementTime,(float)counter/10,CLKrate);
        fclose(daqlog);
    }
    fprintf(stdout,"Info. start data build \n");
    build(runnumber);
    fprintf(stdout,"Info. finish data build \n");
    return 0;
}
