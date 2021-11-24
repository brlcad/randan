# randan
A randan pseudorandom number racer

To compile:

1) you'll need to first install:
   CMake 3.12+
   C and C++11 Compiler
   Build Environment (e.g., GNU Make or MSVC)

2) create a build directory
   mkdir .build
   cd .build
   
3) run cmake
   cmake ..

4) compile
   make

5) run randan
   ./randan

Example output:

(base) morrison@agua .build % ./randan 10
"randan" v1.0.0 by C.S. Morrison

  Usage: ./randan [count]
  Generating 10 pseudorandom numbers using 4 implementations
  with uniform distribution within [0, 1000000)

    rand()	  random()	 lrand48()	std::mt19937	
----------	----------	----------	------------
    289545	    709204	    489858	    529664	
    319735	    452956	    281348	    929079	
    839056	    806946	    542654	    342404	
     23113	     75195	    374325	    449994	
    394394	    103777	    398692	    385367	
    649149	    309927	    270198	       505	
    725332	    136400	    752605	    988962	
    879078	    874979	    233938	    794230	
    659835	    986315	    772046	    904636	
    425269	    903462	    829112	    440668
