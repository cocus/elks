project(romprogrammer_cli)
cmake_minimum_required(VERSION 3.4)

add_executable(romprg
  pc-main.c
  protocol.c
  pc-serial.c
  pc-commands.c
  crc.c
)
