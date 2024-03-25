#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

void bluetoothSendMessage(char *array);
void Adelante();
void Retroceder();
void Izquierda();
void Derecha();
void Stop();
void LeerBluetooth();
void LucesTraseras();
void LucesDelanteras();
void ApagarLucesDelanteras();
void ApagarLucesTraseras();
void Bocina();
void DireccionesTodas();
/* HC06 BLUETOOTH
 * TX-->PC6
 * RX-->PC7*/

int LED;
bool STLD = false;
bool STLB = false;

unsigned char data;

int main(void)
{

  SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

  // HC06 BLUETOOTH Pinleri
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  GPIOPinConfigure(GPIO_PC6_U3RX);
  GPIOPinConfigure(GPIO_PC7_U3TX);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

  GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
  UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE));
  UARTEnable(UART3_BASE);

  while (1)
  {

    LeerBluetooth();
    DireccionesTodas();
    LED = 0;
    if (STLD == true && STLB == true)
    {
      LeerBluetooth();
      DireccionesTodas(data);
      GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 192);
    }
    else if (STLD == false && STLB == true)
    {
      GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b01000000);
    }
    else if (STLD == true && STLB == false)
    {
      GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b10000000);
    }
  };
  UARTDisable(UART1_BASE);
}

void Adelante()
{
  LED = 2;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 9);
  bluetoothSendMessage("\nTiva send = ADELANTE\n");
  SysCtlDelay(100);
}

void Retroceder()
{
  LED = 4;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 6);
  bluetoothSendMessage("\nTiva send = REVERSA\n");
  SysCtlDelay(100);
}

void Derecha()
{
  LED = 8;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 5);
  bluetoothSendMessage("\nTiva send = DERECHA\n");
  SysCtlDelay(100);
}
void Izquierda()
{
  LED = 14;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 10);
  bluetoothSendMessage("\nTiva send = IZQUIERDA\n");
  SysCtlDelay(100);
}

void Stop()
{
  LED = 0;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, LED);
  bluetoothSendMessage("\nTiva send = STOP\n");
  SysCtlDelay(100);
}

void LucesDelanteras()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 128);
  STLD = true;
  if (data == 'U')
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 192);
    STLB = true;
  }
}
void ApagarLucesDelanteras()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
  STLD = false;
}

void LucesTraseras()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 64);
  STLB = true;
  if (data == 'W')
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 192);
    STLD = true;
  }
}
void ApagarLucesTraseras()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
  STLB = false;
}
void Bocina()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 32);
}
void bluetoothSendMessage(char *array)
{
  while (*array)
  {
    UARTCharPut(UART3_BASE, *array);
    array++;
  }
}

void DireccionesTodas()
{

  if (data == 'F')
  {
    Adelante();
  }
  else if (data == 'B')
  {
    Retroceder();
  }
  else if (data == 'R')
  {
    Derecha();
  }
  else if (data == 'L')
  {
    Izquierda();
  }
  else if (data == 'W')
  {
    LucesDelanteras();
  }
  else if (data == 'w')
  {
    ApagarLucesDelanteras();
  }
  else if (data == 'U')
  {
    LucesTraseras();
  }
  else if (data == 'u')
  {
    ApagarLucesTraseras();
  }
  else
  {
    Stop();
  }
}
void LeerBluetooth()
{
  while (!UARTCharsAvail(UART3_BASE));
  data = UARTCharGetNonBlocking(UART3_BASE);
}
