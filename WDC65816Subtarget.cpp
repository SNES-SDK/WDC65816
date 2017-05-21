//===-- WDC65816Subtarget.cpp - WDC65816 Subtarget Information ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the WDC65816 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "WDC65816Subtarget.h"

//#include "llvm/Support/ELF.h"
#include "llvm/Support/TargetRegistry.h"

#include "WDC65816.h"
#include "WDC65816TargetMachine.h"
#include "MCTargetDesc/WDC65816MCTargetDesc.h"

#define DEBUG_TYPE "wdc65816-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "WDC65816GenSubtargetInfo.inc"

namespace llvm {

    WDC65816Subtarget::WDC65816Subtarget(const Triple &TT, const std::string &CPU,
        const std::string &FS, WDC65816TargetMachine &TM)
        : WDC65816GenSubtargetInfo(TT, CPU, FS), InstrInfo(), FrameLowering(),
        TLInfo(TM), TSInfo() {

        // Parse features string.
        ParseSubtargetFeatures(CPU, FS);
    }

} // end of namespace llvm
