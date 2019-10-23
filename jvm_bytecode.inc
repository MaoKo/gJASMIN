
boolean_t?  := $04
char_t?     := $05
float_t?    := $06
double_t?   := $07
byte_t?     := $08
short_t?    := $09
int_t?      := $0A
long_t?     := $0B

repeat ($03)
    repeat ($01), i:($01 shl (% - $01))
        macro u#i? line?*&
            iterate value, line
                if (value < $00) | (value >= ($01 shl ($08 * i)))
                    err "invalid operand"
                end if
                db ((value) bswap (i))
            end iterate
        end macro
        macro s#i? line?*&
            iterate value, line
                if (value < -($01 shl ($07 * i))) | (value >= ($01 shl ($07 * i)))
                    err "invalid operand"
                end if
                db ((value) bswap (i))
            end iterate
        end macro
    end repeat
end repeat

macro aaload?
    u1 ($32)
end macro

macro aastore?
    u1 ($53)
end macro

macro aconst_null?
    u1 ($01)
end macro

__wide := $C4
iterate <instr,value>,  aload,$19,  dload,$18,  iload,$15,\
                        fload,$17,  lload,$16, astore,$3A,\
                       dstore,$39, istore,$36, fstore,$38,\
                       lstore,$37,    ret,$A9,   iinc,$84
    __#instr? := value
end iterate

macro __extend_parameter? line?*&
    local token, remain, param, sign, prev
    remain equ line
    prev = not (__wide)
    if (($ - $01) - $$) 
        load prev : byte from ($ - $02)
    end if
    while ($01)
        match first =, second, remain
            token  equ first
            remain equ second
        else match _, remain
            token  equ _
            remain equ
        else
            break
        end match
        sign = $01 ; Default behavior is SIGNED
        param equ token
        match target =: _, token
            param equ target
            match =UNSIGNED?, _
                sign = $00
            else match =SIGNED?, _
            else
                err "Bad option sign"
            end match
        end match
        if (prev = __wide)
            u2 (param)
        else
            u1 (param)
        end if
    end while
end macro

