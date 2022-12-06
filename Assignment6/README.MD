# CS 2600-05, Fall 2022: Assignment 6
## Name: Thomas Truong | Bronco ID: 014426906
## Description: replica of the tee command, but only supports -a flag.
<br>

### Compiling and Running
- Linux/MacOS
  - Make sure you are in 'Assignment6/build' directory
  - Use command: 'make clean && make'
  - Now go to 'Assignment6/bin' directory.
  - Use command: './tee' alongside with some arguments.
    - Example: './tee ../test/a ../test/b ../test/c -a'
- Others
  - Go to: https://replit.com/
    - Login/sign up.
  - Create new Repl at the top left.
    - Select 'C' template.
    - Give it any title.
  - Copy and paste code from 'Assignment6/src/tee.c'
  - Click 'Run' at top center and ignore console message.
  - Type './main' alongside with some arguments in the console.
    - Example: './main a b c -a'