# External SRAM
Modified hardware initialization files to enable external SRAM for MPC5554 with Freescale CodeWarrior IDE.
Include these files in the corresponding folders of a CodeWarrior project to enable external SRAM.

RAM map is generated by the linker. 
It is not directly user modifiable, but can be changed through startup code and Lcf (linker control file).

These are currently just copies of the default startup files, which do not enable external SRAM
by default. They will eventually be modified to enable external SRAM.