iterate instr,  aload,  dload,  iload,  fload, lload, astore,\
               dstore, istore, fstore, lstore,   ret
    macro instr? varnum?*
        u1 (__#instr)
        __extend_parameter varnum:UNSIGNED
    end macro
end iterate

macro __unbroken_decl? name?*, rep?*, base?*, start?:$00, step?:$01
    local current_base
    current_base = base
    repeat (rep), i:start
        repeat $01, j:current_base
            macro name#_#i?
                u1 (j)
            end macro
        end repeat
        current_base = current_base + step
    end repeat
end macro

__unbroken_decl aload,      $04, $2A
__unbroken_decl astore,     $04, $4B
__unbroken_decl dconst,     $02, $0E
__unbroken_decl dload,      $04, $26
__unbroken_decl dstore,     $04, $47
__unbroken_decl dup_x,      $02, $5A
__unbroken_decl dup2_x,     $02, $5D
__unbroken_decl fconst,     $03, $0B
__unbroken_decl fload,      $04, $22
__unbroken_decl fstore,     $04, $43
__unbroken_decl iconst,     $06, $03
__unbroken_decl iload,      $04, $1A
__unbroken_decl impdep,     $02, $FE
__unbroken_decl istore,     $04, $3B
__unbroken_decl lconst,     $02, $09
__unbroken_decl lload,      $04, $1E
__unbroken_decl lstore,     $04, $3F

purge __unbroken_decl?

macro anewarray? type?*
    u1 ($BD)
    u2 (type)
end macro

macro areturn?
    u1 ($B0)
end macro

macro arraylength?
    u1 ($BE)
end macro

macro athrow?
    u1 ($BF)
end macro

macro baload?
    u1 ($33)
end macro

macro bastore?
    u1 ($54)
end macro

macro bipush? num?*
    u1 ($10)
    s1 (num)
end macro

macro breakpoint?
    u1 ($CA)
end macro

macro caload?
    u1 ($34)
end macro

macro castore?
    u1 ($55)
end macro

macro checkcast? type?*
    u1 ($C0)
    u2 (type)
end macro

macro d2f?
    u1 ($90)
end macro

macro d2i?
    u1 ($8E)
end macro

macro d2l?
    u1 ($8F)
end macro

macro dadd?
    u1 ($63)
end macro

macro daload?
    u1 ($31)
end macro

macro dastore?
    u1 ($52)
end macro

macro dcmpg?
    u1 ($98)
end macro

macro dcmpl?
    u1 ($97)
end macro

macro ddiv?
    u1 ($6F)
end macro

macro dmul?
    u1 ($6B)
end macro

macro dneg?
    u1 ($77)
end macro

macro drem?
    u1 ($73)
end macro

macro dreturn?
    u1 ($AF)
end macro

macro dsub?
    u1 ($67)
end macro

macro dup?
    u1 ($59)
end macro

macro dup2?
    u1 ($5C)
end macro

macro f2d?
    u1 ($8D)
end macro

macro f2i?
    u1 ($8B)
end macro

macro f2l?
    u1 ($8C)
end macro

macro fadd?
    u1 ($62)
end macro

macro faload?
    u1 ($30)
end macro

macro fastore?
    u1 ($51)
end macro

macro fcmpg?
    u1 ($96)
end macro

macro fcmpl?
    u1 ($95)
end macro

macro fdiv?
    u1 ($6E)
end macro

macro fmul?
    u1 ($6A)
end macro

macro fneg?
    u1 ($76)
end macro

macro frem?
    u1 ($72)
end macro

macro freturn?
    u1 ($AE)
end macro

macro fsub?
    u1 ($66)
end macro

macro getfield? index?*
    u1 ($B4)
    u2 (index)
end macro

macro getstatic? index?*
    u1 ($B2)
    u2 (index)
end macro

macro goto? label?*
    local offset
    offset = ((label) - $)
    u1 ($A7)
    s2 (offset)
end macro

macro goto_w? label?*
    local offset
    offset = ((label) - $)
    u1 ($C8)
    s4 (offset)
end macro

macro i2b?
    u1 ($91)
end macro

macro i2c?
    u1 ($92)
end macro

macro i2d?
    u1 ($87)
end macro

macro i2f?
    u1 ($86)
end macro

macro i2l?
    u1 ($85)
end macro

macro i2s?
    u1 ($93)
end macro

macro iadd?
    u1 ($60)
end macro

macro iaload?
    u1 ($2E)
end macro

macro iand?
    u1 ($7E)
end macro

macro iastore?
    u1 ($4F)
end macro

macro iconst_m1?
    u1 ($02)
end macro

macro idiv?
    u1 ($6C)
end macro

iterate <cond,opcd>, eq,$A5, ne,$A6
    macro if_acmp#cond? label?
        local offset
        offset = ((label) - $)
        u1 (opcd)
        s2 (offset)
    end macro
end iterate

iterate <cond,opcd>, eq,$9F, ge,$A2, gt,$A3,\
                     le,$A4, lt,$A1, ne,$A0
    macro if_icmp#cond? label?
        local offset
        offset = ((label) - $)
        u1 (opcd)
        s2 (offset)
    end macro
end iterate

iterate <cond,opcd>, eq,$99, ge,$9C,      gt,$9D,   le,$9E,\
                     lt,$9B, ne,$9A, nonnull,$C7, null,$C6
    macro if#cond? label?
        local offset
        offset = ((label) - $)
        u1 (opcd)
        s2 (offset)
    end macro
end iterate

macro iinc? varnum?*, num?*
    u1 ($84)
    __extend_parameter varnum:UNSIGNED, num
end macro

macro imul?
    u1 ($68)
end macro

macro ineg?
    u1 ($74)
end macro

macro instanceof? type?*
    u1 ($C1)
    u2 (type)
end macro

macro invokedynamic? index?*
    u1 ($B1)
    u2 (index)
    u1 ($00)
    u1 ($00)
end macro

macro invokeinterface? index?*, n?*
    u1 ($B9)
    u2 (index)
    u1 (n)
    u1 ($00) ; cache hashing storage
end macro

iterate <kind,opcd>, virtual,$B6, special,$B7, static,$B8
    macro invoke#kind? index?*
        u1 (opcd)
        u2 (index)
    end macro
end iterate

macro ior?
    u1 ($80)
end macro

macro irem?
    u1 ($70)
end macro

macro ireturn?
    u1 ($AC)
end macro

macro ishl?
    u1 ($78)
end macro

macro ishr?
    u1 ($7A)
end macro

macro isub?
    u1 ($64)
end macro

macro iushr?
    u1 ($7C)
end macro

macro ixor?
    u1 ($82)
end macro

macro jsr? label?
    local offset
    offset = ((label) - $)
    u1 ($A8)
    s2 (offset)
end macro

macro jsr_w? label?
    local offset
    offset = ((label) - $)
    u1 ($C9)
    s4 (offset)
end macro

macro l2d?
    u1 ($8A)
end macro

macro l2f?
    u1 ($89)
end macro

macro l2i?
    u1 ($88)
end macro

macro ladd?
    u1 ($61)
end macro

macro laload?
    u1 ($2F)
end macro

macro land?
    u1 ($7F)
end macro

macro lastore?
    u1 ($50)
end macro

macro lcmp?
    u1 ($94)
end macro

macro ldc? index?*
    u1 ($12)
    u1 (index)
end macro

macro ldc_w? index?*
    u1 ($13)
    u2 (index)
end macro

macro ldc2_w? index?*
    u1 ($14)
    u2 (index)
end macro

macro ldiv?
    u1 ($6D)
end macro

macro lmul?
    u1 ($69)
end macro

macro lneg?
    u1 ($75)
end macro

; Maybe change the decl in another file ...
macro align? upto?*, fill?:$00
    if ((bsf upto) <> (bsr upto))
        err "invalid operand"
    end if
    while ($ mod upto)
        db fill
    end while
end macro

macro lookupswitch?
    local key_count, key_list, key_value, assert_unique
    macro assert_unique? key?*
        if (definite key_list)
            irpv value, key_list
                if (value = key)
                    err "redefinition of key"
                end if
            end irpv
        end if
    end macro

    key_count = $00
    macro key? line&
        local offset, token, remain, range
        match keys =: label, line
            offset = ((label) - $)
            remain equ keys
            while ($01)
                match next =, _, remain
                    token  equ next
                    remain equ _
                else match _, remain
                    token  equ _
                    remain equ
                else
                    break
                end match
                match first =.=.=. last, token
                    if (last < first)
                        err "invalid operand"
                    end if
                    range = (last - first + $01)
                    key_count = key_count + range
                    repeat (range), i:(first)
                        assert_unique i
                        key_list  =: i
                        key_value =: offset
                    end repeat
                else
                    key_count = key_count + $01
                    assert_unique token
                    key_list  =: token
                    key_value =: offset
                end match
            end while
        else
            err "invalid syntax"
        end match
    end macro

    macro default? line?*&
        local offset
        purge key?, default?
        match =: label, line
            offset = ((label) - $)
            u1 ($AB)
            align $04
            s4 (offset)
            s4 (key_count)
            repeat (key_count), i:($01)
                s4 key_list, key_value
                restore key_list, key_value
            end repeat
        else
            err "invalid syntax"
        end match
    end macro
end macro

macro lor?
    u1 ($81)
end macro

macro lrem?
    u1 ($71)
end macro

macro lreturn?
    u1 ($AD)
end macro

macro lshl?
    u1 ($79)
end macro

macro lshr?
    u1 ($7B)
end macro

macro lsub?
    u1 ($65)
end macro

macro lushr?
    u1 ($7D)
end macro

macro lxor?
    u1 ($83)
end macro?

macro monitorenter?
    u1 ($C2)
end macro

macro monitorexit?
    u1 ($C3)
end macro

macro multianewarray? index?*, n?*
    if (~(n))
        err "invalid operand"
    end if
    u1 ($C5)
    u2 (index)
    u1 (n)
end macro

macro new? index?*
    u1 ($BB)
    u2 (index)
end macro

macro newarray? type?*
    u1 ($BC)
    u2 (type)
end macro

macro nop?
    u1 ($00)
end macro

macro pop?
    u1 ($57)
end macro

macro pop2?
    u1 ($58)
end macro

macro putfield? index?*
    u1 ($B5)
    u2 (index)
end macro

macro putstatic? index?*
    u1 ($B3)
    u2 (index)
end macro

macro return?
    u1 ($B1)
end macro

macro saload?
    u1 ($35)
end macro

macro sastore?
    u1 ($56)
end macro

macro sipush? n?*
    u1 ($11)
    s2 (n)
end macro

macro swap?
    u1 ($5F)
end macro

macro tableswitch? low?*, high?
    local label_list, count_label
    count_label = $00
    macro ? line&
        local offset
        match =default? =: label, line
            purge ?
            match _, high
                if (_ < low) | ((_ - low + $01) <> count_label)
                    err "invalid operand"
                end if
            end match
            offset = ((label) - $)
            u1 ($AA)
            align $04
            s4 (offset)
            s4 (low)
            s4 (count_label)
            irpv value, label_list
                indx (%% - % + $01)
                s4 (value)
            end irpv
        else match label, line
            label_list =: ((label) - $)
            count_label = count_label + $01
        end match
    end macro
end macro

macro wide? line?&
    local area_wide, next, found
    u1 (__wide)
    found = $00
    load next : byte from area_wide : $ 
    iterate value,  aload,  dload,  iload,  fload, lload, astore,\
                   dstore, istore, fstore, lstore,   ret,   iinc
        if (next = __#value)
            found = $01
            break
        end if
    end iterate
    if (~(found))
        err "Bad opcode after wide instruction"
    end if
    area_wide::
    line
end macro
