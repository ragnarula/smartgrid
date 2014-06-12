#ifndef HOME_AREA_NETWORK
#define HOME_AREA_NETWORK

#include "ns3/object.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"

namespace ns3 
{

	class HomeAreaNetwork : public Object 
	{
		private:
			static uint32_t hanId;
			Ptr<Node> esp;
			Ptr<Node> wifiAp;
			NodeContainer wifiNodes;
			NetDeviceContainer wifiDevices;
			NetDeviceContainer wifiApDevice;

			void InitWifiNodes();
			void InitIpv4();	
		public:
			HomeAreaNetwork();
			virtual ~HomeAreaNetwork();
			Ptr<Node> GetEsp();
			Ptr<Node> GetAp();

	};

} //namespace
#endif
