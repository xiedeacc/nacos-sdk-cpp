#include "NacosString.h"
#include "src/debug/DebugAssertion.h"
#include <iostream>

using namespace std;
using namespace nacos;

// Use a special variable NULLSTR as null in Java to pass null parameter
// But "" (zero-length string) will still be regarded as null
bool testStringEqual() {
  cout << "In testStringEqual" << endl;
  NacosString s2 = "";
  NacosString s3 = "Nacos";
  SHOULD_BE_TRUE(NacosisNull(NULLSTR), "NULLSTR should be NULL");
  SHOULD_BE_TRUE(NacosisNull(s2), "\"\" should be NULL");
  SHOULD_BE_FALSE(NacosisNull(s3), "\"Nacos\" should not be NULL");

  return true;
}
