
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 130 // 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino

const int XP=7,XM=A1,YP=A2,YM=6; //2ButtonWidthx320 ID=0x9325
const int TS_LEFT=934,TS_RT=137,TS_TOP=125,TS_BOT=917;

//const int TS_LEFT=934,TS_RT=137,TS_TOP=125,TS_BOT=917;


bool changed_txt_Frequency = false;
bool b_Mhz = false;
String txt_Frequency = "7100";
char disp_Freq[9] = "";
int buttondelay = 200;
int MarginLeftOutput = 0;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int digit1 = 0;
int digit2;
int digit3;
int digit4;
int digit5;
int digit6;
int digit7;
int digit8;
int digit9;
int digit0;
int resulttextsize = 4;
Adafruit_GFX_Button one_btn, two_btn, three_btn, four_btn, five_btn, six_btn, seven_btn, eight_btn, nine_btn, del_btn, send_btn, zero_btn;
int Freq_Backgnd;
int Freq_Color;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_RT, TS_LEFT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

    int ButtonWidth = 72;
    int ButtonHeight = 50;
    int MarginLeft = ButtonWidth/2;
    int ButtonCol2 = MarginLeft + ButtonWidth + 5;
    int ButtonCol3 = ButtonCol2 + ButtonWidth + 5;
    int ButtonCol4 = ButtonCol3 + ButtonWidth + 5;
    

    int ButtonRow1 = 104;
    int ButtonRow2 = ButtonRow1 + ButtonHeight;
    int ButtonRow3 = ButtonRow2+ ButtonHeight;
    int ButtonRow4 = ButtonRow3+ ButtonHeight;
void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);            //LANDSCAPE
    tft.fillScreen(BLACK);

//    Serial.println('width' + tft.width());
//    Serial.println('height' + tft.height());



    Freq_Backgnd = BLUE;
    Freq_Color = YELLOW;

    one_btn.initButton(&tft,  MarginLeft, ButtonRow1, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "1", 2);
    two_btn.initButton(&tft, ButtonCol2, ButtonRow1, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "2", 2);
    three_btn.initButton(&tft, ButtonCol3, ButtonRow1, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "3", 2);
    four_btn.initButton(&tft,  ButtonCol4, ButtonRow1, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "4", 2);
    
    five_btn.initButton(&tft, MarginLeft, ButtonRow2, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "5", 2);
    six_btn.initButton(&tft, ButtonCol2, ButtonRow2, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "6", 2);
    seven_btn.initButton(&tft,  ButtonCol3, ButtonRow2, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "7", 2);
    eight_btn.initButton(&tft, ButtonCol4, ButtonRow2, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "8", 2);
    
    nine_btn.initButton(&tft, MarginLeft, ButtonRow3, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "9", 2);
    zero_btn.initButton(&tft,  ButtonCol2, ButtonRow3, ButtonWidth, ButtonHeight, WHITE, CYAN, BLACK, "0", 2);
    del_btn.initButton(&tft, ButtonCol3, ButtonRow3, ButtonWidth, ButtonHeight, WHITE, RED, WHITE, "DEL", 2);
    send_btn.initButton(&tft, ButtonCol4, ButtonRow3, ButtonWidth, ButtonHeight, WHITE, GREEN, BLACK, "ENT", 2);

  // 'display' buttons
    deleteall();
    add_keystroke(7);         
    add_keystroke(1);         
    add_keystroke(0);         
    add_keystroke(0);         
    add_keystroke(0);         
    add_keystroke(0);         
    
    drawchar();

    one_btn.drawButton(false);
    two_btn.drawButton(false);
    three_btn.drawButton(false);
    four_btn.drawButton(false);
    five_btn.drawButton(false);
    six_btn.drawButton(false);
    seven_btn.drawButton(false);
    eight_btn.drawButton(false);
    nine_btn.drawButton(false);
    zero_btn.drawButton(false);
    send_btn.drawButton(false);
    del_btn.drawButton(false);


   // tft.fillRect(ButtonWidth, 80, 160, 80, RED);
   int digitspace = 24; //22
   digit0=0;
   digit1 = digit0 + digitspace;
   digit2 = digit1 + digitspace;
   digit3 = digit2 + digitspace;
digit4 = digit3 + digitspace;
digit5 = digit4 + digitspace;
digit6 = digit5 + digitspace;
digit7 = digit6 + digitspace;
digit8 = digit7 + digitspace;
digit9 = digit8 + digitspace;

