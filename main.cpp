#include <iostream>
#include <tins/tins.h>
#include<unistd.h>
#include <string>

using namespace Tins;
using namespace std;


int main()
{
	PacketSender sender;
	NetworkInterface iface("mon0");
	int i =0;
	while(1)
	{	
		
		Dot11Beacon beacon;
		// Make this a broadcast frame. Note that Dot11::BROADCAST
		// is just the same as "ff:ff:ff:ff:ff:ff"
		beacon.addr1(Dot11::BROADCAST);
		// We'll set the source address to some arbitrary address
		beacon.addr2("00:01:02:03:04:05");
		// Set the bssid, to the same one as above
		beacon.addr3(beacon.addr2());

		// Let's add an ssid option
		string ssid = "HandsomeGilgil" + to_string(i);
		cout << ssid << endl;
		beacon.ssid(ssid);
		// Our current channel is 8
		beacon.ds_parameter_set(8);
		// This is our list of supported rates:
		beacon.supported_rates({ 1.0f, 5.5f, 11.0f });

		// Encryption: we'll say we use WPA2-psk encryption
		beacon.rsn_information(RSNInformation::wpa2_psk());

		// The beacon's ready to be sent!
		RadioTap radio;
		radio.inner_pdu(beacon);

		for(int j =0; j<5; j++)
		{
			sender.send(radio, iface);
			sleep(0.5);
		}

		i ++;

	}
}
