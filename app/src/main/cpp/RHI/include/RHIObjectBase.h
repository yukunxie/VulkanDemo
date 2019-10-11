//
// Created by realxie on 2019-10-11.
//

#ifndef ALITA_RHIOBJECTBASE_H
#define ALITA_RHIOBJECTBASE_H

#include "Macros.h"

#include <memory>

NS_RHI_BEGIN

class RHIObjectBase
{
protected:
    virtual ~RHIObjectBase()
    {}

public:
    RHIObjectBase() = default;

    void Retain()
    {
        ++__referenceCount_;
    }

    void Release()
    {
        --__referenceCount_;
        if (__referenceCount_ <= 0)
        {
            OnDeleteEvent();
            delete this;
        }
    }

    std::int32_t GetReferenceCount() const
    {
        return __referenceCount_;
    }

    virtual void OnDeleteEvent()
    {
        // to override this function to process some logic before delete
    }

private:
    std::int32_t __referenceCount_ = 0;
};

NS_RHI_END

#endif //ALITA_RHIOBJECTBASE_H
