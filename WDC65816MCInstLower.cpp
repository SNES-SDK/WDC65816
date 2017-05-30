//===-- WDC65816MCInstLower.cpp - Convert WDC65816 MachineInstr to MCInst -===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower WDC65816 MachineInstrs to their
// corresponding MCInst records.
//
//===----------------------------------------------------------------------===//

#include "WDC65816.h"
//#include "MCTargetDesc/WDC65816MCExpr.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/IR/Mangler.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;


static MCOperand LowerSymbolOperand(const MachineInstr *MI,
                                    const MachineOperand &MO,
                                    AsmPrinter &AP)
{

    llvm_unreachable("FIXME: Implement LowerSymbolOperand");
}

static MCOperand LowerOperand(const MachineInstr *MI,
                              const MachineOperand &MO,
                              AsmPrinter &AP)
{
    switch(MO.getType()) {
    default:
        llvm_unreachable("unknown operand type");
        break;
    case MachineOperand::MO_Register:
        if (MO.isImplicit()) {
            break;
        }
        return MCOperand::createReg(MO.getReg());
    case MachineOperand::MO_Immediate:
        return MCOperand::createImm(MO.getImm());
    case MachineOperand::MO_MachineBasicBlock:
    case MachineOperand::MO_GlobalAddress:
    case MachineOperand::MO_BlockAddress:
    case MachineOperand::MO_ExternalSymbol:
    case MachineOperand::MO_ConstantPoolIndex:
        return LowerSymbolOperand(MI, MO, AP);
    case MachineOperand::MO_RegisterMask:
         break;
    }
    return MCOperand();
}

void llvm::LowerWDC65816MachineInstrToMCInst(const MachineInstr *MI,
                                             MCInst &OutMI,
                                             AsmPrinter &AP)
{
    OutMI.setOpcode(MI->getOpcode());

    for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
        const MachineOperand &MO = MI->getOperand(i);
        MCOperand MCOp = LowerOperand(MI, MO, AP);
        if (MCOp.isValid()) {
            OutMI.addOperand(MCOp);
        }
    }
}
