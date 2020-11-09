#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int my_rank, len;
    int no_p, source, dest, tag=0;

    std::ostringstream message_stream;
    std::string message_string;
    char message_char[100];

    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status mpi_status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &no_p);
    MPI_Get_processor_name(name, &len);

    if(my_rank != 0) {
        message_stream << "Greetings from process " << my_rank;
        dest=0;
        std::cout << " Hello, I'm " << my_rank << " of " << no_p << " sending to " << dest << std::endl;
        message_string = message_stream.str();
        //message_char = message_string.c_str();
        MPI_Send(message_string.c_str(), message_string.size(), MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }
    else{
        std::cout << "Howdy, here's process " << my_rank << ". I'm waiting for messages!" << std::endl;
        for(source=1; source<no_p; source++) {
            //MPI_Get_count(&mpi_status, MPI_CHAR, &mpi_count);
            MPI_Recv(message_char, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &mpi_status);
            message_string = message_char;
            std::cout << message_string << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}