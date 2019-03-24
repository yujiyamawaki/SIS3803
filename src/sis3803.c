#include "../header/include.h"
#include "../header/define.h"
#include "../header/module.h"

void sis3803_clear(){
    int sval = 1;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_CLR_REG,&sval,cvA32_U_DATA,cvD32);
}

void sis3803_inhi_on(){
    int sval = 4;
    CAENVME_WriteCycle(Handle,SIS3803AD,&sval,cvA32_U_DATA,cvD32);
}

void sis3803_inhi_off(){
    int sval = 0;
    CAENVME_WriteCycle(Handle,SIS3803AD,&sval,cvA32_U_DATA,cvD32);
}

void sis3803_enable(){
    int sval =1;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_ENABLE,&sval,cvA32_U_DATA,cvD32);
}

void sis3803_disable(){
    int sval =1;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_DISABLE,&sval,cvA32_U_DATA,cvD32);
}

bool sis3803_CHK_OF_FLAG(){
    CAENVME_ReadCycle(Handle,SIS3803AD+0x380,&overflowFlag,cvA32_U_DATA,cvD32);
    CAENVME_ReadCycle(Handle,SIS3803AD+0x3A0,&overflowFlag,cvA32_U_DATA,cvD32);
    return overflowFlag;
}

void sis3803_enable_interrupt(int level){
    int val;
    val = ((level&0x7)<<8) | 0x00000800;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_IRQ_REG, &val, cvA32_U_DATA, cvD32);
}

void sis3803_disable_interrupt(){
    int val=0;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_IRQ_REG, &val, cvA32_U_DATA, cvD32);
}

void sis3803_enable_extshadow(){
    int val=SIS3803_ENA_IRQSRC1 | SIS3803_ENA_CTLIN;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_CTL_REG, &val, cvA32_U_DATA, cvD32);
}

void sis3803_disable_extshadow(){
    int val=SIS3803_DIS_IRQSRC1;
    CAENVME_WriteCycle(Handle,SIS3803AD+SIS3803_CTL_REG, &val, cvA32_U_DATA, cvD32);
}
