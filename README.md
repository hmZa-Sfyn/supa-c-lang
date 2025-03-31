# SupaC Programming Language Implementation - BETA

<p align="center">
  <img 
    src="/assets/holyc-logo.png?raw=true"
    alt="alt text"
    title="SupaC logo"
    width="200"
    height="230"/>
</p>

_SupaC: A fork of HolyC implementation of Terry A. Davis's HolyC_

```hc
void Main()
{
  "Hello world\n";
}
Main;
```

Full documentation for the language and this compiler can be found here: 
https://holyc-lang.com/

# Introduction 
SupaC is a custom-built compiler for the SupaC language, written entirely in C. It currently compiles directly from the abstract syntax tree (AST) to raw x86_64 assembly, which is then assembled using GCC. While it doesn’t yet perform optimizations, it fully supports floating-point arithmetic and most core language features. Additionally, there's experimental support for transpiling SupaC to standard C, opening the door for broader compatibility and further development.

## Example
Below is a snippet of code showing some of the features supported by this holyc
compiler. Namely inheritance, loops, `printf` by using a string and loops. All
c-like control flows are supported by the compiler.

```hc
class SomethingWithAnAge
{
  I64 age;
};

class Person : SomethingWithAnAge
{
  U8 name[1<<5];
};

void ExampleFunction(U0)
{
  Person *p = MAlloc(sizeof(Person));

  MemCpy(p->name,"Bob",3);
  p->age = 0;

  while (p->age < 42) {
    p->age++;
  }
  "name: %s, age: %d\n",p->name,p->age;
  Free(p);
}

ExampleFunction;
```

# Compatibility 🖥️⚙️
- The SupaC compiler currently targets x86_64 architectures, generating assembly code that is assembled using GCC. It has been successfully tested on AMD-based Linux systems and Intel-based macOS, ensuring reliable execution across these platforms.

- Since SupaC directly compiles to standard x86_64 assembly, it should be compatible with most modern x86_64 processors, including those running Windows (via WSL or MinGW), various Linux distributions, and even BSD-based systems with appropriate toolchains. While ARM and other architectures are not yet supported, future updates may introduce cross-compilation capabilities to expand its reach. 🚀

## Using the compiler
Once the compiler has been compiled, aside from compiling `.HC` files, more 
options can be displayed by running `supac --help`

## Key Differences between this and TempleOS HolyC
- `auto` key word for type inference, an addition which makes it easier
  to write code.
- Range based for loops can be used with static arrays and structs with 
  an `entries` field with an accompanying `size` field: `for (auto it : <var>)`
- `cast<type>` can be used for casting as well as post-fix type casting.
- `break` and `continue` allowed in loops.
- You can call any libc code by declaring the prototype with 
  `extern "c" <type> <function_name>`. Then call the function as you usually
  would. See [here](https://holyc-lang.com/learn-functions.html) for examples.


## Control Flow Graph Example
Example code:
```hc
int Main()
{
  auto i = 1;

  for (I64 j = 0; j < 10; ++j) {
    "%d",j;
  }
  while (i) {
    printf("hello");
  }

  return 1;
}
```
Compiled with: `supac -cfg ./<file>.HC && dot -Tpng ./<file.dot> -o <file>.png`
Produces the following control flow graph. Note that in order to use 
`-cfg-png` or `-cfg-svg` it requires the use of [graphviz](https://graphviz.org/)

## Experimental Transpiler
A transpiler can be invoked using `supac -transpile <file>.HC`, it is best effort 
however can handle most cases, including assembly. Comments are not preserved
and some if conditions will require brackets to work correctly

```hc
asm {
_TOINT::
    PUSH    RBP
    MOV     RBP, RSP
    MOV     RAX, 0
    XOR     R8,  R8
    CMPB    [RDI], '-'
    JNE     @@01
    ADD     RDI, 1
    MOV     R8,  1 // mark as being negative
@@01:
    CMPB    [RDI], '0'
    JL      @@02
    CMPB    [RDI], '9'
    JG      @@02
    MOVB    BL, [RDI]
    SUBB    BL, '0'
    MOVZBQ  RBX, BL
    IMUL    RAX, 10
    ADD     RAX, RBX
    ADD     RDI, 1
    JMP     @@01
@@02:
    TEST    R8, R8
    JZ      @@03
    NEG     RAX
@@03:
    LEAVE
    RET
}

public _extern _TOINT I64 ToInt(U8 *str);

U0 Main()
{ /* entry to function */
  U8 *number = "12345";
  auto num = ToInt(number);
  "%ld\n",num;
}
```

Becomes the below:
```c
long
ToInt(unsigned char *str)
{
    long retval;
    __asm__ volatile (
        "mov $0, %%rax\n\t"
        "xor %%r8, %%r8\n\t"
        "cmpb $0x2d, (%%rdi)\n\t"
        "jne ._toint_1\n\t"
        "add $1, %%rdi\n\t"
        "mov $1, %%r8\n\t"
        "._toint_1:\n\t"
        "cmpb $0x30, (%%rdi)\n\t"
        "jl ._toint_2\n\t"
        "cmpb $0x39, (%%rdi)\n\t"
        "jg ._toint_2\n\t"
        "movb (%%rdi), %%bl\n\t"
        "subb $0x30, %%bl\n\t"
        "movzbq %%bl, %%rbx\n\t"
        "imul $10, %%rax\n\t"
        "add %%rbx, %%rax\n\t"
        "add $1, %%rdi\n\t"
        "jmp ._toint_1\n\t"
        "._toint_2:\n\t"
        "test %%r8, %%r8\n\t"
        "jz ._toint_3\n\t"
        "neg %%rax\n\t"
        "._toint_3:\n\t"
        "leave\n\t"
        "ret\n\t"
        : "=a"(retval)
        : "D"(str)
    );
    return retval;
}

int
main(void)
{
    unsigned char *number = "12345";
    long num = ToInt(number);
    printf("%ld\n", num);
}
```

## Bugs
Please open an issue on [github](https://github.com/Jamesbarford/holyc-lang/issues)

## Inspirations & Resources:
A lot of the assembly has been cobbled together by running `gcc -S -O0 <file>`
or `clang -s O0 <file>`. Which has been effective in learning assembly, as 
has playing with TempleOS. The following are a non-exhaustive list of compilers
and resources that I have found particularly useful for learning.
- [TempleOS](https://templeos.org/)
- [8cc](https://github.com/rui314/8cc)
- [tcc](http://bellard.org/tcc/)
- [cc65](https://cc65.github.io/)
- [shecc](https://github.com/sysprog21/shecc/tree/master)
- [JS c compiler](https://github.com/Captainarash/CaptCC)

### Want to ask questions?
Find me on twitch: https://www.twitch.tv/Jamesbarford
