# CS 2600-05, Fall 2022: Assignment 5
## Name: Thomas Truong | Bronco ID: 014426906
## Description: Kills a process if it has been asleep for too long (-v FLAG implemented).
<br>

### Compiling and Running
- Linux/MacOS
  - Make sure you are in 'Assignment5/build' directory
  - Use command: 'make clean && make'
  - Now go to 'Assignment5/bin' directory.
  - Use command: './timeout' alongside with some arguments.
    - **!!!: '-v' FLAG FOR VERBOSE.**
    - Example: './timeout -vt15 ../test/Hello.txt'
- Others
  - Go to: https://replit.com/
    - Login/sign up.
  - Create new Repl at the top left.
    - Select 'C' template.
    - Give it any title.
  - Copy and paste code from 'Assignment5/src/timeout.c'
  - Create new file (top left).
    - Give it any name and content.
  - Click 'Run' at top center and ignore console message.
  - Type './main' alongside with some arguments in the console.
    - Example: './main -vt15 FILE_NAME'