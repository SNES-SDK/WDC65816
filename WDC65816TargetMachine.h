//===-- WDC65816TargetMachine.h - Define TargetMachine for WDC65816 --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the WDC65816 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_WDC65816_TARGET_MACHINE_H
#define LLVM_WDC65816_TARGET_MACHINE_H

#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#include "WDC65816FrameLowering.h"
//#include "WDC65816SelLowering.h"
#include "WDC65816InstrInfo.h"
//#include "WDC65816SelectionDAGInfo.h"
#include "WDC65816Subtarget.h"

namespace llvm {

    /// A generic WDC65816 implementation.
    class WDC65816TargetMachine : public LLVMTargetMachine {
    public:
        WDC65816TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
            StringRef FS, const TargetOptions &Options, Optional<Reloc::Model> RM,
            CodeModel::Model CM, CodeGenOpt::Level OL);

        const WDC65816Subtarget *getSubtargetImpl() const;
        const WDC65816Subtarget *getSubtargetImpl(const Function &) const override;

        TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

    private:
        WDC65816Subtarget SubTarget;
    };

} // end namespace llvm

#endif // LLVM_WDC65816_TARGET_MACHINE_H
