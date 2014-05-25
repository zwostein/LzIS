#ifndef _MODEL_NET_PULSELINK_INCLUDED_
#define _MODEL_NET_PULSELINK_INCLUDED_


namespace Model
{
	namespace Net
	{
		class PulseNode;

		struct PulseLink
		{
			bool pulse = false;
			const PulseNode * from = nullptr;
			const PulseNode * to = nullptr;
		};
	}
}


#endif
