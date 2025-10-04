# Arduino Uno R3 — Direct Port Manipulation (Binary Version with OR/AND)

## 1. Overview

Direct port manipulation accesses the hardware registers (`PORTx`, `DDRx`, `PINx`) of the ATmega328P. Advantages:

* Significantly faster than `digitalWrite()` / `digitalRead()`.
* Atomic control of multiple pins at once.

Disadvantages:

* Less readable/portable code.
* Incorrect writing can affect other pins.
* Potential conflicts with timers/peripherals.

---

## 2. Pin ↔ Port Mapping

* **PORTD (PD0..PD7)**: D0=PD0, D1=PD1, D2=PD2, D3=PD3, D4=PD4, D5=PD5, D6=PD6, D7=PD7
* **PORTB (PB0..PB5)**: D8=PB0, D9=PB1, D10=PB2, D11=PB3, D12=PB4, D13=PB5
* **PORTC (PC0..PC5)**: A0=PC0, A1=PC1, A2=PC2, A3=PC3, A4=PC4, A5=PC5

---

## 3. Important Registers

* `DDRx`: 1=output, 0=input
* `PORTx`: set output level or enable pull-up
* `PINx`: read input, writing toggles the bit

---

## 4. Code Examples with Binary OR/AND/XOR

### 4.1 Set Pin as Output

```cpp
// D13/PB5 as output (DDRB bit5)
DDRB |= 0b00100000; // OR sets only PB5 as output, other bits remain unchanged
```

### 4.2 Set Pin HIGH / LOW

```cpp
// PB5 HIGH
PORTB |= 0b00100000; // OR: only bit5 HIGH, others unchanged

// PB5 LOW
PORTB &= ~0b00100000; // AND with inverted mask, bit5 LOW, others unchanged
```

### 4.3 Toggle Pin

```cpp
// Toggle PB5
PORTB ^= 0b00100000; // XOR inverts bit5
```

### 4.4 Set Multiple Pins

```cpp
// PB0=1, PB1=1, PB4=1 (others unchanged)
PORTB |= 0b00010011;

// PB2=0, PB3=0 (others unchanged)
PORTB &= ~0b00001100;
```

### 4.5 Set Pin as Input with Pull-Up

```cpp
// PD2 and PD3 input with Pull-Up
DDRD &= ~0b00001100; // input: 0
PORTD |= 0b00001100; // Pull-Up: 1
```

### 4.6 Read Pin

```cpp
bool state = (PIND & 0b00000100) != 0; // check bit2 PD2
```

### 4.7 Additional Examples

```cpp
// Turn all LEDs on PORTB off
PORTB &= ~0b00111111;

// Turn all LEDs on PORTB on
PORTB |= 0b00111111;

// Toggle all LEDs
PORTB ^= 0b00111111;
```
