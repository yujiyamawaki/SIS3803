# ofxSIS3803
## Overview
VMEcontroller V1718とSIS3803 Scaler/Counterを使用したデータ収集システムです．  
plot/Monitor.pyを使用すれば取得したデータをモニタリングすることができます．
## Description
外部クロック制御で動きます．  
rawxxxx.csvにスケーラ情報を書き出し，指定時間になるか．ctrl+cで中断シグナルを送るとbuildxxxx.csvに取得したデータが出力されます．
## Requirement
firmwareをインストールする必要があります．[V1718firmware](http://www.caen.it/csite/CaenProd.jsp?idmod=417&parent=11)  
SIS3803のマニュアルです．[SIS3803Manuals](http://dasdevpc.triumf.ca/online/manuals/vme/sis3803.pdf)  
## Setup
回路を図のように組み，空きチャンネル(ch.1~15)に信号を入れると計数することができます．
<img width="500" alt="NIM" src="https://user-images.githubusercontent.com/23188436/54983798-e2f58f80-4ff0-11e9-9cbe-884d5a190f40.png">
## Install
1. インストール方法  
git clone git@github.com:yujiyamawaki/ofxSIS3803.git  
2.  更新  
git pull  
## Usage
0. cloneしたままでは動きません，makeしましょう．すると sDAQ って名前の実行ファイルができます．  
1. /misc/config.txtにCLKを入れるチャンネルとCLK rate(Hz)を設定します，デフォルトで10Hzに設定してあります．SIS3803の読み出し理論値が200MHzなのでサンプリングレートの最大値はその辺りです．試したことないけど．   
2. オプションをつけると/misc/DAQ.logにログを残せます．  
- test (この場合，出力ファイルはraw0000.csvに取得データが出力される．)  
./sDAQ -n [time(sec)]  
- junk  
./sDAQ -j [time(sec)]  
- calibration  
./sDAQ -c [time(sec)]  
- physics  
./sDAQ -p [time(sec)]  
3. python3 plot/Monitor.py xxxx  
でリアルタイムで取得データをモニタリングすることができます．事前にmatplotlibやPython3の環境設定をしておく必要があります．(matplotlibをインストールすると毎回のことながらtinker関連のエラーが出力されるけど，ググれば解決できるので自分で対処しましょう，)    
↓こんな感じでモニタリングできる．  
<img src="https://user-images.githubusercontent.com/23188436/54976528-ff3c0100-4fdd-11e9-818d-b5b8968a093c.jpeg" width="500px">
監視したいチャンネルを増やしたり減らしたりするときはplot/Monitor.pyをいじれば変更できる具体的にはここの箇所．  

~~~python:plot.py
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
~~~

## Author
[yujiyamawaki](https://github.com/yujiyamawaki)  
