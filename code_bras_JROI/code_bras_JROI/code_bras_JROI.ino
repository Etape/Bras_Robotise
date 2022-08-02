#include <Servo.h>
Servo base,effecteur,rotation_effecteur,hauteur;
int Base=0,Hauteur=2,Rotation=1,Effecteur=3,button_R=4,button_L=5;
int max_base=180,max_hauteur=145,max_rotation=145;
int min_base=0,min_hauteur=0,min_rotation=0;
int tab_angle[50][4];
int tab_test[20][4]={{90,90,90,0},{120,90,90,0},{120,115,90,0},{120,115,150,0},{120,145,150,0},{120,180,150,0},{120,180,150,90},{120,180,150,0},{120,145,150,0},{120,115,150,0},{120,115,90,0},{120,90,90,0},{90,90,90,0}};

long temp=millis();
boolean state=HIGH;
int lecture=0,lecture_test=0;
long delai_lecture=250;
long temp_lecture;

int element=0;

void setup() {
base.attach(9);
effecteur.attach(4);
hauteur.attach(6);
rotation_effecteur.attach(2);
Serial.begin(9600);
}
int mode=0; //  0,mode normal, commande manuel ;
           //  1,mode auto,repetion de taches;
           //  2, mode enregistrement; 
void loop() {
  if(mode==0){
    normal_loop();
  }
  if(mode==1){
    auto_loop();
  }
  if(mode==2){
    recorder_loop();
  }
}

void normal_loop(){
  while(mode==0){
    digitalWrite(13,state);
    
    if(analogRead(button_R)<200 && analogRead(button_L)<200){
      mode++;
      break;
    }    
  Serial.print("********");
  
  int angle_bas=map(analogRead(Base),0,1023,min_base,max_base);
  int angle_hauteur=map(analogRead(Hauteur),0,1023,min_hauteur,max_hauteur);
  int angle_rotation=;
  int angle_effecteur;
  Serial.print(angle_hauteur);
  hauteur.write(angle_hauteur);

  if(analogRead(4)<230){
    angle_bas=angle_bas+0.5;
    if(angle_bas>max_base)
    angle_bas=max_base;
  }
  
  if(analogRead(5)<100){
    angle_bas=angle_bas-0.5;
    
    if(angle_bas<min_base)
    angle_bas=min_base;
  }  
  
  //int angle_bas=map(analogRead(3),0,1023,0,180);
  Serial.println((int)angle_bas);
  rotation_effecteur.write((int)angle_bas);
  }
}
void auto_loop(){
  while(mode==1){
    if(analogRead(button_R)<200 && analogRead(button_L)<200){
      mode++;
      break;
    }
    if(millis()-temp>500){
      state=!state;
      temp=millis();
    }
    digitalWrite(13,state);
    if(tab_angle[0][0]==NULL){
      lecture=0;
    if(millis()-temp_lecture>delai_lecture){
      ServoWriter(tab_test[lecture_test][0],tab_test[lecture_test][1],tab_test[lecture_test][2],tab_test[lecture_test][3]);
      lecture_test++;
      if(tab_test[lecture_test][0]==NULL)
      lecture_test=0;
      
      temp_lecture=millis();
    }
    }
    else{ 
    if(millis()-temp_lecture>delai_lecture){
      lecture_test=0;
      ServoWriter(tab_angle[lecture][0],tab_angle[lecture][1],tab_angle[lecture][2],tab_angle[lecture][3]);
      lecture++;
      
      if(tab_angle[lecture_test][0]==NULL)
      lecture=0;
      
      temp_lecture=millis();
    }
    }
    
  }
}
void recorder_loop(){
  
    element=0;
  while(mode==2){
    digitalWrite(13,HIGH);
    lecture_test=0;
    lecture=0;
    if(analogRead(button_R)<200 && analogRead(button_L)<200){
      mode++;
      break;
    }
    if(analogRead(button_R)<200 && analogRead(button_L)>200){
      
      if(element==0){
        int  i;
        for(i=0;i<50;i++){
          tab_angle[i][0]=NULL;
          tab_angle[i][1]=NULL;
          tab_angle[i][2]=NULL;
          tab_angle[i][3]=NULL;
      }
      }
      tab_angle[element][0]=map(analogRead(Base),0,1023,min_base,max_base);
      tab_angle[element][1]=map(analogRead(Hauteur),0,1023,min_hauteur,max_hauteur);
      tab_angle[element][2]=map(analogRead(Rotation),0,1023,min_rotation,max_rotation);
      tab_angle[element][3]=map(analogRead(Effecteur),0,1023,0,180);

      element++;  
      }
    }
}
void ServoWriter(int angle_Base,int angle_Hauteur,int angle_Rotation,int angle_Effecteur){
  base.write(angle_Base);
  hauteur.write(angle_Hauteur);
  rotation_effecteur.write(angle_Rotation);
  effecteur.write(angle_Effecteur);
}

