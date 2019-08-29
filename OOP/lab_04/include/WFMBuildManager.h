#ifndef WFM_BUILD_MANAGER_H_
#define WFM_BUILD_MANAGER_H_

#include "WFMReaderBase.h"
#include "WFMBuilderBase.h"

class WFMBuildManager
{
public:
    explicit WFMBuildManager(WFMReaderBase *reader = nullptr, WFMBuilderBase *builder = nullptr);
    ~WFMBuildManager() = default;

    static
    void make(WFMReaderBase *reader, WFMBuilderBase *builder);
    void make();

    void setReader(WFMReaderBase *reader);
    void setBuilder(WFMBuilderBase *builder);

private:
    WFMReaderBase *reader;
    WFMBuilderBase *builder;
};

#endif // WFM_BUILD_MANAGER_H_

