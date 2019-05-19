# CyberPet-use-HT32F1656  <img src="https://github.com/jaydenjian/CyberPet-use-HT32F1656/blob/master/media/246529499_c.gif" width=15% align="right"/>
使用單晶片 _*HT32F1656*_ 以及 16*16點矩陣，所開發出的一套結合紅綠燈元素的養寵物小遊戲。


<br>

## Introduct
使用單晶片HT32F1656及其擴充板做開發。
透過軟體-`keil µVision`編譯單晶片，結合16*16點矩陣與擴充板上的七段顯示器、Led、指撥開關、按鈕，所開發出的一套養寵物遊戲。


<br>

## Table of Content
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

## 遊戲內容
* 小綠人會遵守紅燈停、綠燈行的交通守則來顯示動畫。
* 過程中，小綠人的能量會逐漸下降，並有一定機率會生病。
* 玩家須細心照顧小綠人，確保小綠人在執行任務的過程中能免於死亡。


<br>

## 裝置設計
