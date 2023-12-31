#ifndef __NAMING_CACHE_H_
#define __NAMING_CACHE_H_

#include <map>
#include "NacosString.h"
#include "src/naming/subscribe/EventDispatcher.h"
#include "naming/ServiceInfo.h"
#include "src/thread/RWLock.h"
#include "naming/ChangeAdvice.h"
#include "Compatibility.h"
#include "NacosExceptions.h"

namespace nacos{
class NamingCache {
private:
    std::map<NacosString, ServiceInfo> namingList;
    RWLock _rwLock;
    EventDispatcher *_eventDispatcher;
public:
    NamingCache();
    NamingCache(EventDispatcher *eventDispatcher) { _eventDispatcher = eventDispatcher; };
    ServiceInfo getServiceInfo(const NacosString &key) NACOS_THROW(NacosException);
    bool contains(const NacosString &key);
    void setServiceInfo(const NacosString &key, const ServiceInfo &info);
    void removeServiceInfo(const NacosString &key);
};
}//namespace nacos

#endif