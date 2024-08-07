#include "datawarehousestructs.hpp"
#include <thread>

int main(int argc, char *argv[]) {
    using namespace std::chrono_literals;
    if (argc < 3)
    {
        std::cout << "Wrong number of arguments" << std::endl;
    }
    else 
    {
        std::string shm_name(argv[1]);
        int arr_capacity = atoi(argv[2]);

        SharedMemory shm;
        ServerSharedMemoryBuilder sharedMemoryBuilder(shm_name, arr_capacity);
        SharedMemoryDirector director;
        director.buildSharedMemory(sharedMemoryBuilder);
        
        try
        {
            shm = sharedMemoryBuilder.getResult();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }

        for (size_t i = 0; i < arr_capacity; i++)
        {
            std::this_thread::sleep_for(200ms);
            std::string rec_name = "Record" + std::to_string(i+1);
            switch (i%5)
            {
            case 0:
                {
                    int32_t value = std::rand();
                    shm.addRecord(Record(i, rec_name, Record::T_INT_TYPE, value));
                }
                break;
            case 1:
                {
                    float value =  std::rand();
                    value /= 10;
                    shm.addRecord(Record(i, rec_name, Record::T_FLOAT_TYPE, value));
                }
                break;
            case 2:
                {
                    double value = std::rand();
                    value /= 100;
                    shm.addRecord(Record(i, rec_name, Record::T_DOUBLE_TYPE, value));
                }
                break;
            case 3:
                {
                    uint64_t value = std::rand();
                    shm.addRecord(Record(i, rec_name, Record::T_UINT_TYPE, value));
                }
                break;
            case 4:
                {
                    std::string value = "VALUE";
                    shm.addRecord(Record(i, rec_name, Record::T_STRING_TYPE, value));
                }          
                break;
            }
        }
        shm.getRecords();
    }
}