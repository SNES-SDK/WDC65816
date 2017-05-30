//===- WDC65816.h - Top-level interface for WDC65816 representation -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// WDC65816 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef WDC65816_H
#define WDC65816_H

#include "MCTargetDesc/WDC65816MCTargetDesc.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetMachine.h"


#define WDC_LOG(X) DEBUG_WITH_TYPE("WDC", wdc_dbgs(__FILE__, __func__, __LINE__) << X << "\n");

namespace llvm {
    class FunctionPass;
    class WDC65816TargetMachine;
    class AsmPrinter;
    class MCInst;
    class MachineInstr;

    FunctionPass *createWDC65816ISelDag(WDC65816TargetMachine &TM);
    void LowerWDC65816MachineInstrToMCInst(const MachineInstr *MI,
                                           MCInst &OutMI,
                                           AsmPrinter &AP);
} // end namespace llvm;

#endif
