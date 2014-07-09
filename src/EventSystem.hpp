#ifndef _EVENTSYSTEM_INCLUDED_
#define _EVENTSYSTEM_INCLUDED_


#include <typeindex>
#include <type_traits>
#include <map>
#include <set>


#define HIERARCHICAL_EVENT( baseEventType, thisEventType ) \
	friend EventHandler; \
	friend GlobalEventHandler; \
	virtual void _recursiveDispatch( EventHandler & eventHandler ) const override \
	{ \
		eventHandler.handle( static_cast<thisEventType>(*this) ); \
		baseEventType::_recursiveDispatch( eventHandler ); \
	} \
	virtual void _recursiveDispatch() const override \
	{ \
		GlobalEventHandler::handle( static_cast<thisEventType>(*this) ); \
		baseEventType::_recursiveDispatch(); \
	} \



class EventHandler;
class GlobalEventHandler;


class AutoEventSource
{
public:
	AutoEventSource( EventHandler * eventHandler = nullptr ) : eventHandler(eventHandler) {}
	~AutoEventSource() {}

	template< typename TEvent >
	void dispatch( const TEvent & event );

	EventHandler * getEventHandler() { return this->eventHandler; }
	bool isGlobalEventSource() { return !this->eventHandler; }

private:
	EventHandler * eventHandler;
};


template< typename TEvent >
class AEventListener
{
public:
	virtual void onEvent( const TEvent & ) = 0;
};


template< typename TEvent >
class AAutoEventListener : public AEventListener< TEvent >
{
public:
	AAutoEventListener( EventHandler * eventHandler = nullptr );
	~AAutoEventListener();
	EventHandler * getEventHandler() { return this->eventHandler; }
	bool isGlobalEventListener() { return !this->eventHandler; }

private:
	EventHandler * eventHandler;
};


class AHierarchicalEvent
{
	friend EventHandler;
	friend GlobalEventHandler;
protected:
	virtual void _recursiveDispatch() const = 0;
	virtual void _recursiveDispatch( EventHandler & eventHandler ) const = 0;
};

inline void AHierarchicalEvent::_recursiveDispatch() const {}
inline void AHierarchicalEvent::_recursiveDispatch( EventHandler & eventHandler ) const {}


class EventHandler
{
public:
	template< typename TEvent,
		typename std::enable_if<!std::is_base_of< AHierarchicalEvent, TEvent >::value>::type* = nullptr >
	void dispatch( const TEvent & event )
	{
		handle( event );
	}

	template< typename TEvent,
		typename std::enable_if<std::is_base_of< AHierarchicalEvent, TEvent >::value>::type* = nullptr >
	void dispatch( const TEvent & event )
	{
		event._recursiveDispatch( *this );
	}

	template< typename TEvent >
	void handle( const TEvent & event )
	{
		for( const auto & listener : listeners[typeid(TEvent)] )
			static_cast<AEventListener<TEvent>*>(listener)->onEvent( event );
	}

	template< typename TEvent >
	bool addListener( AEventListener< TEvent > * listener )
	{
		return listeners[typeid(TEvent)].insert( static_cast<void*>(listener) ).second;
	}

	template< typename TEvent >
	bool removeListener( AEventListener< TEvent > * listener )
	{
		return listeners[typeid(TEvent)].erase( static_cast<void*>(listener) );
	}

private:
	typedef std::type_index EventType;
	typedef std::set< void * > ListenerSet;
	typedef std::map< EventType, ListenerSet > ListenerMap;
	ListenerMap listeners;
};


class GlobalEventHandler
{
public:
	template< typename TEvent,
		typename std::enable_if<!std::is_base_of< AHierarchicalEvent, TEvent >::value>::type* = nullptr >
	static void dispatch( const TEvent & event )
	{
		handle( event );
	}

	template< typename TEvent,
		typename std::enable_if<std::is_base_of< AHierarchicalEvent, TEvent >::value>::type* = nullptr >
	static void dispatch( const TEvent & event )
	{
		event._recursiveDispatch();
	}

	template< typename TEvent >
	static void handle( const TEvent & event )
	{
		for( const auto & listener : listeners[typeid(TEvent)] )
			static_cast<AEventListener<TEvent>*>(listener)->onEvent( event );
	}

	template< typename TEvent >
	static bool addListener( AEventListener< TEvent > * listener )
	{
		return listeners[typeid(TEvent)].insert( static_cast<void*>(listener) ).second;
	}

	template< typename TEvent >
	static bool removeListener( AEventListener< TEvent > * listener )
	{
		return listeners[typeid(TEvent)].erase( static_cast<void*>(listener) );
	}

private:
	GlobalEventHandler();
	typedef std::type_index EventType;
	typedef std::set< void * > ListenerSet;
	typedef std::map< EventType, ListenerSet > ListenerMap;
	static ListenerMap listeners;
};


template< typename TEvent >
AAutoEventListener<TEvent>::AAutoEventListener( EventHandler * eventHandler ) : eventHandler(eventHandler)
{
	if( this->eventHandler )
		this->eventHandler->template addListener<TEvent>( this );
	else
		GlobalEventHandler::addListener<TEvent>( this );
}

template< typename TEvent >
AAutoEventListener<TEvent>::~AAutoEventListener()
{
	if( this->eventHandler )
		this->eventHandler->template removeListener<TEvent>( this );
	else
		GlobalEventHandler::removeListener<TEvent>( this );
}


template< typename TEvent >
void AutoEventSource::dispatch( const TEvent & event )
{
	if( this->eventHandler )
		this->eventHandler->dispatch( event );
	else
		GlobalEventHandler::dispatch( event );
}

#endif
