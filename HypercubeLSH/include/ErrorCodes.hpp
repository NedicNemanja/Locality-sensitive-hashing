#ifndef ERRORCODES_HPP
#define ERRORCODES_HPP

typedef enum ERRORCODE { OK=0,
                  UNKNOWN_CMDARGUMENT=1,  //unknown flag at cmd arguments
                  FILE_ACCESS,  //couldnt open a file
                  BAD_STREAM,   //a fstream did not return goodbit
                  UNKNOWN_METRIC, //unknown metric in file @metric
                  MOD_ZERO_EXCEPTION, //tred to modulo 0
} ERRORCODE;

#endif
