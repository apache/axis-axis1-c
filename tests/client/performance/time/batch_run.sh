while read x; 
do 
    echo"";
    echo $x;
    time timeTest $x; 
done < input

