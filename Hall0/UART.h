#ifndef _UART_H_
#define _UART_H_
 
//�w�qTXD RXD
#define TXD _pc2
#define RXD _pc3
//�w�q�����r�����
#define num 16
 
void UART_INIT(void);
void Waitflag();
void WByte(unsigned char input);
unsigned char RByte(void);
void Send(char *buf);//�o�e
void Send_num(unsigned int s,char *buf);//�o�es�Ӧr��
void Send_Array(void);//�o�e�w�İ�
void Receive(void);//�enum�r����w�İ�
void Receive_num(unsigned int s,char *buf);//����s�Ӧr��
void Receive_if(char *buf);//�H'\n'���������󱵦�
 
#endif