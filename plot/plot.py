import sys
import pandas as pd
import matplotlib.pyplot as plt

if __name__ == "__main__":
    args = sys.argv
    argc = len(args)
    if argc != 2:
        print("oosugi ka sukunaika \n")
        sys.exit(1)

    df = pd.read_csv('../../data/lm2017{0}.csv'.format(args[1]),names=['time','sec','ch0','ch1','ch2','ch3','ch4','ch5','ch6','ch7','ch8','ch9','ch10','ch11','ch12','ch13','ch14','ch15'])

    plt.figure(num=None, figsize=(12, 6), dpi=80, facecolor='w', edgecolor='k')
    plt.rcParams["font.size"] = 16

    plt.plot(df['sec'],df['ch4'])
    plt.plot(df['sec'],df['ch5'])
    plt.plot(df['sec'],df['ch6'])
    plt.plot(df['sec'],df['ch7'])
    plt.grid()
    #plt.xlim(left=0)
    plt.xlim([0,90000])
    #plt.ylim([0,90000])
    #plt.ylim(bottom=0)
    plt.title("Scaler Information")
    plt.legend(loc='upper right') #upper or lower
    plt.ylabel('Counts/100ms')
    plt.xlabel('time[s]')
    plt.show()
