﻿#include<math.h>
// send to App
//char datas[] = "t36080000000025001100t03D80000000000000001t36480000000003005B24t31880000000000000000t34580000000000000000t36080000000000002800t3608000000B500001A01t36080000000000140004t36080000000047130502t32180000000000009B00t3218002000000403768Et36386700004F0080791Et42B800000000009B0675t420800000000000000AFt03D8000000000000000Ct31D80000000000000004t3938000000003C000000t31880000000000000003t42B80100000000FA0395t3638C010002F00000000";
// receive the data from App
char buffer[25];


boolean flag=false;  // this is off-on
int  speed=10;
boolean busy=true; // judge highway is or not busy  
long num_loop=0;  // loop's compute label
boolean dir=true; //the direction of send frame

void blink_p(String per){
    digitalWrite(LED_BUILTIN, HIGH);   // turn on the LED(HIGH is the voltage level)
    delay(per.toInt()/2);           // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn off the LED  by making the voltage LOW
	delay(per.toInt()/2);         // wait for a second
}
void success(){   					// it is success
  Serial.print("success");
  Serial.print("\r");
}
void failure(){						// it is failure
  Serial.print("failure");
  Serial.print(char(0x07));
}

void openA(){
  flag=true;
  success();
}

void closeA(){
  flag=false;
  success();
}

void Change_speed(char sped){
	int pos_sped = 0;
	int num[];
    if(flag==true){
		num[]={10,20,50,100,125,250,500,800,1000};
    if( sped < '0' or sped > '8'){
      failure();
    }else{
      pos_sped = int(sped - '0');
      speed = num[pos_speed];
      success();
    }
  }else{
    failure();
  }
}

void Sendstandardframe(String stand){
  Serial.println(stand);
  if(Check_frame(stand,1)){
    Serial.print("send the standar_frame"); 
	Serial.println();
  }
}

void Send_external_frame(String external){
  Serial.println(external);
  if(Check_frame(external,0)){
    Serial.print("sends the external frame");
	Serial.println();
  }
}

// check: n=1 standard frame;n=0，external frame
boolean Check_frame(String frame,int n){   
	int F_length;
  if(n==1){
    Serial.print("standard:");
    String id = frame.substring(1,4);
    Serial.print(id);
    Serial.print(" ");
    F_length = frame.substring(4,5).toInt();
    Serial.print(F_length);
    Serial.print(" ");
	
    String data=frame.substring(5,F_length*2+5);
    Serial.print(data);
    Serial.print(" ");
    String per = frame.substring(F_length*2+5,F_length*2+9);
    Serial.println(per);

    if(frame.length()!=(9+F_length*2)){
      return false;
    }else{
      return true;
    }
  }else if(n==0){
    Serial.print("external:");
    String id=frame.substring(1,9);
    Serial.print(id);
    Serial.print(" ");
    F_length = frame.substring(9,10).toInt();
    Serial.print(F_length);
    Serial.print(" ");
    String data=frame.substring(10,F_length*2+10);
    Serial.print(data);
    Serial.print(" ");
    String per=frame.substring(F_length*2+10,F_length*2+14);
    Serial.print(per);
	Serial.println();
    if(frame.length() != (14+F_length*2)){
      return false;
    }else{
      return true;
    }
  }
}
void print(int x){
    if(x<10)
      Serial.write('0'+x);
    else
      Serial.write('A'+x-10);
  }
  //将x转变为k位的16进制输出
void Transform(unsigned long long x,int k){
    for(int i=k-1;i>=0;i--)
      print((x>>(i*4))&15); //x右移i*4位然后与上1111（即将16进制数转换成二进制数）
  }
void C_sframe(int k){
    Serial.write("t");
    Transform(100,3);
    Transform(8,1);
    unsigned long long a=k*50; //a的偏移量
    unsigned long long b=200-k; //b的偏移量
    Transform(0,10);
    Transform(b,2);
    Transform(a,4);
    Serial.write('\r');
//    Serial.write('\n');
  }
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while(Serial.read() >= 0){}
}
void loop() {
    if(Serial.available() ){
      String command=Serial.readStringUntil('\r');
      Serial.print(command);
      char c=command[0];
      if(c=='O'){
        if(command.length()!=1){
          failure();
        }else{
          openA();
        }
      }else if(c=='V'){ 
        if(command.length()!=1){
          failure();
        }else{
          Serial.print("SV2.5-HV2.0");
		  Serial.println();
		}
      }else if(c=='C'){
        if(command.length()!=1){
          failure();
        }else{
          closeA();
        }
      }else if(c=='S'){
        if(command.length()!=2){
          failure();
        }else{
          Change_speed(command[1]);
        }
      }else if(c=='t' && busy){
        Sendstandardframe(command);
      }else if(c=='T' && busy){
        Sendexternalframe(command);
      }else{
        failure();
      }
  }
//draw the graph
  /*if(flag){
	if(numloop%100000==0 ){
      Serial.println(numloop/10000);
      float cur=(num/10000,0,10,0,)
      C_sframe(numloop/100000);
    }
    if(dir ){
      numloop++;
    }else if(!dir){
      numloop--;
    }
    if(numloop>=1000000){
      dir=false;
    }
    if(numloop<=0){
      dir=true;
    }
  }							*/
}


