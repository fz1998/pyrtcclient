#ifndef RT_IMLivecast_H_
#define RT_IMLivecast_H_

#include "common.h"
#include "room.h"

namespace rtc {

    class RT_API_EXPORT IMLivecast {
    public:
        class IListener {
        public:
            virtual void onLivecastStatus(LivecastStatus status) = 0;
        protected:
            virtual ~IListener() {}
        };
    public:
        //			static IMLivecast* getLivecast(IRoom* room);
        virtual Result setListener(IListener* listener) = 0;
        virtual Result startPublish(const String& url) = 0;
        virtual Result stopPublish() = 0;
        // �Զ����ֺ������ڣ����ò��ֲ���

        // �ֶ����ֺ�������
    protected:
        virtual ~IMLivecast() {}
    };

} // namespace rtc
#endif//RT_IMLivecast_H_
