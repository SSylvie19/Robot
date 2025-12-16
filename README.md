# Build project
```
git submodule update --init --recursive
cmake -S . -B build
cmake --build build
```

# Run project
```
.\build\Debug\robot.exe path-to-txt.txt
```

# Example
```
.\build\Debug\robot.exe commands.txt
```
### Input:
```
DIMENSION 5
MOVE_TO 1,1
LINE_TO 3,3
LINE_TO 3,2
```

### Output:
```
. . . . . 
. + . . .
. . + + .
. . . + .
. . . . .
```

# Run unittest
```
.\build\Debug\robot_test.exe
```

# Core logic
- The core logic of this code is the `Bresenham's line algorithm` that i find [here](https://www.geeksforgeeks.org/dsa/bresenhams-line-generation-algorithm/) 
- This code does not handle all cases. In the comment of the implementation:
```
// C++ program for Bresenham’s Line Generation
// Assumptions :
// 1) Line is drawn from left to right.
// 2) x1 < x2 and y1 < y2
// 3) Slope of the line is between 0 and 1.
//    We draw a line from lower left to upper
//    right.
```
- I'm only improve this implementation that support other cases that work with:
--- All cases of start and end coordinate
--- Other slope cases (The line near horizontal or vertical)

# Complexity
### Time complexity
- The MOVE_TO command only update position so it will take O(1)
- The LINE_TO command is the Bresenham's line algorithm so it will take O(n) with n is the line length
- The parser reads the file line by line to it will take O(m) with m is the number of line
- The Print take O(p^2) with p is the grid size
-> Time complexity will be O(n + m + p^2)
### Space complexity
- With this implementation, i'm parsing all the commands and then execute one by one so there will need O(n) with n is number of commands to store the commands
- We also need to store the whole map so complexity will be O(m^2) with m is the grid size
-> The space complexity will be O(n + m^2)

### Improvement in space complexity
- We do not need store the whole map because we do not track all information of the map, we only need the visited cell and when print, check if visited cell contain that cell or not. So we will only store the visited cell in some container like std::unordered_set. The worse case will also cost O(m^2) but average cases would be lower. 
- The downside if this is increase the time complexity because each print need to find if that the container include that coordinate. The average time complexity check if contain in std::unordered_set is O(1) but worse case is O(n) (hash collision)

- Also this implementation parse all commands then execute. This approach will take space to store commands. The better one is parse then execute right after parse. So the space will be only O(m^2). But the solution execute after parse make it really hard if we want to change the parser that support different set of commands 