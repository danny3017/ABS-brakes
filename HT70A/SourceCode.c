// PROGRAM	: 3-1.c									2013.1025
/* FUNCTION	: LED Scanning Demo Program for 
				  C-Language Introduction			By Steven*/
#include <HT66F70A.h>
void Delay100us(unsigned short);					//�禡�쫬�ŧi
void main()
{	unsigned char i,j;	
	_wdtc=0b10101111;								//�����ݭ̪��p�ɾ�
	_pdc=0x00;										//�W��PC����X�ݩ�
	_pd=0xFE;										//�]�wPC���
	while(1)
	{	
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
}	
void Delay100us(unsigned short del)					//����del*200���O�g��
{	
	unsigned short i,j;								//@fSYS=8MH,����del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}