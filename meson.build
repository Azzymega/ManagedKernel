project('reKe', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=gnu++20'])

subdir('Kernel/Architecture/MIPS64EL')
subdir('Kernel/Architecture/MIPS64BE')
subdir('Kernel/Architecture/I686')
subdir('Kernel/Architecture/RISCV64')

subdir('Kernel/C')
subdir('Kernel/Ke')
subdir('Kernel/Reflector')
subdir('Kernel/Runtime')
subdir('Kernel/October')

Marx = [LibC,LibKe,LibReflector,LibRuntime,LibOctober]

if host_machine.cpu_family() == 'mips64'
        if host_machine.endian() == 'little'
                static_library(
                        'Ke',
                        MIPS64ELAll,
                        Marx,
                        pic: false
                )
                #run_command('dir','MIPS64EL')
        else
                static_library(
                        'Ke',
                        MIPS64BEAll,
                        Marx,
                        pic: false
                )
                #run_command('dir','MIPS64BE')
        endif
elif host_machine.cpu_family() == 'x86'
        static_library(
                'Ke',
                I686All,
                Marx,
                pic: false
        )
        #run_command('make','I686')
elif host_machine.cpu_family() == 'riscv64'
        static_library(
                'Ke',
                RISCV64All,
                Marx,
                pic: false
        )
endif