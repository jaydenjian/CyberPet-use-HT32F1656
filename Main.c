#include "ht32.h"                   //Header file
#include "ht32_board.h"

void Delay(u32 cnt){                //Delay function
 while(cnt--); 
 }  

void CKCU_configuration(void){      //Setting Clock

	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  	CKCUClock.Bit.PA         = 1;       //Enable Port A Clock Function 
  	CKCUClock.Bit.PB         = 1;       //Enable Port B Clock Function
	CKCUClock.Bit.PC         = 1;       //Enable Port C Clock Function
	CKCUClock.Bit.PD         = 1;       //Enable Port D Clock Function
	CKCUClock.Bit.PE         = 1;       //Enable Port E Clock Function
  	CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

void GPIO_configuration(void)       //Pin Setting 
{	
	//Set Port A as output pin , for 7seg(a-g)
  	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_0, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_2, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_3, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_4, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_5, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_6, GPIO_DIR_OUT);
	//Set Port B as output pin , for 7seg(Enable)
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_0, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_1, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_2, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_3, GPIO_DIR_OUT);
    //Setting Dip Switch
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_4, GPIO_DIR_IN);
	GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_4, GPIO_PR_UP);
	GPIO_InputConfig(HT_GPIOB, GPIO_PIN_4, ENABLE);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_5, GPIO_DIR_IN);
	GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_5, GPIO_PR_UP);
	GPIO_InputConfig(HT_GPIOB, GPIO_PIN_5, ENABLE);
	//Set Port C as output pin , Setting LED
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_0, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_1, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_2, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_3, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_4, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_5, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_6, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_7, GPIO_DIR_OUT);
	//16*16matrix(D,C,B,A,G,CLK,LAT)
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_0, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_1, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_2, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_3, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_4, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_5, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_6, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_7, GPIO_DIR_OUT);
	//16*16matrix-DI
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_0, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_1, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_2, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_3, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_4, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_5, GPIO_DIR_OUT);
  	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_6, GPIO_DIR_OUT);
	GPIO_DirectionConfig(HT_GPIOE, GPIO_PIN_7, GPIO_DIR_OUT);
}

//////////////////////////////////////////////////////////////////////
//Use for 138 Decoder
void Scan_Line(unsigned char m); 

//Use for 595 Decoder
void Send( unsigned char dat);

//Use to delay every frame of animation
void Display(unsigned char dat[][32],int light_time);
void dead_Display(unsigned char dat[][32],int light_time);

//595 Decoder register
unsigned char Display_Buffer[2];

///////////////////////////////////////////////////////////////////////////////////

