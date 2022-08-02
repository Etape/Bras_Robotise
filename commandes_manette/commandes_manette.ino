const int volant=2;
const int Cli_gauche=2;
const int  Cli_droit=3;
const int Btn_Cli_gauche=12;
const int  Btn_Cli_droit=13;
const int  Btn_Cli_mil=11;
const int Pedale_Frein=4;
const int  Pedale_Acc=5;
const int Pedale_emb=6;
const int levier_M=7;
const int levier_R=8;
const int levier_PM=9;
const int phares=10;
const int phares_btn=5;
String envoi;
boolean state;
int i,j,Cli1;
int angle;
int val_ac,val_fr;
int Etat_Cli=0;
int Valeur=0;

void setup() {
  pinMode(Pedale_Frein,INPUT);
  pinMode(Pedale_Acc,INPUT);
  pinMode(Cli_gauche,OUTPUT);
  pinMode(Cli_droit,OUTPUT);
  pinMode(Btn_Cli_gauche,INPUT);
  pinMode(Btn_Cli_droit,INPUT);
  pinMode( Btn_Cli_mil,INPUT);
  pinMode(volant,INPUT);
  pinMode(phares_btn,INPUT);
  pinMode(levier_M,INPUT);
  pinMode(levier_R,INPUT);
  pinMode(levier_PM,INPUT);
  pinMode(Pedale_emb,INPUT);
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
  int Cli=0;  
  Valeur=analogRead(volant);
  angle=map(Valeur,0,1023,0,180);
  envoi="s"+angle;
  Envoi();  // on envoi l'angle lu
  
  val_ac=analogRead(Pedale_Acc);
  envoi="a"+val_ac;
  Envoi(); // on envoi le niveau d'acceleration lu
  
  val_fr=analogRead(Pedale_Frein);
  envoi="f"+val_fr;
  Envoi();  // on envoi le niveau de deceleration lu
  
  if(digitalRead(Pedale_emb)==HIGH){ // si la pedale d'embreillage est appuyée,
    if(digitalRead(levier_M)==HIGH){ 
    envoi="1111";//on envoi ce code si le levier est 1ere vitesse
    Envoi();
  }
    if(digitalRead(levier_R)==HIGH){
    envoi="1112"; // celui ci si on est en marche arriere
    Envoi();
  }
    if(digitalRead(levier_PM)==HIGH){
    envoi="1110"; // celui ci si on est  au point mort
    Envoi();
  }
  }
    if(digitalRead(Btn_Cli_gauche)==HIGH){
    envoi="c11"; // celui ci si on est  au point mort
    Envoi();
    Cli=1;
    Etat_Cli=1;
  }
    if(digitalRead(Btn_Cli_droit)==HIGH){
    envoi="c21"; // celui ci si on est  au point mort
    Envoi();
    Cli=1;
    Etat_Cli=2;
  }
    if(digitalRead(Btn_Cli_mil)==HIGH){
    envoi="c31"; // celui ci si on est  au point mort
    Envoi();
    Cli=1;
    Etat_Cli=3;
  }
    if(digitalRead(Btn_Cli_gauche)==LOW){
    envoi="c10"; // celui ci si on est  au point mort
    Envoi();
  }
    if(digitalRead(Btn_Cli_droit)==LOW){
    envoi="c20"; // celui ci si on est  au point mort
    Envoi();
  }
    if(digitalRead(Btn_Cli_mil)==LOW){
    envoi="c30"; // celui ci si on est  au point mort
    Envoi();
  }
    if(digitalRead(phares_btn)==HIGH){
      digitalWrite(phares,HIGH);
    envoi="p1";
    Envoi();
  }
    if(digitalRead(phares_btn)==LOW){
      digitalWrite(phares,LOW);
    envoi="p0"; 
    Envoi();
  }
    int tmp;
  if(Etat_Cli!=0){
    clignotant(Etat_Cli,HIGH);
    tmp=millis();
  }
  if(Cli!=0){
  if((millis()-tmp)>(500*i)){
  clignotant(Etat_Cli,!state);
  state=!state;
  i++;
    }
}
} 
void clignotant(int cote,boolean etat){
  if(cote!=Cli1){
    i=1;
    Cli1=cote;
    }
  if(cote==Cli_gauche){
    digitalWrite(Cli_gauche,etat);   
    }
  if(cote==Cli_droit){
    digitalWrite(Cli_droit,etat);
    }
    if(cote==2){
    digitalWrite(Cli_gauche,etat);
    digitalWrite(Cli_droit,etat);  
    }
  }
  void Envoi(){
    Serial.println(envoi);
    Serial.flush();
    envoi="";
    }
