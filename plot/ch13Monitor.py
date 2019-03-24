import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
plt.rcParams["font.size"] = 16

def animate(i):
    f = open("../../data/raw{0}.csv".format(args[1]),"r").read()
    data = f.split('\n')
    x = np.array([])
    y0 = np.array([0])
    length = len(data) - 3050
    counter = 0
    for eachLine in data:
        if len(eachLine.split(',')) != 17: continue
        else:
            counter += 1
            if counter < 3050 :
                (time, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) = eachLine.split(',')
                x = np.append(x,np.array([int(ch0)/10]))
                y0 = np.append(y0,np.array([int(ch13)]))
            if counter > length and  counter >= 3050:
                (time, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) = eachLine.split(',')
                x = np.append(x,np.array([int(ch0)/10]))
                y0 = np.append(y0,np.array([int(ch13)]))
    diff_y0 = np.diff(y0)
    mx = max(x)
    ax1.clear()
    ax1.plot(x,diff_y0, label='Intensity Monitor')
    ax1.set_xlim([mx-300,mx])
    #ax1.set_ylim(bottom=0)
    ax1.set_ylim([0,3000])
    plt.grid()
    plt.title("Scaler Information #{0}".format(args[1]))
    plt.legend(loc='lower left')
    plt.ylabel('Counts/100ms')
    plt.xlabel('time[s]')

if __name__ == "__main__":
    args = sys.argv
    argc = len(args)
    if argc > 2:
        print("Need an argment.\n")
        sys.exit(1)
    fig = plt.figure(num=None, figsize=(14, 5), dpi=80, facecolor='w', edgecolor='k')
    ax1 = fig.add_subplot(1,1,1)
    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()