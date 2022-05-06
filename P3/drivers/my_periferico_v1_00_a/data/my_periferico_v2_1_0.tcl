##############################################################################
## Filename:          C:\hlocal\Practica3segundointento/drivers/my_periferico_v1_00_a/data/my_periferico_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Mon Oct 18 17:07:10 2021 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "my_periferico" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
