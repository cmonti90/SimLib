

#include "DataLogger.h"

#include <iostream>

namespace SimLib
{

    DataLogger::DataLogger()
    {
    }


    DataLogger::~DataLogger()
    {
    }


    DataLogger* DataLogger::GetInstance()
    {
        static DataLogger instance;
        
        return &instance;
    }
}