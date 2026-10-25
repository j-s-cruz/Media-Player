/*----------------------------------------------------------------------------
 * Name:    usbmain.c
 * Purpose: USB Audio Class Demo
 * Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"

/*From LCD_Blinky Project*/
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#define __FI        1                      /* Font index 16x24               */
/*
extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned char Bg_16bpp_t[];
extern unsigned char Bg_16bpp_l[];
extern unsigned char Bg_16bpp_r[];
extern unsigned char Bg_16bpp_b[];
extern unsigned char ARM_Ani_16bpp[];
*/




/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
		int KBD_but, disp_val = 0;
	  LED_Init ();
		GLCD_Init();
		KBD_Init();	
	
		GLCD_Clear(White);
	/*From LCD_Blinky Project*/
  for (;;) {                            /* Loop forever                       */
  	switch(disp_val){
			case 0:
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "Jameson Stanley Cruz");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_DisplayString(7, 0, __FI, "Game                ");
			break;
			case 1:
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "Jameson Stanley Cruz");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_DisplayString(7, 0, __FI, "Game                ");
			break;
			case 2:
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "Jameson Stanley Cruz");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(7, 0, __FI, "Game                ");
			break;
			case 3:
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "Jameson Stanley Cruz");
				GLCD_DisplayString(2, 0, __FI, "    Media Center    ");
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(5, 0, __FI, "Photo Gallery       ");
				GLCD_DisplayString(6, 0, __FI, "MP3 Player          ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(7, 0, __FI, "Game                ");
			break;
			case 6:
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
				GLCD_DisplayString(1, 0, __FI, "       Game         ");
			break;
		}
		KBD_but = get_button ();
			switch(KBD_but){
			case KBD_SELECT:
				GLCD_Clear(White);
				switch (disp_val){
					case 1:
						LED_On(0);
						photos();
					break;
					case 2:
						LED_On(1);
						MP3();
					break;
					case 3:
						LED_On(2);
						game();
					break;
				}
			break;
			case KBD_UP:
				if(disp_val > 1) {
					disp_val--;
				} else{
					disp_val = 3;
				}
			break;
			case KBD_DOWN:
				if(disp_val < 3) {
					disp_val++;
				} else {
					disp_val = 1;
				}
			break;
		}
  }
  /********* The main Function is an endless loop ***********/ 
  while( 1 ); 
}

/******************************************************************************
**                            End Of File
******************************************************************************/
