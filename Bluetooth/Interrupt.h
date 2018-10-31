#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#endif
 
#define ISR_TMR0//�w�qTM0 TM2
 
void __attribute((interrupt(0x14))) ISR_tmr0_tmr2(void)//TM0�MTM2���_
{
	//�w�qISR_TMR0
	#ifdef ISR_TMR0
	extern volatile unsigned int flag;
	_emi = 0;
	_t0af = 0;
	flag = 1;
	_emi = 1;
	//�w�qISR_TMR2
	#else
	_emi = 0;
	_t2af = 0;
	_emi = 1;
	#endif
	
}
