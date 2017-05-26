//
//  WDC65816TargetAsmStreamer.h
//  llvm
//
//  Created by Jeremy Rand on 2016-04-11.
//  Copyright © 2016 Jeremy Rand. All rights reserved.
//

#ifndef WDC65816TargetStreamer_h
#define WDC65816TargetStreamer_h

#include "llvm/MC/MCStreamer.h"

namespace llvm {
    class WDC65816TargetStreamer : public MCTargetStreamer {
        virtual void anchor();
        
    public:
        explicit WDC65816TargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
        virtual void EmitAutoimportDirective(void) = 0;
        virtual void EmitCodeDirective(void) = 0;
        virtual void EmitP816Directive(void) = 0;
        
        virtual void EmitFunctionEntryLabel(StringRef function) = 0;
        virtual void EmitInstruction(StringRef instruction) = 0;
    };
    
    class WDC65816TargetAsmStreamer : public WDC65816TargetStreamer {
        formatted_raw_ostream &OS;
        
        StringRef &trimFilename(StringRef &filename);
        
    public:
        WDC65816TargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS)
            : WDC65816TargetStreamer(S), OS(OS) {}
        virtual ~WDC65816TargetAsmStreamer();
        
        virtual void EmitAutoimportDirective(void);
        virtual void EmitCodeDirective(void);
        virtual void EmitP816Directive(void);
        
        virtual void EmitFunctionEntryLabel(StringRef function);
        virtual void EmitInstruction(StringRef instruction);
    };
}

#endif /* WDC65816TargetStreamer_h */
