echo on
prompt $g
rem
del cas.exe
SET OMP_PROC_BIND=TRUE
SET OMP_PLACES=CORES
gcc -march=x86-64 -fopenmp -O3 -o %1.exe %1.c -Wextra
REM

