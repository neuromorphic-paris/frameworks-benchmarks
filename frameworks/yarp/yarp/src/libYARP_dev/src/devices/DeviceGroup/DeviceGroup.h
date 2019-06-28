/*
 * Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_DEV_DEVICEGROUP_H
#define YARP_DEV_DEVICEGROUP_H

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ServiceInterfaces.h>


namespace yarp{
    namespace dev {
        class DeviceGroup;
    }
}

/**
 * @ingroup dev_impl_other
 *
 * Lets you make a bunch of devices as a group.
 *
 */
class YARP_dev_API yarp::dev::DeviceGroup : public DeviceDriver,
                                            public IService {

public:
    DeviceGroup() {
        implementation = NULL;
    }

    virtual ~DeviceGroup();

    bool open(yarp::os::Searchable& config) override;

    bool close() override {
        return closeMain();
    }

    bool startService() override;

    bool stopService() override {
        return close();
    }

    bool updateService() override;

private:
    void *implementation;

    bool closeMain();

    PolyDriver source, sink;

    bool open(const char *key, PolyDriver& poly,
              yarp::os::Searchable& config, const char *comment);
};


#endif // YARP_DEV_DEVICEGROUP_H
