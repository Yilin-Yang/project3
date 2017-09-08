# Containers in C++

## Native Arrays (or, C-Style Arrays)
A native array is a fixed-size container of objects stored as a single,
contiguous block.

[This link](https://www.tutorialspoint.com/cplusplus/cpp_arrays.htm)
explains how to work with arrays more thoroughly than we can here, but
we've summarized some important points below.
* A native array _is not_ the same thing as an
  [std::array](https://www.tutorialspoint.com/cplusplus/cpp_arrays.htm),
  although `std::array` is essentially just a wrapper around a native
  array.
* Under the hood, an array is a pointer to the first element in a block of
  objects at some point in memory.
* Native arrays can be indexed using `operator[]`, or using pointer
  arithmetic.
* To delete a dynamically-allocated array, you use `delete[]`.

An example of indexing with `operator[]` is shown below.

    int an_array[] = {10, 20, 30, 40};
    std::cout << an_array[0] << std::endl;  // prints `10`
    std::cout << an_array[3] << std::endl;  // prints `40`

    // prints the contents of the byte after the end of the array,
    // or crashes the program
    std::cout << an_array[4] << std::endl;

An example of a loop that iterates through a native array using pointer
arithmetic is shown below:

    int an_array[] = {10, 20, 30, 40};
    size_t arr_size = 4;

    // prints `10 20 30 40 `
    for (int* ptr = an_array; ptr != an_array + arr_size; ++ptr)
    {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;

To pass a native array into a function, you would do something like this:

    void printArray(const int* arr, size_t arr_size)

    {
        for ( ; ptr != arr + arr_size; ++ptr)
        {
        std::cout << *ptr << " ";
        }
        std::cout << std::endl;
    }

    void zeroArray(int* ptr, size_t arr_size)
    {
        for ( ; ptr != arr + arr_size; ++ptr)
        {
        // Note: the pointer still points to the original array's
        //       elements!
        *ptr = 0;
        }
    }

    // ...

    int main()
    {
        int an_array[] = {10, 20, 30, 40};
        printArray(an_array, 4); // prints `10 20 30 40 `
        zeroArray(an_array, 4);
        printArray(an_array, 4); // prints `0 0 0 0 `
    }

You _cannot_ do this:

    size_t arr_size;
    std::cin >> arr_size;   // ask user for size of array
    int an_array[arr_size]; // error

When you call a function in C++, whether that be `int main()` or
`printArray`, C++ allocates a chunk of memory called a **stack frame**. The
stack frame holds all of that function's local variables (i.e. variables
instantiated inside that function's body).

The reason you can't create native arrays with a size that isn't known at
compile time is that:
    1. There is a limit on how large stack frames can be, and,
    2. Because of the way stack frames work, C++ has to know how _exactly_
    how much memory it needs to allocate to a given stack frame.

For more details on `2.`, see [this link](https://stackoverflow.com/questions/4341570/)

Creating native arrays with a size that is unknown at compile time requires
the use of **dynamic memory** (see: `./dynamic_memory.md`), like so:
    size_t arr_size;
    std::cin >> arr_size;   // ask user for size of array
    int an_array = new int[arr_size]; // dynamic memory allocation!

This allocates a block of memory on the _heap_, not inside a stack frame.

## Standard Library Containers
For complete documentation, see the corresponding page on
[cppreference](http://en.cppreference.com/w/cpp/container).

We'll give brief explanations of the containers that you're most
likely to use.

### std::vector
`#include <vector>`
[cppreference](http://en.cppreference.com/w/cpp/container/vector)

An `std::vector` is a resizeable array.

You can index into it as if it were an array, and you can tack elements
onto the end of it without worrying about native arrays and corrupting
memory. `std::vector` does allocate new arrays whenever it detects that it
needs to resize; most of the time, you don't have to worry about how this
happens.

Example Usage:

    // main.cpp
    #include <iostream>
    #include <vector>

    using std::vector;
    using std::cout;
    using std::endl;

    void printVector(const vector<int>& vec);

    int main()
    {
        // Create a three-by-three two-dimensional vector.
        vector<int> col{1, 2};  // initializes five-element vector
        col.push_back(3);       // lengthen the vector
        col.emplace_back(4);    // same as `col.push_back(int{4});`,
                    // i.e. calls constructor, then pushes to the back
        col.pop_back();     // delete last element

        cout << col.size() << endl; // prints `3`

        // Each of `row`s elements is equal to `vector<int>{1, 2, 3}`
        vector<vector<int>> row{3, col};

        row[2][1] = 5;  // "bottom" row, "middle" column is now five

        // Prints:
        //  1
        //  5
        //  3
        printVector(row[2]);

        // Prints:
        //  1
        //  2
        //  3
        printVector(row[0]);

        //printVector(row); // error; can't `<<` an entire vector (`col`)

        return 0;   // exit with zero-status (i.e. without reporting an error)
    }

    void printVector(const vector<int>& vec)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
        cout << vec.at(i) << endl;
        }
        // cout << vec.at(100)  << endl;    // error
        // cout << vec[100]     << endl;    // prints memory junk
    }

### std::map
`#include <map>`
[cppreference](http://en.cppreference.com/w/cpp/container/map)

An `std::map` is functionally similar to a dictionary (in languages like
Python): given a "word" (a key), a dictionary will give you a "definition"
(a value).

So if I create a map by doing this:

    std::map<string, int> town_populations;
    town_populations["Ann Arbor"] = 100000;
    town_populations["Detroit"] = 6000000;

I could access those values by doing something like this:

    // prints `100000` to stdout
    std::cout << town_populations["Ann Arbor"] << std::endl;

Example Usage:

    // main.cpp
    #include <iostream>
    #include <map>
    #include <string>

    using std::map;
    using std::string;

    using std::cout;
    using std::endl;

    void printMap(const map<string, int>& m);
    void printOtherStuff(map<string, int>& m);

    int main()
    {
        // Create a map associating city names with their populations.
        map<string, int> town_populations;
        town_populations["Detroit"] = 6000000;
        town_populations["Ann Arbor"] = 100000;
        town_populations["Ponyville"] = 5000;

        // Prints:
        //  100000
        //  6000000
        //  5000
        printMap(town_populations);

        printOtherStuff(town_populations);

        return 0;   // exit with zero-status
    }

    void printMap(const map<string, int>& m)
    {
        /*
        for (map<string, int>::const_iterator it = m.begin();
         it != m.end();
         ++it)
        {
        const std::pair<string, int>& key_and_val = *it;
        cout << key_and_val.first << endl;
        cout << key_and_val.second << endl;
        }
        */

        // Functionally equivalent to loop above.
        for (const auto& key_and_val : m)
        {
        cout << key_and_val.first << endl;
        cout << key_and_val.second << endl;
        }
    }

    void printOtherStuff(map<string, int>& m)
    {
        // cout << *m.find("Townsville") << endl; // error, dereferencing an iterator
                              // pointing to a nonexistent value

        cout << m["Townsville"] << endl; // creates a new element by calling default
                         // int constructor

        // Prints:
        //  100000
        //  6000000
        //  5000
        //  0
        printMap(m);
    }
