/*!
 * @file MAX30003.h
 * 
 * Designed to work with the UPC subject DEMU prototype board.
 * http://wwww.upc.edu/content/grau/guiadocent/pdf/esp/295602
 * 
 * This device is connected using SPI interface.
 *
 * MAX30003.h - Library for MAX30003 ultra-low power, single-channel integrated
 *              biopotential (ECG, R-to-R Detection).
 *
 * Created by Paco Bogonez, 15/08/2020.
 * Revision: 1.0.
 * BSD license, all text here must be included in any redistribution.
 * 
 */
#ifndef MAX30003_h
#define MAX30003_h

#include "Arduino.h"
#include <Wire.h>


/* !
 * @brief Register addresses
 */
enum {
    /* STATUS */
    MAX30003_REGISTER_STATUS = 0x00,
    
	/* ENABLE INTERRUPTS*/
	MAX30003_REGISTER_EN_INT = 0x02,
    MAX30003_REGISTER_EN_INT_2 = 0x03,

    /* MANAGER INTERRUPT */
    MAX30003_REGISTER_MNGR_INT = 0x04,

    /* MANAGER DYNAMICS */
    MAX30003_REGISTER_MNGR_DYN = 0x05,

    /* SOFTWARE RESET */
    MAX30003_REGISTER_SW_RST = 0x08,

    /* SYNCHRONIZE */
    MAX30003_REGISTER_SYNCH = 0x09,

	/* FIFO RESET */
	MAX30003_REGISTER_FIFO_RST = 0x0A,

	/* INFO */
	MAX30003_REGISTER_INFO = 0x0F,

	/* CONFIGURATE GENERATOR */
	MAX30003_REGISTER_CNFG_GEN = 0x10,

	/* CONFIGURATION CALIBRATION */
	MAX30003_REGISTER_CNFG_CAL = 0x12,

	/* CONFIGURATION EMUX */
	MAX30003_REGISTER_CNFG_EMUX = 0x14,

	/* CONFIGURATION ECG */
	MAX30003_REGISTER_CNFG_ECG = 0x15,

	/* CONFIGURATION R to R */
	MAX30003_REGISTER_CNFG_RTOR1 = 0x1D,
	MAX30003_REGISTER_CNFG_RTOR1 = 0x1E
}


/*!
* @brief ECG BURST READ
*/
#define MAX30003_ECG_BURST (0x20)

/*!
* @brief ECG READ
*/
#define MAX30003_ECG_READ (0x21)

/*!
* @brief ECG BURST READ
*/
#define MAX30003_RTOR_READ (0x25)



/**
  * @brief  Status register bits
  */
typedef enum
{
	LDOFF_NL	= 0x000001U,		/*!< DC lead-off detection */
	LDOFF_NH	= 0x000002U,		/*!< DC lead-off detection */
	LDOFF_PL	= 0x000004U,		/*!< DC lead-off detection */
	LDOFF_PH	= 0x000008U,		/*!< DC lead-off detection */
	PLLINT		= 0x000010U,		/*!< PLL unlocked interrupt */
	SAMP		= 0x000020U,		/*!< Sample synchronization pulse */
	RRINT		= 0x000040U,		/*!< ECG R to R detector R event interrupt */
	LONINT		= 0x000080U,		/*!< Ultra-low power leads-on detection interrupt */
	DCLOFFINT	= 0x100000U,		/*!< DC Lead-Off detection interrupt */
	FSINT		= 0x200000U,		/*!< ECG Fast Recovery Mode */
	EOF			= 0x400000U,		/*!< ECG FIFO Overflow */
	EINT		= 0x800000U			/*!< ECG FIFO interrupt */
} STATUS_Register;

/**
  * @brief  EN_INT and EN_INT2 register bits
  */
typedef enum
{
	INTB_TYPE_0	= 0x000000U,		/*!< INTB port disable (three-state) */
	INTB_TYPE_1	= 0x000001U,		/*!< INTB port CMOS driver */
	INTB_TYPE_2	= 0x000002U,		/*!< INTB port open-drain NMOS driver */
	INTB_TYPE_3	= 0x000003U,		/*!< INTB port open-drain NMOS driver with internal 125 kOhm pullup resistance */
	INTB_TYPE_4 = 0x000000U,		/*!< INT2B port disable (three-state) */
	INTB_TYPE_5 = 0x000006U,		/*!< INT2B port CMOS driver */
	INTB_TYPE_6 = 0x000008U,		/*!< INT2B port open-drain NMOS driver */
	INTB_TYPE_7 = 0x00000CU,		/*!< INT2B port open-drain NMOS driver with internal 125 kOhm pullup resistance */
	EN_PLLINT	= 0x000010U,		/*!< PLL unlocked interrupt interrupt enable */
	EN_SAMP		= 0x000020U,		/*!< Sample synchronization pulse interrupt enable */
	EN_RRINT	= 0x000040U,		/*!< ECG R to R detector R event interrupt interrupt enable */
	EN_LONINT	= 0x000080U,		/*!< Ultra-low power leads-on detection interrupt interrupt enable */
	EN_DCLOFFINT	= 0x100000U,		/*!< DC Lead-Off detection interrupt interrupt enable */
	EN_FSTINT	= 0x200000U,		/*!< ECG Fast Recovery Mode interrupt enable */
	EN_EOF		= 0x400000U,		/*!< ECG FIFO Overflow interrupt enable */
	EN_EINT		= 0x800000U			/*!< ECG FIFO interrupt interrupt enable */
} EN_INT_Register;

