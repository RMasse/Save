#!/bin/bash


sed 's/</\&lt;/' $1 >> $1.html
sed 's/>/\&gt;/' $1 >> $1.html
sed 's/&/\&amp;/g' $1 >> $1.html



awk 'BEGIN {print "<head><link href=\"style.css\" rel=\"stylesheet\" media=\"all\" type=\"text/css\"></head>"};
BEGIN {print"<html><body><pre>"}; {print $0}; END {print "</pre></body></html>"}' $1 >> $1.html
