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

void Master(unsigned short); 
void Delay100us(short);	
void _SPI_CS(unsigned short);
void _SPI_SCL(unsigned short);
unsigned char ADXL345_SPI_Read(unsigned char);
void LCD_Reset(void);
void delay_ms(unsigned char);
void LCD_Cmd(unsigned char);
void LCD_Senddata(unsigned char);

void main()
{
	volatile unsigned char i;
	_wdtc = 0xab;//�����ݪ���
	
	PAS2=0x10;  //�]�w�U�Ӹ}��\��
	PAS3=0x22;  
	PBS2=0x10;  
	
	_phc0 = 0; _phc1 = 0; _phc2 = 0;
	_pgc = 0x00;
	
	SDOC=0; 	SDAC=1; 	SCKC=0;  //�]�wI/O
	SDAPU=1;	SCK=0;		CSC=0;
	CS=0;
	
	_cp0c = 0x00;	//���������\������
	_cp1c = 0x00;
	
	LCD_Reset();
	delay_ms(5);
	LCD_Cmd(0x80);
	
	unsigned char datax = ADXL345_SPI_Read(0x32);
	unsigned char datay = ADXL345_SPI_Read(0x34);
	datax = ADXL345_SPI_Read(0x32);
	for(i=0;i<=16;i++) //���Logo�}�C���
	{
		LCD_Senddata(datax);
	}
}

void Master(unsigned short Data)
{	unsigned short temp=0b00000001;
	do
	{	
		SDO=Data & temp;						//Set SDO State
		SCK=1; Delay100us(3); SCK=0; //Generate SCK Clock
		temp<<=1;									   //Next Bit
	} while (temp!=0);
}

void Delay100us(short del)						//����del*200���O�g��
{	short i,j;									//@fSYS=8MH,����del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}	

void _SPI_CS(unsigned short isSelect)
{
    CS=isSelect;
    GCC_NOP();
}

void _SPI_SCL(unsigned short bLevel)
{
    SCK=bLevel;
    GCC_NOP();
}

unsigned char ADXL345_SPI_Read(unsigned char Address)
{
  unsigned char ReadData=0;
  unsigned char tempSDO;
  char i;
 
  _SPI_CS(0);
 
  for(i = 7; i >= 0; i-- )
  {
    // F-Edge
    _SPI_SCL(1);
    SDA = 0x1 & ((0x80 | Address) >> i);
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
    tempSDO = SDO; // Read bit
 
    ReadData |= tempSDO << i;
  }
 
  _SPI_CS(1);
  return ReadData & 0xFF;
}
//---�ǰe�R�O��LCD
void LCD_Cmd(unsigned char data)
{
    DATA_BUS = data;  //�R�O�e��BUS
    RS=0; RW=0; EN=1; //�R�O��LCD�� 
    delay_ms(1);
    EN=0;           //�T��LCD
}
void delay_ms(unsigned char del)
{	
	unsigned char i;
	for(i=0;i<del;i++) GCC_DELAY(2000);		//���ب禡�A����2000���O�g��
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
//---�ǰe��ƨ�LCD
void LCD_Senddata(unsigned char data)
{
	DATA_BUS = data; //��ưe��BUS
	RS=1; RW=0; EN=1; //��ƨ�LCD��
	delay_ms(1);
	EN=0; //�T��LCD
}