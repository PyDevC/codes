#!/usr/bin/env bash

startN=$(date +%s%N)
start=$(date +%s)

if [[ "${1##*.}" == "py" ]]; then
  python3 "$1" 
elif [[ "${1##*.}" == "c" ]];then
  gcc "$1" 
fi

endN=$(date +%s%N)
end=$(date +%s)

echo Execution time was $(("$end" - "$start")) seconds.
echo Execution time was "$(("$endN" - "$startN"))" nanoseconds.
