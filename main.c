#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"  //Contiene las API para configurar y manejar los GPIO
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"  //manejo de UART
#include "utils/uartstdio.c"
#include "inc/hw_uart.h"
#include <string.h>
#include "driverlib/interrupt.h"  //Se proporcionan API para habilitar y
//habilitar interrupciones, registrar manejadores de interrupciones y
//establecer la prioridad de las interrupciones.git

char car;
int i =0;
uint8_t Status;
uint32_t ui32Status;

void UARTIntHandler(void) {
  ui32Status = UARTIntStatus(UART1_BASE, true);  //get interrupt staturs
  UARTIntClear(UART1_BASE, ui32Status);          //Clear the asserted interrupts
  while (UARTCharsAvail(UART1_BASE)) {
    car = UARTCharGetNonBlocking(UART1_BASE);
    UARTCharPut(UART1_BASE, car);
    SysCtlDelay(SysCtlClockGet() / (1000 * 3));  //delay ~1msec
  }
}
int main(void) {
  SysCtlClockSet(SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_2_5);
  //*************************UART**********************//
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
  //Pines para conectar el modulo Bluetooth PC4 y PC5
  GPIOPinConfigure(GPIO_PC4_U1RX);
  GPIOPinConfigure(GPIO_PC5_U1TX);
  UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
  UARTStdioConfig(1, 9600, 16000000);
  //************************GPIO*******************************//
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3);
  //*********************Interrupcin*****************************//
  IntMasterEnable();
  IntEnable(INT_UART1);
  UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

  while (1) {
//SysCtlDelay(8000000);
 //     UARTprintf("NINGUNO");
   //   UARTprintf("\n");
    switch (car) {
      case 'x':
          GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3, 2 );
        break;
      case 'y':
          GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3, 4 );
     break;
     case 'z':
         GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3, 8);
       break;
     case 'a':
         GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3, 12 );
         break;
       }
       car = UARTCharGetNonBlocking(UART1_BASE);
       UARTIntClear(UART1_BASE, ui32Status);  //Clear
    }
  }


