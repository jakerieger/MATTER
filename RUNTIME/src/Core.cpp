#include <MatterRT/Core.hpp>
#include <stdio.h>
#include <boost/interprocess/shared_memory_object.hpp>

using boost::interprocess;

void Matter::Core::Run() {
    shared_memory_object shm_obj(
        open_or_create,
        "MatterRT",
        read_write
    );

    printf("Hello, Matter!\n");
}