#ifndef __CLIENT_WORKER_H_
#define __CLIENT_WORKER_H_

#include "Compatibility.h"
#include "ListeningData.h"
#include "NacosExceptions.h"
#include "NacosString.h"
#include "OperateItem.h"
#include "listen/Listener.h"
#include "src/config/AppConfigManager.h"
#include "src/config/LocalSnapshotManager.h"
#include "src/factory/ObjectConfigData.h"
#include "src/server/ServerListManager.h"
#include <map>
#include <pthread.h>
#include <vector>

/**
 * ClientWorker
 *
 * @author Liu, Hanyu
 * Directly migrated from Java, but with significant work of rewrite/redesign
 */
namespace nacos {
class ClientWorker {
private:
  // This list holds the listeners to be removed after a performWatch() event
  // And after all the items in this list is removed, an extra check must be
  // performed on listeningKeys to make sure if the entry of that key is empty,
  // remove the entry
  std::list<OperateItem> deleteList;
  // dataID||group||tenant -> Cachedata* Mapping
  std::map<NacosString, ListeningData *> listeningKeys;
  pthread_mutex_t watchListMutex; // TODO:refactor to Mutex
  ObjectConfigData *_objectConfigData;
  // Listener thread related info
  pthread_t threadId;

  volatile bool stopThread;
  pthread_mutex_t stopThreadMutex;

  int _longPullingTimeout;
  NacosString _longPullingTimeoutStr;

  static void *listenerThread(void *watcher);

  // You just can't construct a ClientWorker object without any parameter
  ClientWorker();

  std::vector<NacosString> parseListenedKeys(const NacosString &ReturnedKeys);

  NacosString checkListenedKeys() NACOS_THROW(NetworkException, NacosException);

  void clearDeleteList(int maxRemoves);

  void cleanUp();

  void addDeleteItem(const OperateItem &item);

public:
  ClientWorker(ObjectConfigData *objectConfigData);

  ~ClientWorker();

  void startListening();

  void stopListening();

  void addListener(const NacosString &dataId, const NacosString &group,
                   const NacosString &tenant, const NacosString &initialContent,
                   Listener *listener);

  void removeListenerActively(const NacosString &dataId,
                              const NacosString &group,
                              const NacosString &tenant, Listener *listener);

  void removeListener(const NacosString &dataId, const NacosString &group,
                      const NacosString &tenant, Listener *listener);

  void performWatch();

  NacosString getServerConfig(const NacosString &tenant,
                              const NacosString &dataId,
                              const NacosString &group, long timeoutMs)
      NACOS_THROW(NacosException);
  NacosString getServerConfigHistory(const NacosString &tenant,
                                     const NacosString &dataId,
                                     const NacosString &group, long timeoutMs)
      NACOS_THROW(NacosException);
  NacosString getServerConfigHistoryDetail(const NacosString &tenant,
                                           const NacosString &dataId,
                                           const NacosString &group,
                                           const NacosString &nid,
                                           long timeoutMs)
      NACOS_THROW(NacosException);
  HttpResult getServerConfigHelper(const NacosString &tenant,
                                   const NacosString &dataId,
                                   const NacosString &group,
                                   const NacosString &url_path,
                                   const std::list<NacosString> *inParamValues,
                                   long timeoutMs) NACOS_THROW(NacosException);
};
} // namespace nacos

#endif
