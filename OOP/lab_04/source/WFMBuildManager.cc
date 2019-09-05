#include "WFMBuildManager.h"

WFMBuildManager::WFMBuildManager(WFMReaderBase *reader, WFMBuilderBase *builder)
{
    setReader(reader);
    setBuilder(builder);
}

void WFMBuildManager::setReader(WFMReaderBase *reader)
{
    this->reader = reader;
}

void WFMBuildManager::setBuilder(WFMBuilderBase *builder)
{
    this->builder = builder;
}

void WFMBuildManager::make()
{
    make(reader, builder);
}

void WFMBuildManager::make(WFMReaderBase *reader, WFMBuilderBase *builder)
{
    builder->setSizes(reader->readVerticesQuan(), reader->readEdgesQuan());
    builder->addVertices(reader->readVertices());
    builder->addEdges(reader->readEdges());
}