/**
  * @brief  MNGR_INT register bits
  */
typedef enum
{
	SAMP_IT_0	= 0x000001U,		/*!< DC lead-off detection */
	SAMP_IT_1	= 0x000002U,		/*!< DC lead-off detection */
	SAMP_IT_2	= 0x000020U,		/*!< Sample synchronization pulse */
	SAMP_IT_3	= 0x000020U,		/*!< Sample synchronization pulse */
	RRINT		= 0x000040U,		/*!< ECG R to R detector R event interrupt */
	LONINT		= 0x000080U,		/*!< Ultra-low power leads-on detection interrupt */
	DCLOFFINT	= 0x100000U,		/*!< DC Lead-Off detection interrupt */
	FSINT		= 0x200000U,		/*!< ECG Fast Recovery Mode */
	EOF			= 0x400000U,		/*!< ECG FIFO Overflow */
	EINT		= 0x800000U			/*!< ECG FIFO interrupt */
} STATUS_Interrupt_Enable_1;

/**
  * @brief  Interrupt Enable 2
  */
typedef enum
{
  DIE_TEMP_RDY_EN = 0x02U,      /*!< Internal temperature ready flag enable */
} STATUS_Interrupt_Enable_2;


/**
  * @brief  FIFO Write Pointer
  */
typedef enum
{
  FIFO_WR_PTR_0 = 0x01U,      /*!< Next sample indication */
  FIFO_WR_PTR_1 = 0x02U,      /*!< Next sample indication */
  FIFO_WR_PTR_2 = 0x04U,      /*!< Next sample indication */
  FIFO_WR_PTR_3 = 0x08U,      /*!< Next sample indication */
  FIFO_WR_PTR_4 = 0x10U,      /*!< Next sample indication */
} FIFO_Write_Pointer;

/**
  * @brief  FIFO Overflow Counter
  */
typedef enum
{
  OVF_COUNTER_0 = 0x01U,      /*!< Counter of samples lost */
  OVF_COUNTER_1 = 0x02U,      /*!< Counter of samples lost */
  OVF_COUNTER_2 = 0x04U,      /*!< Counter of samples lost */
  OVF_COUNTER_3 = 0x08U,      /*!< Counter of samples lost */
  OVF_COUNTER_4 = 0x10U,      /*!< Counter of samples lost */
} FIFO_Overflow_Counter;

/**
  * @brief  FIFO Read Pointer
  */
typedef enum
{
  FIFO_RD_PTR_0 = 0x01U,      /*!< Pointer where to take the next sample */
  FIFO_RD_PTR_1 = 0x02U,      /*!< Pointer where to take the next sample */
  FIFO_RD_PTR_2 = 0x04U,      /*!< Pointer where to take the next sample */
  FIFO_RD_PTR_3 = 0x08U,      /*!< Pointer where to take the next sample */
  FIFO_RD_PTR_4 = 0x10U,      /*!< Pointer where to take the next sample */
} FIFO_Overflow_Counter;

/**
  * @brief  FIFO Data Register
  */
typedef enum
{
  FIFO_DATA_0 = 0x01U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x02U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x04U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x08U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x10U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x20U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x40U,      /*!< Points to the next sample to be read from FIFO */
  FIFO_DATA_0 = 0x80U,      /*!< Points to the next sample to be read from FIFO */
} FIFO_Data_Register;


/*
 * CONFIGURATION Register bits
 */
/**
  * @brief  CONFIGURATION FIFO Configuration
  */
typedef enum
{
  CONFIGURATION_A_FULL_0 = 0x01U,               /*!< Sets the number of data samples (3 bytes/sample) */
  CONFIGURATION_A_FULL_1 = 0x02U,               /*!< Sets the number of data samples (3 bytes/sample) */
  CONFIGURATION_A_FULL_2 = 0x04U,               /*!< Sets the number of data samples (3 bytes/sample) */
  CONFIGURATION_A_FULL_3 = 0x08U,               /*!< Sets the number of data samples (3 bytes/sample) */
  CONFIGURATION_ROLLOVER_EN = 0x10U,            /*!< Control if FIFO rolls over when full */
  CONFIGURATION_SMP_AVE_0 = 0x20U,              /*!< Number of samples averaged per FIFO sample */
  CONFIGURATION_SMP_AVE_1 = 0x40U,              /*!< Number of samples averaged per FIFO sample */
  CONFIGURATION_SMP_AVE_2 = 0x80U,              /*!< Number of samples averaged per FIFO sample */
} CONFIGURATION_FIFO_Configuration;

