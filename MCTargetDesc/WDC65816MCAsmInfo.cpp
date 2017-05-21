//===-- WDC65816MCAsmInfo.cpp - WDC65816 asm properties -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the WDC65816MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "WDC65816MCAsmInfo.h"
#include "llvm/ADT/Triple.h"

using namespace llvm;

void WDC65816MCAsmInfo::anchor() { }

WDC65816MCAsmInfo::WDC65816MCAsmInfo(const Triple &TT) {
    IsLittleEndian = true;
    
    /*PointerSize =*/ CalleeSaveStackSlotSize = 4;
    
    // Disable the ".file <filename>" parameter
    HasSingleParameterDotFile = false;
    
    // Disable the ".size" parameter
    HasDotTypeDotSizeDirective = false;
    
    GlobalDirective = "\t.global\t";

    Data8bitsDirective = "\t.byte\t";
    Data16bitsDirective = "\t.word\t";
    Data32bitsDirective = "\t.dword\t";
    Data64bitsDirective = nullptr;
    ZeroDirective = "\t.res\t";
    // TODO need to special case this, ca65 doesn't support C escape chars
    AsciiDirective = "\t.asciiz\t";
    AscizDirective = "\t.asciiz\t";

    CommentString = ";";

    // ca65 handles this
    //TextAlignFillValue = 0xEA;

    //UseLogicalShr = true;

    //PrivateGlobalPrefix = ".L";

    //HasLEB128 = true;
    //SupportsDebugInformation = true;
    
    //ExceptionsType = ExceptionHandling::DwarfCFI;
    
    //SunStyleELFSectionSwitchSyntax = true;
    //UsesELFSectionDirectiveForBSS = true;
}
