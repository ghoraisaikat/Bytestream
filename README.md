# 📁 File streaming over TCP/IP in C
A very simple TCP Client and Server where the server serves the file requested for or returns "File not found". Currently, chunking is not implemented and the entire file is sent at once. Also, the client exits after making one request.
# Technologies
- C

# Features
- Transfer files over TCP/IP

# Learning Outcomes
Over the course of this project, I learnt:

 1. the lifecycle of `recv()`,  `send()` and how `send()` does not promise to transfer all the bytes passed to it
 2. the system calls - `open()` and `read()`

# How do you run it?
1. Clone the repository (make sure you are on a Linux machine)
2. Run `make server`
3. Run `make client`
4. Run both the executables on different instances of a terminal

# Preview

![Bytestream](https://github.com/user-attachments/assets/7561e421-dc22-4742-a108-c1db18d6f8d1)
