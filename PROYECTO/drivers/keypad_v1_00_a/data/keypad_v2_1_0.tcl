##############################################################################
## Filename:          C:\hlocal\PROYECTO/drivers/keypad_v1_00_a/data/keypad_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sat Jan 29 19:49:12 2022 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "keypad" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
