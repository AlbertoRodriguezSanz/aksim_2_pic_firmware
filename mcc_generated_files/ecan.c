/**
  ECAN Generated Driver  File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan.c

  @Summary
    This is the generated driver implementation for the ECAN driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for CAN.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26K83
        Driver Version    :  2.12.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "ecan.h"

static void (*RXB0InterruptHandler)(void);
static void (*RXB1InterruptHandler)(void);
static void (*TXB0InterruptHandler)(void);
static void (*TXB1InterruptHandler)(void);
static void (*TXB2InterruptHandler)(void);
static void (*RXB0OverflowHandler)(void);
static void (*RXB1OverflowHandler)(void);
static void (*BusOffHandler)(void);
static void (*TXPassiveHandler)(void);
static void (*RXPassiveHandler)(void);
static void (*TXWarningHandler)(void);
static void (*RXWarningHandler)(void);
static void (*WakeUpInterruptHandler)(void);
static void (*MessageErrorInterruptHandler)(void);

/**
    Local Functions
*/  
static uint32_t convertReg2ExtendedCANid(uint8_t tempRXBn_EIDH, uint8_t tempRXBn_EIDL, uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL);
static uint32_t convertReg2StandardCANid(uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL);
static void convertCANid2Reg(uint32_t tempPassedInID, uint8_t canIdType, uint8_t *passedInEIDH, uint8_t *passedInEIDL, uint8_t *passedInSIDH, uint8_t *passedInSIDL);

static void RXB0DefaultInterruptHandler(void) {}
static void RXB1DefaultInterruptHandler(void) {}
static void TXB0DefaultInterruptHandler(void) {}
static void TXB1DefaultInterruptHandler(void) {}
static void TXB2DefaultInterruptHandler(void) {}
static void RXB0OverflowDefaultHandler(void) {}
static void RXB1OverflowDefaultHandler(void) {}
static void BusOffDefaultHandler(void) {}
static void TXPassiveDefaultHandler(void) {}
static void RXPassiveDefaultHandler(void) {}
static void TXWarningDefaultHandler(void) {}
static void RXWarningDefaultHandler(void) {}
static void WakeUpDefaultInterruptHandler(void) {}
static void MessageErrorDefaultInterruptHandler(void) {}

