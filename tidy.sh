#!/bin/bash

OK=0
COMPILEDB_FNAME="compile_commands.json"

#Regenerate the compile_commands.json file
if `compiledb -n make`
then
    #This should not be able to happen
    if [[ -f $COMPILEDB_FNAME ]]
    then
        OK=1
    else
        echo "Error: could not find the file compiledb created. It should be"\
            "named:" $COMPILEDB_FNAME
    fi
else
    if [[ -f $COMPILEDB_FNAME ]]
    then
        OK=1
    else
        echo "Error: compiledb failed to create the" $COMPILEDB_FNAME "file"\
            "failed for some reason check above for error messages and make"\
            "sure compiledb is installed correctly."
    fi
fi

if [[ $OK == 1 ]]
then
    #Check all the headers and cpp files with the stated checks
    clang-tidy --format-style=file --use-color\
            --checks="clang-analyzer-security.*, clang-analyzer-core.*,\
            clang-analyzer-cplusplus.*, clang-analyzer-nullability.*,\
            clang-analyzer-apiModeling.*"\
            --header-filter=.hpp *.cpp
fi
