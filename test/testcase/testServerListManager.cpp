#include <iostream>
#include <map>
#include "server/ServerListManager.h"
#include "config/NacosConfigService.h"
#include "factory/NacosServiceFactory.h"
#include "ResourceGuard.h"
#include "http/HTTPCli.h"
#include "PropertyKeyConst.h"
#include "DebugAssertion.h"
#include "Debug.h"
#include "json/JSON.h"
#include "Constants.h"

using namespace std;

bool testServerListManager()
{
	cout << "in function testServerListManager" << endl;
    Properties props;
    props[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1:8848";
    NacosServiceFactory *factory = new NacosServiceFactory(props);
    ResourceGuard<NacosServiceFactory> _guardFactory(factory);
    ConfigService *n = factory->CreateConfigService();
    ResourceGuard<ConfigService> _serviceFactory(n);

    NacosConfigService *nn = (NacosConfigService*)n;
    ServerListManager *serverListManager = nn->getServerListManager();

    std::map<NacosString, NacosServerInfo> res = serverListManager->__debug();

    for (std::map<NacosString, NacosServerInfo>::iterator it = res.begin(); it != res.end(); it++)
    {
        NacosString key = it->first;
        NacosString val = it->second.toString();

        cout << key << ":" << endl << val << endl;
    }

    cout << "=====================cornercase========================" << endl;
    NacosString fakeSvr = "{\"servers\":[]}";
    list<NacosServerInfo> result = JSON::Json2NacosServerInfo(fakeSvr);
    cout << "result.size == " << result.size() << endl;
    for (list<NacosServerInfo>::iterator it = result.begin(); it != result.end(); it++)
    {
        NacosString key = it->getCompleteAddress();
        NacosString val = it->toString();

        cout << key << ":" << endl << val << endl;
    }
	return true;
}