void ECAN_Initialize(void)
{
    CANCON = 0x80;
    while (0x80 != (CANSTAT & 0xE0)); // wait until ECAN is in config mode
    
    /**
    Mode 0
    */
    ECANCON = 0x00;     
    
    /**
    Initialize CAN I/O
    */
    CIOCON = 0x00;      //CANTX1 will output CANTX, CAN clock is sourced from system clock
    CIOCONbits.TX1SRC = 0;
    /**
    Mask and Filter definitions
    ........................................................    
    CAN ID		ID Type		Mask				Filter		Buffer    
    ........................................................    
    ........................................................
    */
 
/**    
    Initialize Receive Masks
*/   
    RXM0EIDH = 0x00;
    RXM0EIDL = 0x00;
    RXM0SIDH = 0x00;
    //RXM0SIDH = 0xFF;
    //RXM0SIDL = 0x20;
    RXM0SIDL = 0x00;
    RXM1EIDH = 0x00;
    RXM1EIDL = 0x00;
    RXM1SIDH = 0x00;
    RXM1SIDL = 0x00;
 
    /**
    Initialize Receive Filters
    */
    /*
    
     * 
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0xC8;
    RXF0SIDL = 0xC0;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x00;
    RXF1SIDL = 0x00;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0xC8;
    RXF2SIDL = 0xC0;
    RXF3EIDH = 0x00;
    RXF3EIDL = 0x00;
    RXF3SIDH = 0x00;
    RXF3SIDL = 0x00;
    RXF4EIDH = 0x00;
    RXF4EIDL = 0x00;
    RXF4SIDH = 0x00;
    RXF4SIDL = 0x00;
    RXF5EIDH = 0x00;
    RXF5EIDL = 0x00;
    RXF5SIDH = 0x00;
    RXF5SIDL = 0x00;
    */
    
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x00;
    RXF0SIDL = 0x00;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x00;
    RXF1SIDL = 0x00;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x00;
    RXF2SIDL = 0x00;
    RXF3EIDH = 0x00;
    RXF3EIDL = 0x00;
    RXF3SIDH = 0x00;
    RXF3SIDL = 0x00;
    RXF4EIDH = 0x00;
    RXF4EIDL = 0x00;
    RXF4SIDH = 0x00;
    RXF4SIDL = 0x00;
    RXF5EIDH = 0x00;
    RXF5EIDL = 0x00;
    RXF5SIDH = 0x00;
    RXF5SIDL = 0x00;
    
    

    /**
    Initialize CAN Timings
    */
    
  	/**
        Baud rate: 1Mbps
        System frequency: 16000000
        ECAN clock frequency: 16000000
        Time quanta: 8
        Sample point: 1-1-4-2
        Sample point: 75%
	*/ 
    
    BRGCON1 = 0x00;
    BRGCON2 = 0xD8;
    BRGCON3 = 0x41;
    BRGCON3bits.WAKFIL = 0; //Prueba- CAN bus ine filter is not used for wake-up
    
    ECAN_SetRXB0InterruptHandler(RXB0DefaultInterruptHandler);
    PIR5bits.RXB0IF = 0;
    PIE5bits.RXB0IE = 1;
    
    ECAN_SetRXB1InterruptHandler(RXB1DefaultInterruptHandler);
    PIR5bits.RXB1IF = 0;
    PIE5bits.RXB1IE = 1;
    
    ECAN_SetTXB0InterruptHandler(TXB0DefaultInterruptHandler);
    PIR5bits.TXB0IF = 0;
    PIE5bits.TXB0IE = 1;
    
    ECAN_SetTXB1InterruptHandler(TXB1DefaultInterruptHandler);
    PIR5bits.TXB1IF = 0;
    PIE5bits.TXB1IE = 1;
    
    ECAN_SetTXB2InterruptHandler(TXB2DefaultInterruptHandler);
    PIR5bits.TXB2IF = 0;
    PIE5bits.TXB2IE = 1;
    
    ECAN_SetRXB0OverflowHandler(RXB0OverflowDefaultHandler);
    ECAN_SetRXB1OverflowHandler(RXB1OverflowDefaultHandler);
    ECAN_SetBusOffHandler(BusOffDefaultHandler);
    ECAN_SetTXPassiveHandler(TXPassiveDefaultHandler);
    ECAN_SetRXPassiveHandler(RXPassiveDefaultHandler);
    ECAN_SetTXWarningHandler(TXWarningDefaultHandler);
    ECAN_SetRXWarningHandler(RXWarningDefaultHandler);
    PIR5bits.ERRIF = 0;
    PIE5bits.ERRIE = 1;
    
    ECAN_SetWakeUpInterruptHandler(WakeUpDefaultInterruptHandler);
    PIR5bits.WAKIF = 0;
    PIE5bits.WAKIE = 1;
    
    ECAN_SetMessageErrorInterruptHandler(MessageErrorDefaultInterruptHandler);
    PIR5bits.IRXIF = 0;
    PIE5bits.IRXIE = 1;
    
    PIR5bits.ERRIF = 0;
    PIE5bits.ERRIE = 1;
    
    
    CANCON = 0x00;
    while ((CANSTAT & 0xE0) != 0x00); // wait until ECAN is in Normal mode   
    
}
/**
  Section: CAN APIs
*/

void CAN_sleep(void) 
{
    CANCON = 0x20; // request disable mode
    while ((CANSTAT & 0xE0) != 0x20); // wait until ECAN is in disable mode   
    //Wake up from sleep should set the CAN module straight into Normal mode

}

