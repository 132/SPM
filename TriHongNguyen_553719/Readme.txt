For compilation:
icc Montecarlo.cpp function.cpp interval_number.cpp stage.cpp parallelism_ff_server.cpp -std=c++11 -I/home/spm1501/fastflow -pthread -O3 -DNO_DEFAULT_MAPPING -o ff
icc Montecarlo.cpp function.cpp interval_number.cpp parallelism_thread_server.cpp -std=c++11 -pthread -o thread
 
Execution:
./ff <NoThread> <IntervalNumberFile> <PowerFunc> <ElementFunction>
./thread <NoThread> <IntervalNumberFile> <PowerFunc> <ElementFunction>

Example:
./ff 10 ../input/Input100.txt 3 1 5 2 1
./thread 10 ../input/Input100.txt 3 1 5 2 1


For creating an Input.txt file:
icc createInput.cpp -o createInput

Execution:
./createInput <NoIntervalNumber> <MaxRangeFor a> <MaxRangeFor b>

Example:
./createInput 100 1000 1500
