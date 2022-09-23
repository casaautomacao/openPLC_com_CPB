#include <stdlib.h>
extern "C" {
#include "openplc.h"
}
#include "Arduino.h"
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;


//OpenPLC HAL for Arduino Uno and Arduino Nano (old) form factor (Uno, Leonardo, Nano, Micro and Zero)

/******************PINOUT CONFIGURATION*******************

Ver documentação Crescer

**********************************************************/

//Define the number of inputs and outputs for this board (mapping for the Arduino Uno)
#define NUM_DISCRETE_INPUT          8
#define NUM_ANALOG_INPUT            8
#define NUM_DISCRETE_OUTPUT         12
#define NUM_ANALOG_OUTPUT           3


//Create the I/O pin masks
uint8_t pinMask_DIN[] = {5, 6, 7, 8, 13, 14, 15, 2, 3, 4, 5, 6};
uint8_t pinMask_AIN[] = {A0, A1, A2, A3, A4, A5, A6, A7};
uint8_t pinMask_DOUT[] = {9, 10, 11, 12, 0, 1, 2, 4, 7, 8, 12, 13}; 
uint8_t pinMask_AOUT[] = {9, 10, 11};

void hardwareInit()
{


   mcp.begin();


    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
		uint8_t pin = pinMask_DIN[i];
     

         if (i<7)
{
mcp.pinMode(pin, INPUT);
mcp.pullUp(pin, HIGH);
}
         else
{
 pinMode(pin, INPUT_PULLUP);
}

    }
    






    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
		uint8_t pin = pinMask_AIN[i];
        pinMode(pin, INPUT);
    }
    




    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {


		uint8_t pin = pinMask_DOUT[i];
     
         if (i<8) mcp.pinMode(pin, OUTPUT);
         else pinMode(pin, OUTPUT);

    }




    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
		uint8_t pin = pinMask_AOUT[i];
        pinMode(pin, OUTPUT);
    }



}

void updateInputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
		uint8_t pin = pinMask_DIN[i];

int teste = 1;

if (i<11) teste = 1-mcp.digitalRead(pin);
else teste = 1-digitalRead(pin);

	 if (bool_input[i/8][i%8] != NULL) *bool_input[i/8][i%8] = teste;




    }




    
    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
		uint8_t pin = pinMask_AIN[i];
        if (int_input[i] != NULL)
            *int_input[i] = (analogRead(pin) * 64);
    }


}

void updateOutputBuffers()
{


    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
		uint8_t pin = pinMask_DOUT[i];



         if (i<8) 
		{
       	 if (bool_output[i/8][i%8] != NULL) 
             mcp.digitalWrite(pin, *bool_output[i/8][i%8]);
		}
	    else
		{
           if (bool_output[i/8][i%8] != NULL) 
           digitalWrite(pin, *bool_output[i/8][i%8]);


		}


    }






    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
		uint8_t pin = pinMask_AOUT[i];
        if (int_output[i] != NULL) 
            analogWrite(pin, (*int_output[i] / 256));
    }
}
