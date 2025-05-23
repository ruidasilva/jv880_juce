/*
 * Copyright (C) 2021, 2024 nukeykt
 *
 *  Redistribution and use of this code or any derivative works are permitted
 *  provided that the following conditions are met:
 *
 *   - Redistributions may not be sold, nor may they be used in a commercial
 *     product or activity.
 *
 *   - Redistributions that are modified from the original source must include the
 *     complete source code, including the source code for all components used by a
 *     binary built from the modified sources. However, as a special exception, the
 *     source code distributed need not include anything that is normally distributed
 *     (in either source or binary form) with the major components (compiler, kernel,
 *     and so on) of the operating system on which the executable runs, unless that
 *     component itself accompanies the executable.
 *
 *   - Redistributions must reproduce the above copyright notice, this list of
 *     conditions and the following disclaimer in the documentation and/or other
 *     materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <stdint.h>
#include <vector>
#include "mcu_interrupt.h"
#include "pcm.h"
#include "lcd.h"
#include "mcu_timer.h"
#include "submcu.h"

#ifdef __APPLE__
#include <sys/syslimits.h> // PATH_MAX
#include <mach-o/dyld.h>
#endif

enum {
    DEV_P1DDR = 0x00,
    DEV_P5DDR = 0x08,
    DEV_P6DDR = 0x09,
    DEV_P7DDR = 0x0c,
    DEV_P7DR = 0x0e,
    DEV_FRT1_TCR = 0x10,
    DEV_FRT1_TCSR = 0x11,
    DEV_FRT1_FRCH = 0x12,
    DEV_FRT1_FRCL = 0x13,
    DEV_FRT1_OCRAH = 0x14,
    DEV_FRT1_OCRAL = 0x15,
    DEV_FRT2_TCR = 0x20,
    DEV_FRT2_TCSR = 0x21,
    DEV_FRT2_FRCH = 0x22,
    DEV_FRT2_FRCL = 0x23,
    DEV_FRT2_OCRAH = 0x24,
    DEV_FRT2_OCRAL = 0x25,
    DEV_FRT3_TCR = 0x30,
    DEV_FRT3_TCSR = 0x31,
    DEV_FRT3_FRCH = 0x32,
    DEV_FRT3_FRCL = 0x33,
    DEV_FRT3_OCRAH = 0x34,
    DEV_FRT3_OCRAL = 0x35,
    DEV_PWM1_TCR = 0x40,
    DEV_PWM1_DTR = 0x41,
    DEV_PWM2_TCR = 0x44,
    DEV_PWM2_DTR = 0x45,
    DEV_PWM3_TCR = 0x48,
    DEV_PWM3_DTR = 0x49,
    DEV_TMR_TCR = 0x50,
    DEV_TMR_TCSR = 0x51,
    DEV_TMR_TCORA = 0x52,
    DEV_TMR_TCORB = 0x53,
    DEV_TMR_TCNT = 0x54,
    DEV_SMR = 0x58,
    DEV_BRR = 0x59,
    DEV_SCR = 0x5a,
    DEV_TDR = 0x5b,
    DEV_SSR = 0x5c,
    DEV_RDR = 0x5d,
    DEV_ADDRAH = 0x60,
    DEV_ADDRAL = 0x61,
    DEV_ADDRBH = 0x62,
    DEV_ADDRBL = 0x63,
    DEV_ADDRCH = 0x64,
    DEV_ADDRCL = 0x65,
    DEV_ADDRDH = 0x66,
    DEV_ADDRDL = 0x67,
    DEV_ADCSR = 0x68,
    DEV_IPRA = 0x70,
    DEV_IPRB = 0x71,
    DEV_IPRC = 0x72,
    DEV_IPRD = 0x73,
    DEV_DTEA = 0x74,
    DEV_DTEB = 0x75,
    DEV_DTEC = 0x76,
    DEV_DTED = 0x77,
    DEV_WCR = 0x78,
    DEV_RAME = 0x79,
    DEV_P1CR = 0x7c,
    DEV_P9DDR = 0x7e,
    DEV_P9DR = 0x7f,
};

const uint16_t sr_mask = 0x870f;
enum {
    STATUS_T = 0x8000,
    STATUS_N = 0x08,
    STATUS_Z = 0x04,
    STATUS_V = 0x02,
    STATUS_C = 0x01,
    STATUS_INT_MASK = 0x700
};

enum {
    VECTOR_RESET = 0,
    VECTOR_RESERVED1, // UNUSED
    VECTOR_INVALID_INSTRUCTION,
    VECTOR_DIVZERO,
    VECTOR_TRAP,
    VECTOR_RESERVED2, // UNUSED
    VECTOR_RESERVED3, // UNUSED
    VECTOR_RESERVED4, // UNUSED
    VECTOR_ADDRESS_ERROR,
    VECTOR_TRACE,
    VECTOR_RESERVED5, // UNUSED
    VECTOR_NMI,
    VECTOR_RESERVED6, // UNUSED
    VECTOR_RESERVED7, // UNUSED
    VECTOR_RESERVED8, // UNUSED
    VECTOR_RESERVED9, // UNUSED
    VECTOR_TRAPA_0,
    VECTOR_TRAPA_1,
    VECTOR_TRAPA_2,
    VECTOR_TRAPA_3,
    VECTOR_TRAPA_4,
    VECTOR_TRAPA_5,
    VECTOR_TRAPA_6,
    VECTOR_TRAPA_7,
    VECTOR_TRAPA_8,
    VECTOR_TRAPA_9,
    VECTOR_TRAPA_A,
    VECTOR_TRAPA_B,
    VECTOR_TRAPA_C,
    VECTOR_TRAPA_D,
    VECTOR_TRAPA_E,
    VECTOR_TRAPA_F,
    VECTOR_IRQ0,
    VECTOR_IRQ1,
    VECTOR_INTERNAL_INTERRUPT_88, // UNUSED
    VECTOR_INTERNAL_INTERRUPT_8C, // UNUSED
    VECTOR_INTERNAL_INTERRUPT_90, // FRT1 ICI
    VECTOR_INTERNAL_INTERRUPT_94, // FRT1 OCIA
    VECTOR_INTERNAL_INTERRUPT_98, // FRT1 OCIB
    VECTOR_INTERNAL_INTERRUPT_9C, // FRT1 FOVI
    VECTOR_INTERNAL_INTERRUPT_A0, // FRT2 ICI
    VECTOR_INTERNAL_INTERRUPT_A4, // FRT2 OCIA
    VECTOR_INTERNAL_INTERRUPT_A8, // FRT2 OCIB
    VECTOR_INTERNAL_INTERRUPT_AC, // FRT2 FOVI
    VECTOR_INTERNAL_INTERRUPT_B0, // FRT3 ICI
    VECTOR_INTERNAL_INTERRUPT_B4, // FRT3 OCIA
    VECTOR_INTERNAL_INTERRUPT_B8, // FRT3 OCIB
    VECTOR_INTERNAL_INTERRUPT_BC, // FRT3 FOVI
    VECTOR_INTERNAL_INTERRUPT_C0, // CMIA
    VECTOR_INTERNAL_INTERRUPT_C4, // CMIB
    VECTOR_INTERNAL_INTERRUPT_C8, // OVI
    VECTOR_INTERNAL_INTERRUPT_CC, // UNUSED
    VECTOR_INTERNAL_INTERRUPT_D0, // ERI
    VECTOR_INTERNAL_INTERRUPT_D4, // RXI
    VECTOR_INTERNAL_INTERRUPT_D8, // TXI
    VECTOR_INTERNAL_INTERRUPT_DC, // UNUSED
    VECTOR_INTERNAL_INTERRUPT_E0, // ADI
};


struct mcu_t {
    uint16_t r[8];
    uint16_t pc;
    uint16_t sr;
    uint8_t cp, dp, ep, tp, br;
    uint8_t sleep;
    uint8_t ex_ignore;
    int32_t exception_pending;
    uint8_t interrupt_pending[INTERRUPT_SOURCE_MAX];
    uint8_t trapa_pending[16];
    uint64_t cycles;
};

enum {
    // SC55
    MCU_BUTTON_POWER = 0,
    MCU_BUTTON_INST_L = 3,
    MCU_BUTTON_INST_R = 4,
    MCU_BUTTON_INST_MUTE = 5,
    MCU_BUTTON_INST_ALL = 6,

    MCU_BUTTON_MIDI_CH_L = 8,
    MCU_BUTTON_MIDI_CH_R = 9,
    MCU_BUTTON_CHORUS_L = 10,
    MCU_BUTTON_CHORUS_R = 11,
    MCU_BUTTON_PAN_L = 12,
    MCU_BUTTON_PAN_R = 13,
    MCU_BUTTON_PART_R = 14,

    MCU_BUTTON_KEY_SHIFT_L = 16,
    MCU_BUTTON_KEY_SHIFT_R = 17,
    MCU_BUTTON_REVERB_L = 18,
    MCU_BUTTON_REVERB_R = 19,
    MCU_BUTTON_LEVEL_L = 20,
    MCU_BUTTON_LEVEL_R = 21,
    MCU_BUTTON_PART_L = 22,

    // SC155 extra buttons
    MCU_BUTTON_USER = 1,
    MCU_BUTTON_PART_SEL = 2,
    MCU_BUTTON_INST_CALL = 7,
    MCU_BUTTON_PAN = 15,
    MCU_BUTTON_LEVEL = 23,
    MCU_BUTTON_PART1 = 24,
    MCU_BUTTON_PART2 = 25,
    MCU_BUTTON_PART3 = 26,
    MCU_BUTTON_PART4 = 27,
    MCU_BUTTON_PART5 = 28,
    MCU_BUTTON_PART6 = 29,
    MCU_BUTTON_PART7 = 30,
    MCU_BUTTON_PART8 = 31,

    // JV880
    MCU_BUTTON_CURSOR_L = 0,
    MCU_BUTTON_CURSOR_R = 1,
    MCU_BUTTON_TONE_SELECT = 2,
    MCU_BUTTON_MUTE = 3,
    MCU_BUTTON_DATA = 4,
    MCU_BUTTON_MONITOR = 5,
    MCU_BUTTON_COMPARE = 6,
    MCU_BUTTON_ENTER = 7,
    MCU_BUTTON_UTILITY = 8,
    MCU_BUTTON_PREVIEW = 9,
    MCU_BUTTON_PATCH_PERFORM = 10,
    MCU_BUTTON_EDIT = 11,
    MCU_BUTTON_SYSTEM = 12,
    MCU_BUTTON_RHYTHM = 13,
};


enum {
    ROM_SET_MK2 = 0,
    ROM_SET_ST,
    ROM_SET_MK1,
    ROM_SET_CM300,
    ROM_SET_JV880,
    ROM_SET_SCB55,
    ROM_SET_RLP3237,
    ROM_SET_SC155,
    ROM_SET_SC155MK2,
    ROM_SET_COUNT
};

enum class ResetType {
    NONE,
    GS_RESET,
    GM_RESET,
};

extern const char* rs_name[ROM_SET_COUNT];

static const int ROM1_SIZE = 0x8000;
static const int ROM2_SIZE = 0x80000;
static const int ROM2_SIZE_JV880 = 0x40000;
static const int RAM_SIZE = 0x400;
static const int SRAM_SIZE = 0x8000;
static const int NVRAM_SIZE = 0x8000; // JV880 only
static const int CARDRAM_SIZE = 0x8000; // JV880 only
static const int ROMSM_SIZE = 0x1000;
const uint32_t uart_buffer_size = 8192;

static const int audio_buffer_size = 4096 * 8;
static const int audio_page_size = 512;

static const int ROM_SET_N_FILES = 6;

struct MCU {
    int romset = 0;

    int mcu_mk1 = 0; // 0 - SC-55mkII, SC-55ST. 1 - SC-55, CM-300/SCC-1
    int mcu_cm300 = 0; // 0 - SC-55, 1 - CM-300/SCC-1
    int mcu_st = 0; // 0 - SC-55mk2, 1 - SC-55ST
    int mcu_jv880 = 0; // 0 - SC-55, 1 - JV880
    int mcu_scb55 = 0; // 0 - sub mcu (e.g SC-55mk2), 1 - no sub mcu (e.g SCB-55)
    int mcu_sc155 = 0; // 0 - SC-55(MK2), 1 - SC-155(MK2)

    uint32_t mcu_button_pressed;

    uint8_t mcu_p0_data = 0x00;
    uint8_t mcu_p1_data = 0x00;

    mcu_t mcu;

    uint8_t rom1[ROM1_SIZE];
    uint8_t rom2[ROM2_SIZE];
    uint8_t ram[RAM_SIZE];
    uint8_t sram[SRAM_SIZE];
    uint8_t nvram[NVRAM_SIZE];
    uint8_t cardram[CARDRAM_SIZE];

    int rom2_mask = ROM2_SIZE - 1;

    float sample_buffer_l[audio_buffer_size] = {0};
    float sample_buffer_r[audio_buffer_size] = {0};
    int sample_write_ptr = 0;

    int ga_int[8] = {0};
    int ga_int_enable = 0;
    int ga_int_trigger = 0;
    int ga_lcd_counter = 0;

    uint8_t dev_register[0x80] = {0};

    uint16_t ad_val[4] = {0};
    uint8_t ad_nibble = 0x00;
    uint8_t sw_pos = 3;
    uint8_t io_sd = 0x00;

    int adf_rd = 0;
    uint64_t analog_end_time = 0;

    int ssr_rd = 0;
    
    bool midi_ready = false;

    uint32_t uart_write_ptr;
    uint32_t uart_read_ptr;
    uint8_t uart_buffer[uart_buffer_size];

    uint8_t uart_rx_byte;
    uint64_t uart_rx_delay;
    uint64_t uart_tx_delay;

    uint32_t operand_type;
    uint16_t operand_ea;
    uint8_t operand_ep;
    uint8_t operand_size;
    uint8_t operand_reg;
    uint8_t operand_status;
    uint16_t operand_data;
    uint8_t opcode_extended;

    FILE *s_rf[ROM_SET_N_FILES] =
    {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };

    Pcm pcm;
    LCD lcd;
    MCU_Timer mcu_timer;
    SubMcu sub_mcu;

    void* resampleL = 0;
    void* resampleR = 0;
    int savedDestSampleRate = 0;
    double samplesError = 0;
    
    struct MidiEvent {
        uint8_t data[32];
        int length;
        int samplePos;
        bool processed;
    };
    std::vector<MidiEvent> midiQueue;

    MCU();

    void MCU_ErrorTrap(void);

    uint8_t MCU_Read(uint32_t address);
    uint16_t MCU_Read16(uint32_t address);
    uint32_t MCU_Read32(uint32_t address);
    void MCU_Write(uint32_t address, uint8_t value);
    void MCU_Write16(uint32_t address, uint16_t value);

    uint8_t MCU_ReadP0(void);
    uint8_t MCU_ReadP1(void);
    void MCU_WriteP0(uint8_t data);
    void MCU_WriteP1(uint8_t data);
    void MCU_GA_SetGAInt(int line, int value);
    void MCU_UpdateUART_RX(void);
    void MCU_UpdateUART_TX(void);

    void MCU_PostSample(int *sample);
    void MCU_PostUART(uint8_t data);
    void MCU_EncoderTrigger(int dir);

    int startSC55(const uint8_t* s_rom1, const uint8_t* s_rom2, const uint8_t* s_waverom1, const uint8_t* s_waverom2, const uint8_t* s_nvram);
    void updateSC55WithSampleRate(float *dataL, float *dataR, unsigned int nFrames, int destSampleRate);
    void postMidiSC55(const uint8_t* message, int length);
    void enqueueMidiSC55(const uint8_t* message, int length, int samplePos);
    void SC55_Reset();

    uint8_t RCU_Read(void);
    uint16_t MCU_AnalogReadPin(uint32_t pin);
    void MCU_AnalogSample(int channel);
    void MCU_DeviceWrite(uint32_t address, uint8_t data);
    uint8_t MCU_DeviceRead(uint32_t address);
    void MCU_DeviceReset(void);
    void MCU_UpdateAnalog(uint64_t cycles);
    void MCU_ReadInstruction(void);
    void MCU_Init(void);
    void MCU_Reset(void);
    void MCU_PatchROM(void);

    uint32_t MCU_GetAddress(uint8_t page, uint16_t address);
    uint8_t MCU_ReadCode(void);
    uint8_t MCU_ReadCodeAdvance(void);
    void MCU_SetRegisterByte(uint8_t reg, uint8_t val);
    uint32_t MCU_GetVectorAddress(uint32_t vector);
    uint32_t MCU_GetPageForRegister(uint32_t reg);
    void MCU_ControlRegisterWrite(uint32_t reg, uint32_t siz, uint32_t data);
    uint32_t MCU_ControlRegisterRead(uint32_t reg, uint32_t siz);
    void MCU_SetStatus(uint32_t condition, uint32_t mask);
    void MCU_PushStack(uint16_t data);
    uint16_t MCU_PopStack(void);
};
