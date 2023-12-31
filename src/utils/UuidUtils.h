#ifndef __UUID_UTILS_H_
#define __UUID_UTILS_H_

#include "NacosString.h"

#define UUID_LEN_BYTES 16

/**
 * UuidUtils
 *
 * @author yzz-ihep
 * Generates UUID from /dev/urandom
 */

namespace nacos{
class UuidUtils {
private:
public:
    static NacosString generateUuid();

    static void Init();

    static void DeInit();
};
}//namespace nacos

#endif
