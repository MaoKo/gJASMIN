
include "jvm_bytecode.inc"

MAGIC?              := $CAFEBABE
ACC_PUBLIC?         := $00000001
ACC_PRIVATE?        := $00000002
ACC_PROTECTED?      := $00000004
ACC_STATIC?         := $00000008
ACC_FINAL?          := $00000010
ACC_SUPER?          := $00000020
ACC_SYNCHRONIZED?   := $00000020
ACC_BRIDGE?         := $00000040
ACC_VOLATILE?       := $00000040
ACC_VARARGS?        := $00000080
ACC_TRANSIENT?      := $00000080
ACC_NATIVE?         := $00000100
ACC_INTERFACE?      := $00000200
ACC_ABSTRACT?       := $00000400
ACC_STRICT?         := $00000800
ACC_SYNTHETIC?      := $00001000
ACC_ANNOTATION?     := $00002000
ACC_ENUM?           := $00004000

macro constant_pool?
    local constant_pool_counter, constant_pool_count
    __constant_pool_counter equ constant_pool_counter
    __constant_pool_count   equ constant_pool_count

    constant_pool_counter = $01
    u2 (constant_pool_count)

    struc constant_utf8? string?*&
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        local data, length
        u1 ($01)
        u2 (length)
        data: db string
        length = ($ - data)
    end struc

    struc constant_integer? value?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($03)
        db ((value) bswap ($04))
    end struc

    struc constant_float? value?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($04)
        db ((value) bswap ($04))
    end struc

    struc constant_long? value?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $02
        u1 ($05)
        db ((value) bswap ($08))
    end struc

    struc constant_double? value?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $02
        u1 ($06)
        db ((value) bswap ($08))
    end struc

    struc constant_class? index?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($07)
        db ((index) bswap ($02))
    end struc

    struc constant_string? index?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($08)
        db ((index) bswap ($02))
    end struc

    struc constant_fieldref? cindex?*, ntindex?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($09)
        db ((cindex)  bswap ($02))
        db ((ntindex) bswap ($02))
    end struc

    struc constant_methodref? cindex?*, ntindex?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($0A)
        db ((cindex)  bswap ($02))
        db ((ntindex) bswap ($02))
    end struc

    struc constant_interfacemethodref? cindex?*, ntindex?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($0B)
        db ((cindex)  bswap ($02))
        db ((ntindex) bswap ($02))
    end struc

    struc constant_nameandtype? nindex?*, tindex?*
        . = constant_pool_counter
        constant_pool_counter = constant_pool_counter + $01
        u1 ($0C)
        db ((nindex) bswap ($02))
        db ((tindex) bswap ($02))
    end struc
end macro

macro end?.constant_pool?
    match count counter, __constant_pool_count __constant_pool_counter
        count := ((counter) - $01)
    end match
    restore __constant_pool_counter, __constant_pool_count
    restruc constant_utf8?,                 \
            constant_integer?,              \
            constant_float?,                \
            constant_long?,                 \
            constant_double?,               \
            constant_class?,                \
            constant_string?,               \
            constant_fieldref?,             \ 
            constant_methodref?,            \
            constant_interfacemethodref?,   \
            constant_nameandtype? 
end macro

macro interfaces?
    local interfaces_counter, interfaces_count
    __interfaces_counter equ interfaces_counter
    __interfaces_count   equ interfaces_count

    interfaces_counter = $00
    u2 (interfaces_count)

    macro interface? index?*
        interfaces_counter = interfaces_counter + $01
        u2 (index)
    end macro
end macro

macro end?.interfaces?
    match count counter, __interfaces_count __interfaces_counter
        count := (counter)
    end match
    restore __interfaces_counter, __interfaces_count
    purge interface?
end macro

macro attributes?
    local attributes_counter, attributes_count
    __attributes_counter equ attributes_counter
    __attributes_count   equ attributes_count
    
    attributes_counter = $00
    u2 (attributes_count)

    macro attribute? name_index?*
        local begin, length
        __attribute_begin  equ begin
        __attribute_length equ length
        attributes_counter = attributes_counter + $01
        u2 (name_index)
        u4 (length)
        begin := $
    end macro
       
    macro end?.attribute?
        match beg len, __attribute_begin __attribute_length
            len := ($ - (beg))
        end match
        restore __attribute_begin, __attribute_length
    end macro
end macro

macro end?.attributes?
    match count counter,  __attributes_count __attributes_counter
        count := (counter)
    end match
    restore __attributes_counter, __attributes_count
    purge attribute?, end?.attribute?
end macro

macro fields?
    local fields_counter, fields_count
    __fields_counter equ fields_counter
    __fields_count   equ fields_count
    
    fields_counter = $00
    u2 (fields_count)
    
    macro field? access_flag?*, name_index?*, descriptor_index?*
        __fields_counter = __fields_counter + $01
        u2 (access_flag)
        u2 (name_index)
        u2 (descriptor_index)
        attributes
    end macro
    macro end?.field?
        end attributes
    end macro
end macro

macro end?.fields?
    match count counter, __fields_count __fields_counter
        count := (counter)
    end match
    purge field?, end?.field?
end macro

macro methods?
    local methods_counter, methods_count
    __methods_counter equ methods_counter
    __methods_count   equ methods_count
    
    methods_counter = $00
    u2 (methods_count)
    
    macro method? access_flag?*, name_index?*, descriptor_index?*
        methods_counter = methods_counter + $01
        u2 (access_flag)
        u2 (name_index)
        u2 (descriptor_index)

        attributes
        macro bytecode? code_index?*, stack?:$01, locals?:$01
            local begin, length
            __bytecode_begin  equ begin
            __bytecode_length equ length
            attribute code_index
            u2 (stack)
            u2 (locals)
            u2 (length)
            begin := $
            org $00
            ;macro exceptions?
            ;end macro
        end macro
        macro end?.bytecode?
            match beg len, __bytecode_begin __bytecode_length
                len := $
                org (beg + len)
            end match
            end attribute
            restore __bytecode_begin, __bytecode_length
        end macro
    end macro
    macro end?.method?
        end attributes
        purge bytecode?, end?.bytecode?
    end macro
end macro

macro end?.methods?
    match count counter, __methods_count __methods_counter
        count := (counter)
    end match
    purge method?, end?.method?
end macro

;methods
;    method ACC_PUBLIC, $00, $01
;        bytecode $00
;           aload_1
;        end bytecode
;    end method
;end methods
