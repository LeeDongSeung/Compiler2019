#!/bin/bash
/*this is for array*/
declare -a lex_test_files
main_prog="20161616"
resource_dir="resources"
lex_test_files={"binary_search.c","keyword1.c","keyword2.c"}

for i in "${lex_test_files[@]}"
do
	./$main_prog $resources/$i | grep ERROR
done
