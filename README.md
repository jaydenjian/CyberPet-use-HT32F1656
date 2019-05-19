# CyberPet-use-HT32F1656  <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/246529499_c.gif" width=15% align="right"/>
使用單晶片 _*HT32F1656*_ 以及 16*16點矩陣，所開發出的一套結合紅綠燈元素的養寵物小遊戲。


<br>

## 介紹 Introduct
使用單晶片HT32F1656及其擴充板做開發。
透過軟體-`keil µVision`編譯單晶片，結合16*16點矩陣與擴充板上的七段顯示器、Led、指撥開關、按鈕，所開發出的一套養寵物遊戲。


<br>

## 目錄 Table of content
* 遊戲內容
* 裝置設計
  * 使用元件
  * 介面配置
* 16*16點矩陣設計
  * Decoder Data Sheet 研究
  * 動畫編碼
* 程式設計
  * 有限狀態機設計(FSM Design)
  * 程式流程圖
  * Main程式碼
* Prototype


<br>

## 遊戲內容 Game Design
* 小綠人會遵守紅燈停、綠燈行的交通守則來顯示動畫。
* 過程中，小綠人的能量會逐漸下降，並有一定機率會生病。
* 玩家須細心照顧小綠人，確保小綠人在執行任務的過程中能免於死亡。


<br>

## 裝置設計 Device Design
* 使用元件 
  * 單晶片 HT32F1656 以及 擴充板 <br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/%E5%9C%96%E5%B1%A4%201.png" width=20% > <br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/%E5%9C%96%E5%B1%A4%202.png" width=40% >
  
  <br> 
  
  * 七段顯示器：顯示剩餘秒數與死亡訊息 <br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/7seg.png" width=15% >
  
  <br>
  
  * LED燈：顯示小綠人能量<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Led.png" width=15% >
  <br>
  
  * 指撥開關：控制小綠人餵食與打針<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/%E6%8C%87%E6%92%A5.png" width=15% >
  
  <br>
  
  * 16*16點矩陣：顯示小綠人動畫<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/%E5%9C%96%E5%B1%A4%203.png" width=30% >
  
  <br>
  
  * RGB LED燈：顯示紅綠燈狀態<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/RGB%20LED.jpg" width=15% >



<br>

* 介面配置
<p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/device_setting.png" width=80% >


<br>


## 16＊16點矩陣設計 LED Matrix Design
* Decoder Data Sheet 研究：<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/LED%20Matrix%20Pin.png" width=50% align="right"/>

  16x16點矩陣是利用2個74HC138D, 2個74HC595D 所控制，2種decoder的功能都是可以利用3隻PIN腳控制8bit的輸出，由2個138 decoder控制「行」，2個    595 decoder控制「列」，並藉由視覺暫留的方式，將圖形呈現出來。

<br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/LED%20Matrix%20Data%20Process-04.png" width=70% />
<br> <p align="center"> 圖像顯示流程圖

> 74HC595D： <br>
   使用16x16點矩陣上的DI, CLK, LAT腳位來輸出入。
 <br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/595_function%20Flow-05.png" width=70% />
<br> <p align="center"> 74HC595D Decode訊號傳輸流程
 
> 74HC138D： <br>
   使用16x16點矩陣上的G,A,B,C,D腳位，D腳位是用來選擇2個138IC的其中一個，G腳位則是致能端。A,B,C腳位可以組合出8種8bit的輸出
 <br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/138_outputTable.png" width=70% />
<br> <p align="center"> 74HC138D Decode輸出表
 







