void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  int knapD6 = digitalRead(7);
  int knapD8 = digitalRead(9);

  //Er knappen trykket på?
  if(knapD6 == 0){

    //Tænd og sluk specfikke LED lys
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } 

  //Er knappen trykket på?
  if(knapD8 == 0){

    //Tænd og sluk specfikke LED lys
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  } 
}