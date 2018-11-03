# Kendryte K210 (Sipeed K210 Dock) Hello World PWM

This Kendryte K210 processor is located on the Sipeed K210 Dock board. General specs of the processor is as follows:

- Kendryte K210 dual core 64-bit RISC-V processor
- KPU Convolutional Neural Network (CNN) hardware accelerator
- APU audio hardware accelerator
- 6MiB of on-chip general-purpose SRAM memory and
2MiB of on-chip AI SRAM memory
- AXI ROM to load user program from SPI flash

Source: [https://www.cnx-software.com/2018/10/19/kendryte-kd233-risc-v-board-k210-soc-machinve-vision/](https://www.cnx-software.com/2018/10/19/kendryte-kd233-risc-v-board-k210-soc-machinve-vision/)

For instructions on how to deploy the project: [https://hackaday.io/project/162174-kendryte-k210-development-tutorial-for-windows-10](https://hackaday.io/project/162174-kendryte-k210-development-tutorial-for-windows-10)

After following the instructions, to build the code, you need to change "hello_world" to the "k210-hello_world_pwm":

    cmake .. -DPROJ=k210-hello_world_pwm -DTOOLCHAIN=D:/kendryte-toolchain/bin -G "Unix Makefiles" && make

The short PWM code is based on this example:
[https://github.com/kendryte/kendryte-freertos-demo/tree/master/pwm](https://github.com/kendryte/kendryte-freertos-demo/tree/master/pwm)

This program, with the RGB LED on the K210 board fades in the blue, fades out the green, fades in the green, fades out the blue, and this process repeats.