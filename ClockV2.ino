#include <SimpleTimer.h>


SimpleTimer timer;
int count = 0;


void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT); 
}

bool started = false;
int priority = 0;
int tapX = 0;
int tapactual;
int tap_time;
int time_actual;
int input1X = 0;
float BPM; 
int max_BPM = 500; /* Max BPM*/
int min_BPM = 60;  /*Min BPM */
int max_time = ((1/(min_BPM/60)) * 1000);
int min_time = ((1/(max_BPM/60)) * 1000);


void loop() {
  
  if (!started) {
    cycle_on();
    started = true;
  }
  
  timer.run();

  

}


/*********************************************************************/



void cycle_off() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  count++;

  if (count == 8) {
    count = 0;
  }
}



/*********************************************************************/


void cycle_on() {

  switch (count) {
    case 0:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      break;

    case 1:
      digitalWrite(8, HIGH);
      break;

    case 2:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      break;

    case 3:
      digitalWrite(8, HIGH);
      break;
  
    case 4:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      break;

    case 5:
      digitalWrite(8, HIGH);
      break;

    case 6:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      break;

    case 7:
      digitalWrite(8, HIGH);
      break;
  }

  int input1 = analogRead(A1);
  int input2 = analogRead(A2);

  if (priority == 0){
     BPM = map(input1, 0, 1023, min_BPM, max_BPM);
     
  }
  
  if (priority == 1){
     BPM = (60000 / tap_time);
    
     
  }


  if (input1X - input1 > 5){
    priority = 0;
  }
  if (input1X - input1 < -5){
    priority = 0;
  }

  input1X = input1;
  
  
  


  
  float duration_percentage =  map(input2, 0, 1023, 1, 90);
 
  int cycletime = (60000/BPM);

  float cycle_start = cycletime;
  float cycle_stop = (cycletime * (duration_percentage/100));


  timer.setTimeout(cycle_start, cycle_on);
  timer.setTimeout(cycle_stop, cycle_off);

}

/*********************************************************************/
