#include<ESP8266WiFi.h>
#include<DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11
WiFiServer server(80);
DHT dht(DHTPIN,DHTTYPE);
char ssid[]="sreerupasengupta";
char pass[]="sree1999";
char status;
 char str1[15]="";
char str2[15]="";
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.print("hello");
  WiFi.begin(ssid,pass);
  dht.begin();
  while(WiFi.status()!=WL_CONNECTED)
  {delay(500);
  Serial.println("**");
  }
  Serial.println();
  Serial.println();
  Serial.print("connecting to : http// ");
  Serial.println(WiFi.localIP());
  server.begin();
  
 }

void loop() {
  // put your main code here, to run repeatedly:
  
  WiFiClient client=server.available();
  if(digitalRead(D4)==LOW)
  {strcpy(str1,"DAY");
  delay(200);}
  else
  {strcpy(str1,"NIGHT");
  delay(200);
  }
  if(analogRead(A0)>=900)
  {strcpy(str2,"NO RAIN");
  delay(200);}
  else if(analogRead(A0)>=700)
  {strcpy(str2,"LOW RAIN");
  delay(200);}
  else if(analogRead(A0)>=500 && analogRead(A0)<=700)
  
  {strcpy(str2,"NORMAL RAIN");
  delay(200);}
  else
  {strcpy(str2,"HEAVY RAIN");
  delay(200);}
  float t=dht.readTemperature();
  delay(200);
  float h=dht.readHumidity();
  delay(200);
  float hic=dht.computeHeatIndex(t,h,false);
  delay(200);
 client.println("http/1.1 200 OK");
client.println("content-type:text/html");
client.println("connection:close");\
client.println("refresh: 10");
client.println();
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<body bgcolor='blue'>");
client.println("<h1><u><font face='algerian' size='8' color='yellow'> <p align='center'>WEATHER MONITORING SYSTEM</h1></u></font><br></p>");
client.println("<ul><font face='jokerman' size='6' color='red'>");
client.println("<li><b><i>TIME =");
client.println(str1);
client.println("</b></i></li></p>");
client.println("<li><b><i>TEMPERATURE =");
client.print(t);
client.println(" celcius  -- ");
client.print(" FEELS LIKE :");
client.println(hic);
client.println(" celcius ");
client.println("</b></i></li></p>");
client.println("<li><b><i>HUMIDITY =");
client.print(h);
client.println(" % ");
client.println("</b></i></li></p>");
client.println("<li><b><i>RAIN =");
client.println(str2);
client.println("</b></i></li></p>");
client.println("</font><br></ul>");
client.println("<h2><u><font face='algerian' size='2' color='yellow'> <p align='right'>BY- ANKAN NATH, SREERUPA SENGUPTA, SIDHANT PANDEY, SAYANTAN PAUL</h2></u></font><br></p>");
client.println("</body>");
client.println("</html>");
delay(1000);

}
