/**
 * MSTP Callback Test
 * --------------------------------------
 * This application is to used to test the MSTP callback function on variouse 
 * hardware platforms. 
 * 
 * This application is built to work with the Linux-HighSpeedSerialMonitor 
 * application. https://github.com/chipkin/Linux-HighSpeedSerialMonitor
 * 
 * Created by: Steven Smethurst 
 * Created on: May 22, 2019 
 * Last updated: May 22, 2019 
 */
#include "linuxMSTPFunctions.h"
#include <iostream> // std::cout, std::ios
#include <stdio.h>

static const char* APPLICATION_VERSION_MAJOR = "0.0.0.1";

static const char* CONFIGURATION_SERIAL_PORT = "/dev/ttyS4";
static const uint8_t CONFIGURATION_TIMER_RANGE_MS = 1;

bool testTimer(uint32_t timerMS)
{
    uint32_t microsecondTimer;
    uint32_t millisecondTimer;

    std::cout << "FYI: Testing high speed timer. timerMS=" << timerMS << std::endl;

    mstp_TimerReset();
    mstp_Sleep(timerMS);
    microsecondTimer = mstp_TimerDifference();
    millisecondTimer = microsecondTimer / 1000; // 1000 microseconds in 1 millisecond

    if (millisecondTimer < timerMS - CONFIGURATION_TIMER_RANGE_MS || millisecondTimer > timerMS + CONFIGURATION_TIMER_RANGE_MS) {
        std::cerr << "Error: Timer is not accurate. timerMS: " << timerMS << ", millisecondTimer: " << (float)microsecondTimer / 1000 << std::endl;
        return false;
    }
    std::cout << "     Success. timerMS: " << timerMS << ", millisecondTimer: " << (float)microsecondTimer / 1000 << std::endl;
    return true;
}

int main()
{
    uint8_t buffer = 'a';
    uint32_t microsecondTimer = 0;

    std::cout << "FYI: MSTP Callback Test. Version: " << APPLICATION_VERSION_MAJOR << std::endl;

    // Test 1: Internal high speed timer.
    // In this test we are testing to see if the high speed timer is accuret internally.
    // The timer should be accuret to the ms

    std::cout << "FYI: Test 1: Internal high speed timer" << std::endl;
    if (!testTimer(10)) {
        return EXIT_FAILURE;
    }
    if (!testTimer(20)) {
        return EXIT_FAILURE;
    }
    if (!testTimer(40)) {
        return EXIT_FAILURE;
    }
    if (!testTimer(80)) {
        return EXIT_FAILURE;
    }
    if (!testTimer(101)) {
        return EXIT_FAILURE;
    }
    std::cout << "FYI: Internal high speed timer success " << std::endl
              << std::endl;

    // Open the serial port
    std::cout << "FYI: Connecting to serial port. SerialPort=" << CONFIGURATION_SERIAL_PORT << std::endl;
    if (!serialConnect(CONFIGURATION_SERIAL_PORT)) {
        std::cout << "Error: Could not connect to the serial port. SerialPort=" << CONFIGURATION_SERIAL_PORT << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "FYI: Connectec to serial port" << std::endl
              << std::endl;

    // Test 1: Sending a byte
    // In this test we are checking to ensure that the serial port can transmit a BYTE.
    // In your serial monitor tool you should see the letter 'a" being sent by this device.

    // Send a single byte
    std::cout << "FYI: Test 2: Sending inital test byte. buffer='0' 0x30" << std::endl;
    if (!mstp_SendByte((uint8_t*)"0", 1)) {
        std::cerr << "Error: Could not send the intial test byte. buffer='0' 0x30" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "FYI: Check the serial port for the results to this test." << std::endl
              << std::endl;

    // Test 2: Sleep timer
    // In this test the application will send a byte out of the serial port at a constant rate.
    // In your serial monitoring tool check the rate that the bytes are being sent out.
    //
    // |  Time (ms) |     CHAR |      HEX |
    // * ---------- * -------- * -------- *
    // |            |        0 |       00 |
    // |      0.628 |        a |       0a |
    // |     10.392 |        b |       0b |
    // |     10.531 |        c |       0c |
    // |     10.931 |        d |       0d |
    // |     21.001 |        e |       0e |
    // |     31.027 |        f |       0f |
    // |     40.892 |        g |       0g |
    // |     50.499 |        h |       0h |

    std::cout << "FYI: Test 3: Sleep timer" << std::endl;
    mstp_SendByte((uint8_t*)"a", 1);
    mstp_Sleep(10);
    mstp_SendByte((uint8_t*)"b", 1);
    mstp_Sleep(10);
    mstp_SendByte((uint8_t*)"c", 1);
    mstp_Sleep(10);
    mstp_SendByte((uint8_t*)"d", 1);
    mstp_Sleep(20);
    mstp_SendByte((uint8_t*)"e", 1);
    mstp_Sleep(30);
    mstp_SendByte((uint8_t*)"f", 1);
    mstp_Sleep(40);
    mstp_SendByte((uint8_t*)"g", 1);
    mstp_Sleep(50);
    mstp_SendByte((uint8_t*)"h", 1);
    mstp_Sleep(100);

    std::cout << "FYI: Check the serial port for the results to this test." << std::endl
              << std::endl;

    // Test 4: Recive byte
    // In this test we are check to ensure that the serial port can recive a BYTE.
    // In your serial monitor tool send a byte to the device. The same byte should be echoed back.

    // Wait for a incoming byte
    std::cout << "FYI: Test 4: Action required ! - Send a byte to the serial port..." << std::endl;
    for (;;) {
        if (mstp_RecvByte(&buffer)) {
            printf("FYI: Byte recived. buffer='%c' 0x%02X\n", buffer, buffer);
            printf("FYI: Sending recived byte. buffer='%c' 0x%02X\n", buffer, buffer);
            if (!mstp_SendByte(&buffer, 1)) {
                printf("Error: Could not send the recived test byte. buffer='%c' 0x%02X\n", buffer, buffer);
                return EXIT_FAILURE;
            }
            // Done with this test.
            break;
        }
    }

    std::cout << "FYI: Success. All tests compleat." << std::endl;
    return EXIT_SUCCESS;
}
