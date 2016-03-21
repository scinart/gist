#!/bin/bash


## functions
function errcho() { echo "$@" 1>&2; }

function fail()
{
    echo "Failed $@, backtrace:";
    local i=0; while caller $i ;do ((i++)) ;done
    return 1;
}

function __program_exists()
{
    command -v "$1" >/dev/null 2>&1
}

function __usage()
{
    if [[ $# -eq 0 ]]; then
	[[ ! -z $USAGE ]] && echo "Usage: ${USAGE}" || (
	    echo "Available functions:"
	    compgen -A function |grep -ve "^__"
	)
    else
	declare -f $1;
    fi
}

function __main()
{
    if [[ $# -eq 0 ]]; then
	main
    elif [[ $1 = "-h" ]]; then
	__usage "${@:2}"
    else
    	"$1" "${@:2}"
    fi
}
