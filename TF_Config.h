//
// TinyFrame configuration file.
//
// Rename to TF_Config.h
//

#pragma once

#include <stdint.h>
#include <stdio.h> // used by the TF_Error() macro defined below
//#include <esp8266.h> // when using with esphttpd

#include "OS_Dataport.h"

//----------------------------- FRAME FORMAT ---------------------------------
// The format can be adjusted to fit your particular application needs

// If the connection is reliable, you can disable the SOF byte and checksums.
// That can save up to 9 bytes of overhead.

// ,-----+-----+-----+------+------------+- - - -+-------------,
// | SOF | ID  | LEN | TYPE | HEAD_CKSUM | DATA  | DATA_CKSUM  |
// | 0-1 | 1-4 | 1-4 | 1-4  | 0-4        | ...   | 0-4         | <- size (bytes)
// '-----+-----+-----+------+------------+- - - -+-------------'

// !!! BOTH PEERS MUST USE THE SAME SETTINGS !!!

// Adjust sizes as desired (1,2,4)
#define TF_ID_BYTES 1
#define TF_LEN_BYTES 2
#define TF_TYPE_BYTES 1

// Checksum type. Options:
//   TF_CKSUM_NONE, TF_CKSUM_XOR, TF_CKSUM_CRC8, TF_CKSUM_CRC16, TF_CKSUM_CRC32
//   TF_CKSUM_CUSTOM8, TF_CKSUM_CUSTOM16, TF_CKSUM_CUSTOM32
// Custom checksums require you to implement checksum functions (see TinyFrame.h)
#define TF_CKSUM_TYPE TF_CKSUM_CRC16

// Use a SOF byte to mark the start of a frame
#define TF_USE_SOF_BYTE 1
// Value of the SOF byte (if TF_USE_SOF_BYTE == 1)
#define TF_SOF_BYTE 0x01

//----------------------- PLATFORM COMPATIBILITY ----------------------------

// used for timeout tick counters - should be large enough for all used timeouts
typedef uint16_t TF_TICKS;

// used in loops iterating over listeners
typedef uint8_t TF_COUNT;

//----------------------------- PARAMETERS ----------------------------------

// Maximum received payload size (static buffer)
// Larger payloads will be rejected.

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *  DISCLAIMER
 * BELOW define TF_MAX_PAYLOAD_RX is done considering  max Ethernet FRAME which is usually 1560 bytes.
 * PLEASE DO NOT ALTER THIS UNTIL YOU KNOW WHAT YOU DO
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
// Plz read disclaimer before changing this
#define TF_MAX_PAYLOAD_RX OS_DATAPORT_DEFAULT_SIZE

// Size of the sending buffer. Larger payloads will be split to pieces and sent
// in multiple calls to the write function. This can be lowered to reduce RAM usage.
#define TF_SENDBUF_LEN OS_DATAPORT_DEFAULT_SIZE

// --- Listener counts - determine sizes of the static slot tables ---

// Frame ID listeners (wait for response / multi-part message)
#define TF_MAX_ID_LST 10
// Frame Type listeners (wait for frame with a specific first payload byte)
#define TF_MAX_TYPE_LST 10
// Generic listeners (fallback if no other listener catches it)
#define TF_MAX_GEN_LST 5

// Timeout for receiving & parsing a frame
// ticks = number of calls to TF_Tick()
#define TF_PARSER_TIMEOUT_TICKS 10

// Whether to use mutex - requires you to implement TF_ClaimTx() and TF_ReleaseTx()
#define TF_USE_MUTEX 0

// Error reporting function. To disable debug, change to empty define
#define TF_Error(format, ...) printf("[TF] " format "\n", ##__VA_ARGS__)

#if (TF_CKSUM_TYPE == TF_CKSUM_CRC16)
#define TF_OVERHEAD_SIZE \
    (TF_ID_BYTES + TF_LEN_BYTES + TF_TYPE_BYTES + 5) // CRC(2) x 2 + SOF(1)
#else
#error "please define this case!!"
#endif
//------------------------- End of user config ------------------------------
