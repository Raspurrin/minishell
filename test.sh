#!/bin/bash

RED="\033[1;31m"
GREEN="\033[1;32m"
BLACK="\033[035m"
CYAN="\033[0;36m"
VIOLET="\033[0;30m"
NC="\033[0m"
DESC1="test1:"
DESC2="test2:"
DESC3="test3:"
DESC4="test4:"

while getopts "d1234" opt; do
	case $opt in
		d)
			DESC1="test1: ${VIOLET}(${BLACK}export something=BLACK${VIOLET} | ${BLACK}env ${VIOLET}>outfile1):${NC}\\n"
			DESC2="test2: ${VIOLET}(<heredoc1 <heredoc2 ${BLACK}grep yo ${VIOLET}>outfile2 >outfile3):${NC}\\n"
			DESC3="test3: ${VIOLET}(<infile1 <heredoc1 ${BLACK}grep yo ${VIOLET}>outfile1 | <infile4 ${BLACK}grep file ${VIOLET}>outfile5):${NC}\\n"
			DESC4="test4: ${VIOLET}(${BLACK}cat ${VIOLET}| ${BLACK}cat${VIOLET} | ${BLACK}ls ${VIOLET}>outfile6):${NC}\\n"
			;;
		1)
			rm -f outfile1 test1
			./minishell 1
			export something=BLACK | env >test1
			if diff -a outfile1 test1 > diff1 ; then
				TEST1="${DESC1} ${GREEN}[OK]${NC}\\n"
			else 
				TEST1="${DESC1} ${RED}[nope]${NC}\\n"
			fi
			;;
		2)
			rm -f outfile2 outfile3 test2 test3
			./minishell 2
			< heredoc1 < heredoc2 grep yo >test2 >test3
			if diff -a outfile3 test3 > diff2 ; then
				TEST2="${DESC2} ${GREEN}[OK]${NC}\\n"
			else 
				TEST2="${DESC2} ${RED}[nope]${NC}\\n"
			fi
			;;
		3)
			rm -f outfile4 outfile5 test4 test5
			./minishell 3
			<infile1 <heredoc1 grep yo >test4 | <infile2 grep file >test5
			if diff -a outfile5 test5 > diff3 ; then
				TEST3="${DESC3} ${GREEN}[OK]${NC}\\n"
			else 
				TEST3="${DESC3} ${RED}[nope]${NC}\\n"
			fi
			;;
		4)
			rm -f outfile6  test6
			./minishell 4
			cat | cat | ls >test6
			if diff -a outfile6 test6 > diff4 ; then
				TEST4="${DESC4} ${GREEN}[OK]${NC}\\n"
			else 
				TEST4="${DESC4} ${RED}[nope]${NC}\\n"
			fi
			;;
	esac
done
echo -e "${TEST1}${TEST2}${TEST3}${TEST4}" | awk '/./'