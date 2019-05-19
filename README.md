# CyberPet-use-HT32F1656  <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/246529499_c.gif" width=15% align="right"/>
使用單晶片 _*HT32F1656*_ 以及 16*16點矩陣，所開發出的一套結合紅綠燈元素的養寵物小遊戲。


<br>

## 介紹 Introduct
使用單晶片HT32F1656及其擴充板做開發。
透過軟體-`keil µVision`編譯單晶片，結合16*16點矩陣與擴充板上的七段顯示器、Led、指撥開關、按鈕，所開發出的一套養寵物遊戲。


<br>

## 目錄 Table of content
* [遊戲內容](#遊戲內容-Game-Design)
* [裝置設計](#裝置設計-Device-Design)
  * 使用元件
  * 介面配置
* [LED點矩陣設計](#LED點矩陣設計-LED-Matrix-Design)
  * Decoder Data Sheet 研究
  * 動畫編碼
* [程式設計](#程式設計-Programming)
  * 有限狀態機設計(FSM Design)
  * 程式流程圖
  * Main程式碼
* [Prototype](#Prototype)


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


## LED點矩陣設計 LED Matrix Design
### Decoder Data Sheet 研究：<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/LED%20Matrix%20Pin.png" width=50% align="right"/>

  16x16點矩陣是利用2個74HC138D, 2個74HC595D 所控制，2種decoder的功能都是可以利用3隻PIN腳控制8bit的輸出，由2個138 decoder控制「行」，2個    595 decoder控制「列」，並藉由視覺暫留的方式，將圖形呈現出來。

<br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/LED%20Matrix%20Data%20Process-04.png" width=70% />
<br> <p align="center"> 圖像顯示流程圖

> **74HC595D**： <br>
使用16x16點矩陣上的`DI`, `CLK`, `LAT`腳位來輸出入 —— DI腳用於傳輸每bit的LED是否亮(HIGH=亮,LOW=不亮)；CLK腳用於shift register clock，上升時發送data出去；LAT腳用於鎖存剛發送出來的data，給後面的138解碼器做掃描讀取資料用。<br>
每張圖共由***32組8bit編碼*** 所組成，每次發送一組8bit的data出去(eg.0xF4)，接著由138解碼器掃描輸出LED。因為速度很快，足以在人眼上產生視覺暫留效果，達到圖形顯現。<br>
595解碼器主要負責程式碼`Send`的部分。
   
<br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/595_function%20Flow-05-06-06.png" width=70% />
<br> <p align="center"> 74HC595D Decode訊號傳輸流程
 
   ```C++
   void Send( unsigned char dat) //* LEDARRAY_G(138 IC) need be HIGH level(close)
{
	...
}
   ```

 
> **74HC138D**： <br>
使用16x16點矩陣上的G,A,B,C,D腳位，D腳位是用來選擇2個138解碼器的其中一個，G腳位則是致能端，須在每次讀取圖形資料時***關閉***(G腳位設為HIGH為關閉，G=0x10)以避免重影。A,B,C腳位則可以組合出8種8bit的輸出，來掃描前端595解碼器所存入的data，最後將G腳位開啟致能，顯是圖形。 <br> 
138解碼器主要負責程式碼 `Scan_Line` 的部分。
 <br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/138_outputTable.png" width=70% />
<br> <p align="center"> 74HC138D Decode輸出表
 
 ```C++
   void Scan_Line( unsigned char m) //Scan colum
{	
	switch(m)
	{
		...
	}
}
   ```
 <br>
 
 
### 動畫編碼
LED Matrix為共陽的16進制編碼，人物走動動畫共有7張圖，人物靜止動畫共有4張圖，人物餵食共2張圖，人物醫療共5張圖，人物生病共7張圖，以及人物死亡1張圖，總共有26張圖，26個矩陣，832個8bit編碼，6656個bit要數。編碼著實耗費時間體力！ <br> 
請查閱：[圖形編碼文件檔](https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/Animation%20Code.docx)

<br> <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/GIF%20File/%E5%B0%8F%E7%B6%A0%E4%BA%BAwalkGIF.gif" width=15% />
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/GIF%20File/%E5%B0%8F%E7%B6%A0%E4%BA%BAstopGIF.gif" width=15% />
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/GIF%20File/%E5%B0%8F%E7%B6%A0%E4%BA%BAsickGIF.gif" width=15% />
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/GIF%20File/%E5%B0%8F%E7%B6%A0%E4%BA%BAinjectionGIF.gif" width=15% />
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/GIF%20File/%E5%B0%8F%E7%B6%A0%E4%BA%BAeatGIF.gif" width=15% />



<br>


## 程式設計 Programming
 
### 有限狀態機設計(FSM Design) <br>
有限狀態機（縮寫：FSM），用於表示有限個狀態以及在這些狀態之間的轉移和動作等行為的數學模型。
 <br> <p align="center"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/%E5%9C%96%E7%89%87%201.png" width=30% />

<br>

### 程式流程圖 <br> 
* Main主程式流程圖 <br> 
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Main_Process-07.png" width=60% />
<br>

* 生病程式流程圖 <br>
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Sick_-10.png" width=25% />
<br> 

* 紅燈程式流程圖 <br>
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Red_-09.png" width=35% />
<br> 

* 綠燈程式流程圖 <br>
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Green_-11.png" width=35% />
<br> 

* 黃燈程式流程圖 <br>
<img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Yellow_-08.png" width=10% />
<br> 

### Main程式碼
請參照此：[Main程式碼](https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/Main.c)



<br>


## Prototype
<br> 點擊圖片觀看影片！
<br> <a href="https://youtu.be/5tuspHQ5WGk" target="_blank"><img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/Prototype.png" 
width=70% /></a>

