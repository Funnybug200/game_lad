//defining all the pins
#define a 13//pin 1
#define b 12//pin 2
#define f 14//pin 3
#define d 27//pin 4
#define e 26//pin 5
//defining all the button pins "inputs"
#define b1 33//input 1
#define b2 22//input 2
#define b3 21//input 3
#define b4 19//input 4
#define b5 18 //input 5
#define b6 5//input 6

#define clock 25//clock pin
#define reset 33//reset pin
//_________________________________________________________________________________________________
const int height=8;//height of the display
const int width=5;//width of the display
const int tick_rate=40;//tick rate " the update per second in the game "
const float display_delay=1;//use this to alter frame rate "dont use it unles you have to :| "

char pins[5]={a,b,f,d,e};//all the display pins in order

char bpins[6]={b1,b2,b3,b4,b5,b6};//all the button pins in order :left,up,down,right,B,A

bool buttons[6]={0};//button stats in order of the button pins

TaskHandle_t display_task = NULL;
TaskHandle_t game_task = NULL;
//_______________________________________________________________________________________________
bool back_round [height][width]={{0,0,0,0,0}//back round arry
                                ,{0,0,0,0,0}
                                ,{0,0,0,0,1}
                                ,{0,1,0,1,1}
                                ,{1,1,1,1,1}
                                ,{1,1,0,1,0}
                                ,{0,1,1,1,1}
                                ,{1,1,0,1,1}};

bool play [height][width]={{0,1,1,1,0}//play arry "the arry that moves!!"
                          ,{0,0,1,0,0}
                          ,{0,0,0,0,0}
                          ,{0,0,0,0,0}
                          ,{0,0,0,0,0}
                          ,{0,0,0,0,0}
                          ,{0,0,0,0,0}
                          ,{0,0,0,0,0}};

//________________________________________________________________________________________________

void setup() {//all the pin set up
  Serial.begin(115200);

  for(int display=0;display<5;display++){//display pins set up
  pinMode(pins[display], OUTPUT);
 }
  

  for(int input=0;input<6;input++){//button pins set up
  pinMode(bpins[input], INPUT);
  }

  pinMode(reset,OUTPUT);//reset and clock pins set up
  pinMode(clock,OUTPUT);


  digitalWrite(clock,0);//flashing the clock and reset pins to make sur CD4017 chip is on the track 
  digitalWrite(reset,1);
  delay(10);
  digitalWrite(reset,0);


  for(int i=0;i<5;i++){//flashing all the display pins to +3.3v becase display is "comen anode"!!
    digitalWrite(pins[i],0);
  }

//_____________________________________________________________________________________________________
  xTaskCreate(//esp task manegment
  print,
  "display task",
  10000,
  NULL,
  2,
  &display_task
 );
 xTaskCreate(
  game,
  "game task",
  110000,
  NULL,
  1,
  &game_task
 );
 //_________________________________________________________________________________________________
}  


//__________________________________________________________________________________________________

  

void print(void * parametrs){//the print void is for showing the summ of tow arrys on screen
  for(;;){//it runs infinitly and shows 41fps you can modefi by redusing display_delay on top 
    
  for(int i =0;i<height;i++){

   for(int j=0;j<width;j++){
    digitalWrite(pins[j],!(play[i][j]||back_round[i][j]));
   }
   vTaskDelay(display_delay/portTICK_PERIOD_MS);
   for(int k=0;k<width;k++){
    digitalWrite(pins[k],1);
   }

  digitalWrite(clock,0);
  vTaskDelay(display_delay/portTICK_PERIOD_MS);
  digitalWrite(clock,1);
  
  }
  
  }
  
  }

//____________________________________________________________________________________________________

void game(void * parameters){// this is the void that game update loop will run 1.24fops 
  for(;;){




}
}
//_______________________________________________________________________________________________________
void loop() {
  
}
