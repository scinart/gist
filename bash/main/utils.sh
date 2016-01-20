#!/bin/bash


## functions
function errcho() { echo "$@" 1>&2; }

function fail()
{
    echo "Failed $@, backtrace:";
    local i=0; while caller $i ;do ((i++)) ;done
    return 1;
}

function usage()
{
    if [[ $# -eq 0 ]]; then
    	echo "Usage: ${USAGE}"
	declare -f main
    else
	declare -f $1;
    fi
}

function __main()
{
    if [[ $# -eq 0 ]]; then
	main
    elif [[ $1 = "-h" ]]; then
	usage "${@:2}"
    else
    	"$1" "${@:2}"
    fi
}
