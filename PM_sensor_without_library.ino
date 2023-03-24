void read_ps_PM(int*,int*,int*);

//Pollution sensor commands
const byte ps_start_QAmode_cmd[] = {0XFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46};
const byte ps_read_cmd[] = {0XFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

byte ps_received_byte[24];


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//pollution sesnor startup code for Q&A mode
for(int i = 0;i<9;i++)
{
  Serial.write(ps_start_QAmode_cmd[i]);
}
delay(2000);
for(int i = 0;i<9;i++)
{
  Serial.write(ps_read_cmd[i]);
}
delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  //pollution 
  int pm1_0;
  int pm2_5;
  int pm10;
  
  read_ps_PM(&pm1_0 , &pm2_5 , &pm10); // ("*") =>> 1 = PM1.0  , 2 = PM2.5  , 3 = PM10
  Serial.print("PM1.0          :  ");
  Serial.print(pm1_0);
  Serial.println("    ug/m3");
 

  Serial.print("PM2.5          :  ");
  Serial.print (pm2_5);
  Serial.println("    ug/m3");
 

  Serial.print("PM10           :  ");
  Serial.print (pm10);
  Serial.println("    ug/m3");
  Serial.println("--------------------");
  delay(1000);
}
void read_ps_PM(int* res1,int* res2,int *res3)
{
   if(Serial.write(ps_read_cmd,sizeof(ps_read_cmd)) == 9)
   {
    for(byte i = 0;i<9;i++)
    {
      ps_received_byte[i] = Serial.read();
    }

//    debug code
//    for(byte j = 0;j<9;j++)
//    {
//      Serial.println(ps_received_byte[j]);
//    }

      //pm1_0
      *res1 = (0x00 * 256) + ps_received_byte[7]; 
      //*res1 = *res1/1000;  //converts ug/m3 to ppm   
      
      //pm2_5
      *res2 = (0x00 * 256) + ps_received_byte[3];
      //*res2 = *res2/1000;  //converts ug/m3 to ppm  
      
     
      //pm10
      *res3 = (0x00 * 256) + ps_received_byte[5];
      //*res3 = *res3/1000;  //converts ug/m3 to ppm  
   }
}
