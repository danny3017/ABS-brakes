#include "HT66F70A.h"
#include "TM.h"
 
//�M�Τ_�Ҳզ�f���w�ɾ�
void TM0_INIT(void)
{
	//TXD RXD��l��
	_pcc2 = 0;
	_pcc3 = 1;
	_pcpu3 = 1;
	_pcpu2 = 1;
	
    _tm0c0=0x10;//�p�ƾ��Ȱ��B��
    _tm0c1=0xc1;//�M0               
    _tm0al=0x41;//buad rate 9600
    _tm0ah=0x03; 
 
       
    _t0ae = 1;
    _t0af = 0;
    _t0on = 0;
    _emi = 1;
    _mf0e = 1;
    _mf0f = 0;
	}
 
 
