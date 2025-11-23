cmake_minimum_required(VERSION 3.30)
project(MarkovGraphTest C)

set(CMAKE_C_STANDARD 11)

add_executable(Run
        main.c ImportMG.c part2.c part3.c data/exemple1.txt graph_mermaid.txt mermaid.c data/exemple_valid_step3.txt data/exemple_Step_2_Part2.txt data/exemple_meteo.txt)

