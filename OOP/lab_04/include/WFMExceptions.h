#ifndef WFM_EXCEPTONS_H_
#define WFM_EXCEPTONS_H_

#include "Exception.h"

_EXCEPTION_FORK(WFMReadException, "Wire-frame model reading error.");
_EXCEPTION_FORK(WFMExtractException, "Wire-frame model extracting error");

_EXCEPTION_FORK(WFMBuildException, "Wire-frame model building error.");
_EXCEPTION_FORK(WFMWriteException, "Wire-frame model writing error.");

#endif // WFM_EXCEPTONS_H_

