cmake_minimum_required(VERSION 3.1.0)

project(lab_02)

add_executable(lab_02
    source/main.cc
    source/rblavlnode.cc
    source/rblavltree.cc
    source/rblexception.cc
    source/rblset.cc
)

target_include_directories(lab_02
    PUBLIC
        "include"
)

