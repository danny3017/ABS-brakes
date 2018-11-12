#include "HT66F70A.h"

#define fsys 8000000                             //�t���W�v8MHz
#define	_TX			_pc1
#define	_TXC		_pcc1
#define	_RX			_pc3
#define	_RXC		_pcc3			
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant

typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;
u8 AxisXH;
u8 AxisXL;
u16 AxisX;
u8 Head;
u8 HallHead;
u8 Axcount=0;
u8 Hacount=0;

unsigned char AXCRC,AXSUM;
unsigned char HallCRC,HallSUM;
u16 HallData = 0;
u8 HallCount = 0;
u16 XArr[5],ADx,XArrAvg=0;

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

u8 SEC,R1sec,AD10ms,Hall200ms,Whell,Whell100ms,i;
s16 temp,Index,auto1;
u16 XArrSort[5],tempx;
//�禡
void TM_Set();  	  //�ɶ����_�]�w
void Interrupt_Set(); //�~�����_�]�w
void Moto_Set();	  //���F�}��]�w
void Moto_C(u8 angle);//���F����]�w
void AD_Set();		  //AD�ഫ�]�w
void Delay100us(u16);
void delay_ms(unsigned char);
void UARTTxData(u8);
void TranHall();
void TranAxis();
void XArrayAvg();
void XArrayPut();
void XArraySort();
void AxisCal();

void main()
{	
	_TX=1; _TXC=0;  //_TX����X�Ҧ�(��XHi)		
    _wdtc = 0xab;   //�����ݪ���
	Head = 3;
	HallHead = 2;
	//ledc=0;
	_wdtc = 0xab; 
	AD10ms=1; Whell=0; Whell100ms=50;
	TM_Set();
	Interrupt_Set();
	Moto_Set();
	AD_Set();
	_emi=1;								//�Ұʤ��_
	Moto_C(107);
	auto1=1;
	while(1)
	{
		AxisCal();
		TranAxis();
		TranHall();
	/*	if(auto1==0){
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
		}*/
		
	}
}

void TM_Set(){
	_tm4c0=0b00100000;
	_tm4c1=0b11000001;
	_tm4al=5000%256; _tm4ah=5000/256;
	_tm0c0=0b00010000;	//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;	//T/C, TM0A Match Clear
	_tm2c0=0; _tm2c1=0b00110001;	//STM:���k�X��X�Ҧ�,CCRA�k�X�M��
	_mf4e=1; _t4ae=1;
	_t4on=1;
	SEC=0; R1sec=100; AD10ms=1; Hall200ms=20;
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
	_adcr1=0b01100110;							//A/D Clock=fSYS/64,VREFS=0
	_pas0=0b00110000;							//�]�wPA1��AN1 A/D�q�D
	_pas3=0b00000011;							//�]�wPA6��AN6 A/D�q�D
	//_ade=1;									//�Ұ�ADC���_�P���_�`�}��
}

DEFINE_ISR(button_up,0x04){		//INT0 PA3���_�{��
	HallData++;
	_int0f = 0;	
}


DEFINE_ISR(Button_Down,0x08){	//INT1 PA4���_�{��
	led2=1;
	_int1f = 0;
}

DEFINE_ISR(ISR_STM,0x38){		//�ɶ����_�{��
	if(--AD10ms==0){
		AD10ms=1;
		_start=1; _start=0;						//�_�lADC�ഫ
		GCC_NOP();
		AxisXH = _adrh;
		AxisXL = _adrl;
	}
	/*if(--Hall200ms==0){
		HallData = HallCount;
		//HallCount = 0;
		Hall200ms=20;
	}*/
	/*if(--R1sec==0){	
		R1sec=100;
		led=1;

		if(++SEC==5)
		{
			SEC=0;
			led=0;
			
		}
	}*/
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

void TranAxis(void)
{
	//AXSUM = AxisX + Head;
	//AXCRC = ~AXSUM;
	//AXCRC++;
	Axcount++;
	AXCRC = Head+AxisXH;
	UARTTxData(Head);
	UARTTxData(AxisXH);
	UARTTxData(AxisXL);
	UARTTxData(Axcount);
	//UARTTxData(Head);
	UARTTxData(AXCRC);
}

void TranHall(void)
{
	u8 HalldataH,HalldataL;
	HalldataH = (u8)((HallData>>8) & 0xff);
	HalldataL = (u8)(HallData & 0xff);
	//HallSUM = HallData + HallHead;
	//HallCRC = ~HallSUM + Head;   ///���ۧ���Ƽƭ�
	//HallCRC++;
	Hacount++;
	HallCRC = HallHead+HalldataH;
	UARTTxData(HallHead);
	UARTTxData(HalldataH);
	UARTTxData(HalldataL);
	UARTTxData(Hacount);
	UARTTxData(HallCRC);
	//UARTTxData(HallCRC);
}

void XArrayAvg(){
 u16 sum=0;
 for(i=0;i<5;i++){
  sum+=XArr[i];
 }
 XArrAvg=sum/5;
}

void XArrayPut(){
 for(i=5;i>0;i--){
  XArr[i]=XArr[i-1];
 }
 XArr[0]=AxisX;
}

void XArraySort(){
	int j;
 for(i=0;i<5;i++){
  XArrSort[i]=XArr[i];
 }
 for (i=0;i<5;i++) {
     for (j =0;j<5;j++) {
        if (XArrSort[j+1] < XArrSort[j]) {
          tempx = XArrSort[j];
          XArrSort[j]=XArrSort[j+1];
          XArrSort[j+1] =tempx;
        }
     }
   }
}

void AxisCal(){
	AxisX = (u16)(AxisXH << 8);
	AxisX += AxisXL;
}