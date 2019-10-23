
include "jvm_class.inc"
format binary as 'class'

u4 (MAGIC)
u2 ($00), ($31)

constant_pool
    _Object         constant_utf8           "java/lang/Object"
    _hello          constant_utf8           "hello"
    _init           constant_utf8           "<init>"
    _init_args      constant_utf8           "()V"
    _main           constant_utf8           "main"
    _main_args      constant_utf8           "([Ljava/lang/String;)V"
    _Hello          constant_utf8           "Hello, World"
    _Code           constant_utf8           "Code"
    
    Object_class    constant_class          _Object
    Object_init     constant_methodref      Object_class, init_method
    hello_class     constant_class          _hello
    init_method     constant_nameandtype    _init, _init_args
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
                    invokespecial Object_init
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
