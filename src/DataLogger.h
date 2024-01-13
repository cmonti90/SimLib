#ifndef A7303F7F_F4B4_4130_B41B_BD74A8051642
#define A7303F7F_F4B4_4130_B41B_BD74A8051642

#include "H5Cpp.h"

namespace SimLib
{
    class DataLogger
    {
      public:
        DataLogger();
        ~DataLogger();

        static DataLogger* GetInstance();

        // void log( const std::string& data );

      private:
        // H5::H5File m_file;

        DataLogger( const DataLogger& ) = delete;
        DataLogger& operator=( const DataLogger& ) = delete;
    };
}

#endif /* A7303F7F_F4B4_4130_B41B_BD74A8051642 */