//Animation Code
unsigned char  Walk1[1][32] = 
{

 0xF3, 0xe1, 0xF3, 0xf9, 0xf8, 0xf8, 0xf4, 0xee, 0xfe, 0xfe, 0xFd, 0xFb, 0xe3, 0xff, 0xFF, 0xFF,
  0xff, 0xFF, 0xFF, 0xff, 0x3f, 0xdf, 0xef, 0x7f, 0x7f, 0xbf, 0xdF, 0xeF, 0xF7, 0xF7, 0xFF, 0xFF
};
unsigned char  Walk2[1][32] = 
{

  0xf3, 0xe1, 0xf3, 0xf9, 0xf8, 0xf8, 0xf4, 0xee, 0xfe, 0xfe, 0xfe, 0xfd, 0xfb, 0xc7, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x3f, 0xdf, 0xef, 0x7f, 0x7f, 0xbf, 0xcf, 0xf7, 0xf7, 0xf7, 0xef, 0xff

};
unsigned char  Walk3[1][32] = 
{

0xf3, 0xe1, 0xf3, 0xf9, 0xfc, 0xfc, 0xf8, 0xf6, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xf1, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0xdf, 0x5f, 0x7f, 0xbf, 0xbf, 0xdf, 0xef, 0xcf, 0xff, 0xff
};
unsigned char  Walk4[1][32] = 
{

   0xf9, 0xf0, 0xf9, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfd, 0xfe, 0xfd, 0xfb, 0xfc, 0xfe, 0xf8, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x5f, 0x5f, 0x3f, 0x3f, 0xbf, 0xcf, 0xf7, 0xf7, 0xff, 0xff
};
unsigned char  Walk5[1][32] = 
{

 0xf9, 0xf0, 0xf9, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfd, 0xfe, 0xfd, 0xfd, 0xfe, 0xff, 0xfc, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x5f, 0x5f, 0x3f, 0x3f, 0xbf, 0xdf, 0x6f, 0x4f, 0x7f, 0xff
};
unsigned char  Walk6[1][32] = 
{

 0xf9, 0xf0, 0xf9, 0xfd, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x9f, 0x5f, 0x1f, 0xdf, 0x1f, 0xff,
};
unsigned char  Walk7[1][32] = 
{

  0xf9, 0xf0, 0xf9, 0xfc, 0xfc, 0xfe, 0xfc, 0xfc, 0xff, 0xff, 0xfe, 0xfd, 0xfe, 0xfc, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x5f, 0x5f, 0x3f, 0x3f, 0x7f, 0xbf, 0xcf, 0xf7, 0xc7, 0xff
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  Stop1[1][32] = 
{

   0xfc,0xfb,0xf7,0xf7,0xf7,0xfb,0xfc,0xfe,0xf8,0xf4,0xf4,0xf8,0xfc,0xfe,0xfd,0xf1,
0x3f,0xdf,0xef,0xed,0x83,0xdf,0x3f,0x7f,0x1f,0x2f,0x2f,0x1f,0x3f,0x7f,0x7f,0x1f,

};
unsigned char  Stop2[1][32] = 
{

  0xfc,0xfb,0xf7,0xf7,0xf7,0xfb,0xfc,0xfe,0xf8,0xf4,0xf4,0xf8,0xfc,0xf6,0xf9,0xfd,
0x3f,0xdf,0xeb,0xed,0x83,0xdf,0x3f,0x7f,0x1f,0x2f,0x2f,0x1f,0x3f,0x7f,0x7f,0x1f,
};
unsigned char  Stop3[1][32] = 
{

  0xfc,0xfb,0xf7,0xf7,0xf7,0xfb,0xfc,0xfe,0xf8,0xf4,0xf4,0xf8,0xfc,0xf6,0xf9,0xfd,
0x3f,0xdf,0xeb,0xed,0x83,0xdf,0x3f,0x7f,0x1f,0x2f,0x2f,0x1f,0x3f,0x7f,0x7f,0x1f,
};
unsigned char  Stop4[1][32] = 
{

   0xfc,0xfb,0xf7,0xf7,0xf7,0xfb,0xfc,0xfe,0xf8,0xf4,0xf4,0xf8,0xfc,0xf6,0xf9,0xfd,
0x3b,0xdd,0xeb,0xed,0x83,0xdf,0x3f,0x7f,0x1f,0x2f,0x2f,0x1f,0x3f,0x7f,0x7f,0x1f,

};
/////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  Eat1[1][32] = 
{

 0xfe,0xfd,0xfb,0xfb,0xf8,0xff,0xff,0xfe,0xf3,0xed,0xe4,0xe5,0xf3,0xff,0xff,0xff,
0x1f,0xef,0xf7,0xf7,0x77,0xb7,0x6f,0x0f,0xc3,0xc5,0x26,0xe6,0xe7,0xe7,0xdb,0x3c
};
unsigned char  Eat2[1][32] = 
{

0xfe,0xfd,0xfb,0xfb,0xfb,0xea,0xfd,0xf6,0xe5,0xdb,0xe7,0xff,0xff,0xff,0xff,0xff,
0x1f,0xef,0xf7,0xf7,0x77,0xf7,0xef,0x0f,0xc3,0xc5,0x26,0xe6,0xe7,0xe7,0xdb,0x3c,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  Inj1[1][32] = 
{


  0xf8,0xfe,0xfe,0xfe,0xfe,0xe0,0xfa,0xfa,0xf8,0xf8,0xf8,0xf8,0xf8,0xfe,0xfe,0xff,
0x1f,0x7f,0x7f,0x7f,0x7f,0x07,0x5f,0x5f,0x1f,0x1f,0x1f,0x1f,0x1f,0x7f,0x7f,0x7f,
};
unsigned char  Inj2[1][32] = 
{

 0xff,0xf8,0xfe,0xfe,0xfe,0xe0,0xfa,0xfa,0xfa,0xf8,0xf8,0xf8,0xf8,0xfe,0xfe,0xff,
0xff,0x1f,0x7f,0x7f,0x7f,0x07,0x5f,0x5f,0x5f,0x1f,0x1f,0x1f,0x1f,0x7f,0x7f,0x7f,
};
unsigned char  Inj3[1][32] = 
{

0xff,0xff,0xf8,0xfe,0xfe,0xe0,0xfa,0xfa,0xfa,0xfa,0xf8,0xf8,0xf8,0xfe,0xfe,0xff,
0xff,0xff,0x1f,0x7f,0x7f,0x07,0x5f,0x5f,0x5f,0x5f,0x1f,0x1f,0x1f,0x7f,0x7f,0x7f,
};
unsigned char  Inj4[1][32] = 
{

0xff,0xff,0xff,0xf8,0xfe,0xe0,0xfa,0xfa,0xfa,0xfa,0xf8,0xf8,0xf8,0xfe,0xfe,0xff,
0xff,0xff,0xff,0x1f,0x7f,0x07,0x5f,0x5f,0x5f,0x5f,0x1f,0x1f,0x1f,0x7f,0x7f,0x7f,
};
unsigned char  Inj5[1][32] = 
{

0xff,0xff,0xff,0xff,0xf8,0xe0,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xf8,0xfe,0xfe,0xff,
0xff,0xff,0xff,0xff,0x1f,0x07,0x5f,0x5f,0x5f,0x5f,0x5f,0x5f,0x1f,0x7f,0x7f,0x7f,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  Sick1[1][32] = 
{
0xf3, 0xe1,0xf3,0xf9,0xfc,0xfc,0xf8,0xf6,0xfe,0xfe,0xfe,0xfd,0xfd,0xf1,0xff,0xff,
0xff,0xff,0xff,0xff,0x7f,0xbf,0xdf,0x5f,0x7f,0xbf,0xbf,0xdf,0xef,0xcf,0xff,0xff
};
unsigned char  Sick2[1][32] = 
{

  0xff,0xf3,0xe1,0xf3,0xf9,0xfc,0xf8,0xf4,0xfa,0xfe,0xfd,0xfc,0xff,0xfc,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0x7f,0xbf,0x7f,0x7f,0x3f,0xbf,0x5f,0x6f,0x4f,0xff,0xff,

};
unsigned char  Sick3[1][32] = 
{

0xff,0xff,0xff,0xe3,0xc1,0xe0,0xf8,0xf1,0xfa,0xfc,0xfc,0xfb,0xf1,0xfd,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0x3f,0x3f,0x3f,0x7f,0x8f,0xef,0xff,0xff,
};
unsigned char  Sick4[1][32] = 
{

   0xff,0xff,0xff,0xff,0xff,0xe3,0xc0,0xe0,0xf0,0xe0,0xf0,0xfb,0xfb,0xf9,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xbf,0x7f,0x7f,0x7f,0x7f,0x1f,0xff,0xff,
};
unsigned char  Sick5[1][32] = 
{

 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0x83,0xc0,0xd8,0x36,0xcf,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1f,0xdf,0x23,0xff,0xff,
};
unsigned char  Sick6[1][32] = 
{

 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0x80,0x03,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x88,0xff,0xff
};
unsigned char  Sick7[1][32] = 
{

  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc7,0x80,0x03,0xff,0xff,
0xff,0xcf,0xcf,0x03,0x03,0xcf,0xcf,0xff,0xff,0xff,0xff,0xff,0x07,0x88,0xff,0xff
};
unsigned char  Dead[1][32] = 
{

  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
////////////////////////////////////////////////////////////////////////////////////////
	u16 LEDARRAY_D ; //GPIO_PIN_0//HT_GPIOD&0x01
	u16 LEDARRAY_C ; //GPIO_PIN_1//HT_GPIOD&0x02
	u16 LEDARRAY_B ; //GPIO_PIN_2//HT_GPIOD&0x04
	u16 LEDARRAY_A ; //GPIO_PIN_3//HT_GPIOD&0x08
	u16 LEDARRAY_G ; //GPIO_PIN_4//HT_GPIOD&0x10
	u16 LEDARRAY_DI;              //HT_GPIOE&0x01
	u16 LEDARRAY_CLK ;//GPIO_PIN_6//HT_GPIOD&0x40
	u16 LEDARRAY_LAT; //GPIO_PIN_7//HT_GPIOD&0x80
//////////////////////////////////////////////////////////////////////////

//Display the animation 
void walking_mod(int light_time){
	int i,j;
	
			for(i=0;i<20;i++){
				Display(Walk1,light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk2, light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk3, light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk4, light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk5, light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk6, light_time);
			}
			for(i=0;i<20;i++){
				Display(Walk7, light_time);
			}
	

}
void dead_mod(int light_time){
	int i;
	for(i=0;i<1;i++){
		dead_Display(Dead,light_time);
	}
}
void stop_mod(int light_time){
	int i;
	for(i=0;i<30;i++){
		Display(Stop1,light_time);
	}
	for(i=0;i<30;i++){
		Display(Stop2, light_time);
	}
	for(i=0;i<30;i++){
		Display(Stop3,light_time);
	}
	for(i=0;i<30;i++){
		Display(Stop4,light_time);
	}
}
void eating_mod(int light_time){
	int i;
	for(i=0;i<40;i++){
		Display(Eat1, light_time);
	}
	for(i=0;i<40;i++){
		Display(Eat2, light_time);
	}
}
void injection_mod(int light_time){
	int i;
	for(i=0;i<20;i++){
		Display(Inj1, light_time);
	}
	for(i=0;i<20;i++){
		Display(Inj2, light_time);
	}
	for(i=0;i<20;i++){
		Display(Inj3, light_time);
	}
	for(i=0;i<20;i++){
		Display(Inj4, light_time);
	}
	for(i=0;i<20;i++){
		Display(Inj5, light_time);
	}
	
}
 void sick_mod(int light_time){
	 int i;
	 for(i=0;i<20;i++){
		Display(Sick1, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick2,light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick3,light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick4, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick5, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick6, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick7, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick6, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick7, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick6, light_time);
	}
	 for(i=0;i<20;i++){
		Display(Sick7, light_time);
	}
	 
 }
 ///////////////////////////////////////////////////////////////////
 void Display(unsigned char dat[][32],int light_time)					
{
	int i;
	int ten_num = light_time/10%10;
	int per_num = light_time%10;
	u16 number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x67};

	for( i = 0 ; i < 16 ; i++ )
	{
		LEDARRAY_G = 0x10;			 //prevent overlapping ,HIGH is close 138 IC,LOW is Enable
    GPIO_WriteOutData(HT_GPIOD,LEDARRAY_G);
		
		
		Display_Buffer[0] = dat[0][i];		
		Display_Buffer[1] = dat[0][i+16];

		Send(Display_Buffer[1]);
		Send(Display_Buffer[0]);

		LEDARRAY_LAT = 0x90;	//1001 0000//lock data//latch Enable,update data,Shift register's data copy 	to Storage register
    GPIO_WriteOutData(HT_GPIOD,LEDARRAY_LAT);
		Delay(100);
	
		LEDARRAY_LAT = 0x10;//0001 0000//data unchange
		GPIO_WriteOutData(HT_GPIOD,LEDARRAY_LAT);
		Delay(100);

		Scan_Line(i);						

		LEDARRAY_G = 0;
		//GPIO_WriteOutData(HT_GPIOA,LEDARRAY_G);
		//Delay(1000);
				GPIO_WriteOutData(HT_GPIOA,number[ten_num]);
				GPIO_WriteOutData(HT_GPIOB,0x02);
				Delay(5000);
				GPIO_WriteOutData(HT_GPIOA,number[per_num]);
				GPIO_WriteOutData(HT_GPIOB,0x01);
				Delay(5000);

		//for( j = 0 ; j < 100 ; j++);					
	}	
}
///////////////////////////////////////////////////////////////////////////////
void dead_Display(unsigned char dat[][32],int light_time)					
{
	int i;
	int ten_num = light_time/10%10;
	int per_num = light_time%10;
	u16 number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x67};

	for( i = 0 ; i < 16 ; i++ )
	{
		LEDARRAY_G = 0x10;			 //prevent overlapping ,HIGH is close 138 IC,LOW is Enable
    GPIO_WriteOutData(HT_GPIOD,LEDARRAY_G);
		
		
		Display_Buffer[0] = dat[0][i];		
		Display_Buffer[1] = dat[0][i+16];

		Send(Display_Buffer[1]);
		Send(Display_Buffer[0]);

		LEDARRAY_LAT = 0x90;	//1001 0000//lock data//latch Enable,update data,Shift register's data copy 	to Storage register
		GPIO_WriteOutData(HT_GPIOD,LEDARRAY_LAT);
		Delay(100);
	
		LEDARRAY_LAT = 0x10;//0001 0000//data unchange
		GPIO_WriteOutData(HT_GPIOD,LEDARRAY_LAT);
		Delay(100);

		Scan_Line(i);						

		LEDARRAY_G = 0;
		//GPIO_WriteOutData(HT_GPIOA,LEDARRAY_G);
		//Delay(1000);
					GPIO_WriteOutData(HT_GPIOA,0x5e);  //d
					GPIO_WriteOutData(HT_GPIOB,0x08);
					Delay(1000);

					GPIO_WriteOutData(HT_GPIOA,0x79);  //e
					GPIO_WriteOutData(HT_GPIOB,0x04);
					Delay(1000);

					GPIO_WriteOutData(HT_GPIOA,0x77);  //a
					GPIO_WriteOutData(HT_GPIOB,0x02);
					Delay(1000);

					GPIO_WriteOutData(HT_GPIOA,0x5e);  //d
					GPIO_WriteOutData(HT_GPIOB,0x01);
					Delay(1000);

		//for( j = 0 ; j < 100 ; j++);					
	}	
}
//////////////////////////////////////////////////////////
 void Scan_Line( unsigned char m) //Scan colum
{	
	switch(m)
	{
		case 0:			
			LEDARRAY_D = 0;LEDARRAY_C = 0;LEDARRAY_B = 0;LEDARRAY_A = 0;
			GPIO_WriteOutData(HT_GPIOD,0x00);
			break;
		case 1:					
			LEDARRAY_D = 0;LEDARRAY_C = 0;LEDARRAY_B = 0;LEDARRAY_A = 1; 	
			GPIO_WriteOutData(HT_GPIOD,0x08);	
			break;
		case 2:					
			LEDARRAY_D = 0;LEDARRAY_C = 0;LEDARRAY_B = 1;LEDARRAY_A = 0;
			GPIO_WriteOutData(HT_GPIOD,0x04);	 		
			break;
		case 3:					
			LEDARRAY_D = 0;LEDARRAY_C = 0;LEDARRAY_B = 1;LEDARRAY_A = 1;
			GPIO_WriteOutData(HT_GPIOD,0x0c);	 		
			break;
		case 4:
			LEDARRAY_D = 0;LEDARRAY_C = 1;LEDARRAY_B = 0;LEDARRAY_A = 0; 
			GPIO_WriteOutData(HT_GPIOD,0x02);			
			break;
		case 5:
			LEDARRAY_D = 0;LEDARRAY_C = 1;LEDARRAY_B = 0;LEDARRAY_A = 1;
			GPIO_WriteOutData(HT_GPIOD,0x0A);	
			break;
		case 6:
			LEDARRAY_D = 0;LEDARRAY_C = 1;LEDARRAY_B = 1;LEDARRAY_A = 0;
			GPIO_WriteOutData(HT_GPIOD,0x06);
			break;
		case 7:
			LEDARRAY_D = 0;LEDARRAY_C = 1;LEDARRAY_B = 1;LEDARRAY_A = 1; 
			GPIO_WriteOutData(HT_GPIOD,0x0e);
			break;
		case 8:
			LEDARRAY_D = 1;LEDARRAY_C = 0;LEDARRAY_B = 0;LEDARRAY_A = 0;
			GPIO_WriteOutData(HT_GPIOD,0x01);
			break;
		case 9:
			LEDARRAY_D = 1;LEDARRAY_C = 0;LEDARRAY_B = 0;LEDARRAY_A = 1;
			GPIO_WriteOutData(HT_GPIOD,0x09);
			break;	
		case 10:
			LEDARRAY_D = 1;LEDARRAY_C = 0;LEDARRAY_B = 1;LEDARRAY_A = 0;
			GPIO_WriteOutData(HT_GPIOD,0x05);
			break;
		case 11:
			LEDARRAY_D = 1;LEDARRAY_C = 0;LEDARRAY_B = 1;LEDARRAY_A = 1;
			GPIO_WriteOutData(HT_GPIOD,0x0d);
			break;
		case 12:
			LEDARRAY_D = 1;LEDARRAY_C = 1;LEDARRAY_B = 0;LEDARRAY_A = 0; 	
			GPIO_WriteOutData(HT_GPIOD,0x03);
			break;
		case 13:
			LEDARRAY_D = 1;LEDARRAY_C = 1;LEDARRAY_B = 0;LEDARRAY_A = 1; 
			GPIO_WriteOutData(HT_GPIOD,0x0b);		
			break;
		case 14:
			LEDARRAY_D = 1;LEDARRAY_C = 1;LEDARRAY_B = 1;LEDARRAY_A = 0; 
			GPIO_WriteOutData(HT_GPIOD,0x07);
			break;
		case 15:
			LEDARRAY_D = 1;LEDARRAY_C = 1;LEDARRAY_B = 1;LEDARRAY_A = 1; 		
			GPIO_WriteOutData(HT_GPIOD,0x0f);
			break;
		default : break;	
	}
}

///////////////////////////////////////////////////////////////////////////
void Send( unsigned char dat) //LEDARRAY_G(138 IC) need be HIGH level(close)
{
	unsigned char i;
	char j = 0;
	LEDARRAY_CLK = 0x10; //0001 0000 //cLK close,595 SH_CP won't shift data
	GPIO_WriteOutData(HT_GPIOD,LEDARRAY_CLK);
	Delay(10);	
	LEDARRAY_LAT = 0x10;		//0001 0000	//latch close,data unchange
	GPIO_WriteOutData(HT_GPIOD,0x10);
	Delay(10);

	for( i = 0 ; i < 8 ; i++ )      //create a signal to 525 IC. Storing in 595 Shift register(CLK)
	{
		if( dat&0x01 )
		{
			LEDARRAY_DI = 0x01; //0000 0001 //525 IC DS-HIGH
			GPIO_WriteOutData(HT_GPIOE,LEDARRAY_DI);			
		}
		else
		{
			LEDARRAY_DI = 0x00;//0000 0000 //525 IC DS-LOW
			GPIO_WriteOutData(HT_GPIOE,LEDARRAY_DI);	
		}


		LEDARRAY_CLK = 0x50; //0101 0000//CLK Enable ,data shift
		GPIO_WriteOutData(HT_GPIOD,LEDARRAY_CLK);	
			Delay(10);
		LEDARRAY_CLK = 0x10;//0001 0000 //CLK close, data unchange
		GPIO_WriteOutData(HT_GPIOD,LEDARRAY_CLK);	
			Delay(10);

		
		dat >>= 0x01;
			
	}			
}
//////////////////////////////////////////////////////////////////////////////////

enum Light_State{red, green, yellow};  //Red,Green,Yellow Light status
int Is_feed = 0;                        //Feed Flag
int feed_flag = 0;                      //Feed animation flag

//Display 7 Segment, Led Matrix Animation, RGB LED
void show_time_man(int light_time, enum Light_State light_state)  
{
	u16 number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x67};
	int ten_num = light_time/10%10;
	int per_num = light_time%10;
	int i, j;
	
	
	if(light_state == green)
	{
		walking_mod(light_time);
		
	}
	
	if(light_state == red)
	{
		if(Is_feed == 1){
				eating_mod(light_time);
			
		}else{ //Is_feed==0
				stop_mod(light_time);
        
		}
	}
}

void show_led(int energy)   //Display Energy
{
	int P0 = 0xff;
	P0 = ~(P0>>(8-energy));
	GPIO_WriteOutData(HT_GPIOC, P0);
	Delay(1000);
}

int main(void)              //Status Switch
{
  enum Light_State light_state = green;
  int light_time = 5;       //Red,Green,Yellow Light maintain Time
  int ten_num;
  int per_num;
  int energy = 8;           //Character Default Energy
  int feed;
  int i, j;

  u16 number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x67};

  int LED_Control[8]={0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
  int needle;
  CKCU_configuration();
  GPIO_configuration();
	
  while(1)
  {
    ten_num = light_time/10%10;
	per_num = light_time%10;
	if(energy == 0)  //man_is_dead
	{
			
					
					dead_mod(light_time);
					
			/////////////////////////////////////////////
				GPIO_WriteOutData(HT_GPIOC, 0xff);  //led
				Delay(1000);
	}else if((rand()%50) ==1){
			while(1)//sick_state
			{
				needle = GPIO_ReadInData(HT_GPIOB);
				needle = needle|0xdf;
				if(needle == 0xdf)
				{
					break;
				}else{
						sick_mod(light_time);
					
				}	
			}
				while(1)
				{
					needle = GPIO_ReadInData(HT_GPIOB);
					needle = needle|0xdf;
					if(needle != 0xdf)
					{
						break;
					}
								injection_mod(light_time);
	
				}

	}else{
		switch(light_state){
			
		case red:                                   //Red State
				feed = GPIO_ReadInData(HT_GPIOB);
				feed = feed|0xef;
				if(feed == 0xef)
				{
						energy++;
						if(energy>8)
						{
							energy=8;
						}
						Is_feed = 1;
				}else{
						Is_feed = 0;
				}
				show_time_man(light_time, light_state);
				light_time--;
				if(light_time == -1)
				{
					light_time = 5;
					light_state = green;
					energy--;
				}
				show_led(energy);
				break;
		case green:                                 //Green State
				show_time_man(light_time, light_state);
				light_time--;
				if(light_time == -1)
				{
					light_time = 5;
					light_state = yellow;
					energy--;
				}
				show_led(energy);
				break;
		case yellow:                                //Yellow State
				Delay(1000);
				light_state = red;
		
				break;
		}
	}
  }
}
