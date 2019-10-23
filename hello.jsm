
include "jvm_class.inc"
format binary as 'class'

u4 (MAGIC)
u2 ($00), ($31)

constant_pool
    _Object         constant_utf8               "java/lang/Object"
    _PrintStream    constant_utf8               "java/io/PrintStream"
    _System         constant_utf8               "java/lang/System"
    _println        constant_utf8               "println"
    _println_args   constant_utf8               "(Ljava/lang/String;)V"
    _hello          constant_utf8               "hello"
    _init           constant_utf8               "<init>"
    _init_args      constant_utf8               "()V"
    _main           constant_utf8               "main"
    _main_args      constant_utf8               "([Ljava/lang/String;)V"
    _Hello          constant_utf8               "Hello, World"
    _Code           constant_utf8               "Code"
    _out            constant_utf8               "out"
    _out_type       constant_utf8               "Ljava/io/PrintStream;"

    Object_class        constant_class          _Object
    PrintStream_class   constant_class          _PrintStream
    System_class        constant_class          _System
    Object_init         constant_methodref      Object_class, init_method
    PrintStream_println constant_methodref      PrintStream_class, println_method
    System_out          constant_fieldref       System_class, out_field
    hello_class         constant_class          _hello
    init_method         constant_nameandtype    _init, _init_args
    println_method      constant_nameandtype    _println, _println_args
    out_field           constant_nameandtype    _out, _out_type
    Hello               constant_string         _Hello
end constant_pool

u2 (ACC_PUBLIC) ; check ACC_SUPER
u2 (hello_class)
u2 (Object_class)

interfaces
end interfaces

fields
end fields

methods
    method ACC_PUBLIC, _init, _init_args
            attribute _Code
                bytecode
                    aload_0
                    invokespecial Object_init
                    return
                end bytecode
   
                exceptions
                end exceptions
                
                attributes
                end attributes
            end attribute
    end method

    method ACC_PUBLIC+ACC_STATIC, _main, _main_args
        attribute _Code
            bytecode $02, $01
                getstatic System_out
                ldc Hello
                invokevirtual PrintStream_println
                return
            end bytecode

            exceptions
            end exceptions

            attributes
            end attributes
        end attribute
    end method
end methods

attributes
end attributes
