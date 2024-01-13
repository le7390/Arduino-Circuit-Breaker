# Arduino-Circuit-Breaker
The primary goal of this project is to create a system that monitors the voltage of the power supply to ensure that the device connected to it does not draw too much power or contain a short circuit. The circuit will be temporarily turned off during a fault.

## Usage
This is used in an environment where the power supply does not have short circuit protection and where a short circuit is momentary, such as tinkering with electronics and accidentally shorting the terminals.

## How it works
1. Two resistors create a voltage divider that the Arduino uses to monitor the load. When a high amperage device is used, the voltage drops.
2. The Arduino uses this data and determines if it is a short, which sends a signal to the relay to turn off immediately. If a high load is consumed over time, the power will turn off after a longer period of time preventing damage to the wiring.
3. After the power is shut off, there is a 10 second delay before it automatically turns the power back on. If the power gets shut off three times in a short period of time, the power will be turned off and locked out, requiring a manual reset.

## Wiring Diagram
![Wiring Diagram](https://github.com/le7390/Arduino-Circuit-Breaker/assets/60799129/b8efd1eb-e6ad-400c-983a-68f13119a893)
