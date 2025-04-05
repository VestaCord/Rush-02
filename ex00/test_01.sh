echo "rush-02 test 01"
echo "./rush-02 42 | cat -e"
./rush-02 42 | cat -e
echo "expected: forty two$"
echo "./rush-02 0 | cat -e"
./rush-02 0 | cat -e
echo "expected: zero$"
echo "./rush-02 10.4 | cat -e"
./rush-02 10.4 | cat -e
echo "expected: Error$"
echo "./rush-02 100000 | cat -e"
./rush-02 100000 | cat -e
echo "expected: one hundred thousand$"
# try changing numbers.dict later
echo "grep "20" numbers.dict | cat -e"
grep "20" numbers.dict | cat -e
echo "expected: 20 : twenty$"
echo "./rush-02 20 | cat -e"
./rush-02 20 | cat -e
echo "expected: twenty$"