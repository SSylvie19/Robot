# Build project
```
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

# Example result
## Input:
```
DIMENSION 5
MOVE_TO 1,1
LINE_TO 3,3
LINE_TO 3,2
```

## Output:
```
. . . . . 
. + . . .
. . + + .
. . . + .
. . . . .
```