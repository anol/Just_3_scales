/*
 * primary_activity.cpp
 *
 *  Created on: 26. apr. 2016
 *      Author: Anders
 */

#include <cstdint>
#include <cmath>
#include <ctime>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_hibernate.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/qei.h"
#include "uartstdio.h"
#include "qei_sensor.h"
#include "ssi_display.h"
#include "primary_activity.h"

primary_activity::primary_activity() :
        m_oDisplay_X(aeo1::ssi_display::SSI0),
        m_oDisplay_Y(aeo1::ssi_display::SSI1),
        m_oDisplay_Z(aeo1::ssi_display::SSI2),
        m_oDisplay_M(aeo1::ssi_display::SSI3),
        m_nCount_X(0),
        m_nCount_Y(0),
        m_nCount_Z(0) {
}

static void SetupInput() {
    // PB3, Y-Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // PC4, IDX1, Y-Index
    // PC7, X-Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_7,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // PF4, IDX0, X-Index
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

static bool GetButton_X() {
    return GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7) == 0;
}

static bool GetButton_Y() {
    return GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) == 0;
}

static bool GetButton_Z() {
    return GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) == 0;
}

void primary_activity::Initialize() {
    SetupInput();
    m_oDisplay_X.Initialize();
    m_oDisplay_Y.Initialize();
    m_oDisplay_Z.Initialize();
    m_oDisplay_M.Initialize();
}

bool primary_activity::CheckInputs(int &rCount, bool bButton,
                                   bool bIndex) const {
    enum {
        MinimumPressedCount = 5,
        MaximumShortPressed = 32,
        MinimumLongPressed = 100
    };
    bool bZero = false;
    int nTempCount = rCount;
    if (bButton) {
        nTempCount++;
        if (MinimumLongPressed < nTempCount) { // This is a press and hold
            if (bIndex) { // The scale is at an index point
                nTempCount = 0;
                bZero = true;
            }
        }
    } else if ((MinimumPressedCount < nTempCount)
               && (MaximumShortPressed > nTempCount)) { // This is a push and release
        nTempCount = 0;
        bZero = true;
    } else {
        nTempCount = 0;
    }
    // Return both results
    rCount = nTempCount;
    return bZero;
}

void primary_activity::OnTick() {
    int nCount;
    if (CheckInputs(nCount, GetButton_X(), false)) m_nCount_X = 0;
    if (CheckInputs(nCount, GetButton_Y(), false)) m_nCount_Y = 0;
    if (CheckInputs(nCount, GetButton_Z(), false)) m_nCount_Z = 0;
    // Update the displays
    m_oDisplay_X.Set(m_nCount_X);
    m_oDisplay_Y.Set(m_nCount_Y);
    m_oDisplay_Z.Set(m_nCount_Z);
    m_oDisplay_M.Set(m_nCount_X);
}

void primary_activity::Diag() {
    UARTprintf("X: button=%5s, count=%d\n", GetButton_X() ? "true" : "false", m_nCount_X);
    UARTprintf("Y: button=%5s, count=%d\n", GetButton_Y() ? "true" : "false", m_nCount_Y);
    UARTprintf("Z: button=%5s, count=%d\n", GetButton_Z() ? "true" : "false", m_nCount_Z);
    m_oDisplay_X.Diag();
    m_oDisplay_Y.Diag();
    m_oDisplay_Z.Diag();
    m_oDisplay_M.Diag();
}
