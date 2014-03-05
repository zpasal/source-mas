        .device p12ce518
        .include p12ce518.inc

ScratchPadRam = 0x20
CountDown     = ScratchPadRam+0
Doubler       = ScratchPadRam+1
OuterLoop     = ScratchPadRam+2


      .org     0
                goto    Start
      .org     0x50
Start:
                movlw   255             ;   Initialize the variables to
                movwf   CountDown       ; their starting values.
                movlw   1
                movwf   Doubler
                movlw   7
                movwf   OuterLoop
Loop:
                call    Reduce          ;   Perform the inner portion of
                decfsz  OuterLoop,F     ; the loop.
                goto    Loop

                goto    Start           ;   Repeat the whole thing.

;--------------------------------------------------------------------------
Reduce:
                swapf   Doubler,F       ;   Reduce CountDown by the
                swapf   Doubler,W       ; value of Doubler.  Then
                swapf   Doubler,F       ; call the doubling routine.
                subwf   CountDown,F
                call    Double
                retlw   0

;--------------------------------------------------------------------------
Double:
                swapf   Doubler,F       ;   Double the value of Doubler
                swapf   Doubler,W       ; by adding it to itself.
                swapf   Doubler,F
                addwf   Doubler,F
                retlw   0


