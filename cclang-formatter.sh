echo "Running clang-formatter..."

# -iname pattern: Returns true if the file’s name matches the provided shell 
# pattern. The matching here is case insensitive.

# xargs is a great command that reads streams of data from standard input, 
# then generates and executes command lines; meaning it can take output of a 
# command and passes it as argument of another command. If no command is specified, 
# xargs executes echo by default. You many also instruct it to read data from a file 
# instead of stdin.

# This will return anything with '.c' or '.h' extension recurssively, except for outputs
# that contain './build' or './unity' string
find . -name '*.c' -o -name '*.h' | grep --invert-match './build\|./unity' | xargs clang-format -i -style=file
