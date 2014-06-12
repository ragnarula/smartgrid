#include "home-area-network.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/object.h"

using namespace ns3;
int main (){
	Ptr<HomeAreaNetwork> app = CreateObject<HomeAreaNetwork> ();

}
