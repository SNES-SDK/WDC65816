//===-- WDC65816MCTargetDesc.cpp - WDC65816 Target Descriptions -----------===//
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

#include "WDC65816MCTargetDesc.h"
#include "WDC65816MCAsmInfo.h"
#include "WDC65816TargetStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "WDC65816GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "WDC65816GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "WDC65816GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createWDC65816MCInstrInfo() {
    MCInstrInfo *X = new MCInstrInfo();
    InitWDC65816MCInstrInfo(X);
    return X;
}

static MCRegisterInfo *createWDC65816MCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitWDC65816MCRegisterInfo(X, 0);
    return X;
}

static MCSubtargetInfo *createWDC65816MCSubtargetInfo(const Triple &TT,
                                                      StringRef CPU, StringRef FS) {
    return createWDC65816MCSubtargetInfoImpl(TT, CPU, FS);
}


#if 0
static MCCodeGenInfo *createWDC65816MCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                                   CodeModel::Model CM,
                                                   CodeGenOpt::Level OL) {
    MCCodeGenInfo *X = new MCCodeGenInfo();

    // The default 32-bit code model is abs32/pic32.
    if (CM == CodeModel::Default)
        CM = CodeModel::Medium;

    X->InitMCCodeGenInfo(RM, CM, OL);
    return X;
}
#endif


static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
    return new WDC65816TargetAsmStreamer(S, OS);
}


extern "C" void LLVMInitializeWDC65816TargetMC() {
    // Register the MC asm info.
    RegisterMCAsmInfo<WDC65816MCAsmInfo> X(getTheWDC65816Target());

#if 0
    // Register the MC codegen info.
    TargetRegistry::RegisterMCCodeGenInfo(getTheWDC65816Target(),
                                          createWDC65816MCCodeGenInfo);
#endif

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(getTheWDC65816Target(), createWDC65816MCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(getTheWDC65816Target(), createWDC65816MCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(getTheWDC65816Target(),
                                            createWDC65816MCSubtargetInfo);

    // Register the asm target streamer.
    TargetRegistry::RegisterAsmTargetStreamer(getTheWDC65816Target(), createTargetAsmStreamer);
}
