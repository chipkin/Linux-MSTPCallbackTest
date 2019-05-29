# Linux MSTP Callback Test

This application is an example of how to test the MSTP callback functions on Linux. This application can be be ported to other hardware to test to ensure that it will support the requirements of BACnet MSTP.

This application is designed to work in tandem with [Linux High Speed Serial Monitor](https://github.com/chipkin/Linux-HighSpeedSerialMonitor)

## Testing instructions

1. Connect a USB RS485 converter to a Linux computer.
2. Connect the USB RS384 [D+], [D-], [GND] to the unit under test [D+], [D-], [GND].
3. Run [Linux High Speed Serial Monitor](https://github.com/chipkin/Linux-HighSpeedSerialMonitor) on a Linux computer.
4. Run the *MSTP Callback Test* on the unit under test.

## Example output of *MSTP Callback Test*

```txt
./test
FYI: MSTP Callback Test. Version: 0.0.0.1
FYI: Test 1: Internal high speed timer
FYI: Testing high speed timer. timerMS=10
     Success. timerMS: 10, millisecondTimer: 10.041
FYI: Testing high speed timer. timerMS=20
     Success. timerMS: 20, millisecondTimer: 20.172
FYI: Testing high speed timer. timerMS=40
     Success. timerMS: 40, millisecondTimer: 40.14
FYI: Testing high speed timer. timerMS=80
     Success. timerMS: 80, millisecondTimer: 80.048
FYI: Testing high speed timer. timerMS=101
     Success. timerMS: 101, millisecondTimer: 101.327
FYI: Internal high speed timer success

FYI: Connecting to serial port. SerialPort=/dev/ttyS4
FYI: Connectec to serial port

FYI: Test 2: Sending inital test byte. buffer='0' 0x30
FYI: Check the serial port for the results to this test.

FYI: Test 3: Sleep timer
FYI: Check the serial port for the results to this test.

FYI: Test 4: Action required ! - Send a byte to the serial port...
FYI: Byte recived. buffer='f' 0x66
FYI: Sending recived byte. buffer='f' 0x66
FYI: Success. All tests compleat.

```

## Example output from Linux High Speed Serial Monitor

```txt

FYI: High speed serail monitor. Version: 0.0.0.1
FYI: Connecting to serial port. SerialPort=/dev/ttyS5, BaudRate=38400
FYI: Connected to serial port

|  Time (ms) |     CHAR |      HEX |
* ---------- * -------- * -------- *
|   3071.264 |        0 |       00 |
|      0.628 |        a |       0a |
|     10.392 |        b |       0b |
|     10.531 |        c |       0c |
|     10.931 |        d |       0d |
|     21.001 |        e |       0e |
|     31.027 |        f |       0f |
|     40.892 |        g |       0g |
|     50.499 |        h |       0h |

```

## Building

A included [makefile](https://github.com/chipkin/Linux-MSTPCallbackTest/blob/master/makefile) can be built with [GCC](https://gcc.gnu.org/)

```bash
make all
```

This project also auto built using [Gitlab CI](https://docs.gitlab.com/ee/ci/) on every commit.

## Binary

A compiled version of the serial monitor is included in this repo. [mstpCallbackTest](https://github.com/chipkin/Linux-MSTPCallbackTest/blob/master/mstpCallbackTest)

## Change log

### 2019 May 23

- 0.0.2 Added CI build number. Updated make file to include "all", and "Clean" steps. Added Gitlab CI auto builds.
- 0.0.1 Initial version
