/*
 * Muhammet Tayyip Çankaya
 * HC 06 Bluetooth
 */
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

/* HC06 BLUETOOTH
 * TX-->PC6
 * RX-->PC7*/

int LED;

int main(void)
{
    unsigned char data;

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // HC06 BLUETOOTH Pinleri
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE));
    UARTEnable(UART3_BASE);

    while (1)
    {
        while (!UARTCharsAvail(UART3_BASE))
            ;
        data = UARTCharGetNonBlocking(UART3_BASE);
        LED = 0;
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
        else
        {
            Stop();
        }
    };
    UARTDisable(UART1_BASE);
}

void Adelante()
{
    LED = 2;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 9);
    bluetoothSendMessage("\nTiva send = RED\n");
    SysCtlDelay(100);
}

void Retroceder()
{
    LED = 4;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 6);
    bluetoothSendMessage("\nTiva send = BLUE\n");
    SysCtlDelay(100);
}

void Derecha()
{
    LED = 8;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 5);
    bluetoothSendMessage("\nTiva send = GREEN\n");
    SysCtlDelay(100);
}
void Izquierda()
{
    LED = 14;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 10);
    bluetoothSendMessage("\nTiva send = WHITE\n");
    SysCtlDelay(100);
}

void Stop()
{
    LED = 0;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, LED);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, LED);
    bluetoothSendMessage("\nTiva send = NO\n");
    SysCtlDelay(100);
}
void bluetoothSendMessage(char *array)
{
    while (*array)
    {
        UARTCharPut(UART3_BASE, *array);
        array++;
    }
}
