/*
* Programa que incorpora ina funcion que evita el "rebote" en interruptores
*
*/

#include <LiquidCrystal_I2C.h>

// Seteamos columnas y filas del display (también vienen de 20x4)
int lcdColumns = 16;
int lcdRows = 2;

// seteo de dirección,columnas,filas del  LCD 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

const int pulsador = 4; // Entrada digital para el pulsador
const int tiempoAntirrebote = 10; // tiempo en ms para evitar el rebote
 
int cuenta = 0;
int estadoBoton;
int estadoBotonAnterior;

void setup(){
  // inicializo LCD
  lcd.init();
  // enciende backlight                      
  lcd.backlight();
  pinMode(pulsador, INPUT_PULLUP);
}

void loop(){
  

  estadoBoton = digitalRead(pulsador);
   
    if(estadoBoton != estadoBotonAnterior)
    {
      if(antirrebote(pulsador))
      {
        cuenta++;
        lcd.setCursor(13,0);
        lcd.print(cuenta);  // Se muestra a través del LCD el nº de veces que presionamos el pulsador
      }
    }  
    estadoBotonAnterior = estadoBoton;
}

// Función que evita el rebote del pulsador
  boolean antirrebote(int pin)
  {
    int contador = 0;
    boolean estado;
    boolean estadoAnterior;
   
    do
    {
      estado = digitalRead(pin);
      if(estado != estadoAnterior)
      {
        contador = 0;
        estadoAnterior = estado;
      }
      else
      {
        contador = contador+ 1;
      }
      delay(1);
    } while(contador < tiempoAntirrebote);
   
    return estado;
  }
