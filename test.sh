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
DESC6="test6:"
DESC7="test7:"
DESC8="test8:"
DESC9="test9:"
DESC10="test10:"
DESC11="test11:"
DESC12="test12:"
FOLDER1="minishell_tester/test1/"
FOLDER2="minishell_tester/test2/"
FOLDER3="minishell_tester/test3/"
FOLDER4="minishell_tester/test4/"
FOLDER5="minishell_tester/test5/"
FOLDER6="minishell_tester/test6/"
FOLDER7="minishell_tester/test7/"
FOLDER8="minishell_tester/test8/"
FOLDER9="minishell_tester/test9/"
FOLDER10="minishell_tester/test10/"
FOLDER11="minishell_tester/test11/"
FOLDER12="minishell_tester/test12/"

while getopts "d123456789abc" opt; do
	case $opt in
		d)
			DESC1="test1: ${VIOLET}(${BLACK}export something=blue${VIOLET} | ${BLACK}env ${VIOLET}>outfile1):${NC}\\n"
			DESC2="test2: ${VIOLET}(<infile1 <infile2 ${BLACK}grep yo ${VIOLET}>outfile2 >outfile3):${NC}\\n"
			DESC3="test3: ${VIOLET}(<infile1 <infile2 ${BLACK}grep yo ${VIOLET}>outfile1 | <infile4 ${BLACK}grep file ${VIOLET}>outfile5):${NC}\\n"
			DESC4="test4: ${VIOLET}(${BLACK}cat ${VIOLET}| ${BLACK}cat${VIOLET} | ${BLACK}ls ${VIOLET}>outfile6):${NC}\\n"
			DESC5="test5: ${VIOLET}(${BLACK}export something=blue; env ${VIOLET}>outfile1)${NC}\\n"
			DESC6="test6: ${VIOLET}(${BLACK}export something=;env ${VIOLET}>outfile1 ${BLACK};export ${VIOLET}>outfile2;${BLACK}unset something; export ${VIOLET}>outfile3):${NC}\\n"
			DESC7="test7: ${VIOLET}(${BLACK}export something=====blue;env ${VIOLET}>outfile1;):${NC}\\n"
			DESC8="test8: ${VIOLET}(${BLACK}echo -nnn -----nn --nnnnn ${VIOLET}>outfile1):${NC}\\n"
			DESC9="test9: ${VIOLET}(${BLACK}env env env ${VIOLET}>outfile1):${NC}\\n"
			DESC10="test10: ${VIOLET}(${BLACK}env env hoi ${VIOLET}>outfile1):${NC}\\n"
			DESC11="test11: ${VIOLET}(${BLACK}unset PWD; env | grep PWD ${VIOLET}>outfile1):${NC}\\n"
			DESC12="test12: ${VIOLET}(${BLACK}/bin/cd ../;pwd ${VIOLET}>outfile1):${NC}\\n"
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
			rm -f ${FOLDER4}outfile1 ${FOLDER4}test1
			./minishell 4
			cat | cat | ls >${FOLDER4}/test1
			if diff -a ${FOLDER4}outfile1 ${FOLDER4}test1 > ${FOLDER4}diff ; then
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
		6)
			rm -f ${FOLDER6}outfile1 ${FOLDER6}outfile2 ${FOLDER6}outfile3 ${FOLDER6}test1 ${FOLDER6}test2 ${FOLDER6}test3
			./minishell 6
			export something=;env >test1;export >test2;unset something; export >test3
			if diff -a ${FOLDER6}outfile3 ${FOLDER6}test3 > ${FOLDER6}diff ; then
				TEST6="${DESC6} ${GREEN}[OK]${NC}\\n"
			else 
				TEST6="${DESC6} ${RED}[nope]${NC}\\n"
			fi
			;;
		7)
			rm -f ${FOLDER7}outfile1 ${FOLDER7}test1
			./minishell 7
			export something=====blue;env >test1;
			if diff -a ${FOLDER7}outfile1 ${FOLDER7}test1 > ${FOLDER7}diff ; then
				TEST7="${DESC7} ${GREEN}[OK]${NC}\\n"
			else 
				TEST7="${DESC7} ${RED}[nope]${NC}\\n"
			fi
			;;
		8)
			rm -f ${FOLDER8}outfile1 ${FOLDER8}test1
			./minishell 8
			 echo -nnn -----nn --nnnnn > ${FOLDER8}test1
			if diff -a ${FOLDER8}outfile1 ${FOLDER8}test1 > ${FOLDER8}diff ; then
				TEST8="${DESC8} ${GREEN}[OK]${NC}\\n"
			else 
				TEST8="${DESC8} ${RED}[nope]${NC}\\n"
			fi
			;;
		9)
			rm -f ${FOLDER9}outfile1 ${FOLDER9}test1
			./minishell 9
			env env env > ${FOLDER9}test1
			if diff -a ${FOLDER9}outfile1 ${FOLDER9}test1 > ${FOLDER9}diff ; then
				TEST9="${DESC9} ${GREEN}[OK]${NC}\\n"
			else 
				TEST9="${DESC9} ${RED}[nope]${NC}\\n"
			fi
			;;
		a)
			rm -f ${FOLDER10}outfile1 ${FOLDER10}test1
			./minishell 10
			env env hoi > ${FOLDER10}test1
			if diff -a ${FOLDER10}outfile1 ${FOLDER10}test1 > ${FOLDER10}diff ; then
				TEST10="${DESC10} ${GREEN}[OK]${NC}\\n"
			else 
				TEST10="${DESC10} ${RED}[nope]${NC}\\n"
			fi
			;;
		b)
			rm -f ${FOLDER11}outfile1 ${FOLDER11}test1
			./minishell 11
			unset PWD; env | grep PWD > ${FOLDER11}test1
			if diff -a ${FOLDER11}outfile1 ${FOLDER11}test1 > ${FOLDER11}diff ; then
				TEST11="${DESC11} ${GREEN}[OK]${NC}\\n"
			else 
				TEST11="${DESC11} ${RED}[nope]${NC}\\n"
			fi
			;;
		c)
			rm -f ${FOLDER12}outfile1 ${FOLDER12}test1
			./minishell 12
			/bin/cd ../;pwd > ${FOLDER12}test1
			if diff -a ${FOLDER12}outfile1 ${FOLDER12}test1 > ${FOLDER12}diff ; then
				TEST12="${DESC12} ${GREEN}[OK]${NC}\\n"
			else 
				TEST12="${DESC12} ${RED}[nope]${NC}\\n"
			fi
			;;
	esac
done
echo -e "${TEST1}${TEST2}${TEST3}${TEST4}${TEST5}${TEST6}${TEST7}${TEST8}${TEST9}${TEST10}${TEST11}${TEST12}" | awk '/./'

# Hanging: 4 6 b c