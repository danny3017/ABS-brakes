#include <HT66F70A.h>

#define	DATA_BUS _pg
#define RS  _ph0
#define RW  _ph1
#define EN  _ph2

#define SDO _pa5	//�H���s�����
#define SDA _pa6	//�H���s�����
#define SCK _pa7
#define CS  _pb5

#define SDOC _pac5	//�H���s�����
#define SDAC _pac6
#define SCKC _pac7
#define CSC  _pbc5

#define SDOPU _papu5	//���s�����
#define SDAPU _papu6
#define SCKPU _papu7
#define CSPU  _pbpu5

#define PAS2 _pas2	//pas 5 SDO
#define PAS3 _pas3	//pas 6 7 SDI SCL
#define PBS2 _pbs2	//pbs5 scs

void Delay100us(short);	
void _SPI_CS(unsigned short);
void _SPI_SCL(unsigned short);
unsigned char ADXL345_SPI_Read(unsigned char);
void delay_ms(unsigned char);
void ADXL345_SPI_Write(unsigned char , unsigned char);
void LCD_Cmd(unsigned char data);
void LCD_Senddata(unsigned char data);
void LCD_Reset(void);
void PinSet(void);
void DataFormat(void);
void PrintLCD(unsigned char);
volatile unsigned char datax=0;

void main()
{
	PinSet();	//�}��]�w
	//DataFormat();	//3�b��Ʈ榡�]�w
	
	LCD_Reset();		//LCD���m
	delay_ms(250);		//����20�@�� 				
	LCD_Cmd(0xc0);  	//LCD�Ĥ@�����
	delay_ms(250);            
	
	while(1)
	{
		datax = ADXL345_SPI_Read(0x00);
		Delay100us(100);
	
		LCD_Cmd(0x80);  //�q�Ĥ@���0��m�}�l���   C0���ĤG��
		delay_ms(150);
	 	PrintLCD(datax);

	  		
	  	delay_ms(1250);
	  		
	  	LCD_Cmd(0x85);	//�q�Ĥ@���5��m�}�l���
	 	delay_ms(150);
	  	PrintLCD(datax);
		delay_ms(50);	  		
	}
	
}

//////////////////////////////
///�}��]�w�[��
//////////////////////////////
void PinSet(void)
{
	_wdtc = 0xa8;//�����ݪ���
	_cp0c = 0x00;	//���������\������
	_cp1c = 0x00;
	_scomen = 0;
	_smod = 0xe0;//4MHz
	_sdis0=0;
	_sdis1=0;
	_simen=1;  
	_simc0=0x42;
	_simc2=0x24;
	
	//PAS2=0x10;  //�]�w�U�Ӹ}��\��
	//PAS3=0x22;  
	//PBS2=0x10;

	
	_ifs4=0;
	
	_pac5=0; 	_pac6=1; 	_pac7=0;		CSC=0;//�]�wI/O
	_phc0 = 0; _phc1 = 0; _phc2 = 0; //�]�mPH0�BPH1�BPH2����X   
	SDAPU=1;	SDOPU=1;	SCKPU=1;	CSPU=1;		SCK=0;		CS=1;		_pgc = 0x00;   
}


//////////////////////////////
///SPIŪ���[��
//////////////////////////////
unsigned char ADXL345_SPI_Read(unsigned char Address)
{
  unsigned char ReadData=0;
  unsigned char tempSDO;
  char i;
 
  _SPI_CS(0);
  SDO = 0;
  for(i = 7; i >= 0; i-- )
  {
    // F-Edge
    _SPI_SCL(1);
    //SDO = 0x0 & ((0x0 | Address) >> i);
    _SPI_SCL(0);
  }
 
  //===========================
  _SPI_SCL(1);
  //===========================
 
  for(i = 7; i >= 0; i-- )
  {
    // R-Edge
    _SPI_SCL(0);
    _SPI_SCL(1);
    tempSDO = SDA; // Read bit
 
    ReadData |= tempSDO << i;
  }
 
  _SPI_CS(1);
  return ReadData & 0xFF;
}

//////////////////////////////
///��Ʈ榡�[��
//////////////////////////////
void DataFormat(void)
{
	ADXL345_SPI_Write(0x31, 0x0B); //�]�w���q�d��&��Ʈ榡
	ADXL345_SPI_Write(0x2D, 0x08); //�}�l���q
}

//////////////////////////////
///LCD��ܲ[��
//////////////////////////////
void PrintLCD(unsigned char data)
{
	LCD_Senddata((data/1000)%10+0x30);  //�d��ʦ�.....
	LCD_Senddata((data/100)%10+0x30); 
	LCD_Senddata((data/10)%10+0x30);
	LCD_Senddata((data/1)%10+0x30);
}

//////////////////////////////
///Delay100us�[��
//////////////////////////////
void Delay100us(short del)						//����del*200���O�g��
{	short i,j;									//@fSYS=8MH,����del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}	

//////////////////////////////
///CS�}�q��[��
//////////////////////////////
void _SPI_CS(unsigned short isSelect)
{
    CS=isSelect;
    _nop();
}

//////////////////////////////
///SCL�}�q��[��
//////////////////////////////
void _SPI_SCL(unsigned short bLevel)
{
    SCK=bLevel;
    _nop();
}

//////////////////////////////
///SPI�g�J�[��
//////////////////////////////
void ADXL345_SPI_Write(unsigned char Address, unsigned char WriteData)
{
  char i;
 
  _SPI_CS(0);
 
  for(i=7; i >= 0; i--)
  {
    // F-Edge
    _SPI_SCL(1);
    SDO = 0x1 & ((0x7F & Address) >> i);
    _SPI_SCL(0);
  }
 
  for(i=7; i >= 0; i--)
  {
    // F-Edge
    _SPI_SCL(1);
    SDO = 0x1 & ((WriteData) >> i);
    _SPI_SCL(0);
  }
 
  _SPI_CS(1);
}

//---�ǰe�R�O��LCD
void LCD_Cmd(unsigned char data)
{
    DATA_BUS = data;  //�R�O�e��BUS
    RS=0; RW=0; EN=1; //�R�O��LCD�� 
    delay_ms(1);
    EN=0;           //�T��LCD
}
//---�ǰe��ƨ�LCD 
void LCD_Senddata(unsigned char data)
{
    DATA_BUS = data;  //��ưe��BUS
    RS=1; RW=0; EN=1; //��ƨ�LCD��
    delay_ms(1);
    EN=0;           //�T��LCD
}
//---LCD���ҩl�{��  
void LCD_Reset(void)
{
    LCD_Cmd(0b00111000);//8bit�ǿ�,���2��,5*7�r��
                        //bit4:DL=1,8bit�ǿ�,
                        //bit3:N=1,���2��
                        //bit2:F=0,5*7�r��                        
    LCD_Cmd(0b00001100);//��ܹ�ON,����ܴ��,��Ф��{�{
                        //bit2:D=1,��ܹ�ON
                        //bit1:C=0,����ܴ��                      
    LCD_Cmd(0b00000110);//��ܧ���Хk��,��в���T�� 
                        //bit1:I/D=1,��ܧ���Хk��
                        //bit0:S=0,��в���T��                                   
    LCD_Cmd(0b00000001); //�M����ܹ�
    LCD_Cmd(0b00000010); //��Ц^��� 
}

//////////////////////////////
///Delay�@��[��
//////////////////////////////
void delay_ms(unsigned char del)
{	
	unsigned char i;
	for(i=0;i<del;i++) GCC_DELAY(2000);		//���ب禡�A����2000���O�g��
}
