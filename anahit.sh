#!/bin/sh

RS="\033[0m"
RED="\033[1;31m"

DESC="${RED}(asdfasdfsadf${NC}\\n"


echo -e "${DESC}" | awk '/./'

