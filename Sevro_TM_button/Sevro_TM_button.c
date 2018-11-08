#include "HT66F70A.h"
#include "Interrupt.h"
#include "TM.h"
#include "UART.h"
#include "String.h"

typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;
char *AxisX="";
char *Head;

char *l;


//�����ܼ�
extern char buff[num];
extern char Buff[32];
extern unsigned int count;

#define LED_Port  _pg								
#define LED_PortC _pgc
#define led _pb6
#define ledc _pbc6
#define led2 _pb7
#define ledc2 _pbc7

#define  SW_P0			_pe0
#define	 SW_P1 		    _pe1
#define  SW_P0C			_pec0
#define	 SW_P1C			_pec1
#define  SW_P0PU		_pepu0
#define	 SW_P1PU		_pepu1		

u8 SEC,R1sec,AD50ms;
s16 temp,Index,auto1;

//�禡
void delay1s(void);
void TM_Set();  	  //�ɶ����_�]�w
void Interrupt_Set(); //�~�����_�]�w
void Moto_Set();	  //���F�}��]�w
void Moto_C(u8 angle);//���F����]�w
void AD_Set();		  //AD�ഫ�]�w
void Delay100us(u16);
void delay_ms(unsigned char);

void main()
{	
	_wdtc = 0xab; 
	ledc=0; ledc2=0;
	UART_INIT();
	LED_PortC=0;
	TM_Set();
	Interrupt_Set();
	Moto_Set();
	AD_Set();
	_emi=1;								//�Ұʤ��_
	Moto_C(107);
	auto1=1;
	Head = 85;
	while(1)
	{
		Send(&Head);
		Send(l);
		if(auto1==0){
			Moto_C(107);
			delay_ms(100);
			Moto_C(135);
			delay_ms(100);
		}
		if(!SW_P0){
			auto1=1;
			Moto_C(107);
		}
		if(!SW_P1){
			auto1=0;
		}
	}
}

void TM_Set(){
	_tm4c0=0b00100000;							
	_tm4c1=0b11000001;							
	_tm4al=5000%256; _tm4ah=5000/256;         	
	_mf4e=1; _t4ae=1; 							
	_t4on=1;
	SEC=0; R1sec=100; AD50ms=5; 
}

void Interrupt_Set(){
	_pac3=1; _papu3=1;
	_pac4=1; _papu4=1;
	_integ=0b00000110; //INT0�BINT1 �t�t�B�o 
	_int0e=1;
	_ifs0=0x00;
	_int1e=1;
	_ifs1=0x00;
}

void Moto_Set(){			//���F�]�w
	SW_P0C=1; SW_P0PU=1;	//�W������}�쬰��J�ݩʨñҥδ��ɹq��
	SW_P1C=1; SW_P1PU=1;
	_pds2=0x01;				//�]�wPD4��TP2�\��
	_tm2c0=0b00000000;
	_tm2c1=0b10101000;
	_tm2rp=160;
	_t2on=1;
}

void Moto_C(u8 angle){
		temp=Index*20+1000;
		_tm2al=temp%256;
		_tm2ah=temp/256;
		temp>>=1;
		Index=angle;
}

void AD_Set(){
	_adcr0=0b00000001;							//���AN1���ഫ,�]�w�ഫ���G�s��榡
	_adcr1=0b00000110;							//A/D Clock=fSYS/64,VREFS=0
	_pas0=0b00110000;							//�]�wPA1��AN1 A/D�q�D
	_pas3=0b00000011;							//�]�wPA6��AN6 A/D�q�D
	//_ade=1;									//�Ұ�ADC���_�P���_�`�}��
}

DEFINE_ISR(button_up,0x04){		//INT0 PA3���_�{��
	led2=0;
	_int0f = 0;	
	
}


DEFINE_ISR(Button_Down,0x08){	//INT1 PA4���_�{��
	led2=1;
	_int1f = 0;
}

DEFINE_ISR(ISR_STM,0x38){		//�ɶ����_�{��
	if(--AD50ms==0){
		AD50ms=1;
		_start=1; _start=0;							//�_�lADC�ഫ
		LED_Port=~_adrh;
		AxisX = _adrh;
		l=&AxisX;
	}
	if(--R1sec==0){	
		R1sec=100;
		led=1;

		if(++SEC==5)
		{
			SEC=0;
			led=0;
			
		}
	}
	_t4af=0;
}

void Delay100us(u16 del){
	u16 a,k;;
	for(a=0;a<del;a++)
		for(k=0;k<=25;k++)
			GCC_NOP();
}

void delay_ms(unsigned char del){	
	unsigned char a;
	for(a=0;a<del;a++) 
		GCC_DELAY(2000);		//���ب禡�A����2000���O�g��
}

void delay1s(void)   //�~�t 1us
{
    unsigned char a,b,c,n;
    for(c=205;c>0;c--)
        for(b=171;b>0;b--)
            for(a=8;a>0;a--);
    for(n=1;n>0;n--);
}