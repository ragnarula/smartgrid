#ifndef NEIGHBOURHOOD_AREA_NETWORK
#define NEIGHBOURHOOD_AREA_NETWORK = 1

#include "ns3/object.h"
#include <vector>
#include "home-area-network.h"

namespace ns3 {

	class NeighbourhoodAreaNetwork : public Object {
		private:
			Ptr<Node> server;
			NetDeviceContainer p2pDevices;
			std::vector<HomeAreaNetwork> hanList;
		public:
			NeighbourhoodAreaNetwork();
			virtual ~NeighbourhoodAreaNetwork();
			void Add(const Ptr<HomeAreaNetwork>);
		
	};
} //namespace

#endif
				
