#!/bin/bash

#相对路径转绝对路径
routeRelative=../bin/main
dirRelative=${routeRelative%/*}
name=${routeRelative##*/}
routeAbsoluteDir=`cd $dirRelative;pwd`
routeAbsolute=$routeAbsoluteDir/$name
# echo $routeAbsolute
#
#
binaryName=$routeAbsolute

function start()
{
    pss0=`ps aux | grep "$binaryName" | awk '{print $11}'`
    for ps in $pss0
    do
        if [[ $ps != "$binaryName" ]]; then
            continue
        else
            echo "already running"
            exit 0
        fi
    done

    $binaryName &
    sleep 1s
    pss1=`ps aux | grep "$binaryName" | awk '{if($11==binaryName) print $2}' binaryName=$binaryName`

    psIdArray=()
    i=1
    for ps in $pss1
    do
        echo "run success pid$i  =  $ps"
        psIdArray[$i-1]=$ps
        i+=1
        #     exit 0
        # if [[ $ps != "$binaryName" ]]; then
        #     continue
        # else
        #     echo "run success"
        #     exit 0
        # fi
    done

    psNum=${#psIdArray[@]}
    if [[ $psNum<1 ]]; then
        echo "run faild"
    fi
}

function stop()
{
    pids=`ps aux | grep $binaryName | awk '{if($11==binaryName) print $2;}' binaryName=$binaryName`
    i=1
    psIdArray=()
    for pid in $pids
    do
        # echo  $pid
        psIdArray[$i-1]=$ps
        kill $pid
        echo "kill pid $pid success"
    done
    # echo "no ps belone to $binaryName"

    pidsNum=${#psIdArray[@]}
    if [[ $pidsNum < 1 ]]; then
        echo "do nothing,no process bind to $binaryName"
    fi
}

function restart()
{
    stop
    start
}

function help()
{
    echo "run binary for stitching: "
    echo ""
    echo "Usage: ./main.sh [start/stop/restart]"
    echo "      Options:"
    echo "      start       start run "
    echo "      stop        stop run "
    echo "      restart     stop then start run "
}

function main()
{
    typeset -l op
    op=$1
    if [[ $op == start ]]; then
        start
    elif [[ $op == stop ]]; then
        stop
    elif [[ $op == restart ]]; then
        restart
    elif [[ $op == -h || $1 == --help ]]; then
        restart
    else
        help
    fi
}

main $1
