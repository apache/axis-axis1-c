This test let you test with large string arrays.
String as well as the array size can be changed at run time
for testing. Also you can change the number of test runs.

To create a data input file which contains strings of given maximum length
and given number of lines, execute the following. The array size corresponds
to String array size.

format:java GetInput <maximum line length> <array size>

eg:java GenInput 128 1024 > stringdata.txt

If you want to test with larger strings, increase the maximum line length.
If you need to test with large array sizes, increase the array size.

Now to run the sample using this generated stringdata.txt input file

format:largeArrays <array size> <maximum line length> <number of runs> <datafile>
<comment>

eg:./largeArrays 1024 128 100 result "time(micro secs) taken each for 100 runs of
sending 1024 size string arrays"

array size should be less than or equal to number of lines in stringdata.txt.

maximum line length should be greater than or equal to the maximum string size
in stringdata.txt.

number of runs is the number of times you need to run the test

datafile is the stringdata.txt you created in the first step.

comment you put will appear in the head of the result file generated at the
end of the test run.
