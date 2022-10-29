#!/bin/bash

RED="\033[1;31m"
GREEN="\033[1;32m"
VIOLET="\033[035m"
CYAN="\033[0;36m"
BLUE="\033[0;30m"
NC="\033[0m"
DESC1="test1:"
DESC2="test2:"
DESC3="test3:"
DESC4="test4:"

while getopts "d1234" opt; do
	case $opt in
		d)
			DESC1="test1: ${VIOLET}(${BLUE}export something=blue${VIOLET} | ${BLUE}env ${VIOLET}>outfile1):${NC}\\n"
			DESC2="test2: ${VIOLET}(<heredoc1 <heredoc2 ${BLUE}grep yo ${VIOLET}>outfile2 >outfile3):${NC}\\n"
			DESC3="test3: ${VIOLET}(<infile1 <heredoc1 ${BLUE}grep yo ${VIOLET}>outfile1 | <infile2 ${BLUE}grep file ${VIOLET}>outfile4):${NC}\\n"
			DESC4="test4: ${VIOLET}(${BLUE}cat ${VIOLET}| ${BLUE}cat${VIOLET} | ${BLUE}ls ${VIOLET}>outfile5):${NC}\\n"
			;;
		1)
			./minishell 1
			export something=blue | env >test1
			if diff -a outfile1 test1 > /dev/null ; then
				TEST1="${DESC1} ${GREEN}[OK]${NC}\\n"
			else 
				TEST1="${DESC1} ${RED}[nope]${NC}\\n"
			fi
			;;
		2)
			./minishell 2
			< heredoc1 < heredoc2 grep yo >outfile1 >test2
			if diff -a outfile3 test2 > /dev/null ; then
				TEST2="${DESC2} ${GREEN}[OK]${NC}\\n"
			else 
				TEST2="${DESC2} ${RED}[nope]${NC}\\n"
			fi
			;;
		3)
			./minishell 3
			<infile1 <heredoc1 grep yo >outfile1 | <infile2 grep file >test3
			if diff -a outfile4 test3 > /dev/null ; then
				TEST3="${DESC3} ${GREEN}[OK]${NC}\\n"
			else 
				TEST3="${DESC3} ${RED}[nope]${NC}\\n"
			fi
			;;
		4)
			./minishell 4
			cat | cat | ls >test4
			if diff -a outfile5 test4 > /dev/null ; then
				TEST4="${DESC4} ${GREEN}[OK]${NC}\\n"
			else 
				TEST4="${DESC4} ${RED}[nope]${NC}\\n"
			fi
			;;
	esac
done
echo -e "${TEST1}${TEST2}${TEST3}${TEST4}" | awk '/./'