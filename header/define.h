#ifndef _DEFINE_H_

#define _DEFINE_H_

int i=0,j=0,k=0;
int CLKch=0;
int runnumber = 0;

bool overflowFlag = 0;
bool endflag = 0;
bool flag[4]={0};

unsigned int setStoptime = 0;
double CLKrate = 10000;
double initialTime = 0, startTime = 0, measurementTime = 0;

short Link = 0;
short Device = 0;

unsigned long int Buffer[16]={0};
long int Offset[16]={0};
long int sumCLK=0;
unsigned long counter = 0;

struct tm tm;
struct timeval tv;
struct timespec req;

time_t t;
int32_t Handle;
char str[17][14]= {{"UNIXTIME"},{"ch.0"},{"ch.1"},{"ch.2"},{"ch.3"},{"ch.4"},{"ch.5"},{"ch.6"},{"ch.7"},{"ch8"},{"ch9"},{"ch10"},{"ch11"},{"ch12"},{"ch13"},{"ch14"},{"ch15"}};
FILE *fp, *config, *runcounter, *daqlog;

#endif
