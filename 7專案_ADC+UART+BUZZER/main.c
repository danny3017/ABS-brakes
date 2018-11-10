#include "HT66F70A.h"
#include "MyType.h"
#define fsys 8000000                             //�t���W�v8MHz
#define	_TX			_pc1
#define	_TXC		_pcc1
#define	_RX			_pc3
#define	_RXC		_pcc3			
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
u8 SUM=30;
void UARTTxData(u8);
void delay_ms(u16);
void main(void)
{
	_RXC=1;	//INT0�t��Ĳ�o
	_TX=1; _TXC=0;					//_TX����X�Ҧ�(��XHi)		
    _wdtc = 0xab;   //�����ݪ���
	_scomen = 0;    //����LCD����
	_tm0c0=0b00010000;	//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;	//T/C, TM0A Match Clear	    
	_tm2c0=0; _tm2c1=0b00110001;	//STM:���k�X��X�Ҧ�,CCRA�k�X�M��
	_emi=1;	         //�}�Ҥ��_
	while(1)
	{
				UARTTxData(SUM);	   
				UARTTxData(20);	  
				delay_ms(1000);
				delay_ms(1000);
	}
}

void UARTTxData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=BITC%256; _tm0ah=BITC/256;				//T
	_TX=0;											//�_�l�줸
	_t0on=1;
	_t0af=0;
	while(!_t0af);									//����T��
	_t0af=0;
	do 
	{	_TX=(data & temp)? 1 : 0 ;	  				//�̸�Ʀ줸�]�w�}�쪬�A
		while(!_t0af);								//����T�ɶ�
		_t0af=0;
		temp<<=1;
	} while (temp);	
	_TX=1;											//�����줸
	while(!_t0af);
	_t0on=0;
}
void delay_ms(u16 del)
{	u16 i;
	for(i=0;i<del;i++) {GCC_DELAY(2000);}			//Delay del ms @fSYS=8MHz
}