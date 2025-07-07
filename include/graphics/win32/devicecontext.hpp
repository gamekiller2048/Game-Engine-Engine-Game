#pragma once

namespace mgl
{
    class DeviceContextImpl;
    class DeviceContext
    {
    public:
        DeviceContext();

        DeviceContextImpl* getImpl() const;

    protected:
        Owned<DeviceContextImpl> impl;
    };
}