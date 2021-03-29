
/*
!!!Linker default script generated automatically !!!
Please note that this file and all script files included from this one can not be modified directly
If you need to use your own script please do it from Ride7 LD linker options taking this one as example
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\tien\PROJEKTY\procesory\STM\T108_V100a")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
STARTUP("C:\Program Files (x86)\Raisonance\Ride\lib\ARM\crt0_STM32x_HD.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\stm32f10x_flash.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\control.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\sys.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\stm32f10x_it.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\RTC.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\main.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\lcd.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\hardware.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\gui.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_core.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_init.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_int.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_mem.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_regs.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_desc.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_istr.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_prop.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_pwr.o")
INPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\usb_endp.o")
INCLUDE "C:\tien\PROJEKTY\procesory\STM\T108_V100a\STM32F103_256K_48K_FLASH.ld"
EXTERN( __io_putchar )
EXTERN( _write )
INPUT("STM32x_io_putchar_thumb.a")
INPUT("e_stdio_thumb.a")
INPUT("STM32F10x_thumb.lib")
OUTPUT("C:\tien\PROJEKTY\procesory\STM\T108_V100a\T104_GA_V100a.elf")
