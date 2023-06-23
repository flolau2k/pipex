#!/bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

test_func()
{
	< $1 $2 | $3 > $4-b 
	statusb=$?
	./pipex $1 "$2" "$3" $4
	statusp=$?
	if [ $statusb == $statusp ]
	then 
		printf "${GREEN}status match${NC}\n"
	else
		printf "${RED}status fail${NC}: got status $statusp but expected $statusb\n"
	fi
	if cmp -s $4-b $4
	then
		printf "${GREEN}files match${NC}\n"
	else
		printf "${RED}files fail${NC}: got output $(cat $4) but expected $(cat $4-b)\n"
	fi
}

test_func infile "cat" "wc -l" outfile
test_func infile

