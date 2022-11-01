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
DESC5="test5:"
FOLDER1="minishell_tester/test1/"
FOLDER2="minishell_tester/test2/"
FOLDER3="minishell_tester/test3/"
FOLDER4="minishell_tester/test4/"
FOLDER5="minishell_tester/test5/"

while getopts "d12345" opt; do
	case $opt in
		d)
			DESC1="test1: ${VIOLET}(${BLACK}export something=blue${VIOLET} | ${BLACK}env ${VIOLET}>outfile1):${NC}\\n"
			DESC2="test2: ${VIOLET}(<infile1 <infile2 ${BLACK}grep yo ${VIOLET}>outfile2 >outfile3):${NC}\\n"
			DESC3="test3: ${VIOLET}(<infile1 <infile2 ${BLACK}grep yo ${VIOLET}>outfile1 | <infile4 ${BLACK}grep file ${VIOLET}>outfile5):${NC}\\n"
			DESC4="test4: ${VIOLET}(${BLACK}cat ${VIOLET}| ${BLACK}cat${VIOLET} | ${BLACK}ls ${VIOLET}>outfile6):${NC}\\n"
			DESC5="test5: ${VIOLET}(${BLACK}export something=blue; env ${VIOLET}>outfile1)${NC}\\n"
			;;
		1)
			rm -f ${FOLDER1}outfile1 ${FOLDER1}test1
			./minishell 1
			export something=blue | env >${FOLDER1}test1
			if diff -a ${FOLDER1}outfile1 ${FOLDER1}test1 > ${FOLDER1}diff ; then
				TEST1="${DESC1} ${GREEN}[OK]${NC}\\n"
			else 
				TEST1="${DESC1} ${RED}[nope]${NC}\\n"
			fi
			;;
		2)
			rm -f ${FOLDER3}outfile1 ${FOLDER3}outfile2 ${FOLDER3}test1 ${FOLDER3}test2
			./minishell 2
			< ${FOLDER2}infile1 < ${FOLDER2}infile2 grep yo >${FOLDER2}test1 >${FOLDER2}test2
			if diff -a ${FOLDER2}outfile2 ${FOLDER2}test2 > ${FOLDER2}diff ; then
				TEST2="${DESC2} ${GREEN}[OK]${NC}\\n"
			else 
				TEST2="${DESC2} ${RED}[nope]${NC}\\n"
			fi
			;;
		3)
			rm -f ${FOLDER3}outfile1 ${FOLDER3}outfile2 ${FOLDER3}test1 ${FOLDER3}test2
			./minishell 3
			<${FOLDER3}infile1 <${FOLDER3}infile2 grep yo >${FOLDER3}test1 | <${FOLDER3}infile3 grep file >${FOLDER3}test2
			if diff -a ${FOLDER3}outfile2 ${FOLDER3}test2 > ${FOLDER3}diff ; then
				TEST3="${DESC3} ${GREEN}[OK]${NC}\\n"
			else 
				TEST3="${DESC3} ${RED}[nope]${NC}\\n"
			fi
			;;
		4)
			rm -f ${FOLDER4}outfile1 ${FOLDER4}test2
			./minishell 4
			cat | cat | ls >${FOLDER4}/test2
			if diff -a ${FOLDER4}outfile1 ${FOLDER4}test2 > ${FOLDER4}diff ; then
				TEST4="${DESC4} ${GREEN}[OK]${NC}\\n"
			else 
				TEST4="${DESC4} ${RED}[nope]${NC}\\n"
			fi
			;;
		5) 
			rm -f ${FOLDER5}outfile1 ${FOLDER5}test1
			./minishell 5
			export something=blue;env >${FOLDER5}/test1
			if diff -a ${FOLDER5}outfile1 ${FOLDER5}test1 > ${FOLDER5}diff ; then
				TEST5="${DESC5} ${GREEN}[OK]${NC}\\n"
			else 
				TEST5="${DESC5} ${RED}[nope]${NC}\\n"
			fi
			;;

	esac
done
echo -e "${TEST1}${TEST2}${TEST3}${TEST4}${TEST5}" | awk '/./'