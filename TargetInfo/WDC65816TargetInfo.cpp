//===-- WDC65816TargetInfo.cpp - WDC65816 Target Implementation -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

namespace llvm {
Target &getTheWDC65816Target() {
  static Target TheWDC65816Target;
  return TheWDC65816Target;
}
}

extern "C" void LLVMInitializeWDC65816TargetInfo() {
  llvm::RegisterTarget<llvm::Triple::wdc65816> X(llvm::getTheWDC65816Target(),
                                                 "wdc65816",
                                                 "WDC 65816");
}
