// Kelompok OBSTACLE ADVOIDING //

#include <Servo.h> //Library Servo

Servo Scanservo;    //Ping Sensor Servo

#define motorkif  5 //motor kiri forward//
#define motorkib  4 //motor kiri back//
#define motorkaf  3 //motor kanan forward//
#define motorkab  2 //motor kanan back//
#define trigPin  12 
#define echoPin  13
const int Scanservopin = 11;
const int distancelimit = 15; //dalam satuan cm

void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(motorkif, OUTPUT);
pinMode(motorkib, OUTPUT);
pinMode(motorkaf, OUTPUT);
pinMode(motorkab, OUTPUT);
Scanservo.attach(Scanservopin); // Untuk pemindaian Servo
delay(2000);                    // Menunggu selama dua detik
Serial.begin(9600);
}

void loop() {
go();
int jarak = ping();
  if (jarak<distancelimit){
    stopp();
    char turndir = scan();
        switch (turndir){
            case 'l':
            turnleft();
            break;

            case 'r':
            turnright();
            break;

            case 's':
            turnaround();
            break;

            case 'g':
            go();
            break;
            }
  }
}

int ping(){

  long duration, distance;
  //Megirim Pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  //Echo Menerima
  duration = pulseIn(echoPin, HIGH);
  // Mengkonversi jarak Waktu
  distance = (duration/2) / 29.1;
  return round(distance);
}

void go(){  // Maju//
digitalWrite(motorkif,HIGH);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,HIGH);
digitalWrite(motorkab,LOW); 
}

void turnleft(){  // Belok Kiri//
digitalWrite(motorkif,LOW);
digitalWrite(motorkib,HIGH);
digitalWrite(motorkaf,HIGH);
digitalWrite(motorkab,LOW);
delay(500);
digitalWrite(motorkif,LOW);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,LOW);
}

void turnright(){  // Belok Kanan//
digitalWrite(motorkif,HIGH);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,HIGH);
delay(600);
digitalWrite(motorkif,LOW);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,LOW);
}

void turnaround(){ // Putar Balik //
digitalWrite(motorkif,HIGH);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,HIGH);
delay(1000);
digitalWrite(motorkif,LOW);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,LOW);
}

void stopp(){ //Berhenti//
digitalWrite(motorkif,LOW);
digitalWrite(motorkib,LOW);
digitalWrite(motorkaf,LOW);
digitalWrite(motorkab,LOW);
delay(500);
}

char scan(){

  int leftscanval, centerscanval, rightscanval, serongkiri, serongkanan;
  char choice;

  //Lihat Kekiri
  Scanservo.write(190);
  delay(350);
  leftscanval = ping();

  //Lihat Serong kekiri
  Scanservo.write(130);
  delay(200);
  serongkiri = ping();

  //Lihat Kekanan
  Scanservo.write(0);
  delay(450);
  rightscanval = ping();

  //Lihat Serong kekanan
  Scanservo.write(30);
  delay(200);
  serongkanan = ping();

  //scan kearah tengah servo
  Scanservo.write(80);
  delay(200);
  centerscanval = ping();
  Serial.println("");
  Serial.println("        S c a n n n  ! ! !");
 
  if ((leftscanval>rightscanval) && (leftscanval>centerscanval)){
  choice = 'l';
  Serial.println("        K i r i   =>");
  }

  else if ((rightscanval>leftscanval) && (rightscanval>centerscanval)){
  choice = 'r';
  Serial.println("        K a n a n =>");
  }
  
  else{
  choice = 'g';
  Serial.println("        M a j u    =>");
  }

  return choice;
}
