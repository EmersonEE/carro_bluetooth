#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include "driverlib/pwm.h"

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
void ApagarBocina();
void ConfiguracionLuces();
void Sensores();
/* HC06 BLUETOOTH
 * TX-->PC6
 * RX-->PC7*/

int LED;
bool STLD = false;
bool STLB = false;
bool STBO = false;
unsigned long pwmNow = 0;
unsigned char data;
int valor = 0;

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
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); // Changed to use port D
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R = 0x0f;
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  // GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Entradas
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

  GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
  UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE));
  UARTEnable(UART3_BASE);
  GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);
  GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  // Configure PWM Clock to match system
  SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

  // Enable the peripherals used by this program.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  // The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins
  // Configure PD0, PD1, PD2 Pins as PWM
  GPIOPinConfigure(GPIO_PD0_M1PWM0);                        // Changed to use port D pins
  GPIOPinConfigure(GPIO_PD1_M1PWM1);                        // Changed to use port D pins
                                                            // GPIOPinConfigure(GPIO_PD2_M1PWM2); // Changed to use port D pins
  GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Changed to use port D pins

  // Configure PWM Options
  PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
  PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

  // Set the Period (expressed in clock ticks)
  PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 400);
  PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, 400);

  // Set PWM duty-50% (Period /2)
  PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 200);
  PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, 200);
  // PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, 100);

  // Enable the PWM generator
  PWMGenEnable(PWM1_BASE, PWM_GEN_0);
  PWMGenEnable(PWM1_BASE, PWM_GEN_1);

  // Turn on the Output pins
  PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT, true);

  while (1)
  {


    LeerBluetooth();
    DireccionesTodas();

    LED = 0;
    ConfiguracionLuces();
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, pwmNow);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, pwmNow);
  };
  UARTDisable(UART1_BASE);
}

void Adelante()
{
  LED = 2;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0b00000101);
  bluetoothSendMessage("\nTiva send = ADELANTE\n");
  SysCtlDelay(100);
}

void Retroceder()
{
  LED = 4;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0b00001010);
  bluetoothSendMessage("\nTiva send = REVERSA\n");
  SysCtlDelay(100);
}

void Derecha()
{
  LED = 8;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0b00001001);
  bluetoothSendMessage("\nTiva send = DERECHA\n");
  SysCtlDelay(100);
}
void Izquierda()
{
  LED = 12;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0b00000110);
  bluetoothSendMessage("\nTiva send = IZQUIERDA\n");
  SysCtlDelay(100);
}

void Stop()
{
  LED = 0;
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
  GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
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
  STBO = true;
}

void ApagarBocina()
{
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
  STBO = false;
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
  else if (data == 'V')
  {
    Bocina();
  }
  else if (data == 'v')
  {
    ApagarBocina();
  }
  else if (data == '1')
  {
    pwmNow = 40;
  }
  else if (data == '2')
  {
    pwmNow = 80;
  }
  else if (data == '3')
  {
    pwmNow = 120;
  }
  else if (data == '4')
  {
    pwmNow = 160;
  }
  else if (data == '5')
  {
    pwmNow = 200;
  }
  else if (data == '6')
  {
    pwmNow = 240;
  }
  else if (data == '7')
  {
    pwmNow = 280;
  }
  else if (data == '8')
  {
    pwmNow = 320;
  }
  else if (data == '9')
  {
    pwmNow = 360;
  }
  else if (data == 'q')
  {
    pwmNow = 400;
  }
  else if (data == '0')
  {
    pwmNow = 0;
  }
  else
  {
    Stop();
  }
}

void ConfiguracionLuces()
{
  if (STLD == true && STLB == true && STBO == true)
  {
    LeerBluetooth();
    DireccionesTodas();
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b11100000);
  }
  else if (STLD == false && STLB == false && STBO == true)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b00100000);
  }
  else if (STLD == false && STLB == true && STBO == false)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b01000000);
  }
  else if (STLD == false && STLB == true && STBO == true)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b01100000);
  }
  else if (STLD == true && STLB == false && STBO == false)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b10000000);
  }
  else if (STLD == true && STLB == false && STBO == true)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b10100000);
  }
  else if (STLD == true && STLB == true && STBO == false)
  {
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0b11000000);
  }
}
void Sensores(){
    valor = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2);
    if ( valor ==  1)
    {
    Retroceder();
    SysCtlDelay(10000000);

    }
    else if ( valor ==  16)
    {
    Retroceder();
    SysCtlDelay(10000000);
    Adelante();
    SysCtlDelay(10000);
    }
    else if ( valor ==  0)
    {
    Retroceder();
    SysCtlDelay(10000000);
    }
    else
    {
        DireccionesTodas();
    }

}
void LeerBluetooth()
{
  while (!UARTCharsAvail(UART3_BASE)){
      Sensores();
  }
  data = UARTCharGetNonBlocking(UART3_BASE);
}


