#!/usr/bin/env bash

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
	-m|--minimum)
	MINIMUM="$2"
	shift # past argument
	shift # past value
	;;
	-M|--maximum)
	MAXIMUM="$2"
	shift # past argument
	shift # past value
	;;
	-r|--row-count)
	ROWCOUNT="$2"
	shift # past argument 
	shift # past value 
	;;
	-c|--col-count)
	COLCOUNT="$2"
	shift # past argument
	shift # past value
	;;
	-n|--trial-count)
	TRICOUNT="$2"
	shift # past argument
	shift # past value
	;;
	-i|--increment)
	INCREMENT="$2"
	shift # past argument
	shift # past value
	;;
	-p|--percolate)
	PERCOLATE="$2"
	shift # past argument
	shift # past value
	;;
	*) # unknown argument
	POSITIONAL+=("$1") # save it in an array for later
	shift # past argument
	;;
esac
done

DENSITY=$MINIMUM

echo $(ROWCOUNT) $(COLCOUNT)
while (( $(echo "$DENSITY <= $MAXIMUM"|bc) ))
do
	PROBABLITY="$( $PERCOLATE -r $ROWCOUNT -c $COLCOUNT -d $DENSITY -n $TRICOUNT)"
	echo $DENSITY $PROBABLITY
	DENSITY=$(echo "$DENSITY + $INCREMENT"|bc)
done





