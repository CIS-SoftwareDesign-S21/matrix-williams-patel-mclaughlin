# matrix-williams-patel-mclaughlin

1. Distributed parallel computing:
Parallel computing is used when larger computation-intensive problems are to be solved.  There are many approaches to managing the computation more effectively. In this lab, this is done by dividing the work between several processors. 
We are using SIMD, SIMT, symmetric processing and distributed processing for solving the problem of matrix multiplication.
 In Single Instruction Multiple Data (SIMD), the same operation is performed on multiple streams of data simultaneously.
 In Single Instruction Multiple Threads (SIMT), the work is divided within several threads which simplifies the programming.
 In symmetric processing, multiple processors share common memory and input-output resources. 
In distributed memory, a high-speed network connects independent computers to solve the intensive computing.

2.  Teamwork

  I)  Tom McLaughlin
  
    - I took responsibility for setting up the project board, branches, and commits. 
      I did my best to help coordinate everyone’s efforts and communicate well through documentation and support. 
  
    -  I wrote the code for some of the matrix multiplication tasks 
       (Meshwa had to fix my indexing (Thank you Meshwa!), but the rest was there)
  
    -  I also did the timing portion of the code, as well as helping with miscellaneous tasks as assistance was needed.
    
  II) Meshwa
  
    - I wrote the code for the first day submission, I guess it was SIMD
    
    - I had to write the code to read the matrices from the file.
    
    - Also, did the additional task to combine OpenMP and MPI. We all contributed to the readme file.
    
    Thank you Tom and Sean for working out most of the things and helping me a lot in this project. 
    I was a little unwell in the middle and also overwhelmed with this project. Thanks again.
    
    
  III) Sean
  
    - My responsibilities included making the automated graph maker in python which allowed us to create 
      the combined graph by calling “python3 grapher.py” in the command line. 
    
    - My other responsibility was the mpi matrix multiplication code. 
      This was my task mostly in weeks 2 and 3 because once I completed the mpi code in week 2 I created the timing in week 3.
    
    - I also reworked the timing in task 4 so that it fit our format for our graphs.
    

-We locked the master branch so that each other’s work needs to be reviewed before merging it into the master branch. Whenever someone committed to the branch, we used discord to notify each other so that the other person could review and merge into the master. Discord made it easier.

3. Full project life cycle
  We used the Github project board for all the tasks that had to be done. It was easier to track everything that way. Once a person starts on a task, the task goes into in-progress. When the task is completed, it is transferred to ready to merge and the other person is notified for the merge in discord so reviewing and merging can be done. Once, the tasks are merged into the master branch, it is transferred to the completed section in the project board. Keeping track of what is done and what is to be done in larger groups becomes a lot easier with these tools.
  Wolfgang cluster is a new concept. We write the code, compile the code and when testing is to be done, we log in to the cluster and proceed to test the modifications that we made. 
  Here our development workflows diverged a little. Once on the cluster, if we (Tom, Meshwa) had to make changes in one of the c files, then we do not go back to IntelliJ. We simply use the commands like vim or nano to open the files and alter them according to the needs. We learnt many new and different commands which we used in the course of the project. Sean continued to use an IDE on his machine, and would then push the changes from there.
  Testing was mainly done calculating the actual matrix multiplication by hand, manually. 
  The approach we originally took to timing the performance of the matrix multiplications meant that we needed to take a bunch of text files and plot them on the same graph. We got tired of typing in the names of the files which contained the graph data, so Sean created a nifty little part of the script that picks up any text file with a special tag in the name. From there, complete automation of graphing was pretty trivial.
  Writing the variations on the matrix multiplication tasks took about thirty percent of the whole time, testing and correcting the timing issues and errors took most of the time used for the project.

  4. Include all tables, graphs and explanations needed to understand your work in the README.md file. No new or supplemental information should need to be communicated during the demo to grade your work.  
 
  The mpi code works as follows. It takes a single parameter, N, and from there it calculates the time it takes to multiply two random N by N matrices using MPI. Our timing program, mpi_timing, loops through the mpi code N times in order to calculate the time it takes to multiply a MxM matrix where M is the iteration we are currently on. The mpi code itself finds the number of rows it will send to each child and stores that in the variable rows. Then it loops from 1 to workerTaskCount where workerTaskCount is the number of processes connected to root. It then sends the entire matrix b, the rows of a to compute, and a value offset. Offset allows us to make sure that we aren’t sending the same rows, so after each loop rows are added to offset to iterate through the matrix a. Then the program checks to see if there are any extra rows because rows are computed by doing N/workerTaskCount which has the possibility of leaving a remainder. Those remaining rows are computed by the root process. We thought this would be a good approach to deal with the modulus because in our case we only have 3 processes so the most the root will have to compute is 2 rows. Then after the rows have been computed by the workers they are sent back and placed right into c. The only issue with this method that we encountered was the fact that it can only handle up to 590 by 590 size matrices. Any matrix greater than 590 by 590 matrices produced a segmentation fault. Which could possibly be the error of the cluster running out of memory or a buffer being overloaded. But otherwise the program works well and correctly.

![task-graphs](https://user-images.githubusercontent.com/70284209/112647599-160ccc80-8e1f-11eb-9d3e-e0d242bbe7bd.png)

 

