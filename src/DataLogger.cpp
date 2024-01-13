

#include "DataLogger.h"

#include <iostream>

namespace SimLib
{

    DataLogger::DataLogger()
    // : m_file( "OutputStat.h5", H5F_ACC_TRUNC )
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