/**
  * @brief  CONFIGURATION Mode Configuration
  */
typedef enum
{
  CONFIGURATION_HEART_RATE = 0x02U,             /*!< Operating state of MAX30003. Heart Rate mode. Red only */
  CONFIGURATION_SPO2 = 0x03U,                   /*!< Operating state of MAX30003. SpO2 mode. Red and IR */
  CONFIGURATION_MULTI_LED = 0x07U,              /*!< Operating state of MAX30003. Multi-LED mode. Green, red and/or IR */
  CONFIGURATION_RESET = 0x40U,                  /*!< Reset registers to their power-on state */
  CONFIGURATION_SHDN = 0x80U,                   /*!< Shutdown control */
} CONFIGURATION_Mode_Configuration;

/**
  * @brief  CONFIGURATION Mode Configuration
  */
typedef enum
{
  CONFIGURATION_HEART_RATE = 0x02U,             /*!< Operating state of MAX30003. Heart Rate mode. Red only */
  CONFIGURATION_SPO2 = 0x03U,                   /*!< Operating state of MAX30003. SpO2 mode. Red and IR */
  CONFIGURATION_MULTI_LED = 0x07U,              /*!< Operating state of MAX30003. Multi-LED mode. Green, red and/or IR */
  CONFIGURATION_RESET = 0x40U,                  /*!< Reset registers to their power-on state */
  CONFIGURATION_SHDN = 0x80U,                   /*!< Shutdown control */
} CONFIGURATION_Mode_Configuration;

/**
  * @brief  CONFIGURATION SpO2 Configuration
  */
typedef enum
{
  CONFIGURATION_LED_PW_69 = 0x00U,              /*!< LED Pulse width. 69 us, 15 bits resolution */
  CONFIGURATION_LED_PW_118 = 0x01U,             /*!< LED Pulse width. 118 us, 16 bits resolution */
  CONFIGURATION_LED_PW_215 = 0x02U,             /*!< LED Pulse width. 215 us, 17 bits resolution */
  CONFIGURATION_LED_PW_411 = 0x03U,             /*!< LED Pulse width. 411 us, 18 bits resolution */
  CONFIGURATION_SPO2_SPR_50 = 0x03U,            /*!< 50 samples per second */
  CONFIGURATION_SPO2_SPR_100 = 0x07U,           /*!< 100 samples per second */
  CONFIGURATION_SPO2_SPR_200 = 0x07U,           /*!< 200 samples per second */
  CONFIGURATION_SPO2_SPR_400 = 0x07U,           /*!< 400 samples per second */
  CONFIGURATION_SPO2_SPR_800 = 0x07U,           /*!< 800 samples per second */
  CONFIGURATION_SPO2_SPR_1000 = 0x07U,          /*!< 1000 samples per second */
  CONFIGURATION_SPO2_SPR_1600 = 0x07U,          /*!< 1600 samples per second */
  CONFIGURATION_SPO2_SPR_3200 = 0x07U,          /*!< 3200 samples per second */
  CONFIGURATION_SPO2_RC_2048 = 0x40U,           /*!< 2048 uA full scale at 18 bits */
  CONFIGURATION_SPO2_RC_4096 = 0x80U,           /*!< 4096 uA full scale at 18 bits */
  CONFIGURATION_SPO2_RC_8192 = 0x40U,           /*!< 8192 uA full scale at 18 bits */
  CONFIGURATION_SPO2_RC_16384 = 0x80U,          /*!< 16384 uA full scale at 18 bits */
} CONFIGURATION_SpO2_Configuration;

/**
  * @brief  CONFIGURATION LED Pulse Amplitude
  */
typedef enum
{
  ECG_VALID_SAMPLE = 0x000U,					/*!< This is a valid sample */
  ECG_FAST_MODE_SAMPLE = 0x001U,				/*!< This sample was taken while the ECG channel was in a FAST mode. */
  ECG_LAST_VALID_SAMPLE = 0x002U,				/*!< This is a valid FIFO sample, but this is the last sample currently available in the FIFO */
  ECG_LAST_FAST_MODE_SAMPLE = 0x003U,           /*!< This sample was taken while the ECG channel was in a FAST mode, but this is the last sample in FIFO */
  ECG_FIFO_EMPTY = 0x006U,						/*!< This is an invalid sample provided in response to an SPI request to read an empty FIFO. */
  ECG_FIFO_OVERFLOW = 0x007U,					/*!< The FIFO has been allowed to overflow – the data is corrupted */
} MAX30003_ECG_ETAG_Register;



class MAX30003
{
  public:
    MAX30003();
    MAX30003(int Sample);
    (int pin);
    void setSpO2Sampling(int samples_per_second);
    void dash();
    // Constructors


  private:
    int _address;
};

#endif