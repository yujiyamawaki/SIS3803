# ofxSIS3803
## Overview
VMEcontroller V1718とSIS3803 Scaler/Counterを使用したデータ収集システムです．  
plot/Monitor.pyを使用すれば取得したデータをモニタリングすることができます．
## Description
外部クロック制御で動きます．  
rawxxxx.csvにスケーラ情報を書き出し，
- 指定時間になる
- Ctrl+cで中断シグナルを送る  
するとbuildxxxx.csvにBuildしてくれます．  
## Demo
あとで書く．  
## Requirement
PCにfirmwareをインストールする必要があります．  
[V1718firmware](http://www.caen.it/csite/CaenProd.jsp?idmod=417&parent=11)  
SIS3803のマニュアルです．  
[SIS3803Manuals](http://dasdevpc.triumf.ca/online/manuals/vme/sis3803.pdf)  
## Install
1. インストール方法  
git clone git@github.com:yujiyamawaki/ofxSIS3803.git  
2.  更新  
git pull  
## Usage
0. cloneしたままでは動きません，makeしましょう．
1. /misc/config.txtにCLKを入れるチャンネルとCLK rate(Hz)を設定します．  
2. オプションをつけると/misc/DAQ.logにログを残せます．  
- test 出力ファイルはraw0000.csv  
./sDAQ -n [time(sec)]  
- junk  
./sDAQ -j [time(sec)]  
- calibration  
./sDAQ -c [time(sec)]  
- physics  
./sDAQ -p [time(sec)]  
<img src="https://user-images.githubusercontent.com/23188436/54976528-ff3c0100-4fdd-11e9-818d-b5b8968a093c.jpeg" width="400px">

````csharp
for eachLine in data:
    if len(eachLine.split(',')) != 17: continue
    else:
        counter +=1
        if counter < timeScale:
            (time, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) = eachLine.split(',')
            x = np.append(x,np.array([int(ch0)/10]))
            y0 = np.append(y0,np.array([int(ch1)]))
            y1 = np.append(y1,np.array([int(ch2)]))

        if counter > readlen and counter >= timeScale:
            (time, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15) = eachLine.split(',')
            x = np.append(x,np.array([int(ch0)/10]))
            y0 = np.append(y0,np.array([int(ch1)]))
            y1 = np.append(y1,np.array([int(ch2)]))

diff_y0 = np.diff(y0)
diff_y1 = np.diff(y1)

mx = max(x)
ax1.clear()

ax1.plot(x,diff_y0, label='Ch.1')
ax1.plot(x,diff_y1, label='Ch.2')
````
## Author
[yujiyamawaki](https://github.com/yujiyamawaki)  
