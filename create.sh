#!/usr/bin/bash

# Help message func
help() {
    echo "====================================================================================================================================================="
    echo "You are in $0."
    echo "Use $0 <name>"
    echo "Be happy!"
    echo "====================================================================================================================================================="
}

create() {
    mkdir ./src/$name
    cd ./src/$name
    touch $name.c $name"_lib".c  $name"_lib".h BUILD
    echo "Files $name.c $name"_lib".c BUILD $name"_lib".h created"
    exit 0
}

if [[ "$1" == "?" ]]; then
    help
    exit 0
elif [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
    echo "Please write <name> in lines."
    read -p "Name: " name
    create

else
    name=$1
    create
fi

