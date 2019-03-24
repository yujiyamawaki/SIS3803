# ofxSIS3803
## Overview
VMEcontroller V1718とSIS3803 Scaler/Counterを使用したデータ収集システムです。
## Description
外部クロック制御で動きます。  
rawxxxx.csvにスケーラ情報を書き出し、
- 指定時間になる
- Ctrl+cで中断シグナルを送る  
するとbuildxxxx.csvにBuildしてくれます。  
## Demo
あとで書く。  
## Requirement
PCにfirmwareをインストールする必要があります。  
[V1718firmware](http://www.caen.it/csite/CaenProd.jsp?idmod=417&parent=11)  
SIS3803のマニュアルです。  
[SIS3803Manuals](http://dasdevpc.triumf.ca/online/manuals/vme/sis3803.pdf)  
## Usage
0. make しましょう  
1. /misc/config.txtにCLKを入れるチャンネルとCLK rate(Hz)を設定します。  
2. オプションをつけると/misc/DAQ.logにログを残せます。  
- test 出力ファイルはraw0000.csv  
./sDAQ [-n] [time(sec)]  
- junk  
./sDAQ [-j] [time(sec)]  
- calibration  
./sDAQ [-c] [time(sec)]  
- physics  
./sDAQ [-p] [time(sec)]  
## Install
1. インストール方法  
git clone git@github.com:yujiyamawaki/ofxSIS3803.git  
2.  更新  
git pull  
## Author
[yujiyamawaki](https://github.com/yujiyamawaki)  
