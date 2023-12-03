#ifndef GUARD_SIMLIB_EVENT_MNGR_H
#define GUARD_SIMLIB_EVENT_MNGR_H

#include "Message.h"
#include "Component.h"
#include "Endpoint.h"

#include <queue>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <memory>
#include <list>


namespace SimLib
{
    class Endpoint;

    typedef std::list<Endpoint*> EndpointList;
    typedef std::unordered_map<Message_Name, EndpointList> SubcriberList;

    class EventMngr
    {
      public:
        EventMngr() = default;
        ~EventMngr() = default;

        void subscribe( Endpoint* endpoint, const Message_Name msgName );
        void unsubscribe( Endpoint* endpoint, const Message_Name msgName );
        void push( const Message* value );
        Message* popFront();
        void dispatch();

      private:
        SubcriberList m_subscriberList;

        std::queue<Message*> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_condition;
    };
} // namespace SimLib

#endif // GUARD_SIMLIB_EVENT_MNGR_H