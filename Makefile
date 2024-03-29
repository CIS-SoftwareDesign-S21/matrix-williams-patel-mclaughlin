PGMS=mmult_omp_timing matrix_times_vector hello test_mmult mxv_omp_mpi mmult_mpi_omp

all:	${PGMS}

mmult_mpi_omp:		mmult.o mmult_mpi_omp.o mat.c
	mpicc -o mmult_mpi_omp -fopenmp -O3 mmult.o mmult_mpi_omp.o mat.c

mmult_mpi_omp.o:	mmult_mpi_omp.c
	mpicc -c -fopenmp -O3 mmult_mpi_omp.c

mmult_omp_timing:	mmult.o mmult_omp.o mmult_omp_timing.o mat.c
	gcc -o mmult -fopenmp -O3 mmult.o mmult_omp.o mmult_omp_timing.o mat.c -o mmult_omp_timing

mat.o:	mat.c
	gcc -c mat.c 

mmult.o:	mmult.c
	gcc -c mmult.c

mmult_omp.o:	mmult_omp.c
	gcc -c -O3 -fopenmp mmult_omp.c

mmult_omp_timing.o:	mmult_omp_timing.c
	gcc -c -O3 mmult_omp_timing.c

matrix_times_vector:	matrix_times_vector.c mat.c
	mpicc -O3 -o matrix_times_vector matrix_times_vector.c mat.c

hello:	hello.c
	mpicc -O3 -o hello hello.c

mxv_omp_mpi:	mxv_omp_mpi.c mat.c
	mpicc -fopenmp -O3 -o mxv_omp_mpi mxv_omp_mpi.c mat.c

test_mmult:	test_mmult.c mmult.c mat.c
	gcc test_mmult.c mmult.c mat.c -lm -o test_mmult

test_mmult_simd:	test_mmult.c mmult_simd.c mat.c
	gcc test_mmult.c mmult_simd.c mat.c -lm -o test_mmult_simd

test_o3_simd:	test_mmult.c mmult_simd.c mat.c
	gcc -O3 test_mmult.c mmult_simd.c mat.c -lm -o test_o3_simd

test_mpi:	test_mmult.c mmult_simd.c mat.c
	mpicc mmult_mpi.c mat.c -lm -o test_mpi

test_mpi2:	test_mmult.c mmult_simd.c mat.c
	mpicc mpi_mmult.c mat.c -lm -o test_mpi2

mmult_timing:		timing.c mmult.c mat.c
	gcc timing.c mmult.c mat.c -lm -o mmult_timing

mmult_simd_timing:	timing.c mmult_simd.c mat.c
	gcc timing.c mmult_simd.c mat.c -lm -o mmult_simd_timing

mmult_o3_simd_timing:	timing.c mmult_simd.c mat.c
	gcc -O3 timing.c mmult_simd.c mat.c -lm -o mmult_o3_simd_timing

clean:
	rm -f *.o
	rm -f ${PGMS}

