; Generated by holtek-gcc v3.18, Wed Oct 31 19:08:40 2018
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 48
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.18" "build 20130711"
; Rebuild 521

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [48]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___intc0 equ [48]
___mfi0 equ [52]
public _ISR_tmr0_tmr2
#pragma debug scope 2 1
#line 8 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
rombank 0 @ISR_tmr0_tmr2_code
@ISR_tmr0_tmr2_code .section at 20 'code'
	mov r1,a
	mov a,bp
	clr bp
	jmp _ISR_tmr0_tmr2
ROMBANK 0 _ISR_tmr0_tmr2
#pragma debug scope 1 1
@dummy20 proc
	call _ISR_tmr0_tmr2
@dummy20 endp
#pragma debug scope 3 1
_ISR_tmr0_tmr2 .section 'code'
_ISR_tmr0_tmr2 proc
	mov r2,a
	mov a, status
	mov r3,a
#line 12 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
	clr [48].0
#line 13 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
	clr [52].5
#line 14 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
	mov a,1
	mov _flag[0],a
	clr _flag[1]
#line 15 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
	set [48].0
	mov a,r2
	mov bp,a
	mov a,r3
	mov status,a
	mov a,r1
	reti
_ISR_tmr0_tmr2 endp

#line 15 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Interrupt.h"
#pragma debug scope 1 1
___wdtc equ [62]
@crom	.section 'crom'
_LC0:
	db 038h,035h,00h
public _main
#pragma debug scope 4 1
#line 19 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
IFDEF WITH_DEFAULT_STARTUP
extern _main_initial0:near
extern _main_startup:near
ENDIF

ROMBANK 0 @start
@start .section com_l 'code'
_main_startup1:
@start .section com_e 'code'
	mov a,bank _main
	mov bp,a
	jmp _main

_main .section 'code'
_main proc
#line 21 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
	mov a,171
	mov [62],a
#line 23 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
	fcall _UART_INIT
_L3:
#line 25 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
	mov a,low offset _LC0
	mov _Send_2[0],a
	mov a,high offset _LC0
	mov _Send_2[1],a
	fcall _Send
	jmp _L3
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 25 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
#pragma debug scope 1 1
public _delay1s
#pragma debug scope 5 1
#line 38 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
_delay1s .section 'code'
_delay1s proc
	ret
_delay1s endp
#line 38 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
#pragma debug scope 1 1
#pragma debug struct_begin 42 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int0e" ;1,1
#pragma debug field 21 8 0 1 "__int1e" ;2,1
#pragma debug field 21 8 0 1 "__cp0e" ;3,1
#pragma debug field 21 8 0 1 "__int0f" ;4,1
#pragma debug field 21 8 0 1 "__int1f" ;5,1
#pragma debug field 21 8 0 1 "__cp0f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___intc0 "__intc0" 1
#pragma debug struct_begin 44 "__mfi0_bits"
#pragma debug field 21 8 0 1 "__t0pe" ;0,1
#pragma debug field 21 8 0 1 "__t0ae" ;1,1
#pragma debug field 21 8 0 1 "__t2pe" ;2,1
#pragma debug field 21 8 0 1 "__t2ae" ;3,1
#pragma debug field 21 8 0 1 "__t0pf" ;4,1
#pragma debug field 21 8 0 1 "__t0af" ;5,1
#pragma debug field 21 8 0 1 "__t2pf" ;6,1
#pragma debug field 21 8 0 1 "__t2af" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___mfi0 "__mfi0" 1
#pragma debug struct_begin 46 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___wdtc "__wdtc" 1

; output external variables
extern _flag:byte
extern r1:byte
extern r2:byte
extern r3:byte
#line 19 "C:\Users\IIIT\Documents\HTK_Project\Bluetooth\Bluetooth.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1

extern _UART_INIT:near
extern _Send_2:byte
extern _Send:near

; 
; Generated by holtek-gcc v3.18, Wed Oct 31 19:08:40 2018
; Rebuild 521
; end of file
