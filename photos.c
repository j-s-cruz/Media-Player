/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include "LPC17xx.h"                      /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "greninja.c"
#include "charizard.c"
#include "torterra.c"

#define __FI        1                      /* Font index 16x24               */

void menu_Init (void) {
		GLCD_Clear(White);
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, __FI, "   COE718 Project   ");
		GLCD_DisplayString(1, 0, __FI, "   Photo Gallery    ");
		GLCD_DisplayString(2, 0, __FI, "  Up/Down: Scroll   ");
		GLCD_DisplayString(9, 0, __FI, "  Select->Main Menu ");
}
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int photos (void) {                       /* Main Program                       */
	int KBD_but, pic = 0;
	
	unsigned char* gallery[]= {(unsigned char *)&TORTERRA_pixel_data,(unsigned char *)&CHARIZARD_pixel_data,(unsigned char *)&GRENINJA_pixel_data };

  KBD_Init ();
	LED_Init ();
  GLCD_Init();
	menu_Init();
	for (;;){
		KBD_but=get_button();
		switch(KBD_but) {
			case KBD_UP:
				pic= (pic + 1) % 3;
				menu_Init();
				GLCD_Bitmap (  100,  80, 120,  120, gallery[pic]);
				break;
			case KBD_DOWN:
				pic= (pic - 1 + 3) % 3;
				menu_Init();
				GLCD_Bitmap (  100,  80, 120,  120, gallery[pic]);
				break;
			case KBD_SELECT: 
				GLCD_Clear(White);
				LED_Off(0);
				return 0;
		}
  }
}

