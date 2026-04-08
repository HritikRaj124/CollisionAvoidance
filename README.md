# Collision Avoidance Embedded Controller (STM32)

A bare‑metal embedded control system developed on **STM32F407 (Cortex‑M4F)**, demonstrating **safety‑critical sequencing**, **closed‑loop control**, and **low‑level hardware interaction**.  
The project follows controller architectures commonly used in **automotive and aerospace systems**, including engine and actuator control units.

---

## Project Overview

This project implements a **finite‑state‑machine‑based control system** that regulates vehicle velocity in response to obstacle proximity.  
While the application scenario uses a collision‑avoidance use case, the underlying architecture reflects **real‑time embedded controller patterns** applicable to propulsion, actuation, and safety‑critical systems.

Key focus areas:
- Deterministic behavior
- Low‑level register programming
- Control‑system correctness
- Debugging of real runtime hardware issues

---

## System Architecture

### Key Modules
- **FSM (`fsm.c`)**  
  Safety and sequencing logic; determines target operating state and velocity setpoint.
- **Controller (`controller.c`)**  
  PI controller regulating measured velocity toward the target velocity.
- **PWM Driver (`pwm.c`)**  
  Register‑level configuration of timers and GPIO for actuator control.
- **UART Driver (`uart.c`)**  
  Bare‑metal UART implementation for telemetry and debugging.
- **Application (`main.c`)**  
  Orchestrates control flow and execution order.

---

## Technical Highlights

### Bare‑Metal Programming
- No HAL or middleware used
- Direct register access for RCC, GPIO, TIM, and USART peripherals
- Precise control over timing and behavior

### Finite State Machine
States:
- `IDLE`
- `BRAKING`
- `FULL_BRAKE`
- `RELEASED`

FSM enforces deterministic transitions and clearly separates **safety logic from control logic**.

### Correct Closed‑Loop Control Design
- **Controlled variable:** Velocity
- **Setpoint:** Computed by FSM based on distance
- **Feedback:** Measured velocity
- **Control effort:** PWM duty cycle

This matches industry‑standard control architectures used in **engine throttle, turbopump speed, and valve control loops**.

### Floating‑Point Debugging (Cortex‑M4F)
- Identified and resolved a **silent HardFault** caused by FPU not being enabled
- Enabled CP10 and CP11 via `SCB_CPACR`
- Demonstrates understanding of runtime hardware configuration

---

## Testing & Emulation

- Tested using **Renode** emulator
- UART output visualized via Renode UART Analyzer
- PWM behavior verified through timer register inspection
- Emulator limitations (e.g. timer preload bits) identified and worked around without breaking hardware‑correct design

---

## Challenges Faced

- Debugging silent runtime faults due to FPU enablement
- Correcting control‑architecture mistakes through control‑theory review
- Adapting design to emulator limitations while preserving correctness

---

## Future Work

Possible extensions include:
- RTOS‑based task scheduling (FreeRTOS)
- Interrupt‑driven control loop
- Fixed‑point PI controller for deterministic execution
- Expanded FSM with FAULT / ABORT states
- Hardware‑in‑the‑Loop (HIL) testing
- Integration with real sensors and actuators

---

## Skills Demonstrated

- Embedded C (bare‑metal)
- Real‑time control systems
- FSM‑based sequencing
- Low‑level driver development
- Debugging runtime MCU faults
- Architecture design for safety‑critical systems
- Emulator‑based validation

---

## Author

**Hritik Raj**  