drawchar();

}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    one_btn.press(down && one_btn.contains(pixel_x, pixel_y));
    two_btn.press(down && two_btn.contains(pixel_x, pixel_y));
    three_btn.press(down && three_btn.contains(pixel_x, pixel_y));
    four_btn.press(down && four_btn.contains(pixel_x, pixel_y));
    five_btn.press(down && five_btn.contains(pixel_x, pixel_y));
    six_btn.press(down && six_btn.contains(pixel_x, pixel_y));
    seven_btn.press(down && seven_btn.contains(pixel_x, pixel_y));
    eight_btn.press(down && eight_btn.contains(pixel_x, pixel_y));
    nine_btn.press(down && nine_btn.contains(pixel_x, pixel_y));
    zero_btn.press(down && zero_btn.contains(pixel_x, pixel_y));
    send_btn.press(down && send_btn.contains(pixel_x, pixel_y));
    del_btn.press(down && del_btn.contains(pixel_x, pixel_y));
    String save_txt_Frequency = txt_Frequency;

    if (one_btn.justReleased()){
        one_btn.drawButton();
        add_keystroke(1);         
        delay(buttondelay);
    }
    
    if (two_btn.justReleased()){
        two_btn.drawButton();
        add_keystroke(2);         
         delay(buttondelay);
   }
    
    if (three_btn.justReleased()){
        three_btn.drawButton();
        add_keystroke(3);         
        delay(buttondelay);
    }

    if (four_btn.justReleased()){
        four_btn.drawButton();
        add_keystroke(4);         
        delay(buttondelay);
    }

    if (five_btn.justReleased()){
        five_btn.drawButton();
        add_keystroke(5);         
        delay(buttondelay);
    }
    if (six_btn.justReleased()){
        six_btn.drawButton();
        add_keystroke(6);         
        delay(buttondelay);
    }
    if (seven_btn.justReleased()){
        seven_btn.drawButton();
        add_keystroke(7);         
        delay(buttondelay);
    }
    if (eight_btn.justReleased()){
        eight_btn.drawButton();
        add_keystroke(8);         
        delay(buttondelay);
    }
    if (nine_btn.justReleased()){
        nine_btn.drawButton();
        add_keystroke(9);         
        delay(buttondelay);
    }
    if (zero_btn.justReleased()){
        zero_btn.drawButton();
          add_keystroke(0);
          delay(buttondelay);
    }

    if (send_btn.justReleased()){
        send_btn.drawButton();
        sendToOscillator();
        delay(buttondelay);    
    }

    if (del_btn.justReleased()){
        del_keystroke();
        del_btn.drawButton();
        delay(buttondelay);
    }


    if (changed_txt_Frequency){
     drawchar();
     changed_txt_Frequency = false;
               }

             
    if (one_btn.justPressed()) {
        one_btn.drawButton(true);
    }
    if (two_btn.justPressed()) {
        two_btn.drawButton(true);
    }
    if (three_btn.justPressed()) {
        three_btn.drawButton(true);
    }
    if (four_btn.justPressed()) {
        four_btn.drawButton(true);
    }
    if (five_btn.justPressed()) {
        five_btn.drawButton(true);
    }
    if (six_btn.justPressed()) {
        six_btn.drawButton(true);
    }
    if (seven_btn.justPressed()) {
        seven_btn.drawButton(true);
    }
    if (eight_btn.justPressed()) {
        eight_btn.drawButton(true);
    }
    if (nine_btn.justPressed()) {
        nine_btn.drawButton(true);
    }
    if (zero_btn.justPressed()) {
        zero_btn.drawButton(true);
    }
    if (send_btn.justPressed()) {
        send_btn.drawButton(true);
    }
    if (del_btn.justPressed()) {
        del_btn.drawButton(true);
    }
}

void drawchar(){
            tft.drawChar(digit0, MarginLeftOutput, disp_Freq[0], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit1,MarginLeftOutput,  disp_Freq[1], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit2,MarginLeftOutput, disp_Freq[2], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit3, MarginLeftOutput, disp_Freq[3], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit4, MarginLeftOutput,  disp_Freq[4], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit5, MarginLeftOutput,  disp_Freq[5], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit6,  MarginLeftOutput,disp_Freq[6], Freq_Color, Freq_Backgnd, resulttextsize);
          tft.drawChar(digit7, MarginLeftOutput, disp_Freq[7], Freq_Color, RED, resulttextsize);
          tft.drawChar(digit8, MarginLeftOutput, disp_Freq[8], Freq_Color, RED, resulttextsize);

}

void add_keystroke(int parKeyCharCode){
    disp_Freq[0] = disp_Freq[1];
    disp_Freq[1] = disp_Freq[2];
    disp_Freq[2] = disp_Freq[3];
    disp_Freq[3] = disp_Freq[4];
    disp_Freq[4] = disp_Freq[5];
    disp_Freq[5] = disp_Freq[6];
    disp_Freq[6] = disp_Freq[7];
    disp_Freq[7] = disp_Freq[8];
    disp_Freq[8] = (48 + parKeyCharCode);
    changed_txt_Frequency= true;

}

void del_keystroke(){
    disp_Freq[8] = disp_Freq[7];
    disp_Freq[7] = disp_Freq[6];
    disp_Freq[6] = disp_Freq[5];
    disp_Freq[5] = disp_Freq[4];
    disp_Freq[4] = disp_Freq[3];
    disp_Freq[3] = disp_Freq[2];
    disp_Freq[2] = disp_Freq[1];
    disp_Freq[1] = disp_Freq[0];
    disp_Freq[0] = 95;
    changed_txt_Frequency= true;

}

void deleteall(){
    disp_Freq[0] = 95;
    disp_Freq[1] = 95;
    disp_Freq[2] = 95;
    disp_Freq[3] = 95;
    disp_Freq[4] = 95;
    disp_Freq[5] = 95;
    disp_Freq[6] = 95;
    disp_Freq[7] = 95;
    disp_Freq[8] = 95;
    changed_txt_Frequency= true;
      
}

void sendToOscillator(){

  txt_Frequency="";  //clear
  for (int i=0; i<9; i++) {
    if (disp_Freq[i] !=95){
      txt_Frequency += (disp_Freq[i]-48);
    }
   }

   
    unsigned long nOscill = strtol(disp_Freq,NULL,10);
    nOscill = nOscill *1000;

      Serial.println(txt_Frequency);
      
}
