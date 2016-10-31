int le = 3;
int lm = 4;
int ld = 5;
int lscE = 2;
int lscD = 6;



int md1 = 7;
int md2 = 8;
int pwmMD = 9;

int me1 = 12;
int me2 = 13;
int pwmME = 11;

int se = A0;
int sm = A1;
int sd = A2;
int spcE = A3;
int spcD = A4;

int smRead;
int seRead;
int sdRead;
int spcERead;
int spcDRead;

//int meio = 511;
int meio = 600;
int flagPC = 0;

int flagCruzamento = 0;

void setup() {
  // put your setup code here, to run once:
  // ligar os sensores
  pinMode(le, OUTPUT);
  pinMode(lm, OUTPUT);
  pinMode(ld, OUTPUT);
  pinMode(lscE, OUTPUT);
  pinMode(lscD, OUTPUT);
  
  digitalWrite(le, HIGH);
  digitalWrite(ld, HIGH);
  digitalWrite(lm, HIGH);
  digitalWrite(lscE, HIGH);
  digitalWrite(lscD,HIGH);
  // fim
  // declarar os sensores
  pinMode(sm, INPUT);
  pinMode(sd, INPUT);
  pinMode(se, INPUT);
  pinMode(spcE, INPUT);
  pinMode(spcD, INPUT);
  // fim
  // declarar os motores 
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  pinMode(me1, OUTPUT);
  pinMode(me2, OUTPUT);
  // fim
  //declarar comunicar serial
  Serial.begin(9600);
  //fim
}

void loop() {
               
  smRead = analogRead(sm);
  seRead = analogRead(se);
  sdRead = analogRead(sd);
  spcERead = digitalRead(spcE);
  spcDRead = digitalRead(spcD);
   
//    if ((flagPC ==0) && (spcRead ==1) && (smRead >meio)&&(seRead <meio)&&(sdRead<meio)){
//       flagPC = 1; 
//    }
//    else if ((flagPC == 1) && (spcRead==0) && (smRead >meio)&&(seRead <meio)&&(sdRead<meio)){
//        flagPC = 2;
//    }
//    else if ( (flagPC ==2) && (spcRead ==1) && (smRead >meio)&&(seRead <meio)&&(sdRead<meio)){
//      flagPC = 3;
//     delay(1500);
//      off();  
//      delay(20000);
//  }
        //Controle partida chegada
         if ((flagCruzamento == 0) && (spcDRead == 1)) {   //largada
           flagCruzamento = 1;      //Estado 1
           
         }
         else if ((flagCruzamento ==1) && (spcDRead == 0)){
            flagCruzamento = 4; 
         }
         
         else if ((seRead > meio) && (smRead>meio) &&(sdRead>meio)){   //Cruzamento  - sensor do meio
            if (flagCruzamento == 4){
                 flagCruzamento = 2; 
            }
          }
          
          else if ((flagCruzamento == 2) && (spcDRead == 1)){      //Cruzamento - sensor traseiro
                 flagCruzamento = 3; 
          }
          else if ((flagCruzamento == 3 ) && (spcDRead==0)) { //cruzamento
                flagCruzamento = 4;
          }
          else if ((spcDRead == 1) && (flagCruzamento == 4)){         //Chegada
            off();  
            delay(20000);
            
          }
          
          
          //Controle das curvas
      
          if((smRead > seRead && smRead > sdRead && sdRead < meio && seRead < meio) || (smRead > meio && sdRead > meio && seRead > meio))
          {
            forward();

          }
          else if ((seRead > smRead && seRead > sdRead) || (seRead > sdRead && smRead > sdRead && smRead > meio))
          {
            left();
          }
          else if((sdRead > seRead && sdRead > smRead) || (smRead > seRead && sdRead > seRead && smRead > meio))
          {
            right();
          }
          
          else if(smRead < meio && sdRead < meio && seRead < meio)
          {
              backward();
          }  

     
    
 
    
  Serial.print("sm ");
  Serial.println(smRead);
  Serial.print("se"); 
  Serial.println(seRead);
  Serial.print("sd ");
  Serial.println(sdRead);
  Serial.println("");
  
  Serial.println("spcD");
  Serial.print(spcDRead);
  Serial.println("");
  Serial.print("contador ");
  Serial.println(flagCruzamento);


}


void forward()
{
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
  digitalWrite(me1, HIGH);
  digitalWrite(me2, LOW);

}

void left()
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);//MUDEI AQUI PRA LOW
  digitalWrite(me1, HIGH);
  digitalWrite(me2, LOW);

}

void right()
{
    digitalWrite(md1, HIGH);
    digitalWrite(md2, LOW);
    digitalWrite(me1, LOW);
    digitalWrite(me2, HIGH);//MUDEI AQUI PEA LOW 
}

void backward()
{
    digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
    digitalWrite(me1, LOW);
    digitalWrite(me2, HIGH);
}  

void off()
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, LOW);
  digitalWrite(me1, LOW);
  digitalWrite(me2, LOW);
}


