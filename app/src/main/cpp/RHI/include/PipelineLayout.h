//
// Created by realxie on 2019-10-10.
//

#ifndef ALITA_PIPELINELAYOUT_H
#define ALITA_PIPELINELAYOUT_H

#include "Macros.h"
#include <memory>

NS_RHI_BEGIN

class PipelineLayout;

typedef std::shared_ptr<PipelineLayout> PipelineLayoutHnd;

class PipelineLayout
{
public:
    virtual ~PipelineLayout(){}
};

NS_RHI_END

#endif //ALITA_PIPELINELAYOUT_H
