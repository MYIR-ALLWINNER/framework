#ifndef MOUNT_H
#define MOUNT_H

#include "NetlinkManager.h"
#include "NetlinkHandler.h"
#include "NetlinkEvent.h"
#include <errno.h>

class mount
{
public:
    mount(void *usrdata);
    ~mount();
};

#endif // MOUNT_H
