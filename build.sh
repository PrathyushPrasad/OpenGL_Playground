#!/usr/bin/env bash

#enumerate variables
projectname=${PWD##*/}

#get into build directory
mkdir -p build
cd build

# functions for build script
show_options () {
    PS3='What You want to Do (enter your choice no.): '
    options=("Configure" "make" "clean" "Cancel")
    select opt in "${options[@]}"
    do
        case $opt in
            "Configure")
                cmake ..
                ;;
            "make")
                make -j4
                ;;
            "clean")
                ;;
            "Cancel")
                break
                ;;
            *)
                echo $opt
                echo "invalid option $REPLY";;
        esac
        REPLY=
    done
}

show_main () {
    echo "Welcome to Build Script for $projectname"
    PS3='Proceed ? (enter your choice no.): '
    options=("Yes" "No")
    select opt in "${options[@]}"
    do
        case $opt in
            "Yes")
                clear
                show_options
                PS3='Proceed ? (enter your choice no.): '
                ;;
            "No")
                break
                ;;
            *)
                echo "invalid option $REPLY";;
        esac
        REPLY=
    done
}

# Start Execution
show_main

