// PROGRAM	: 3-1.c									2013.1025
/* FUNCTION	: LED Scanning Demo Program for 
				  C-Language Introduction			By Steven*/
#define		SW0		   	_pe0		//PE0
#define		SW0C		_pec0		//PEC0
#define		SW0PU	 	_pepu0		//PEPU0
#include <HT66F70A.h>

void Delay100us(unsigned short);
void LED(void);
void main()
{	
	_pdc=0x00;
	_wdtc=0b10101111;							//�����ݭ̪��p�ɾ�
	SW0C=1; SW0PU=1;                      		//�W��SW0���}����J�ñҥδ��ɹq��
	while(1)
	{	
		if(SW0) _pd=0b01010101;						//���� 120 mSec; 		            	//�P�_�u���O�_����
		else _pd=0b11111111;
	}
}

//////////////
//�ɶ�����
//////////////
void Delay100us(unsigned short del)					//����del*200���O�g��
{	
	unsigned short i,j;								//@fSYS=8MH,����del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}

//////////////
//LED����
//////////////
void LED()
{
	unsigned char i,j;
	for(j=0;j<7;j++)	
		{	
			Delay100us(1000);
			_pd=_pd<<1|0x01;						//PG�����ø�1��LSB
		}
		do	
		{	
			Delay100us(1000); _pd=_pd>>1|0x80;		//PG�k���ø�1��MSB
		}while(_pd!=0b11111110);
}