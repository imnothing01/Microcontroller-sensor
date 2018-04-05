#IFNDEF  LCD_RS
#DEFINE  LCD_RS               PIN_E0
#ENDIF

#IFNDEF  LCD_RW
#DEFINE  LCD_RW               PIN_E1
#ENDIF

#IFNDEF  LCD_E
#DEFINE  LCD_E                PIN_E2
#ENDIF

#IFNDEF  OUTPUT_LCD
#DEFINE  OUTPUT_LCD        OUTPUT_D
#ENDIF

#DEFINE     FUNCTION_SET            0X38  //GIAO TIEP 8 BIT, 2 HANG
#DEFINE     DISPLAY_CONTROL         0X0F
#DEFINE     CLEAR_DISPLAY           0X01
#DEFINE     ENTRY_MODE              0X06
#DEFINE     SHIFT_LEFT              0X18
#DEFINE     SHIFT_RIGHT             0X1C
#DEFINE     ADDR_LINE1              0X80
#DEFINE     ADDR_LINE2              0XC0
UNSIGNED int16  ng3, tr3, ch3, dv3, tr, ch, dv, d,VT,time,a,i;
void LCD_COMMAND(UNSIGNED CHAR MDK)    //RS=0
{
      OUTPUT_LOW(LCD_RS);        OUTPUT_LCD(MDK);
      OUTPUT_HIGH(LCD_E);        DELAY_US(20);
      OUTPUT_LOW(LCD_E);         DELAY_US(20);
}
void LCD_DATA(UNSIGNED CHAR MHT)       //RS=1
{
      OUTPUT_HIGH(LCD_RS);       OUTPUT_LCD(MHT); 
      OUTPUT_HIGH(LCD_E);        DELAY_US(20);
      OUTPUT_LOW(LCD_E);         DELAY_US(20);
}
VOID LCD_SETUP()
{
      OUTPUT_LOW(LCD_E);
      OUTPUT_LOW(LCD_RS);
      OUTPUT_LOW(LCD_RW);
      LCD_COMMAND(FUNCTION_SET);          DELAY_MS(1);        
      LCD_COMMAND(DISPLAY_CONTROL);
      LCD_COMMAND(CLEAR_DISPLAY);         DELAY_MS(2);
      LCD_COMMAND(ENTRY_MODE);
}
void giaima_lcd()
{
      dv3 = VT%10 + 0X30;
      ch3 = VT/10%10 + 0X30;
      tr3 = VT/100%10 + 0X30;
      ng3 = VT/1000%10 + 0X30;
      if (ng3 == 0x30)
      {     ng3 =  ' ' ;
            if (tr3 == 0x30)
            {
                  tr3 = ' ';
                  if (ch3 == 0x30)
                     ch3 = ' ';
            }
      }
      dv = d%10 + 0X30;
      ch = d/10%10 + 0X30;
      tr = d/100%10 + 0X30;
      if (tr == 0x30)
      {
            tr = ' ';
            if (ch == 0x30)
               ch = ' ';
      }      
}
void ht_lcd()
{
      LCD_COMMAND(0XC0);
      LCD_DATA("V:    ml d:   cm");
      LCD_COMMAND(0XC2);
      LCD_DATA(ng3);
      LCD_DATA(tr3);
      LCD_DATA(ch3);
      LCD_DATA(dv3);
      LCD_COMMAND(0XCB);
      LCD_DATA(tr);
      LCD_DATA(ch);
      LCD_DATA(dv);
}
void HT_LCD_STOP()
{
   LCD_COMMAND(0X80);
   LCD_DATA(" DUNG HOAT DONG ");
   giaima_lcd();
   ht_lcd();
}

void HT_LCD_START()
{
    LCD_COMMAND(0X80);
    LCD_DATA("  HT HOAT DONG  ");
    giaima_lcd();
    ht_lcd();
}

