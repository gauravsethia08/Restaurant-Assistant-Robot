// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
const int rs = 37, rw =36, en = 35, d4 = 33, d5 = 32, d6 = 31, d7 = 30;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Declaring Variables
int red, green, blue;

int s0 = 12;
int s1 = 7;
int s2 = 8;
int s3 = 38;
int output = 21;

int l1=0,l2=0,l3=0;

int A[9], B[9], C[9];

int k=0, l=0, m=0, i;

int table=1;


// Reading Color
void color()
{
      //Reading Red Color
      digitalWrite(s2,LOW);
      digitalWrite(s3,LOW);
      red = pulseIn(output,LOW);
      
      //Reading Green Color
      digitalWrite(s2,HIGH);
      digitalWrite(s3,HIGH);
      green = pulseIn(output,LOW);

      //Reading Blue Color
      digitalWrite(s2,LOW);
      digitalWrite(s3,HIGH);
      blue = pulseIn(output,LOW);
}

//Taking Order
void order()
{
      if(red<green && red<blue)
        A[k++] = table++;
        
      else if(green<red && green<blue)
         B[l++] = table++;
         
      else if(blue<red && blue<green)
          C[m++] = table++;

       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Thank You");
       lcd.setCursor(0,1);
       lcd.print("Order Taken");

       delay(1000);
}

//Placing Order
void place()
{
       if(red<green && red<blue)
       {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Order from - ");
            lcd.setCursor(0,1);
            lcd.print(" ");
            for(i=0;i<k;i++)
            {
                  lcd.print(A[i]);
                  lcd.print(" ");
            }
       }
        
       else if(green<red && green<blue)
       {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Order from - ");
            lcd.setCursor(0,1);
            lcd.print(" ");
            for(i=0;i<l;i++)
            {
                  lcd.print(B[i]);
                  lcd.print(" ");
            }
       }
         
       else if(blue<red && blue<green)
       {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Order from - ");
            lcd.setCursor(0,1);
            lcd.print(" ");
            for(i=0;i<m;i++)
            {
                  lcd.print(C[i]);
                  lcd.print(" ");
            }
       }
}

//Moving Forward
void forward()
{
      //Right Motor
      digitalWrite(24,HIGH);
      digitalWrite(25,LOW);
      //Left Motor
      digitalWrite(23,HIGH);
      digitalWrite(22,LOW);
}

//Moving Left
void left()
{
      //Right Motor
      digitalWrite(24,LOW);
      digitalWrite(25,LOW);
      //Left Motor
      digitalWrite(23,HIGH);
      digitalWrite(22,LOW);
}

//Moving Right
void right()
{
      //Right Motor
      digitalWrite(24,HIGH);
      digitalWrite(25,LOW);
      //Left Motor
      digitalWrite(23,LOW);
      digitalWrite(22,LOW);
}

//Stopping
void stay()
{
      //Right Motor
      digitalWrite(24,LOW );
      digitalWrite(25,LOW);
      //Left Motor
      digitalWrite(23,LOW);
      digitalWrite(22,LOW);     
}

//Reading Sensor Value
void value()
{
      l1 = analogRead(A1); //l1 for Right Sesnor
      l2 = analogRead(A2); //l2 for Center Sensor
      l3 = analogRead(A3); //l3 for Left Sesnor
}


void setup() 
{
      //Pin Delecartion for WHite Line Sensors
      pinMode(A1,INPUT);
      pinMode(A2,INPUT);
      pinMode(A3,INPUT);

      //Pin Declaration for turning on the White Line Sensors
      pinMode(39,OUTPUT);

      //Pin Declaration for turning on the Motors
      pinMode(25,OUTPUT);
      pinMode(24,OUTPUT);
      pinMode(23,OUTPUT);
      pinMode(22,OUTPUT);

      //Pin Declaration of PWN Speed Control for Motors
      pinMode(46,OUTPUT); //Left Motor
      pinMode(45,OUTPUT); //Right Motor
      
      //Setting Speed as High/255
      analogWrite(46,100);
      analogWrite(45,100);

      //Declaring pin modes
      pinMode(s0,OUTPUT);    //s0
      pinMode(s1,OUTPUT);    //s1
      pinMode(s2,OUTPUT);    //s2
      pinMode(s3,OUTPUT);    //s3
      pinMode(output,INPUT);     //output


      //Setting s0 ans s1 to get 20% frequency
      digitalWrite(s0,HIGH);
      digitalWrite(s1,LOW);

      //Settig Up LCD Output
      pinMode(rw,OUTPUT);
      digitalWrite(rw,LOW);
      lcd.begin(16, 2);
}

void loop() 
{
       value();
       lcd.setCursor(0,0);
       lcd.print("S3  S2  s1");
       lcd.setCursor(0,1);
       lcd.print(l3);
       lcd.print("  ");
       lcd.print(l2);
       lcd.print("  ");
       lcd.print(l1);
      
      //Currently 5 tables are present
      if (table > 5)
      {
          //Checking Sensor and applying conditions
           if( l1>=200 && l3>=200  && l2>=200)
           {
              stay();
              delay(100);
              lcd.clear();
              color(); 
              place();
              delay(1000);
              lcd.clear();
              forward();
              delay(1000);
           }
           
           else if( l1>=200 ) 
           {  
              left();
              delay(100);
              value();
              while(l2<=200 || l1>=200)
              {
                   left();
                   value();
              }
           }
           
           else if( l3>=200 )
           {  
              right();
              delay(100);
              value();
              while(l2<=200 || l3>=200)
              {
                   right();
                   value();
              }
           }
           
           else if( l2>=200 )
           {  
              forward();
           }
           
           else
           {
              stay();
           }  
           delay(100);
      }
       
       //If all the tables have placed order, giving order to kitchen
       else
       {
           //Checking Sensor and applying conditions
           if(l1>=200 && l3>=200  && l2>=200)
           {
              stay();
              delay(100);
              lcd.clear();
              color(); 
              order();
              delay(100);
              lcd.clear();
              forward();
              delay(1000);
           }
           
           else if( l1>=200 ) 
           {  
              left();
              delay(100);
              value();
              while(l2<=200 || l1>=200)
              {
                   left();
                   value();
              }
           }
           
           else if( l3>=200 )
           {  
              right();
              delay(100);
              value();
              while(l2<=200 || l3>=200)
              {
                   right();
                   value();
              }
           }
           
           else if( l2>=200 )
           {  
              forward();
           }
           
           else
           {
              stay();
           }
           delay(100);
       }
}

