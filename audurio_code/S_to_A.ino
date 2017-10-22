//from APP send to Arduino

char data[] = "t36080000000025001100t03D80000000000000001t36480000000003005B24t31880000000000000000t34580000000000000000t36080000000000002800t3608000000B500001A01t36080000000000140004t36080000000047130502t32180000000000009B00t3218002000000403768Et36386700004F0080791Et42B800000000009B0675t420800000000000000AFt03D8000000000000000Ct31D80000000000000004t3938000000003C000000t31880000000000000003t42B80100000000FA0395t3638C010002F00000000";
char buffer[30];
long Data_num = 0;

void setup() {
  Serial.begin(115200);
  while(Serial.read() >= 0){}
  }

void send(){
	int j;
	int i;
	for(j=0;j<20;j++){
		for(i=0;i<=20;i++){
			if(i!=20){
				Serial.print(data[21*j+i]);
				Serial.println()
					}
			else{
				Serial.print(data[21*j+i]);
				Serial.println()
                       }
            }
    }
}
void receive(){
  if(Serial.available()>0){
    delay(100);
    Data_num = Serial.readBytes(buffer,21);
    Serial.print(buffer);
    Serial.println();
  }
   while(Serial.read() >= 0){}
   for(int i=0;i<25;i++){
     buffer[i]='\0';
  }
}
void loop(){
    send();
    receive();
}
