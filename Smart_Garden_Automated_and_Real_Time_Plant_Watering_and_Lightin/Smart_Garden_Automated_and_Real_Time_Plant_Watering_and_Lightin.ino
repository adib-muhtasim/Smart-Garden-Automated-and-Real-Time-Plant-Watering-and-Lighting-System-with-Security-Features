
#include <DS3231.h>
#include <IRremote.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int pos = 0;

int Buzzer = 7;
int LED = 6;



int trigPin1=8;
int echoPin1=9;

int trigPin2=10;
int echoPin2=11;

int trigPin3=12;
int echoPin3=13;



int RECV_PIN = 2;
int light1 = A0;
int light2 = A1;
int buzzer_relay = 3;

int waterPump = A3;


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
int greenLED=12;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

  pinMode(light1, OUTPUT);
  digitalWrite(light1, HIGH);

  pinMode(light2, OUTPUT);
  digitalWrite(light2, HIGH);

  pinMode(buzzer_relay, OUTPUT);
  digitalWrite(buzzer_relay, HIGH);



  //servo

   pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
   pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
   pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  myservo.attach(5);  // attaches the servo on pin 5 to the servo object
  myservo.write(pos);
  delay(100);

  pinMode(Buzzer, OUTPUT);
   pinMode(LED, OUTPUT);

 ////////// //pump

  pinMode(waterPump, OUTPUT);
 digitalWrite(waterPump, HIGH);


 /////////////rtc

 // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
 //rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
// rtc.setTime(22, 25, 0);     // Set the time to 12:00:00 (24hr format)
// rtc.setDate(23, 7, 2017);   // Set the date to January 1st, 2014


}

void loop() 
{
  

  

  ////remote/////

  
  if (irrecv.decode(&results))
  {


  ////light1//
    
   if(results.value==0x10)//light1 on
   {
     digitalWrite(light1, LOW); 
     
    }

     if(results.value==0x810)//light1 off
    {
     digitalWrite(light1, HIGH);     
      
    }

    ///light 2//

     if(results.value==0x410)//light2 on
   {
     digitalWrite(light2, LOW); 
     
    }

     if(results.value==0xC10)//light2 off
    {
     digitalWrite(light2, HIGH);     
      
    }

////water pump////remote

     if(results.value==0x210)//pump on
   {
    Serial.println("pump on");
     digitalWrite(waterPump, LOW); 
     delay(5000);
    digitalWrite(waterPump, HIGH);     
      Serial.println("pump off");
     
    }

   


    

    //BUZZER

       if(results.value==0x610)//buzzer on
   {
     digitalWrite(buzzer_relay, LOW); 
     Serial.println("buzzer on");
     
    }

     if(results.value==0xE10)//buzzer off
    {
     digitalWrite(buzzer_relay, HIGH);     
      Serial.println("buzzer off");
    }

  
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);

  //remote end

  


  
  

/////water pump////

int humidityRaw = analogRead(A2); // 1023 to 0 ===> 0 to 100%
int humidityReal = map(humidityRaw, 1023, 0, 0, 100);
Serial.println(humidityReal);
delay(100);
 if (humidityReal < 30)
  {
    digitalWrite(waterPump, LOW);//turn on
     digitalWrite(LED, HIGH);//turn on
    delay(5000);//water for 3 sec
  }
  else
  {
    digitalWrite(waterPump, HIGH);//turnoff
     digitalWrite(LED, LOW);//turn on
  }



  //security/////


  
     long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

   if (distance1 >= 30 || distance1 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
    digitalWrite(Buzzer, HIGH);
myservo.write(120);
delay(1000);
digitalWrite(Buzzer, LOW);
  }
  delay(200);

  
long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;

   if (distance2 >= 30 || distance2 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor2  ");
    Serial.print(distance2);
    Serial.println("cm");
    digitalWrite(Buzzer, HIGH);
myservo.write(80);
delay(1000);
digitalWrite(Buzzer, LOW);
  }
  delay(200);


  
  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= (duration3/2) / 29.1;

   if (distance3 >= 30 || distance3 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor3  ");
    Serial.print(distance3);
    Serial.println("cm");
    digitalWrite(Buzzer, HIGH);
myservo.write(45);
delay(1000);
digitalWrite(Buzzer, LOW);
  }
  delay(200);



/////////rtc//////
String Day=rtc.getDOWStr();
   String Date = rtc.getDateStr();
     String TIME = rtc.getTimeStr();



     Serial.print(Day);
  //Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
 
  Serial.print(Date);
 // Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
 
   Serial.println(TIME);
  //Serial.println(rtc.getTimeStr());

  


  if(TIME == "23:00:00")
  {

     digitalWrite(light1, LOW);
      digitalWrite(light2, LOW);  
      digitalWrite(LED, HIGH);//turn on
      digitalWrite(waterPump, LOW);//turn on
      delay(5000);//water for 3 sec
      digitalWrite(light1, HIGH);
      digitalWrite(light2, HIGH);  
      digitalWrite(waterPump, HIGH);//turn on
      digitalWrite(LED, LOW);//turn on

  
  }



  
}
