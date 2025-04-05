echo "rush-02 test 01"
./rush-02 42 | cat -e
echo "expected: forty two$"
./rush-02 0 | cat -e
echo "expected: zero$"
./rush-02 10.4 | cat -e
echo "expected: Error$"
./rush-02 100000 | cat -e
echo "expected: one hundred thousand$"
# try changing numbers.dict later
grep "20" numbers.dict | cat -e
echo "expected: 20 : twenty$"
./rush-02 20 | cat -e
echo "expected: twenty$"