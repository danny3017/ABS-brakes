#include "HT66F70A.h"
#include "Interrupt.h"
#include "TM.h"
#include "UART.h"
#include "String.h"
 
char *Head;
char *l;
 
//�����ܼ�
extern char buff[num];
extern char Buff[32];
extern unsigned int count;
 
//�禡
void delay1s(void);
 
 
//�D�{�ǤJ�f
void main()
{
    //TO DO
    _wdtc = 0xab;//�ݪ����T��
    unsigned char key;
    UART_INIT();
    Head=85;
    l=75;
    while(1){
    Send(&Head);
    Send(&l);
    }
    /*
    Receive();
    Send_Array();
    Receive_if(Buff);
    //Send_num(8,Buff);
    Send(Buff);	
    */
}
 
void delay1s(void)   //�~�t 1us
{
    unsigned char a,b,c,n;
    for(c=205;c>0;c--)
        for(b=171;b>0;b--)
            for(a=8;a>0;a--);
    for(n=1;n>0;n--);
}
	
 
