
const int trigPin = 13;
const int echoPin = 12;
long duration;
int distance;
//Initalisera Distans sensorn så att den har variabler och portar fixade


void setup() {
  pinMode(trigPin, OUTPUT); //Sätter trigPin till en Output
  pinMode(echoPin, INPUT);  //Sätter echoPin till en Input 
  pinMode(11, OUTPUT); //Relay 1 Front
  pinMode(10, OUTPUT); //Relay 2 Back
  pinMode(7, OUTPUT); //Yellow Lamp
  pinMode(6, OUTPUT); //Blue Lamp
  pinMode(5, OUTPUT); //Green Lamp
  pinMode(4, OUTPUT); //Red Lamp
  pinMode(8, INPUT); //Blue Button
  pinMode(2, INPUT); //Green Button
  pinMode(9, INPUT); //Red Button
  Serial.begin(9600); //Användes under debugging och används inte längre då 
  // tåget går på batteri (Kabel krävs för avlässning vilket går emot användningen av batterier)
  
  

}

void loop() {
  //Följande kod om distans sensorn är tagen från internet och jag är inte säker på varför man måste sätta trigPin till LOw och echoPin till High, annars funkar det inte.
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); //En kort delay för tillåta signalen som skickats ut att ha tid att komma tillbaka innan man fångar upp den. 
digitalWrite(trigPin, HIGH);

duration = pulseIn(echoPin, HIGH); //Gör om avståndet som kom tillbaka till variabeln duration för lättare skrivning av koden. 

distance = duration * 0.034/2; //Hittade en ekvation på internet som gjorde om avståndet till cm för lättare kalibrering i verkligheten

Serial.println(distance); //Användes under kalibreringen för att hitta ett bra avstånd där bromsträckan var tillräckligt lång men samtidigt inte för lång.

if (distance < 40) {
  stopengine();
  digitalWrite(7, HIGH);
  delay(6000);
  digitalWrite(7, LOW);
  //Denna if-sats sägger till tåget att stanna om den kommer inom 40cm av något. Funktionen "Stopengine" körs först för att stanna tåget
  //Port 7 är den gula lampan som ska tändas för att signalera att tåget stannat av sig självt.
  //En delay lägs på 6 sekunder för att tåget inte ska starta igen direkt av sig själv och så att användaren hinner flytta/hantera tåget innan lampan släcks.
}
  

if (digitalRead(9) == HIGH){
  stopengine();
  //Om röd knapp trycks, stoppa motorn.
}



if (digitalRead(2) == HIGH){
  startengine();
  //Om grön knapp trycks, starta motorn (En motor enbart)
}

if (digitalRead(8) == HIGH){
  maxengine();
  //om blå knapp trycks, starta motorn på max (Båda motorerna startar)
}

}

void stopengine(){
    //Stopengine funktionen kommer att som sagt, stoppa motorn manuellt (Distans sensorn använder denna funktionen för att stoppa motorn också)
    //Används när man inte längre vill att tåget ska köra och istället stanna
    digitalWrite(4, HIGH); //Tänder röd lampa då tåget stannat
    digitalWrite(5, LOW); //Släcker grönlampa
    digitalWrite(6, LOW); //Släcker blå lampa
    digitalWrite(10, HIGH); //OFF
    digitalWrite(11, HIGH);// OFF
}

void startengine(){
  //Startengine funktionen används för att starta motorn på en bas nivå, enbart en motor används och är bäst för säker transport då den inte åker i max hastighet
  digitalWrite(5, HIGH); //Tänder grön lampa då tåget startat
  digitalWrite(4, LOW); //Släcker röd lampa
  digitalWrite(6, LOW); //Släcker blå lampa
  digitalWrite(11, LOW); //ON
  digitalWrite(10, HIGH); //OFF
}

void maxengine(){
  Serial.println(digitalRead(3)); //Användes under debugging då maxengine automatiskt startade ibland.
  //Maxengine funktionen används för att starta båda motorerna så att tåget får max styrka och hastighet.
  digitalWrite(6, HIGH); //Tänder blå lampa på Maxengine startat
  digitalWrite(5, LOW); //Släcker grön lampa
  digitalWrite(4, LOW); //Släcker röd lampa
  digitalWrite(10, LOW); //ON
  digitalWrite(11, LOW); //ON
}
