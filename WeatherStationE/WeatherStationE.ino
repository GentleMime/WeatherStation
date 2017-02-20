#include <DS3231_Simple.h>

//Instantiate clock object
DS3231_Simple Clock;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Clock.begin();
  SetupAlarms();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(readTime());
  delay(1000);

  uint8_t AlarmsFired = Clock.checkAlarms();

  if(AlarmsFired & 1){
    Clock.printTo(Serial);
    Serial.println("Alarm 1 fired");
  }

  if(AlarmsFired & 2){
    Clock.printTo(Serial);
    Serial.println("Alarm 2 fired");
  }
  
}

void reset(){
  
}

String readTime(){
  DateTime currentDateTime;
  String  dateTime;
  currentDateTime = Clock.read();
  dateTime = currentDateTime.Hour + currentDateTime.Minute + currentDateTime.Second;
  return dateTime;
}

void SetupAlarms(){
  Clock.disableAlarms();
  DateTime timeStampReset = Clock.read();
  timeStampReset.Hour = 23;
  timeStampReset.Minute = 59;
  Clock.setAlarm(timeStampReset, DS3231_Simple::ALARM_DAILY);
}

