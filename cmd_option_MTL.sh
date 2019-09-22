#Setting PATH 64-bit Apple Mac
DYLD_LIBRARY_PATH=/Applications/MATLAB_R2019a.app/extern/bin/maci64:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH

g++ -std=c++11 -o main_MTL main_MTL.cpp -I /Applications/MATLAB_R2019a.app/extern/include/ -L /Applications/MATLAB_R2019a.app/extern/bin/maci64 -lMatlabDataArray -lMatlabEngine

if [ "$1" == "0" ]; then
	echo "
		Case: 2-Comb
		"
	time ./main_MTL ExtractedInfo/output20190325/201903251056/190325EDAIDESFORTMT/objects.txt ExtractedInfo/output20190325/201903251056/190325EDAIDESFORTMT/dtime.txt
elif [ "$1" == "1" ]; then
	echo "
		Case: 0326-1
		"
	time ./main_MTL ExtractedInfo/output20190326/260319/20190326_1/190326EDALAPLACE1/objects.txt ExtractedInfo/output20190326/260319/20190326_1/190326EDALAPLACE1/dtime.txt
elif [ "$1" == "2" ]; then
	echo "
		Case: 0326-2
		"
	time ./main_MTL ExtractedInfo/output20190326/260319/20190326_2/190326EDALAPLACE2/objects.txt ExtractedInfo/output20190326/260319/20190326_2/190326EDALAPLACE2/dtime.txt
elif [ "$1" == "3" ]; then
	echo "
		Case: 0326-3
		"
	time ./main_MTL ExtractedInfo/output20190326/260319/20190326_3/190326EDALAPLACE3/objects.txt ExtractedInfo/output20190326/260319/20190326_3/190326EDALAPLACE3/dtime.txt
elif [ "$1" == "4" ]; then
	echo "
		Case: 0326-4
		"
	time ./main_MTL ExtractedInfo/output20190326/260319/20190326_4/190326EDALAPLACE4/objects.txt ExtractedInfo/output20190326/260319/20190326_4/190326EDALAPLACE4/dtime.txt
elif [ "$1" == "5" ]; then
	echo "
		Case: 0326-5
		"
	time ./main_MTL ExtractedInfo/output20190326/260319/20190326_5/190326EDALAPLACE5/objects.txt ExtractedInfo/output20190326/260319/20190326_5/190326EDALAPLACE5/dtime.txt
else
	echo "NON-supported case!!!!!"
fi
# example:
# $1 (input, obj path): 	../ExtractedInfo/output0418/layer1/objects.txt
# $2 (input, obj conflict: 	../ExtractedInfo/output0418/layer1/conflict.txt
# $3 (time threshold): 		30
# $4 (output common name):	../Result/layer1


