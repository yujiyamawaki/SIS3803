# ofxSIS3803
## Overview
VMEcontroller V1718とSIS3803 Scaler/Counterを使用したデータ収集システムです．plot/Monitor.pyを使用すれば取得したデータをモニタリングすることができます．
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

(https://user-images.githubusercontent.com/23188436/54976528-ff3c0100-4fdd-11e9-818d-b5b8968a093c.jpeg)


````csharp
using System;
namespace Xamalist
{
    // 外部に公開したくない文字列などの設定ファイル
    public static class Consts
    {
        // 接続先の Webサーバのアドレス
        public static readonly string AzureWebsitesUrl = "https://(サーバーのURL文字列).azurewebsites.net";

        // Azure 上のストレージの接続文字列
        public static readonly string StorageConnectionString = "めっちゃ長い接続文字列。Azureのポータルの「アクセスキー」から取って来てね";
        // 参照:『Microsoft Azure Storage の概要』 https://docs.microsoft.com/ja-jp/azure/storage/storage-introduction
    }
}
````
## Author
[yujiyamawaki](https://github.com/yujiyamawaki)  
