#!/bin/bash

set -ex 

echo "cleanup..."
rm -f application_parent application_child lib*

echo "Compiling now..."
g++ -std=c++14 -fPIC -c -o libparent_plugin_sum.o  parent_plugin_sum.cpp
g++ -shared -o libparent_plugin_sum.so libparent_plugin_sum.o

g++ -std=c++14 -fPIC -c -o libchild_plugin_mult.o  child_plugin_mult.cpp
g++ -shared -o libchild_plugin_mult.so libchild_plugin_mult.o

g++ -std=c++14 -lboost_filesystem -lboost_system -ldl application_parent.cpp -o application_parent
g++ -std=c++14 -lboost_filesystem -lboost_system -ldl application_child.cpp -o application_child



