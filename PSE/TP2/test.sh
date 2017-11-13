#!/bin/sh

POINT=""

for i in $*
do
  echo $POINT$i
  POINT=$POINT^"\b "
done
