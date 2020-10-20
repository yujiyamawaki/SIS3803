#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "CAENVMElib.h"

int main(int argc, char **argv)
{
    CVBoardTypes  VMEBoard;
    short         Link;
    short         Device;
    int32_t       Handle;
    CVAddressModifier AM=cvA32_U_DATA;
    CVDataWidth   DW=cvD32;
    int           bitFlag0 = 0;
    int           bitFlag1 = 1;
    int           bitFlag4 = 4;
    if(argc!=3)
    {
        printf("Usage: CAENVMEDemo V1718 <VMEDevice>\n");
        exit(-1);
    }
    else
    {
        if(strcmp((char*)argv[1],"V1718") == 0)
        {
            VMEBoard = cvV1718;
            Device   = atoi((const char*)argv[2]);
            Link     = 0;
        }
	else
	{
            printf("Usage: V1718");
        }
    }
//  Initialize the Board
    if(CAENVME_Init( VMEBoard, Link, Device, &Handle)!=cvSuccess)
    {
        printf("Error opening the device\n");
        exit(-1);
    }

    CAENVME_WriteCycle( Handle, SIS3803AD + SIS3803_DISABLE, &bitFlag1,  AM, DW);
    sleep(1);

    CAENVME_WriteCycle( Handle, SIS3803AD + SIS3803_CLR_REG, &bitFlag1,  AM, DW);
    sleep(1);
    
    printf("you can start data taking\n");

    return 0;
}
