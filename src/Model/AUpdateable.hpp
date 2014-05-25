#ifndef _MODEL_AUPDATEABLE_INCLUDED_
#define _MODEL_AUPDATEABLE_INCLUDED_


namespace Model
{
	class AUpdateable
	{
	public:
		virtual void update( double delta ) = 0;
	};
}


#endif
