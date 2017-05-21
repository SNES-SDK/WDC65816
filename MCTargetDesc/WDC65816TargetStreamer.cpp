//
//  WDC65816TargetAsmStreamer.cpp
//  llvm
//
//  Created by Jeremy Rand on 2016-04-11.
//  Copyright © 2016 Jeremy Rand. All rights reserved.
//

#include "WDC65816.h"
#include "WDC65816TargetStreamer.h"
#include "llvm/Support/FormattedStream.h"


using namespace llvm;


// pin vtable to this file
void WDC65816TargetStreamer::anchor() {}


WDC65816TargetAsmStreamer::~WDC65816TargetAsmStreamer()
{
}

StringRef &WDC65816TargetAsmStreamer::trimFilename(StringRef &filename)
{
    size_t lastSlash = filename.find_last_of('/');
    if (lastSlash != StringRef::npos) {
        filename = filename.drop_front(lastSlash + 1);
    }
    
    size_t lastPeriod = filename.find_last_of('.');
    if (lastPeriod != StringRef::npos) {
        filename = filename.substr(0, lastPeriod);
    }
    
    return filename;
}

void WDC65816TargetAsmStreamer::EmitCodeDirective()
{
    OS << "\t.code\n";
}

void WDC65816TargetAsmStreamer::EmitAutoimportDirective()
{
    OS << "\t.autoimport\t+\n";
}

void WDC65816TargetAsmStreamer::EmitP816Directive()
{
    OS << "\t.p816\n";
}

void WDC65816TargetAsmStreamer::EmitFunctionEntryLabel(StringRef function)
{
    OS << function;
    OS << ":\n";
}


void WDC65816TargetAsmStreamer::EmitInstruction(StringRef instruction)
{
    instruction = instruction.ltrim();
    OS << '\t';
    OS << instruction;
    OS << '\n';
}
