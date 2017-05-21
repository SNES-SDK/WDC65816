//===- WDC65816FrameLowering.h - Define frame lowering for Sparc -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef WDC65816_FRAMEINFO_H
#define WDC65816_FRAMEINFO_H

#include "WDC65816.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
    class WDC65816Subtarget;
    
    class WDC65816FrameLowering : public TargetFrameLowering {
    public:
        WDC65816FrameLowering() : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 1, 0) {}

        bool hasFP(const MachineFunction &MF) const override;

        /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
        /// the function.
        void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
        void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
    };
    
} // End llvm namespace

#endif
