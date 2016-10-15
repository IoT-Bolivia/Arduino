#include <SoftwareSerial.h> 
SoftwareSerial mySerial(2, 3); //pin2 Rx, pin3 Tx 

int CMD[64];
int comlen =0;
int out_flag =0;

int tag1[4] = {0xCD, 0xB9, 0x3D, 0x96};
int tag2[4] = {0xBD, 0x39, 0x36, 0x96};
int newtag[4] = {0x00,0x00,0x00,0x00};
int i = 0;
int led = 13;
boolean flag = false;
boolean sw = false;

void setup() 
{ 
  Serial.begin(9600);
  mySerial.listen();
  Serial.println("Serial number will be displayed here if a card is detected by the module:\n"); 
  // set the data rate for the SoftwareSerial port 
  mySerial.begin(9600); 
  delay(10);
  mySerial.write(0x02); //Send the command to RFID, please refer to RFID manual 

  pinMode(led, OUTPUT);
} 
void loop() // run over and over 
{       
    while (mySerial.available()) {
        byte C = mySerial.read();
        //Serial.println(C);
        newtag[i] = C;
        if (C<16) Serial.print("0");
        Serial.print(C ,HEX); //Display the Serial Number in HEX 
        Serial.print(" ");
        out_flag =1;
        i++;
    }
    
    if (out_flag >0) {               
        Serial.println();
        out_flag = 0;
        i = 0;
        flag = comparetag(newtag, tag2);
        if(flag){
            Serial.println("true");
            sw = !sw;
            if(sw){
                digitalWrite(led, HIGH);
            }
            else{
                digitalWrite(led, LOW);
            }
        }          
    }     
}

boolean comparetag(int aa[4], int bb[4])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 4 ; cc++)
  {
      if (aa[cc] == bb[cc])
      {
        fg++;
      }
  }
  if (fg == 4)
  {
      ff = true;
  }
  
  return ff;
}
