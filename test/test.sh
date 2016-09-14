echo "1: NORMAL"
./lem-in < ./test/test1.txt
echo "2: INSTANT"
./lem-in < ./test/test2.txt
echo "3: ERROR: double end"
./lem-in < ./test/test3.txt
echo "4: ERROR: no end"
./lem-in < ./test/test4.txt
echo "5: NORMAL: weird names"
./lem-in < ./test/test5.txt
echo "6: UNDEFINED: end and start is same"
./lem-in < ./test/test6.txt
echo "7: UNDEFINED: ant <= 0"
./lem-in < ./test/test7.txt
echo "8: ERROR: duplicate room"
./lem-in < ./test/test8.txt
echo "9: NORMAL: 2"
./lem-in < ./test/test9.txt
echo "10: NORMAL: 3"
./lem-in < ./test/test10.txt
echo "11: NORMAL: 4"
./lem-in < ./test/test11.txt
echo "12: NORMAL: 5"
./lem-in < ./test/test12.txt
