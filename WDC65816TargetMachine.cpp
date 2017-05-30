//===--- WDC65816TargetMachine.cpp - Define TargetMachine for WDC65816 ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the WDC65816 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#include "WDC65816TargetMachine.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"

//#include "WDC65816TargetObjectFile.h"
#include "MCTargetDesc/WDC65816MCTargetDesc.h"

namespace llvm {

    static const char *WDC65816DataLayout = "e-p:32:8:8-i8:8:8-i16:8:8-i32:8:8-n8:16";

    static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
        return RM.hasValue() ? *RM : Reloc::Static;
    }

    WDC65816TargetMachine::WDC65816TargetMachine(const Target &T, const Triple &TT,
        StringRef CPU, StringRef FS,
        const TargetOptions &Options,
        Optional<Reloc::Model> RM, CodeModel::Model CM,
        CodeGenOpt::Level OL)
        : LLVMTargetMachine(
            T, WDC65816DataLayout, TT,
            CPU, FS, Options, getEffectiveRelocModel(RM), CM, OL),
        SubTarget(TT, CPU, FS, *this) {
        //this->TLOF = make_unique<AVRTargetObjectFile>();
        initAsmInfo();
    }

    namespace {
        /// WDC65816 Code Generator Pass Configuration Options.
        class WDC65816PassConfig : public TargetPassConfig {
        public:
            WDC65816PassConfig(WDC65816TargetMachine *TM, PassManagerBase &PM)
                : TargetPassConfig(TM, PM) {}

            WDC65816TargetMachine &getWDC65816TargetMachine() const {
                return getTM<WDC65816TargetMachine>();
            }

            bool addInstSelector() override;
            void addPreSched2() override;
            void addPreRegAlloc() override;
        };
    } // namespace

    TargetPassConfig *WDC65816TargetMachine::createPassConfig(PassManagerBase &PM) {
        return new WDC65816PassConfig(this, PM);
    }

    extern "C" void LLVMInitializeWDC65816Target() {
        // Register the target.
        RegisterTargetMachine<WDC65816TargetMachine> X(getTheWDC65816Target());

#if 0
        auto &PR = *PassRegistry::getPassRegistry();
        initializeWDC65816ExpandPseudoPass(PR);
        initializeWDC65816InstrumentFunctionsPass(PR);
        initializeWDC65816RelaxMemPass(PR);
#endif
    }

    const WDC65816Subtarget *WDC65816TargetMachine::getSubtargetImpl() const {
        return &SubTarget;
    }

    const WDC65816Subtarget *WDC65816TargetMachine::getSubtargetImpl(const Function &) const {
        return &SubTarget;
    }

    //===----------------------------------------------------------------------===//
    // Pass Pipeline Configuration
    //===----------------------------------------------------------------------===//

    bool WDC65816PassConfig::addInstSelector() {
        // Install an instruction selector.
        addPass(createWDC65816ISelDag(getWDC65816TargetMachine()));
#if 0
        // Create the frame analyzer pass used by the PEI pass.
        addPass(createWDC65816FrameAnalyzerPass());
#endif

        return false;
    }

    void WDC65816PassConfig::addPreRegAlloc() {
#if 0
        // Create the dynalloc SP save/restore pass to handle variable sized allocas.
        addPass(createWDC65816DynAllocaSRPass());
#endif
    }

    void WDC65816PassConfig::addPreSched2() {
#if 0
        addPass(createWDC65816RelaxMemPass());
        addPass(createWDC65816ExpandPseudoPass());
#endif
    }

} // end of namespace llvm