uint8_t CAN_transmit(uCAN_MSG *tempCanMsg) {
    uint8_t tempEIDH = 0;
    uint8_t tempEIDL = 0;
    uint8_t tempSIDH = 0;
    uint8_t tempSIDL = 0;

    uint8_t returnValue = 0;
    
    // To access the message buffers the TXREQ bit must be clear, indicating there is no more pending messages to be transmited
    // All three transmit buffers are checked
    if (TXB0CONbits.TXREQ != 1) 
    {
        
        
        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB0EIDH = tempEIDH;
        TXB0EIDL = tempEIDL;
        TXB0SIDH = tempSIDH;
        TXB0SIDL = tempSIDL;
        TXB0DLC  = tempCanMsg->frame.dlc;
        TXB0D0   = tempCanMsg->frame.data0;
        TXB0D1   = tempCanMsg->frame.data1;
        TXB0D2   = tempCanMsg->frame.data2;
        TXB0D3   = tempCanMsg->frame.data3;
        TXB0D4   = tempCanMsg->frame.data4;
        TXB0D5   = tempCanMsg->frame.data5;
        TXB0D6   = tempCanMsg->frame.data6;
        TXB0D7   = tempCanMsg->frame.data7;
        
       
        TXB0CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
        
    } 
    else if (TXB1CONbits.TXREQ != 1) 
    {
          
        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB1EIDH = tempEIDH;
        TXB1EIDL = tempEIDL;
        TXB1SIDH = tempSIDH;
        TXB1SIDL = tempSIDL;
        TXB1DLC  = tempCanMsg->frame.dlc;
        TXB1D0   = tempCanMsg->frame.data0;
        TXB1D1   = tempCanMsg->frame.data1;
        TXB1D2   = tempCanMsg->frame.data2;
        TXB1D3   = tempCanMsg->frame.data3;
        TXB1D4   = tempCanMsg->frame.data4;
        TXB1D5   = tempCanMsg->frame.data5;
        TXB1D6   = tempCanMsg->frame.data6;
        TXB1D7   = tempCanMsg->frame.data7;

        
        TXB1CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    } 
    else if (TXB2CONbits.TXREQ != 1) 
    {
       
        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB2EIDH = tempEIDH;
        TXB2EIDL = tempEIDL;
        TXB2SIDH = tempSIDH;
        TXB2SIDL = tempSIDL;
        TXB2DLC  = tempCanMsg->frame.dlc;
        TXB2D0   = tempCanMsg->frame.data0;
        TXB2D1   = tempCanMsg->frame.data1;
        TXB2D2   = tempCanMsg->frame.data2;
        TXB2D3   = tempCanMsg->frame.data3;
        TXB2D4   = tempCanMsg->frame.data4;
        TXB2D5   = tempCanMsg->frame.data5;
        TXB2D6   = tempCanMsg->frame.data6;
        TXB2D7   = tempCanMsg->frame.data7;
        
        TXB2CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    }

    return (returnValue);
}

uint8_t CAN_messagesInBuffer(void) 
{
    uint8_t messageCount = 0;
    if (RXB0CONbits.RXFUL != 0) //CheckRXB0
    {
        messageCount++;
    }
    if (RXB1CONbits.RXFUL != 0) //CheckRXB1
    {
        messageCount++;
    }

    return (messageCount);
}

