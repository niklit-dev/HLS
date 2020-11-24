# Скрипт запуска проекта FIR в Vivado HLS

### default setting
set Project     FIR
set Solution    SolutionX
set Device      "xc7a200tfbg676-2"
set Flow        ""
set Clock       5.0
set Uncertainty 0.6

#### main part

# Настройки проекта
open_project $Project -reset

# Добавление файлов для синтеза
add_files src/FIR.cpp    -cflags "-DHLS"

# Добавляем файлы testbench для co-simulation
add_files -tb  src/FIR_test.cpp -cflags "-DHLS"
add_files -tb  src/DataIn.txt
add_files -tb  src/DataOut.txt

# Set top module of the design
set_top FIR

# Solution settings
open_solution -reset $Solution

# set Part Number
set_part $Device 

# Set the target clock period
create_clock -period $Clock
set_clock_uncertainty $Uncertainty

###############
## Directives #
##############

# Директивы все в файле FIR.cpp

# Настраиваем путь планирования, печатаем критический путь, если
# планирование не отвечает директивам или ограничениям
config_schedule -verbose

#################
# C SIMULATION
#################
# csim_design

#############
# SYNTHESIS #
#############
csynth_design

#################
# CO-SIMULATION #
#################
cosim_design -rtl vhdl -trace_level port

##################
# IMPLEMENTATION #
##################
export_design -evaluate vhdl -format ip_catalog


exit
