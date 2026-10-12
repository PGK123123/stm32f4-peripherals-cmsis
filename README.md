# STM32F401 Peripheral Drivers & Laboratory Projects (Pure CMSIS)

[![MCU](https://img.shields.io/badge/MCU-STM32F401CCU6-blue.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32f401cc.html)
[![Core](https://img.shields.io/badge/Core-ARM%20Cortex--M4%20(84MHz)-green.svg)]()
[![Architecture](https://img.shields.io/badge/Architecture-Bare--Metal%20%2F%20CMSIS-orange.svg)]()
[![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE%20%2F%20GCC-lightblue.svg)]()

A comprehensive suite of bare-metal embedded drivers and systems programming projects developed on pure **CMSIS** (direct hardware register manipulation) for the **STM32F401** (ARM Cortex-M4) microcontroller.

---

## 📚 Laboratory Projects Overview

| Module | Focus Peripherals | Key Implementation Details |
| :--- | :--- | :--- |
| **[Lab 1: GPIO & SysTick](./lab1/)** | RCC, GPIO, SysTick | Clock tree setup (HSI / HSE / PLL), multi-channel LED sequencing, button handling, non-blocking timing. |
| **[Lab 2: Timers, PWM & ADC](./lab2/)** | TIM, PWM, ADC1, EXTI/TIM4 | Multi-channel PWM brightness control, hardware timer-based button debouncing (`TIM4`), analog potentiometer acquisition. |
| **[Lab 3: ADC + DMA + FPU](./lab3/)** | ADC1, DMA, FPU, USART2 | Multi-channel ADC circular scanning, zero-CPU DMA streaming, hardware FPU mathematical scaling, USART telemetry. |
| **[Lab 4: I2C, OLED & Encoder](./lab4/)** | I2C, SSD1306, TIM (Encoder), RGB PWM | I2C master driver, SSD1306 128x64 graphic framebuffer & font engine, quadrature rotary encoder tracking, RGB LED control. |

---

## 🛠 Deep Dive into Lab Modules

### 🔹 Lab 1: Basic I/O, Clocking & SysTick
- **RCC Configuration:** Pure register setup for HSI (16 MHz), HSE (25 MHz), and PLL configurations up to maximum system frequency.
- **Atomic Pin Control:** Fast bit-set/reset using `GPIOx->BSRR`.
- **System Timer:** Millisecond non-blocking delay engine via Cortex-M4 `SysTick` registers (`STK_CTRL`, `STK_LOAD`, `STK_VAL`).

### 🔹 Lab 2: Timer PWM, Hardware Debounce & ADC
- **PWM Channels:** Timer compare registers (`TIMx->CCRx`) configured in PWM Mode 1 with variable duty cycle.
- **Hardware Button Debouncing:** Elimination of contact bounce via hardware timer interval tracking (`TIM4`) without blocking CPU execution.
- **Analog Acquisition:** Single-conversion ADC reading from channel `ADC1_IN1` (PA1).
- **Clock Invariance:** Dynamic adaptation of timer prescalers and ADC sample times to maintain consistent behavior across HSI, HSE, and PLL modes.

### 🔹 Lab 3: High-Performance ADC Streaming via DMA & FPU
- **DMA Streaming:** Autonomous transfer of ADC multi-channel conversion results directly into RAM circular buffer using DMA1/DMA2 streams.
- **Hardware FPU Activation:** Access granted to Coprocessor CP10 and CP11 via `SCB->CPACR` for single-cycle IEEE 754 floating-point operations.
- **Telemetry:** Continuous formatted packet transmission over `USART2` at 115200 baud.

### 🔹 Lab 4: I2C Graphic Display & Hardware Rotary Encoder
- **I2C Master Driver:** Full implementation of START/STOP conditions, address phase, ACK/NACK verification, and data transfer on `I2C1`.
- **SSD1306 OLED Engine:** Low-level graphics subsystem supporting strings, integer formatting, custom font glyphs, and partial/full buffer redraws.
- **Quadrature Encoder Interface:** Timer configured in Encoder Interface Mode (`TIMx->SMCR[2:0] = 0b011`) decoding both TI1 and TI2 channels with direction and speed detection.
- **Interactive RGB Subsystem:** Real-time color wheel adjustment via rotary encoder inputs.

---

## 📁 Repository Structure

```text
├── lab1/                     # Lab 1: GPIO, RCC Clock Tree & SysTick
│   ├── Inc/ & Src/           # CMSIS sources & headers
│   └── STM32F401CCUX_FLASH.ld# Linker script
├── lab2/                     # Lab 2: Timers, PWM & Hardware Debounce
│   ├── Inc/ & Src/
│   └── STM32F401CCUX_FLASH.ld
├── lab3/                     # Lab 3: ADC + DMA Streaming + Hardware FPU
│   ├── Inc/ & Src/
│   └── STM32F401CCUX_FLASH.ld
├── lab4/                     # Lab 4: I2C Master, SSD1306 OLED & Encoder
│   ├── Inc/ & Src/
│   └── STM32F401CCUX_FLASH.ld
├── docs/                     # Course manuals, reference manuals & datasheets
│   ├── мпусу_stm32f4.pdf     # University course manual
│   ├── rm0368-...pdf         # STM32F401 Reference Manual
│   ├── pm0214-...pdf         # Cortex-M4 Programming Manual
│   └── stm32f401cc.pdf       # STM32F401CC Datasheet
└── .gitignore                # Filters out compiler output (Debug/Release)
```

---

## 🚀 Building in STM32CubeIDE

Each laboratory directory (`lab1`, `lab2`, `lab3`, `lab4`) is a standalone project:
1. Open **STM32CubeIDE**.
2. Select **File -> Import... -> General -> Existing Projects into Workspace**.
3. Point to the desired folder (`lab1` .. `lab4`).
4. Click **Finish**, build with **Ctrl+B**, and flash via **ST-Link (SWD)**.

---

## 📄 License
Educational and laboratory project under the MIT License.
