#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#define TxD 1
#define RxD 0
char  codigoSecreto[4]={'1','1','1','1'}; // Aqui va el codigo secreto
char   araytemp[4];

// Para cambiar el tamano de la clave, solo hay que cambiar el tamano del arrayint input0=0;
int input0=0;
int input=0;    // necesaria para la clave
int input2=0;
int input3=0;
int input4=0;
int a,b,c,d;
int direc0=0,direc1=1,direc2=2,direc3=3;
int ledVerde=6;   // pin para el LED verde
int ledRojo=7;    // pin para el LED rojo
int rele = 8;
SoftwareSerial Bluetooth(TxD, RxD);
void setup()
   {
      Bluetooth.begin(9600) ;
      pinMode (ledVerde,OUTPUT);
      pinMode (ledRojo, OUTPUT);
      pinMode (rele,OUTPUT);
      digitalWrite(ledRojo,LOW); // apagamos el LED rojo
      digitalWrite(ledVerde,LOW); // apagamos el verde     
      Serial.begin(9600) ;
      Serial.print("Introduzca_su_Opcion");
      
   }
    void loop()
{
     //if (Serial.available()>0){
         input0 = Serial.read();
         input= Serial.read();
         input2=Serial.read();
         input3=Serial.read();   
       
     //}   
           
               
  
  switch(input0)
     {
   case 'e':
 Serial.print("Introduzca_su_Password"); 
       delay(10000);
  if((input=Serial.read()==(a=EEPROM.read(direc0)))&&(input2=Serial.read()== (b=EEPROM.read(direc1)))&&(input3=Serial.read()==(c= EEPROM.read(direc2)))&&(input4=Serial.read()==(d=EEPROM.read(direc3))))
      
      {

        Serial.print("Password_Correcto");
        delay(1000);
        digitalWrite(ledVerde, HIGH); // encendemos el verde
        delay(3000);
        digitalWrite(ledVerde,LOW);
      //Codigo para activar el relay de la chapa y tomar la foto 
         digitalWrite(rele,HIGH);  // Activamos el relé y la chapa 
         delay(2000);              // 2 segundo
         digitalWrite(rele,LOW);   // Desactivamos el relé 
     
         }
      //termina codigo de Relay de Chapa 
      
            else{
             Serial.print("Password Incorrecto");
             digitalWrite(ledRojo,HIGH); // encendemos el LED rojo
             delay(3000);
             digitalWrite(ledRojo,LOW);     
           
             } //cierre else
           break;
     case 'c':
         Serial.print("Ingrese_Password_de_Origen"); 
         delay(10000);
        if((input=Serial.read()==codigoSecreto[0])&&(input2=Serial.read()==codigoSecreto[1])&&(input3=Serial.read()==codigoSecreto[2])&&(input4=Serial.read()==codigoSecreto[3]))
          {
        digitalWrite(ledVerde, HIGH); // encendemos el verde   
        Serial.write("Introduzca Nuevo Password");
        delay(10000);
        
        araytemp[0]=(input=Serial.read());     // lo recibido del imput se almacena en las posiciones del aray
        araytemp[1]=(input2=Serial.read());  
        araytemp[2]=(input3=Serial.read());  
        araytemp[3]=(input4=Serial.read());  
        
           a=araytemp[0];     // lo que tenemos en araytemp  se almacena en la variable a 
           b=araytemp[1];
           c=araytemp[2];
           d=araytemp[3];
           
        EEPROM.write(direc0,a);  // Guardamosen la Memoria eeprom el dato almacenado en la variable a con la direccion direc0 
        EEPROM.write(direc1,b);
        EEPROM.write(direc2,c);
        EEPROM.write(direc3,d);
   
      Serial.print("Cambio de Password Exitoso"); //envia mensaje cambio exitoso
             digitalWrite(ledVerde, LOW); // encendemos el verde   
             
           
           } 
        
        else{
             Serial.print("Password no Coincide");
             digitalWrite(ledRojo,HIGH); // encendemos el LED rojo
             delay(3000);
             digitalWrite(ledRojo,LOW); // Apagamos  el LED rojo
          
             } //cierre else  
        break;
      }  //cierre de switch 
   }
   //cierre del Setup 


