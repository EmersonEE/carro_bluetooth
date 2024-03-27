# Carro Bluetooth - TIVA C TM4C123GH6PM

Proyecto final del curso de Practica Electonica 3 - **USAC**

![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white) ![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white) ![Mega.nz](https://img.shields.io/badge/Mega-%23D90007.svg?style=for-the-badge&logo=Mega&logoColor=white) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) [![Twitter](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/EmersonPrez15)

# Temario Proyecto

- [Introducción](#introducción)
- [TIVA C TM4C123GH6PM](#tiva-c-tm4c123gh6pm)
- [Materiales](#materiales)
- [Bluetooth RC Controller](#bluetooth-rc-controller)
- [PWM](#video-del-funcionamiento)
- [Placa KiCad](#placa-kicad)
- [Video de Funcionamiento](#video-del-funcionamiento)

# Introducción

# Tiva C TM4C123GH6PM

La Tiva C TM4C123GH6PM es un microcontrolador de la familia Tiva C Series de Texas Instruments. Está basado en el núcleo ARM Cortex-M4, lo que significa que ofrece un alto rendimiento de procesamiento y una amplia gama de capacidades periféricas. Algunas características clave de la Tiva C TM4C123GH6PM incluyen:

- Núcleo ARM Cortex-M4: Ofrece un rendimiento de procesamiento de hasta 80 MHz, con soporte para instrucciones de punto flotante y DSP (Procesamiento Digital de Señales).

- Memoria: Incorpora una memoria Flash de hasta 256 KB para almacenamiento de código, y 32 KB de memoria SRAM para almacenamiento de datos.

- Periféricos integrados: Incluye una amplia variedad de periféricos integrados, como UARTs, I2C, SPI, GPIO, PWM, ADC (convertidor analógico a digital), y timers, lo que permite una gran flexibilidad en el diseño de sistemas embebidos.

- Interfaces de comunicación: Admite varios protocolos de comunicación, como UART, I2C, SPI y USB, lo que facilita la comunicación con otros dispositivos y sistemas.

## Pinout de la Tiva

![Pinout de la Tiva](https://arduining.com/wp-content/uploads/2014/04/tiva_c_launchpad_pinout_001b.jpg)

[Temario](#temario-proyecto)

# Materiales

Para este proyecto se utilizaron materiales importantes como el modulo bluetooth HC-06, el puente H L298N, Motoreductores.

### Modulo Bluetooth HC-06

- **Módulo Bluetooth HC-06**:
El módulo Bluetooth HC-06 es un dispositivo que permite la comunicación inalámbrica mediante la tecnología Bluetooth. Este módulo actúa como un puente entre dispositivos que utilizan Bluetooth y microcontroladores u otros sistemas embebidos. Es comúnmente utilizado en proyectos de electrónica para habilitar la comunicación entre un microcontrolador y un dispositivo móvil, como un teléfono inteligente o una tableta.
<div align="center"">
<img src="https://laelectronica.com.gt/image/cache/catalog/Productos/M%C3%B3dulos/modulo-bluetooth-hc-06-2-1200x1200.jpg" alt="Descripción de la imagen" width="150" height="150" />
</div>

### Puente H L298N

- **Driver puente H L298N**:
El driver puente H L298N es un circuito integrado utilizado para controlar motores de corriente continua (DC) y motores paso a paso. Funciona como un puente H, que es un circuito que permite controlar la dirección y la velocidad de un motor DC. El L298N puede manejar corrientes de hasta 2 amperios por canal y voltajes de alimentación de hasta 35 voltios.
<div align="center"">
<img src="https://m.media-amazon.com/images/I/61VkNn0PcaL.jpg" alt="Descripción de la imagen" width="150" height="150" />
</div>

### Motoreductor

- **Motoreductores**:
Los motoreductores son dispositivos que combinan un motor eléctrico con una caja de engranajes para reducir la velocidad y aumentar el torque de salida. Estos son componentes comunes en una amplia variedad de aplicaciones, desde robots y vehículos controlados por radio hasta equipos industriales y electrodomésticos.
<div align="center"">
<img src="https://http2.mlstatic.com/D_NQ_NP_791502-MLM48603564951_122021-O.webp" alt="Descripción de la imagen" width="150" height="150" />
</div>

[Temario](#temario-proyecto)

# Bluetooth RC Controller

La aplicación que se utilizo para poder controlar el dispositivo fue **[Bluetooth RC Controller](https://bluetooth-rc-car.softonic.com/android)**, es una aplicación que permite controlar dispositivos electrónicos a través de una conexión Bluetooth desde un dispositivo móvil, como un teléfono inteligente o una tableta. La aplicación actúa como un control remoto, lo que significa que puedes enviar comandos desde tu dispositivo móvil a otro dispositivo que esté equipado con tecnología Bluetooth.

**[Descarga la Aplicación](https://mega.nz/file/lItFECAC#N41DOoMR8TuIGPPzliTAuHlfmP3obIDxUFIn1bvfIek)**

<div align="center"">
<img src="https://images.sftcdn.net/images/t_app-cover-l,f_auto/p/4e2b2251-80eb-4e9b-8a72-1dc68041c662/3160506404/bluetooth-rc-car-screenshot.png" alt="Descripción de la imagen" width="300" height="150" />
</div>

[Temario](#temario-proyecto)

# PWM

El PWM (Pulse Width Modulation) se utlizo para poder controlar la velocidad de los motoreductores ya que el PWM es una técnica utilizada en electrónica para controlar la cantidad de energía entregada a un dispositivo o carga, como por ejemplo un motor, una bombilla LED o un altavoz.
Consiste en variar el ancho de un pulso de señal eléctrica (la duración en que la señal está en alto) mientras se mantiene constante la frecuencia de repetición de estos pulsos.

<!-- ![Pinout de la Tiva](https://solectroshop.com/img/cms/PWM/Analogico_deseado.webp) -->

<div align="center"">
<img src="https://solectroshop.com/img/cms/PWM/Analogico_deseado.webp" alt="Descripción de la imagen" width="400" height="225" />
</div>

[Temario](#temario-proyecto)

# Placa KiCad

[Temario](#temario-proyecto)

# Video del Funcionamiento

[Temario](#temario-proyecto)

codigo para agregar videos

[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE)

<!--
  <iframe width="560" height="315" src="https://www.youtube.com/embed/HOG0K7A2Ea4" title="YouTube video player"
    frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
    allowfullscreen></iframe>

    <iframe width="560" height="315" src="https://www.youtube.com/embed/LHhnxjv8vxk?si=h4xPD6NWSBa-INWs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

    -->
