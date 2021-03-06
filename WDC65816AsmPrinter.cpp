//===-- WDC65816AsmPrinter.cpp - WDC65816 LLVM assembly writer ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to ca65-format 65816 assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "WDC65816.h"
#include "InstPrinter/WDC65816InstPrinter.h"
#include "WDC65816InstrInfo.h"
#include "WDC65816TargetMachine.h"
#include "MCTargetDesc/WDC65816BaseInfo.h"
#include "MCTargetDesc/WDC65816TargetStreamer.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Target/Mangler.h"

using namespace llvm;

namespace {
    class WDC65816AsmPrinter : public AsmPrinter {
        WDC65816TargetStreamer &getTargetStreamer();
        
    public:
        WDC65816AsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
            : AsmPrinter(TM, std::move(Streamer)) {}
        
        StringRef getPassName() const override {
            return "WDC65816 Assembly Printer";
        }

        void printOperand(const MachineInstr *MI, int opNum, raw_ostream &OS);
        void printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &OS,
                             const char *Modifier = 0);

        void EmitStartOfAsmFile(Module &module) override;
        void EmitFunctionEntryLabel() override;
        
        void EmitInstruction(const MachineInstr *MI) override;
    };
} // end of anonymous namespace


WDC65816TargetStreamer &WDC65816AsmPrinter::getTargetStreamer()
{
    return static_cast<WDC65816TargetStreamer &>(*OutStreamer->getTargetStreamer());
}


void WDC65816AsmPrinter::EmitStartOfAsmFile(Module &module)
{
    WDC65816TargetStreamer &streamer = getTargetStreamer();
    
    streamer.EmitP816Directive();
    streamer.EmitAutoimportDirective();
    streamer.EmitCodeDirective();
}


void WDC65816AsmPrinter::printOperand(const MachineInstr *MI, int opNum,
                                      raw_ostream &O)
{
    const MachineOperand &MO = MI->getOperand(opNum);
    switch (MO.getType()) {
        default: llvm_unreachable("Not implemented yet!");
        case MachineOperand::MO_Register:
            O << StringRef(WDC65816InstPrinter::getRegisterName(MO.getReg())).lower();
            return;
        case MachineOperand::MO_Immediate:
            O << "#" << MO.getImm();
            return;
        case MachineOperand::MO_MachineBasicBlock:
            O << *MO.getMBB()->getSymbol();
            return;
        case MachineOperand::MO_GlobalAddress: {
            O << *getSymbol(MO.getGlobal());
            return;
        }
        case MachineOperand::MO_ExternalSymbol: {
            O << MO.getSymbolName();
            return;
        }
    }
}


void WDC65816AsmPrinter::printMemOperand(const MachineInstr *MI, int opNum,
                                         raw_ostream &O, const char *Modifier)
{
    llvm_unreachable("FIXME: Implement WDC65816AsmPrinter::printMemOperand");
}


void WDC65816AsmPrinter::EmitFunctionEntryLabel()
{
    WDC65816TargetStreamer &streamer = getTargetStreamer();
    streamer.EmitFunctionEntryLabel(CurrentFnSym->getName());
}


void WDC65816AsmPrinter::EmitInstruction(const MachineInstr *MI)
{
    MCInst TmpInst;
    LowerWDC65816MachineInstrToMCInst(MI, TmpInst, *this);
    EmitToStreamer(*OutStreamer, TmpInst);
}


// Force static initialization.
extern "C" void LLVMInitializeWDC65816AsmPrinter()
{
    RegisterAsmPrinter<WDC65816AsmPrinter> X(getTheWDC65816Target());
}
