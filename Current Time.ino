
/*
Sample Code for fetching data from Internet using WiFi Module
In this code, I am fetching current time of India 
I am using MultiSerialMega code as I'm using Arduino MEGA

code by :- Sachin Soni(SMS)
Date:- 20/11/15

 */
#define DEBUG true // to view the response on Serial Monitor
String ANS="";
char inv='"';

void setup() 
{
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115200);

  sendData("AT+RST\r\n",1000,0);
  delay(3000);
  sendData("AT+CWMODE=3\r\n", 1000, DEBUG);
  delay(3000);
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  delay(3000);
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80
  delay(3000);
  sendData("AT+CWLAP\r\n",1000,1); //It Will list all the available WiFi networks around you
  delay(3000);
 String conn="AT+CWJAP";
        conn+="=";
        conn+=inv;
        conn+=Host_Name; // Enter the host name of your network
        conn+=inv;
        conn+=",";
        conn+=inv; 
        conn+=Password; // Enter the password, if it is open network than delete this line
        conn+=inv;
        conn+="\r\n\r\n";
   sendData(conn,1000,DEBUG); // It will connect the module to the given WiFi Network
   delay(3000);
  
}

void loop() 
{
   
   String add="AT+CIPSTART";
        add+="=";
        add+=inv;
        add+="TCP";
        add+=inv;
        add+=",";
        add+=inv;
        add+="api.thingspeak.com";
        add+=inv;
        add+=",";
        add+="80";
        add+="\r\n";
 sendData(add,1000,1); // This will communicate with the Website
 
 String rest="AT+CIPSEND=90";  // 90 indicates number of characters to send. If you are entering API from thingspeak.com than it will be 90 characters only
        rest+="\r\n";
  sendData(rest,1000,1);
  

String hostt="GET /apps/thinghttp/send_request?api_key=E0F8WDKZ0ZJBA7SK";
       hostt+="\r\n";
       hostt+="Host:api.thingspeak.com";
       hostt+="\r\n\r\n\r\n\r\n\r\n";
       ;
String Time=sendData(hostt,1500,1); // It will send GET request to the Server
String TIME="";
int i=0;
//Serial.println(Time);

while(Time.charAt(i)!=':')
i++;
i++;
TIME=Time.substring(i);
TIME=TIME.substring(0,11);
Serial.println(TIME);
    
}     
     
    
     
   String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the Serial1
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial1.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
   
 

 
