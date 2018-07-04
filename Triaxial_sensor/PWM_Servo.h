#include <HT66F70A.h>
#include "MyType.h"	
#define	 R_PinC	_pdc5     //PDC.5
#define	 R_Pin	_pd5      //PD.5
#define	Period  100									//PWM�P���`��
u8	PCnt,R,RCnt;

DEFINE_ISR(ISR_STM,0x14)
{	
	if(PCnt--==0)									//�P�_PWM�P���O�_�w����
	{	
		PCnt=Period;
		RCnt=R; 	                 	            //�O�A�٭�Ҧ���
		R_Pin=(R==0)? 0 : 1;						//��Duty�]�w�}���l���A
	}
	else
	{	
		if(RCnt!=0) 
		{
		  RCnt--; 
		}
		else
		{ 
		  R_Pin = 0; 
		}			//�P�_Duty�Y�O�����]�w���}��0
	}
	_t2af=0;				  						//�M��T2AF�X��
}

