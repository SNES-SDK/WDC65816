//===-- WDC65816InstPrinter.cpp - Convert WDC65816 MCInst to assembly syntax -----==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints a WDC65816 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "WDC65816InstPrinter.h"
#include "WDC65816.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#if 0
// The generated AsmMatcher SparcGenAsmWriter uses "Sparc" as the target
// namespace. But SPARC backend uses "SP" as its namespace.
namespace llvm {
    namespace Sparc {
        using namespace SP;
    }
}
#endif

#define GET_INSTRUCTION_NAME
#define PRINT_ALIAS_INSTR
#include "WDC65816GenAsmWriter.inc"

void WDC65816InstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const
{
    OS << '%' << StringRef(getRegisterName(RegNo)).lower();
}

void WDC65816InstPrinter::printInst(const MCInst *MI, raw_ostream &O,
    StringRef Annot, const MCSubtargetInfo &STI)
{
    llvm_unreachable("FIXME: Implement WDC65816InstPrinter::printInst");
}

void WDC65816InstPrinter::printOperand(const MCInst *MI, int opNum,
    raw_ostream &O)
{
    llvm_unreachable("FIXME: Implement WDC65816InstPrinter::printOperand");
}

void WDC65816InstPrinter::printMemOperand(const MCInst *MI, int opNum,
    raw_ostream &O, const char *Modifier)
{
    llvm_unreachable("FIXME: Implement WDC65816InstPrinter::printMemOperand");
}
