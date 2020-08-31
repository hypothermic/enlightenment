# Enlightenment Remote Communication Protocol

## Preface

This is a Work In Progress project. There has not been any working implementation written yet.

## Introduction

Interact with your database server from afar using [SCTP](https://en.wikipedia.org/wiki/Stream_Control_Transmission_Protocol).

Caution: because Enlightenment doesn't have users or authentication,
it's suggested you use a private network or secure it using your own authentication structure.

Endianness is determined by the platform which the server is run upon.

## Packets

All packets/messages are prefixed with a single unsigned byte containing the Operation Code.

Here's a list of all packets with their opcode:

| Hex  | Dec  |                   Name                 | Sent by |
| :--- | :--- | :------------------------------------- | :-----: |
| 0x01 | 1    | [Login Request](#login-request-0x01)   | C       |
| 0x02 | 2    | [Login Response](#login-response-0x02) | S       |

`C` indicates the packet is sent by the client.  
`S` indicates the packet is sent by the server.

## Protocol Versions

For future proofing the protocol, a basic number is sent along with some packets
which indicates the version the client/server is currently using.
Currently, this has no effect on the working of the program,
however in the future the client/server may disconnect if the protocol version mismatches or is outdated.

| Hex  | Dec  |              Description             | Start date  | End date    | Last supported git commit |
| :--- | :--- | :----------------------------------: | :---------: | :---------: | :-----------------------: |
| 0x01 | 1    | Draft protocol (alpha stage)         | 31 Aug 2020 |      -      |             -             |

## Response Statuses

A response status indicates if the action has been successful or not.
These are always encoded as 8-bit unsigned integers.

| Hex  | Dec  |              Description             |          Notes           |
| :--- | :--- | :----------------------------------- | :----------------------- |
| 0x00 | 0    | Success                              |                          |
| 0x0A | 10   | Invalid request: unauthenticated     | Unused. Future-proofing. |
| 0x0B | 11   | Invalid request: unknown opcode      |                          |
| 0x0C | 12   | Invalid request: invalid size        |                          |
| 0x0D | 13   | Invalid request: invalid parameters  |                          |
| 0x14 | 20   | Server error                         |                          |

## List of packets

A comprehensive list of all packets with all their fields is available in this chapter.

### Login Request (0x01)

| Offset | Field Name                             | Field Type          | Example value | Notes               |
| :----- | :------------------------------------- | :------------------ | :------------ | :------------------ |
| 0x00   | [Protocol Version](#protocol-versions) | 8-bit unsigned int  | 1             |                     |
| 0x01   | Target IP address                      | 32-bit unsigned int |               | For virtual hosting |

### Login Response (0x02)

| Offset | Field Name                             | Field Type          | Example value | Notes               |
| :----- | :------------------------------------- | :------------------ | :------------ | :------------------ |
| 0x00   | [Status](#response-statuses)           | 8-bit unsigned int  | 0             |                     |