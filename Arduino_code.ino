
#include <Keypad.h>
#include<LiquidCrystal.h>


float vout,p,Q,V;
const float m0=-67.497798082503;
const float m1=0.0237200392​;
const float m2=0.617981660;
const float m3=29.6510904;
const float m4=2.23838912;
const float D=6.0E-3;
const float d=2.0E-3;
const float rho=1.225;
const float A=2.83E-5;
const float rate = 0.01 ;
const int trig=177;
const byte ROWS = 4; 
const byte COLS = 4; 
float B=D/d;
int Gender=2;
int SMOKE=2;

char hexaKeys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'R','0','=','+'}};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9}; 
LiquidCrystal lcd(13,12,11,10,1,0);
Keypad k= Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup(){
  lcd.begin(16,2);
  pinMode(A0,INPUT); 
}

char wait(){
  char buttonState = 0;
  while(1){
    buttonState = k.getKey();;
    if ((buttonState) != 0) {
      return buttonState;
    }
  }
}

int getage(){
  char bs;
  int i,x=0,a=0;
    for (i=0;i<3;i=i+1){
      bs=0;
      while(1){
         bs=k.getKey();
         if(bs != 0){
            break;
         }
      } 
      x=bs-'0';
      a=a+x*pow(10,2-i);
    }
    return a;
 
}
void loop(){
 
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Enter Gender : ");
    lcd.setCursor(0,1);
    lcd.print("MALE:1  FEMALE:2");
    //delay(2000);
    char g=wait();
    if(int(g)!=0){
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.print(g);
      delay(2000);
    }
    if(g=='1'){
      Gender=1;
    }
    /*lcd.clear();
      lcd.setCursor(1,1);
      lcd.print(Gender);
      delay(1000);
    //delay(1000);*/
    
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Enter age : "); 
    //lcd.setCursor(0,1);
    //lcd.print("With 3 digits");  
    //get age
    int age=getage();
    if(int(age)!=0){
      lcd.clear();
      lcd.setCursor(6,1);
      lcd.print(age);
      delay(2000);
    }
   //delay(1000);

    lcd.setCursor(0,0);
    lcd.print("Smoking status : ");
    lcd.setCursor(0,1);
    lcd.print("Ex:1 NO:2 YES:3");
    char smoke=wait();
    //delay(2000);
    if(int(smoke)!=0){
      lcd.clear();
      lcd.setCursor(6,1);
      lcd.print(smoke);
      delay(2000);
    }
    lcd.clear();
    if (smoke=='1'){
      SMOKE=1;
    }
    if(smoke=='3'){
      SMOKE=3;
    }
   /* lcd.clear();
      lcd.setCursor(1,1);
      lcd.print(SMOKE);
      delay(1000);*/

    

    lcd.setCursor(0,0);
    lcd.print("Now please blow ");
    lcd.setCursor(0,1);
    lcd.print("air in the pipe ");
    delay(2000);
    lcd.clear();


    vout=(analogRead(A0)*(255/1024));
    p=1000*(( vout/5- 0.04))/ 0.018;
    Q=((A*sqrt(2*p/rho))  /  sqrt(1-pow(B,4)))*1.0E6;
    V=0;
    while(Q>trig){
      V=V+Q*rate; 
      vout=(analogRead(A0)*(255/1024));
      p=1000*(( vout/5- 0.04))/ 0.018;
      Q=((A*sqrt(2*p/rho))  /  sqrt(1-pow(B,4)))*1.0E6;
      delay(rate*1000);
    }


    //V=2315;
    float per= m0 + m1*V + m2*age + Gender*m3 + SMOKE*m4;
    lcd.setCursor(0,0);
    lcd.print("Lung Healthyness:");
    lcd.setCursor(3,1);
    lcd.print(per);
    lcd.setCursor(9,1);
    lcd.print("%");
    delay(2000);
    

    
}
