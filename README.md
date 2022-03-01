# Processor
---
## Processor architecture:
---
Processor has 8 registers: ```ax, bx, cx, dx, ex, fx, gx, hx```

Processor has acces to RAM: ```4k``` - if you using type ```int```; ```8k``` if you using type ```double```
By default double type of data is used. To change type of data in processot you should use defines: ```#define INT_DATA``` or ```#define FLOAT_DATA```

## Processor instructions:
---

- ```hlt``` - End of program

---

- ```push``` - This command have one argument. It push argument value into *Stack*.
```push 4``` 		- push constant value into *Stack*
```push ax``` 		- push register value into *Stack*
```push [bx + 5]``` - push value from address ```bx + 5``` into *Stack*

- ```pop``` - This command have one or zero argument. It pop value from *Stack* into argument.
```pop``` 			- pop from *Stack*
```pop ax``` 		- pop value from *Stack* into register
```push [cx]``` 	- pop value from *Stack* into address ```cx```

---

- ```add``` - adds two last values in *Stack* and push result

- ```sub``` - subtracts two last values in *Stack* (```first - second```) and push result

- ```mul``` - multiplies two last values in *Stack* and push result

- ```div``` - divides two last values in *Stack* (```first / second```) and push result

- ```sqrt``` - takes square root of value in *Stack* and push result.

---

- ```out``` - print last value from *Stack*

- ```in``` - scan value and push it into *Stack*

---
```:lable_name``` - label must start with ```:```

- ```jmp lable_name``` - jumps into the lable

- ```ja lable_name``` - takes two last values from *Stack*, if ```first > second``` jumps into the lable

- ```jae lable_name``` - takes two last values from *Stack*, if ```first >= second``` jumps into the lable

- ```jb lable_name``` - takes two last values from *Stack*, if ```first < second``` jumps into the lable

- ```jbe lable_name``` - takes two last values from *Stack*, if ```first <= second``` jumps into the lable

- ```je lable_name``` - takes two last values from *Stack*, if ```first == second``` jumps into the lable

- ```jne lable_name``` - takes two last values from *Stack*, if ```first != second``` jumps into the lable

---

```:function_name``` - name of function must start with ```:```

- ```call function_name``` - call function

- ```ret``` - returns from function to the place where it was called

## How to use Processor:
Project consists of thre programs: *Assembler*, *Processor* and *Disassembler*.

- **Assembler**
This programm convert a program in special asm language into binary executable.

Input of *Assembler* - is a program in special asm language. You should pass a path to asm file in the first argument of programm.

Output of *Assembler* is a binary executable. You should pass a path to place where you want to see your executable in the second argument of programm.

- **Processor**
This programm execute a binary executable file received from *Assembler*.

Input of *Processor* - is a binary executable. You should pass a path to binary executable file in the first argument of programm.

- **Disassembler**
This programm convert binary executable file received from *Assembler* back into asm program.

Input of *Disassembler* - is a binary executable. You should pass a path to binary executable file in the first argument of programm.

Output of *Disassembler* is a disassembled file. You should pass a path to place where you want to see your disassembled file in the second argument of programm.