uint8_t CAN_isBusOff(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 5 TXBO: Transmitter Bus-Off bit
    //1 = Transmit error counter > 255
    //0 = Transmit error counter less then or equal to 255

    if (COMSTATbits.TXBO == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

uint8_t CAN_isRXErrorPassive(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 3 RXBP: Receiver Bus Passive bit
    //1 = Receive error counter > 127
    //0 = Receive error counter less then or equal to 127

    if (COMSTATbits.RXBP == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

uint8_t CAN_isTXErrorPassive(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 4 TXBP: Transmitter Bus Passive bit
    //1 = Transmit error counter > 127
    //0 = Transmit error counter less then or equal to 127

    if (COMSTATbits.TXBP == 1) 
    {
        returnValue = 1;
    }
    return (returnValue);
}

/**
Internal functions
*/


static uint32_t convertReg2ExtendedCANid(uint8_t tempRXBn_EIDH, uint8_t tempRXBn_EIDL, uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL) 
{
    uint32_t returnValue = 0;
    uint32_t ConvertedID = 0;
    uint8_t CAN_standardLo_ID_lo2bits;
    uint8_t CAN_standardLo_ID_hi3bits;

    CAN_standardLo_ID_lo2bits = (uint8_t)(tempRXBn_SIDL & 0x03);
    CAN_standardLo_ID_hi3bits = (uint8_t)(tempRXBn_SIDL >> 5);
    ConvertedID = (uint32_t)(tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + CAN_standardLo_ID_hi3bits;
    ConvertedID = (ConvertedID << 2);
    ConvertedID = ConvertedID + CAN_standardLo_ID_lo2bits;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDH;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDL;
    returnValue = ConvertedID;    
    return (returnValue);
}

static uint32_t convertReg2StandardCANid(uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL) 
{
    uint32_t returnValue = 0;
    uint32_t ConvertedID;
    //if standard message (11 bits)
    //EIDH = 0 + EIDL = 0 + SIDH + upper three bits SIDL (3rd bit needs to be clear)
    //1111 1111 111
    ConvertedID = (uint32_t)(tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + (uint32_t)(tempRXBn_SIDL >> 5);
    returnValue = ConvertedID;
    return (returnValue);
}

static void convertCANid2Reg(uint32_t tempPassedInID, uint8_t canIdType, uint8_t *passedInEIDH, uint8_t *passedInEIDL, uint8_t *passedInSIDH, uint8_t *passedInSIDL) 
{
    uint8_t wipSIDL = 0;

    if (canIdType == dEXTENDED_CAN_MSG_ID_2_0B) {

        //EIDL
        *passedInEIDL = 0xFF & tempPassedInID; //CAN_extendedLo_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //EIDH
        *passedInEIDH = 0xFF & tempPassedInID; //CAN_extendedHi_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //SIDL
        //push back 5 and or it
        wipSIDL = 0x03 & tempPassedInID;
        tempPassedInID = tempPassedInID << 3; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 << 3
        wipSIDL = (0xE0 & tempPassedInID) + wipSIDL;
        wipSIDL = (uint8_t)(wipSIDL + 0x08); // TEMP_CAN_standardLo_ID_TX1 = TEMP_CAN_standardLo_ID_TX1 + &H8
        *passedInSIDL = (uint8_t)(0xEB & wipSIDL); //CAN_standardLo_ID_TX1 = &HEB And TEMP_CAN_standardLo_ID_TX1

        //SIDH
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    } 
    else //(canIdType == dSTANDARD_CAN_MSG_ID_2_0B)
    {
        *passedInEIDH = 0;
        *passedInEIDL = 0;
        tempPassedInID = tempPassedInID << 5;
        *passedInSIDL = 0xFF & tempPassedInID;
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    }
}

void ECAN_SetRXB0InterruptHandler(void (*handler)(void))
{
    RXB0InterruptHandler = handler;
}

void ECAN_RXB0I_ISR(void)
{
    RXB0InterruptHandler();
    PIR5bits.RXB0IF = 0;
}

void ECAN_SetRXB1InterruptHandler(void (*handler)(void))
{
    RXB1InterruptHandler = handler;
}

void ECAN_RXB1I_ISR(void)
{
    RXB1InterruptHandler();
    PIR5bits.RXB1IF = 0;
}

void ECAN_SetTXB0InterruptHandler(void (*handler)(void))
{
    TXB0InterruptHandler = handler;
}

void ECAN_TXB0I_ISR(void)
{
    TXB0InterruptHandler();
    PIR5bits.TXB0IF = 0;
}

void ECAN_SetTXB1InterruptHandler(void (*handler)(void))
{
    TXB1InterruptHandler = handler;
}

void ECAN_TXB1I_ISR(void)
{
    TXB1InterruptHandler();
    PIR5bits.TXB1IF = 0;
}

void ECAN_SetTXB2InterruptHandler(void (*handler)(void))
{
    TXB2InterruptHandler = handler;
}

void ECAN_TXB2I_ISR(void)
{
    TXB2InterruptHandler();
    PIR5bits.TXB2IF = 0;
}

void ECAN_SetRXB0OverflowHandler(void (*handler)(void))
{
    RXB0OverflowHandler = handler;
}

void ECAN_SetRXB1OverflowHandler(void (*handler)(void))
{
    RXB1OverflowHandler = handler;
}

void ECAN_SetBusOffHandler(void (*handler)(void))
{
    BusOffHandler = handler;
}

void ECAN_SetTXPassiveHandler(void (*handler)(void))
{
    TXPassiveHandler = handler;
}

void ECAN_SetRXPassiveHandler(void (*handler)(void))
{
    RXPassiveHandler = handler;
}

void ECAN_SetTXWarningHandler(void (*handler)(void))
{
    TXWarningHandler = handler;
}

void ECAN_SetRXWarningHandler(void (*handler)(void))
{
    RXWarningHandler = handler;
}

void ECAN_ERRI_ISR(void)
{
    if (COMSTATbits.RXB0OVFL)
    {
        RXB0OverflowHandler();
        COMSTATbits.RXB0OVFL = 0;
    }
    
    if (COMSTATbits.RXB1OVFL)
    {
        RXB1OverflowHandler();
        COMSTATbits.RXB1OVFL = 0;
    }
    
    if (COMSTATbits.TXBO)
    {
        BusOffHandler();
    }
    
    if (COMSTATbits.TXBP)
    {
        TXPassiveHandler();
    }
    
    if (COMSTATbits.RXBP)
    {
        RXPassiveHandler();
    }
    
    if (COMSTATbits.TXWARN)
    {
        TXWarningHandler();
    }
    
    if (COMSTATbits.RXWARN)
    {
        RXWarningHandler();
    }
    
    PIR5bits.ERRIF = 0;
}

void ECAN_SetWakeUpInterruptHandler(void (*handler)(void))
{
    WakeUpInterruptHandler = handler;
}

void ECAN_WAKI_ISR(void)
{
    WakeUpInterruptHandler();
    PIR5bits.WAKIF = 0;
}

void ECAN_SetMessageErrorInterruptHandler(void (*handler)(void))
{
    MessageErrorInterruptHandler = handler;
}

void ECAN_IRXI_ISR(void)
{
    MessageErrorInterruptHandler();
    PIR5bits.IRXIF = 0;
}
