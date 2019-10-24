
macro format?.class?
    format binary as "class"

    include "jvm_class.inc"
    include "switch.inc"

    virtual at $00
        __constant_pool::
        constant_pool
    end virtual

    __cpool_list equ
    restore __cpool_list

    macro __add_cpool_utf8? string?*, retidx?*
        assert (string eqtype "")
        retidx = $00
        irpv tuple, __cpool_list
            match tag=,index=,value, tuple
                if (tag eq _TAG_UTF8) & (string eq value)
                    retidx = index
                    break
                end if
            end match
        end irpv
        if (~(retidx))
            virtual __constant_pool
                retidx constant_utf8 string
            end virtual
            repeat $01, i:retidx
                __cpool_list reequ _TAG_UTF8,i,string
            end repeat
        end if
    end macro

;    macro __add_cpool_entry? value?*, target?*, ret?*
;        local new_entry, expand_value
;        expand_value equ value
;        match _1 =: _2, value
;            assert (_1 eqtype "")
;            assert (_2 eqtype "")
;        else if (value eqtype "")
;        end match
;
;        ret = $00
;        irpv tuple, __cpool_list
;            match entry =, entry_value, tuple
;                if (entry eq target) & (entry_value eq value)
;                    ret = target ; constant-pool start with $01
;                    break
;                end if
;            end match
;        end irpv
;        if (~(ret))
;            virtual __constant_pool
;                switch (target)
;                    case (_TAG_INTEGER):    assert (value eqtype $00)
;                                            new_entry constant_integer value
;                                            break
;
;                    case (_TAG_LONG):       assert (value eqtype $00)
;                                            new_entry constant_long value
;                                            break
;
;                    case (_TAG_FLOAT):      new_entry constant_float value
;                    case (_TAG_DOUBLE):     new_entry constant_double value
;                    default:                err "invalid operand"
;                end switch
;            end virtual
;            __cpool_list reequ new_entry, value
;            ret = new_entry
;        end if
;    end macro

    _source = __source__
    macro @source? filename?*
        assert (filename eqtype "")
        _source = filename
    end macro
 
    _minor = $00
    _major = $37
    macro @version? minor?*, major?*
        assert (minor eqtype $00) & (major eqtype $00)
        _minor = minor
        _major = major
    end macro

    macro @class? line?*&
    end macro

    macro @super? super_class?*
        assert (super_class eqtype "")
        __find_cpool super_class, _TAG_CLASS
    end macro

;    postpone $
;       __add_cpool_entry "Code", _TAG_STRING, __Code
;       virtual __constant_pool
;           end constant_pool
;           __length_cpool := $
;       end virtual
;        u4 (MAGIC)
;        u2 (minor)
;        u2 (major)
;       repeat __length_cpool
;           load
;           store
;       end repeat
;    end postpone
end macro

