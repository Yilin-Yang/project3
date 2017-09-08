Dynamic Memory
================================================================================

Other Helpful Resources
--------------------------------------------------------------------------------
You can find online resources teaching practically every topic we cover in
our training sequence. These are much more thorough than anything we can
provide, though they're also a bit long-winded.

We've found a few that we like and provided links to them here:
* [LearnCPP](https://goo.gl/77LpvW)
* [CPlusPlus Tutorial](http://www.cplusplus.com/doc/Tutorial/dynamic/)

Your Computer's Memory: The Memory Model
--------------------------------------------------------------------------------
Your computer's **random-access memory** (also called its memory, or its
RAM) is a contiguous, one-dimensional "box" of **memory locations.**

        YOUR COMPUTER'S MEMORY
                   _
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   Z
                   Z
                   Z
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   |
                   _

Each memory location in this box has a "height" of **one byte**. That
memory location can only store one byte of data.

Each memory location has an **address**. The address is the number of
memory locations (i.e. the number of "steps") between that location and the
start of memory.

For instance, if we had a computer with 16 bytes of RAM, its memory would
look something like this:

                 RAM
                  _
                  |     15
                  |     14
                  |     13
                  |     12
                  |     11
                  |     10
                  |     09
                  |     08
                  |     07
                  |     06
                  |     05
                  |     04
                  |     03
                  |     02
                  |     01
                  |     00
                  _

If stored the `int` `5` in memory location `07`, then the computer's memory
would look like:
                 RAM
                  _
                  |     15
                  |     14
                  |     13
                  |     12
                  |     11
                  |     10
                  |     09
                  |     08
                  5     07
                  |     06
                  |     05
                  |     04
                  |     03
                  |     02
                  |     01
                  |     00
                  _

In practice, all of the "empty" memory locations will store actual values,
though these values won't be meaningful. We say that these other locations
are filled with **memory junk.**

                 RAM
                  _
                  5     15
                  1     14
                  3     13
                  9     12
                  1     11
                  5     10
                  3     09
                  7     08
                 =5=    07
                  1     06
                  1     05
                  0     04
                  3     03
                  7     02
                  3     01
                  |     00
                  _

(Memory locations that aren't filled with junk are flanked by `=` on either
side.)

Computer memory is like the whiteboards on the ground floor of the UgLi.
When people are done, they might not erase what they wrote, but when
they're done with it, the whiteboard will still be "free to use". When
somebody wants to use it, they'll stop by, erase however much space they
need, and start writing.

If I wanted to "remember" where I put that `5`, I would have to remember
the memory location in which I put it. I can do this by recording a
**pointer** to that location's memory address.

        int* ptr = 7;       // does actually compile with -fpermissive

If I wanted to get the value stored at that location, I would **dereference** it.

        std::cout << *ptr << std::endl;     // prints `5`
        //           ^ dereference operator

If I wanted to get what the memory location actually was, I could just
print the pointer directly _without_ dereferencing it.

        std::cout << ptr << std::endl;      // prints 0x7

You'll note that memory location `00` doesn't store anything. A pointer
storing the value `0` (e.g. `int* ptr = 0`) is called a **null pointer**
(`nullptr`). Trying to dereference a `nullptr` causes your program to crash
with a **segmentation fault**, which means that your program accessed a
segment of memory that it wasn't allowed to touch.

### Aside: Hexadecimal
The `0x` is a prefix telling you that the number is written in hexadecimal,
which is a numbering system in which one digit can have sixteen values
(rather than ten values for standard numerals, or two values in binary.)

        One digit can have the following values:
        BINARY      DECIMAL     HEXADECIMAL
        0           0           0
        1           1           1
                    2           2
                    3           3
                    4           4
                    5           5
                    6           6
                    7           7
                    8           8
                    9           9
                                A
                                B
                                C
                                D
                                E
                                F

The number `14` would be `1110` in binary.
        14 =
            1 x 2^3 + 1 x 2^2 + 1 x 2^1 + 0 x 2^0
                  8 +       4 +       2 +     0

In hexadecimal, `14` would be `E`. `10` would be `A`, `11` would be `B`,
and so on. `16` would be `10`.

Hexadecimal is useful because it's a very compact way of representing
numbers that a computer stores as binary. Two hexadecimal digits is all you
need to represent a byte.

A byte has eight binary digits, or "bits", giving it `2^8 = 256` possible
values. Two hexadecimal digits can represent `16^2 = 256` possible values.
It lets you write `255` as `0xFF` rather than `11111111`, and it lets you
write `1` as `0x01` rather than `00000001`.


Your Program's Memory Chunk: The Stack and the Heap
--------------------------------------------------------------------------------
When a C++ program runs, your operating system reserves a large, contiguous
chunk of memory for it to use. Your EECS classes usually represent it as a
big box.

          PROGRAM'S MEMORY
            ___________
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            |         |
            ___________

_They draw it as a box because they need to write things inside of it._
Remember that memory is actually one-dimensional, and every "row" in the
box is one-element wide and has a height of one byte.

Let's assume that your computer has 8GB of RAM.

When your computer runs this program, its memory looks something like this:

            _
            | <--- 0x200000000 ( = 8,589,934,592 = 8 * 2^30 = 8 billion-ish)
            |
            |
            |
            |
            |
            |
            | <--- other memory (used for other stuff by your computer)
            |
            |
            |
            |
            |
            |
            I <--- your program's allocated memory
            |
            |
            |
            |
            | <--- other memory (used for other stuff by your computer)
            |
            |
            |
            |
            |
            |
            |
            |
            |
            | <--- 0x000000000 (memory location `NULL`, or `nullptr`)
            _


Let's focus on just the program's memory for now.

Let's say it looks like this:

          PROGRAM'S MEMORY
            ___________
            |_________| 0x12AD11
            |_________| 0x12AD10
            |_________| 0x12AD1F
            |_________| 0x12AD1E
            |_________| 0x12AD1D
            |_________| 0x12AD1C
            |_________| 0x12AD1B
            |_________| 0x12AD1A
            |_________| 0x12AD19
            |_________| 0x12AD18
            |_________| 0x12AD17
            |_________| 0x12AD16
            |_________| 0x12AD15
            |_________| 0x12AD14
            |_________| 0x12AD13
            |_________| 0x12AD12
            |_________| 0x12AD11
            |_________| 0x12AD10
            |_________| 0x12AD0F
            |_________| 0x12AD0E
            |_________| 0x12AD0D
            |_________| 0x12AD0C
            |_________| 0x12AD0B
            |_________| 0x12AD0A
            |_________| 0x12AD09
            |_________| 0x12AD08
            |_________| 0x12AD07
            |_________| 0x12AD06
            |_________| 0x12AD05
            |_________| 0x12AD04
            ___________

(In real life, your program would have _much_ more memory than this, but we
have to fit this drawing into a human-readable text file, so we'll pretend
that your program's allocated memory is really, really small.)

This memory is divided into a number of different "chunks", but for now,
let's ignore all of them except for two. (The other ones are important, but
they're pretty small.)

The program's memory is divided into the **stack** and the **heap**.

The stack is used for **statically-allocated** data objects. The heap is
used for **dynamically-allocated** data objects. We'll explain what this
means below.

### The Stack
We return to the diagram of your program's memory.
            ___________
            |_________| 0x12AD11
            |_________| 0x12AD10
            |_________| 0x12AD1F
            |_________| 0x12AD1E
            |_________| 0x12AD1D <--- the stack
            |_________| 0x12AD1C
            |_________| 0x12AD1B
            |_________| 0x12AD1A
            |_________| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
            |_________| 0x12AD18
            |_________| 0x12AD17
            |_________| 0x12AD16
            |_________| 0x12AD15
            |_________| 0x12AD14
            |_________| 0x12AD13
            |_________| 0x12AD12
            |_________| 0x12AD11
            |_________| 0x12AD10
            |_________| 0x12AD0F
            |_________| 0x12AD0E <--- the heap
            |_________| 0x12AD0D
            |_________| 0x12AD0C
            |_________| 0x12AD0B
            |_________| 0x12AD0A
            |_________| 0x12AD09
            |_________| 0x12AD08
            |_________| 0x12AD07
            |_________| 0x12AD06
            |_________| 0x12AD05
            |_________| 0x12AD04
            ___________

Of course, when the program starts, this memory is largely filled with memory junk.

            ___________
            |____8____| 0x12AD11
            |____9____| 0x12AD10
            |____8____| 0x12AD1F
            |____7____| 0x12AD1E
            |____4____| 0x12AD1D <--- the stack
            |____5____| 0x12AD1C
            |____7____| 0x12AD1B
            |____2____| 0x12AD1A
            |____1____| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
            |____3____| 0x12AD18
            |____5____| 0x12AD17
            |____2____| 0x12AD16
            |____9____| 0x12AD15
            |____5____| 0x12AD14
            |____6____| 0x12AD13
            |____1____| 0x12AD12
            |____5____| 0x12AD11
            |____2____| 0x12AD10
            |____6____| 0x12AD0F
            |____0____| 0x12AD0E <--- the heap
            |____5____| 0x12AD0D
            |____9____| 0x12AD0C
            |____2____| 0x12AD0B
            |____2____| 0x12AD0A
            |____6____| 0x12AD09
            |____8____| 0x12AD08
            |____5____| 0x12AD07
            |____4____| 0x12AD06
            |____9____| 0x12AD05
            |____4____| 0x12AD04


Every time your program enters a function, it creates what's called a
**stack frame.**

Let's say your program looks like this:

        int func()
        {
            int c = 2;
            return c;
        }

        int main()
        {
            int a = 1;
            int b = func();
        }

When your program starts, it creates a stack frame for `main()`.

               STACK
            ___________
            |____8____| 0x12AD11
            |____9____| 0x12AD10 <--- main's stack frame
            |=========|
            |____8____| 0x12AD1F
            |____7____| 0x12AD1E
            |____4____| 0x12AD1D
            |____5____| 0x12AD1C
            |____7____| 0x12AD1B
            |____2____| 0x12AD1A
            |____1____| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
                        <--- the heap

The stack frame stores all of the variables that you **statically
allocated** inside that function.

               STACK
            ___________
    int a  =|____1____|= 0x12AD11
    int b   |____9____| 0x12AD10 <--- not yet initialized to a meaningful value
            |=========|
            |____8____| 0x12AD1F
            |____7____| 0x12AD1E
            |____4____| 0x12AD1D
            |____5____| 0x12AD1C
            |____7____| 0x12AD1B
            |____2____| 0x12AD1A
            |____1____| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
                        <--- the heap

When `func()` is called, your program creates a new stack frame for it.

               STACK
            ___________
    int a  =|____1____|= 0x12AD11 <--- main's stack frame
    int b   |____9____| 0x12AD10
            |=========|
    int c  =|____2____|= 0x12AD1F <--- func's stack frame
            |=========|
            |____7____| 0x12AD1E
            |____4____| 0x12AD1D
            |____5____| 0x12AD1C
            |____7____| 0x12AD1B
            |____2____| 0x12AD1A
            |____1____| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
                        <--- the heap

And when the program `return`s from that function, it "pops" that frame off
of the stack.

               STACK
            ___________
    int a  =|____1____|= 0x12AD11 <--- main's stack frame
    int b  =|____2____|= 0x12AD10 <--- the 2 got copied into b
            |=========|
            |____2____| 0x12AD1F <--- the 2 is now "junk"
            |____7____| 0x12AD1E
            |____4____| 0x12AD1D
            |____5____| 0x12AD1C
            |____7____| 0x12AD1B
            |____2____| 0x12AD1A
            |____1____| 0x12AD19
            |=========| <--- somewhat arbitrary boundary
                        <--- the heap

This is what your programs usually do.

### The Heap
The stack, however, is limited in size. If you write a "simple" C++ program
that tries to use several megabytes of memory, you'll fill the entire
stack, and then your program will crash. This type of error called a
**stack overflow**, which is what [that website](https://stackoverflow.com)
is named after.

If you want to work with very large data objects, rather than
statically allocating them on the stack, you should instead **dynamically
allocate** them on the heap.

To do this, you call an object's constructor using the **`new`** keyword.

        int main()
        {
            int si = 3;             // created on the stack
            int* di = new int{7};   // created on the heap
        }

When you do this, your program's memory will look something like...

             PROGRAM'S MEMORY
                ___________
        int si =|____3____|= 0x12AD11
       int* di =|_0x12AD04|= 0x12AD10
                |____8____| 0x12AD1F
                |____7____| 0x12AD1E
                |____4____| 0x12AD1D <--- the stack
                |____5____| 0x12AD1C
                |____7____| 0x12AD1B
                |____2____| 0x12AD1A
                |____1____| 0x12AD19
                |=========| <--- somewhat arbitrary boundary
                |____3____| 0x12AD18
                     .
                     .
                     .
                |____5____| 0x12AD07
                |____4____| 0x12AD06 <--- the heap
                |____9____| 0x12AD05
               =|____7____|= 0x12AD04 <--- the "real" value of di

If you did this:

        int main()
        {
            int si = 3;                    // created on the stack
            int* dia = new int[1000000];   // created on the heap
            for (int i = 0; i < 1000000; ++i)
            {
                dia[i] = i;
            }
        }

You would create a native array with a size of 1,000,000 bytes. This would
almost definitely cause a stack overflow if allocated on the stack, but on
the heap, this is perfectly okay!

Your program's memory would look something like...

             PROGRAM'S MEMORY
                ___________
        int si =|____3____|= 0x12AD11
       int* dia=|_0x036AC4|= 0x12AD10
                |____8____| 0x12AD1F
                |____7____| 0x12AD1E
                |____4____| 0x12AD1D <--- the stack
                |____5____| 0x12AD1C
                |____7____| 0x12AD1B
                |____2____| 0x12AD1A
                |____1____| 0x12AD19
                |=========| <--- somewhat arbitrary boundary
                |____3____| 0x12AD18
                     .
                     .
                     .
                |____7____| 0x12AD04 <-- the first element *not* in that array
               =|__999999_|= 0x12AD03 <-- the last element in that array
                     .
                     .
                     .
               =|____4____|= 0x036AC8
               =|____3____|= 0x036AC7
               =|____2____|= 0x036AC6
               =|____1____|= 0x036AC5
               =|____0____|= 0x036AC4 <--- the start of a 1,000,000 element array


Just make sure to keep a pointer to that array, and to `delete[]` the array
when you're done with it.

        int* func()
        {
            int* dia = new int[1000000];   // created on the heap
            for (int i = 0; i < 1000000; ++i)
            {
                dia[i] = i;
            }
            return dia;
        }

        int main()
        {
            int si = 3; // created on the stack
            func();     // we do nothing with the int pointer this returns

            // other stuff
        }

This will still create a one-million-element array on the heap. C++ doesn't
know if you still want to do anything with it, so it **won't use that
memory for anything else until you `delete` it.**

And if you "forgot" the location of the array (i.e. if you've **orphaned**
that data object), you can't `delete[]` it anymore.

By the time you get to `other stuff`, you have a _one million byte chunk of
memory that you can't use for anthing._This is called a **memory leak.**

The `delete` Keyword
--------------------------------------------------------------------------------
`delete` tells C++ that it's free to use the memory that _was_ being used
for a dynamically-allocated object for something else. Note that it
_doesn't actually "clear" any of the data on the heap._ It just tells C++
that it's free to overwrite those memory locations with other stuff.

### Deleting Individual Objects vs. Deleting Native Arrays
`delete` will only "delete" (i.e. "free" to be used for other purposes) the
object pointed to by the pointer. If you were to `delete` `dia*`...

        int main()
        {
            int si = 3;
            int* dia = func();  // store the pointer to the start of the array

            // other stuff

            delete dia;
        }

...you would free the first element, but _nothing else._

             PROGRAM'S MEMORY
                ___________
        int si =|____3____|= 0x12AD11
       int* dia=|_0x036AC4|= 0x12AD10
                |____8____| 0x12AD1F
                |____7____| 0x12AD1E
                |____4____| 0x12AD1D <--- the stack
                |____5____| 0x12AD1C
                |____7____| 0x12AD1B
                |____2____| 0x12AD1A
                |____1____| 0x12AD19
                |=========| <--- somewhat arbitrary boundary
                |____3____| 0x12AD18
                     .
                     .
                     .
                |____7____| 0x12AD04 <-- the first element *not* in that array
               =|__999999_|= 0x12AD03 <--- leaked memory
                     .
                     .
                     .
               =|____4____|= 0x036AC8 <--- leaked memory
               =|____3____|= 0x036AC7 <--- leaked memory
               =|____2____|= 0x036AC6 <--- leaked memory
               =|____1____|= 0x036AC5 <--- leaked memory
                |____0____| 0x036AC4 <--- freed memory, no longer leaked

By doing this, you would leak 999,999 bytes of memory. This is only a
marginal improvement.

To clear the entire array, you should use `delete[]`. This is specifically
meant to delete dynamically-allocated arrays.

So, doing this...

        int main()
        {
            int si = 3;
            int* dia = func();  // store the pointer to the start of the array

            // other stuff

            delete[] dia;
        }

...does this:

             PROGRAM'S MEMORY
                ___________
        int si =|____3____|= 0x12AD11
       int* dia=|_0x036AC4|= 0x12AD10
                |____8____| 0x12AD1F
                |____7____| 0x12AD1E
                |____4____| 0x12AD1D <--- the stack
                |____5____| 0x12AD1C
                |____7____| 0x12AD1B
                |____2____| 0x12AD1A
                |____1____| 0x12AD19
                |=========| <--- somewhat arbitrary boundary
                |____3____| 0x12AD18
                     .
                     .
                     .
                |____7____| 0x12AD04
                |__999999_| 0x12AD03 <--- freed memory, no longer leaked
                     .
                     .
                     .
                |____4____| 0x036AC8 <--- freed memory, no longer leaked
                |____3____| 0x036AC7 <--- freed memory, no longer leaked
                |____2____| 0x036AC6 <--- freed memory, no longer leaked
                |____1____| 0x036AC5 <--- freed memory, no longer leaked
                |____0____| 0x036AC4 <--- freed memory, no longer leaked

And you no longer leak any memory!
