#include "home-area-network.h"
#include "ns3/log.h"
#include "ns3/wifi-module.h"
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include <sstream>
#include "ns3/internet-module.h"

using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("HomeAreaNetwork");

uint32_t HomeAreaNetwork::hanId = 0;

HomeAreaNetwork::HomeAreaNetwork() : Object(), 
	esp(CreateObject<Node>()), 
	wifiAp(CreateObject<Node>()),
	wifiNodes(),
	wifiDevices(),
	wifiApDevice()	
{
	HomeAreaNetwork::hanId++;
	wifiNodes.Create(10);
	//logging
	NS_LOG_FUNCTION (this);
	InitWifiNodes();
}
HomeAreaNetwork::~HomeAreaNetwork() {}

void HomeAreaNetwork::InitWifiNodes(){
	NS_LOG_FUNCTION(this);	
	//Phy and channel Helpers with Default settings
	YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
	YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
	//Set channel of phy layer
	phy.SetChannel (channel.Create ());
	//wifi helper with manager
	WifiHelper wifi = WifiHelper::Default ();
	wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
	//Mac helper
	NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();
	//set ssid to HAN number
	std::stringstream ss;
	ss << "HAN-" << HomeAreaNetwork::hanId;
	Ssid ssid = Ssid (ss.str());
	//set mac for clients
	mac.SetType ("ns3::StaWifiMac",
			"Ssid", SsidValue (ssid),
			"ActiveProbing", BooleanValue (false));
	//install devices to wifi nodes nodes	
	wifiDevices = wifi.Install(phy,mac,wifiNodes);
	//install device to esp node
	wifiDevices.Add (wifi.Install(phy,mac,esp));
	//set mac for AP
	mac.SetType ("ns3::ApWifiMac",
			"Ssid", SsidValue (ssid));
	//install device on AP
	wifiDevices.Add (wifi.Install(phy,mac,wifiAp));
	//Position Allocation
	MobilityHelper mobility;
	
	mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
			"MinX", DoubleValue (0.0),
			"MinY", DoubleValue (0.0),
			"DeltaX", DoubleValue (5.0),
			"DeltaY", DoubleValue (10.0),
			"GridWidth", UintegerValue (3),
			"LayoutType", StringValue ("RowFirst"));  
	//constant mobility for all nodes
	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility.Install (wifiAp);
	mobility.Install (wifiNodes);
	mobility.Install (esp);

	//install internet Stack
	InternetStackHelper stack;
	stack.Install (wifiNodes);
	stack.Install (wifiAp);
	stack.Install (esp);
}

void HomeAreaNetwork::InitIpv4(){
	Ipv4AddressHelper address;

	address.SetBase ("192.168.1.0", "255.255.255.0");
	Ipv4InterfaceContainer p2pInterfaces;
	p2pInterfaces = address.Assign (wifiDevices);
}
