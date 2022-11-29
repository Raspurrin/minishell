# minishell
A project where we have to make our own shell! 

### Index:
+ [Example-yo](#example-yo)

## What is a shell?

## Diving tasks, execution and parsing

## Environment variables

## Why built-ins?
There are two types of commands, external programs and built-in functions executed from within the shell. 
A regular command is a program that can be found in one of the folders specified in the environment variable: Path and will be excecuted with 
execv, which has to be done in a child process, as the program executed from execv will take over the process and you wouldn't be able to control it
in any way afterwards.

A builtin would simply look like a function executed inside your program. There are several reasons why it may be used: 
- It's much faster to execute and less resource intensive, which is why it's more efficient for commonly used commands to be built in the shell, like `echo` and `cd`. 
- Commands that need to be able to change the environment of the shell, can't be executed externally:
  - `cd` and `pwd` need to be able to work from the current working directory, which is specific to a process. 
  - `export`, `unset` and `env` change the environment variables. In a child process, any changes to these would only persist for the lifetime of the child.
  -  `exit` because it can only exit the current process.

## Executing in child vs parent

## Redirection and pipe/command groups

## Conquerent vs sequential execution

## Signals

## Exit status
