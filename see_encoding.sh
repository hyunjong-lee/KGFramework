#/bin/bash
LIST=`find . -type f -name "*.h" -o -name "*.cpp"`
for i in $LIST;
do file $i;
done
