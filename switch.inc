macro switch? item?*
    local default_match, case_match, count_exec, list_value, used_default, already_match
    default_match   = $00
    case_match      = $00
    count_exec      = $00
    used_default    = $00
    already_match   = $00
    define list_value

    macro case? value?*
        irpv it, list_value
            match _, it
                if (_ eq value)
                    err "case value redifinition"
                end if
            end match
        end irpv
        list_value equ value
        if (item eq value)
            purge_invoker
            case_match = $01
        end if
    end macro

    macro default?
        if (used_default)
            err "default label has been encounter more than one"
        end if
        default_match = $01
        used_default  = $01
    end macro

    macro parse_switch? line&
        local buffer
        buffer equ line
        while $01
            match =case? _, buffer
                match value =: rest, _
                    buffer equ rest
                    case value
                else match value =:, _
                    buffer equ
                    case value
                else
                    err "case must be followed by a ':' character"
                    break
                end match
            else match =case?, buffer
                err "case cannot be alone"
                break
            else match =default? _, buffer
                match =: rest, _
                    buffer equ rest
                else match =:, _
                    buffer equ
                else
                    err "default must be follow by a ':' character"
                    break
                end match
                default
            else match =default?, buffer
                err "default cannot be alone"
                break
            else
                match =break?, buffer
                    if (case_match)
                        already_match = $01
                    end if
                    case_match    = $00
                    default_match = $00
                end match
                break
            end match
        end while
        if ((case_match) | (default_match)) & ~ (already_match)
            add_invoker buffer
        end if
    end macro

    macro add_invoker? line&
        match _, line
            count_exec = count_exec + $01
            macro exec_invoker
                exec_invoker
                _
            end macro
        end match
    end macro

    macro purge_invoker?
        repeat count_exec
            purge exec_invoker
        end repeat
        count_exec = $00
    end macro

    macro exec_invoker?
    end macro

    macro ? line&
        local is_end
        is_end = $00
        match =end? =switch?, line
            is_end = $01
        else match =end? =. =switch?, line
            is_end = $01
        else
            match =macro? _, line
                err "macro can't be declared here"
            end match
            parse_switch line
        end match
        if (is_end)
            end switch
        end if
    end macro
end macro

macro end?.switch?
    exec_invoker
    purge_invoker
    purge add_invoker?,  purge_invoker?, exec_invoker?,\
          parse_switch?, case?,          default?,\
          ?
end macro

