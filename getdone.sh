#!/usr/bin/env bash

v_verbose=0

print_help() {
  echo "Help on how to get stuff done:"
  echo "-b: [B]uild release mode"
  echo "-t: Run all unity [t]est (will also build in test mode)"
  echo "-a: Static [A]nalysis (Should pass the output file to print static analysis output)"
  echo "-f: Run clang-[f]ormatter only"
  echo "-v: [V]erbose"
}

test_function() {
  echo "Parameter #1 is $1"
}

call_clang_formatter() {
  if [$v_verbose -eq 1]; then
    echo "Running clang-formatter..."
  fi

  # -name pattern: Returns true if the file’s name matches the provided shell 
  # pattern.

  # xargs is a great command that reads streams of data from standard input, 
  # then generates and executes command lines; meaning it can take output of a 
  # command and passes it as argument of another command. If no command is specified, 
  # xargs executes echo by default. You many also instruct it to read data from a file 
  # instead of stdin.

  # This will return anything with '.c' or '.h' extension recurssively, except for outputs
  # that contain './build' or './unity' string
  find . -name '*.c' -o -name '*.h' | grep --invert-match './build\|./unity' | xargs clang-format -i -style=file
  return 1
}

make_build() {
  if [$v_verbose -eq 1]; then
    echo "Building..."
  fi

  rm -rf build
  call_clang_formatter
  cmake -S . -B build -D TARGET_GROUP=$1
  cmake --build build -j 2
  return 1
}

execute_all_tests() {
  if [$v_verbose -eq 1]; then
    echo "Will run all tests"
  fi

  make_build "test"
  make test -C ./build/ ARGS='-VV'
  return 1
}

do_static_analysis() {
  if [$v_verbose -eq 1]; then
    echo "Running static analysis..."
  fi

  local output_stream="/dev/stdout"

  # -name pattern: Returns true if the file’s name matches the provided shell 
  # pattern.

  # xargs is a great command that reads streams of data from standard input, 
  # then generates and executes command lines; meaning it can take output of a 
  # command and passes it as argument of another command. If no command is specified, 
  # xargs executes echo by default. You many also instruct it to read data from a file 
  # instead of stdin.

  # This will return anything with '.c' or '.h' extension recurssively, except for outputs
  # that contain './build' or './unity' string
  find . -name '*.c' -o -name '*.h' | grep --invert-match './build\|./unity' \
  | xargs cppcheck --enable=all --suppress=missingIncludeSystem 2> $output_stream
}

# Execution starts in fact here:
while getopts 'btfavh' flag; do
  case "${flag}" in
    v) v_verbose = 1 ;;

    a) do_static_analysis ;;

    t) execute_all_tests 
      exit 1 ;;

    b) make_build "release";;

    f) call_clang_formatter ;;

    *) print_help
        exit 1 ;;
  esac
done
