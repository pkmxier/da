if ! g++ -std=c++11 main.cpp tbtree.cpp tbtreenode.cpp tstring.cpp -o lab2; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

mkdir -p tests
if ! python3 test_generator.py 1 ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    echo "Execute ${test_file}"
    if ! time ./lab2 < $test_file > tmp ; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" tmp ; then
        echo "Failed"
    else
        echo "OK"
    fi
    
  done
