#pragma once

namespace ly{
    class Object{
        public:
            Object();
            virtual ~Object();
            bool isPendingDistroyed(){return m_isPendingDistroyed;}
            void distroy();
        private:
            bool m_isPendingDistroyed;
    };

}