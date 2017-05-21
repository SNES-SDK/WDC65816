//===-- WDC65816MCTargetDesc.h - WDC65816 Target Descriptions ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides WDC65816 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WDC65816_MCTARGETDESC_WDC65816MCTARGETDESC_H
#define LLVM_LIB_TARGET_WDC65816_MCTARGETDESC_WDC65816MCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectWriter;
class MCRegisterInfo;
class MCTargetOptions;
class StringRef;
class Target;
class Triple;
class raw_pwrite_stream;

Target &getTheWDC65816Target();

/// Creates a machine code emitter for WDC65816.
MCCodeEmitter *createWDC65816MCCodeEmitter(const MCInstrInfo &MCII,
                                           const MCRegisterInfo &MRI,
                                           MCContext &Ctx);

/// Creates an assembly backend for WDC65816.
MCAsmBackend *createWDC65816AsmBackend(const Target &T, const MCRegisterInfo &MRI,
                                       const Triple &TT, StringRef CPU,
                                       const llvm::MCTargetOptions &TO);

/// Creates an ELF object writer for WDC65816.
MCObjectWriter *createWDC65816ELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for WDC65816 registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "WDC65816GenRegisterInfo.inc"

// Defines symbolic names for the WDC65816 instructions.
//
#define GET_INSTRINFO_ENUM
#include "WDC65816GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "WDC65816GenSubtargetInfo.inc"

#endif
