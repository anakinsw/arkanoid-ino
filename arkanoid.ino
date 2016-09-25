#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#define __CS 10
#define __DC 9
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
TFT_ILI9163C display = TFT_ILI9163C(__CS, __DC);
float p = 3.1415926;


bool filas[4][12]={
                    {true,true,true,true,true,true,true,true,true,true,true,true},
                    {true,true,true,true,true,true,true,true,true,true,true,true},
                    {true,true,true,true,true,true,true,true,true,true,true,true},
                    {true,true,true,true,true,true,true,true,true,true,true,true}
                  };

int x_pala=40;

int x_pelota=80;
int y_pelota=60;

int dir_x=-1;
int dir_y=1;

int puntos=0;
int vidas=5;


const int btnRojo = 3;     // the number of the pushbutton pin
const int btnVerde =  4;


void setup() {
  pinMode(btnRojo, INPUT); 
  pinMode(btnVerde, INPUT); 
    
  display.begin(); //iniciamos display
  display.clearScreen();
  display.setCursor(0,0);
  display.setTextColor(RED);  
  display.setTextSize(1);
  display.println("Puntos: 10   Nivel: 1");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  display.fillRect(0,0,128,8, BLACK);
  display.setCursor(1,0);
  display.setTextColor(RED);  
  display.setTextSize(1);
  display.print("Puntos: ");
  display.println(puntos); 

  display.setCursor(80,0);
  display.setTextColor(GREEN);
  display.print("Vidas:");
  display.print(vidas); 
  
  dibuja_linea_ladrillos(1,GREEN);
  dibuja_linea_ladrillos(2,CYAN);
  dibuja_linea_ladrillos(3,RED);
  dibuja_linea_ladrillos(4,YELLOW);
  
  detectar_colisiones();
  actualiza_pelota();
  
  //x_pala=x_pelota-20;
  


   int a=digitalRead(btnRojo);
   int b=digitalRead(btnVerde);
   
    borrar_pala();
    if (a==HIGH){
    x_pala--;  
    }
    if (b==HIGH){
    x_pala++;  
    }
    dibuja_pala();


  delay(10);
}


void detectar_colisiones(){
  int fila;

 //detecta la colision del ladrillo
  for (int b=0;b<5;b++){
    for (int a=0;a<12;a++){
      fila=b+1;
      if(filas[b][a]){ 
        //24
        //(11*a)
        int yfila=20 + (5*fila);
        if( (x_pelota>(11*a) && x_pelota<((11*a)+10)) && (y_pelota>yfila && y_pelota<(yfila+4))  ){
          dir_y=-dir_y;
          filas[b][a]=false;
          puntos=puntos+5;
         // display.fillRect(x_pelota,y_pelota,10,10, BLUE);

          
          //dir_x=-dir_x;
        }
      }
     
    }
  }


 //detectar colision de la pala
if( (x_pelota>x_pala && x_pelota<(x_pala+40)) && (y_pelota>122)  ){
  dir_y=-dir_y;
  borrar_pelota();
  y_pelota=y_pelota+(dir_y*2);
   puntos=puntos+1;
}
 

  
}


void dibuja_linea_ladrillos(int fila, int color){
  
   for (int a=0;a<12;a++){
    if(filas[fila-1][a]){  
      dibuja_ladrillo((11*a),20 + (5*fila),color);
    }else{
      dibuja_ladrillo((11*a),20 + (5*fila),BLACK);
    }
  
  }
}

void dibuja_ladrillo(int x, int y, int color){
  int w,h;
  w=10;
  h=4;
  display.fillRect(x,y,w,h, color);
}

void reset_pelota(){
   borrar_pala();
   
   x_pala=40;

   x_pelota=80;
   y_pelota=50;
  
   dir_x=-abs(dir_x);
   dir_y=abs(dir_y);

   
}

void actualiza_pelota(){
  borrar_pelota();
    x_pelota=x_pelota+dir_x;
    y_pelota=y_pelota+dir_y;

    if (x_pelota>125){
      dir_x=-dir_x;
    }
     if (x_pelota<3){
      dir_x=abs(dir_x);
    }

    if (y_pelota>127){
     // dir_y=-1;
      vidas=vidas -1;
      display.setCursor(5,80);
      display.setTextColor(RED);  
      display.setTextSize(2);
      display.print("BOLA FUERA");
      delay(1000);
      display.setCursor(5,80);
      display.setTextColor(BLACK);
      display.print("BOLA FUERA");
      reset_pelota();
       if(vidas<0){
         display.setCursor(10,80);
        display.setTextColor(RED);
        display.print("GAME OVER");
        delay(90000);
        }
    }
     if (y_pelota<1){
      dir_y=abs(dir_y);
    }
  dibuja_pelota();
}

void borrar_pelota(){
   display.fillCircle(x_pelota, y_pelota, 3,BLACK);
}

void dibuja_pelota(){
   display.fillCircle(x_pelota, y_pelota, 3,WHITE);
}



void borrar_pala(){
  int w,h;
  w=128;
  h=4;
  display.fillRect(0,124,w,h, BLACK);
}
void dibuja_pala(){
  int w,h;
  w=40;
  h=4;
  if (x_pala<1){
    x_pala=0;
   }

  if (x_pala>120){
    x_pala=120;
   }
   
  display.fillRect(x_pala,124,w,h, WHITE);
}
  
 
