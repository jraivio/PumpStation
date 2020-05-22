void u8x8Display(String TitleStr, String row1Str, String row2Str, String row3Str) {
    if (debugging) { Serial.println("OLED func... ");}
    //u8x8.begin(); // Init Oled
    u8x8.clearDisplay();
    //u8x8_SetFlipMode(1,1);
    char row0[32]; char row1[32]; char row2[32]; char row3[32];
    memset(row0, 0, 32); TitleStr.toCharArray(row0, 32);
    memset(row1, 0, 32); row1Str.toCharArray(row1, 32);
    memset(row2, 0, 32); row2Str.toCharArray(row2, 32);    
    memset(row3, 0, 32); row3Str.toCharArray(row3, 32);  
    u8x8.setFont(u8x8_font_pressstart2p_r);
    u8x8.drawString(1,0,row0);
    u8x8.drawString(1,1,"------------------");
    u8x8.drawString(2,2,row1); u8x8.drawString(7,2," C");
    u8x8.drawString(2,3,row2); u8x8.drawString(7,3," %");
    u8x8.drawString(2,4,row3); u8x8.drawString(7,4," V");
    //return;
}

void u8x8Display_common(String TitleStr, String row1Str, String row2Str, String row3Str, String row4Str, String row5Str, String row6Str) {
    //u8x8.begin(); // Init Oled
    u8x8.clearDisplay();
    //u8x8_SetFlipMode(1,1);
    char row0[32]; char row1[32]; char row2[32]; char row3[32]; char row4[32]; char row5[32]; char row6[32];
    memset(row0, 0, 32); TitleStr.toCharArray(row0, 32);
    memset(row1, 0, 32); row1Str.toCharArray(row1, 32);
    memset(row2, 0, 32); row2Str.toCharArray(row2, 32);    
    memset(row3, 0, 32); row3Str.toCharArray(row3, 32); 
    memset(row4, 0, 32); row4Str.toCharArray(row4, 32); 
    memset(row5, 0, 32); row5Str.toCharArray(row5, 32); 
    memset(row6, 0, 32); row6Str.toCharArray(row6, 32); 
    u8x8.setFont(u8x8_font_pressstart2p_r);
    u8x8.drawString(1,0,row0); u8x8.drawString(1,1,row1); u8x8.drawString(1,2,row2); u8x8.drawString(1,3,row3); u8x8.drawString(1,4,row4); u8x8.drawString(1,5,row5); u8x8.drawString(1,6,row6); 
    //return;
}

