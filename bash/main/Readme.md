# Bash 组织形式

最开始是``main``，负责初始化变量，函数，其中常用函数在``utils.sh``里。

然后整个程序从``__main``(在``utils.sh``)里开始

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

用``./main -h``可以看到一些例子。

其中``"$1" "${@:2}"``这个设计是为了在外面(interactive shell)中直接调用shell里的变量和函数。