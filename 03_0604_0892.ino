//                     a b c d e f g
boolean num [12][7] = {0,0,0,0,0,0,1,
                       1,0,0,1,1,1,1,
                       0,0,1,0,0,1,0,
                       0,0,0,0,1,1,0,
                       1,0,0,1,1,0,0,
                       0,1,0,0,1,0,0,
                       0,1,0,0,0,0,0,
                       0,0,0,1,1,0,1,
                       0,0,0,0,0,0,0,
                       0,0,0,0,1,0,0,
                       0,1,0,0,0,0,1,
                       1,1,1,0,0,0,1 };
                       
int buttonPin = A0;
int readButton = 0;
int userGuess = 0;
int randomNo = random(1, 10);
                                              
void setup()
{  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //When start close all LED
  for(int i = 2 ; i <= 8 ; i ++){
    digitalWrite(i, 1);
  }  
}

void loop(){  
  readButton = analogRead(buttonPin);
  handle_start_button();
  handle_guess_button(); 
}

//Displaying LED
void display(int a){
  for(int i = 2 ; i <= 8 ; i ++){
      digitalWrite(i, num [a][i-2]);
    }
}

//When Pressing Left Button : Do Guessing Function
void handle_guess_button(){
  if(readButton == 980 && userGuess == randomNo){ 
    display(0);
    randomNo = random(1, 10);       
  }else if (readButton == 980 && userGuess > randomNo){
    display(10);
  }else if (readButton == 980 && userGuess < randomNo){
    display(11);
  } 
  delay(100);
}

//When Pressing Right Button : Show 1-9
void handle_start_button(){ 
  
  if(readButton == 1001){      
    if(userGuess < 9){
      userGuess+=1;
      display(userGuess);                  
    }
    else{
      display(1); //reset to 1 when x=9
      userGuess = 1;
    }      
    delay(100);
  } 
}
