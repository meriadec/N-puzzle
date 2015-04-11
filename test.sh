#!/bin/bash

function testSolvable {
  ./mapgen -s $1 -i $2 > map
  ./npuzzle map > output
  [[ $CONTENT =~ "not solvable" ]] && printf "\n[KO]\n" || printf "."
}

function testUnsolvable {
  ./mapgen -u $1 -i 5000 > map
  ./npuzzle map > output
  CONTENT=$(cat output)
  [[ $CONTENT =~ "not solvable" ]] && printf "." || printf "\n[KO]\n"
}

printf "\nTesting solvable maps\n"

for i in {1..20}; do
  testSolvable 3 5000
done

for i in {1..20}; do
  testSolvable 4 5000
done

for i in {1..20}; do
  testSolvable 5 50
done

printf "\nTesting unsolvable maps\n"

for i in {1..20}; do
  testUnsolvable 3 5000
done

for i in {1..20}; do
  testUnsolvable 4 5000
done

for i in {1..20}; do
  testUnsolvable 5 50
done

printf "\n\n"

rm -f output
