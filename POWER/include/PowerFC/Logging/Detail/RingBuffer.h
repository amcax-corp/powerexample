#pragma once
#include <vector>

namespace logging{
    namespace Detail{
        template<typename T>
        class RingBuffer{
            std::size_t m_max_pos = 0;
            std::size_t m_head{0};
            std::size_t m_tail{0};
            std::size_t m_overrun_counter{0};

            std::vector<T> m_buffer;

        public:
        using value_type = T;
        RingBuffer()=default;
        explicit RingBuffer(std::size_t max_size):m_max_pos(max_size+1),m_buffer(m_max_pos){}
        RingBuffer(const RingBuffer&)=default;
        RingBuffer& operator=(const RingBuffer&)=default;
        RingBuffer(RingBuffer&& other) noexcept{
            MoveCopy(std::move(other));
        }
        RingBuffer& operator=(RingBuffer&& other) noexcept{
            MoveCopy(std::move(other));
            return *this;
        }

        void Push(T&& item){
            if (m_max_pos > 0)
            {
                m_buffer[m_tail] = std::move(item);
                m_tail = Next(m_tail);
                if (m_tail == m_head)
                {
                    m_head = Next(m_head);
                    ++m_overrun_counter;
                }
            }
        }

        T const& operator[](std::size_t pos) const{
            assert(pos < Size());
            return m_buffer[(m_head + pos) % m_max_pos];
        }

        [[nodiscard]] T const& Front() const{
            return m_buffer[m_head];
        }

        [[nodiscard]] T & Front(){
            return m_buffer[m_head];
        }

        [[nodiscard]] std::size_t Size() const{
            if (m_tail > m_head)
            {
                return m_tail - m_head;
            }else{
                return m_max_pos - m_head + m_tail;
            }
        }

        [[nodiscard]] bool Empty() const{
            return m_head == m_tail;
        }

        [[nodiscard]] bool Full() const{
            if(m_max_pos > 0){
                return Next(m_tail) == m_head;
            }
            return true;
        }

        [[nodiscard]] std::size_t OverrunCounter() const{
            return m_overrun_counter;
        }

        void ResetOverrunCounter(){
            m_overrun_counter = 0;
        }

        void Pop(){
            if(!Empty()){
                m_head = Next(m_head);
            }
        }




        private:
        
        std::size_t Next(std::size_t pos) const noexcept{
            return (pos + 1) % m_max_pos;
        }

        void MoveCopy(RingBuffer && other) noexcept{
            m_max_pos = other.m_max_pos;
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_overrun_counter = other.m_overrun_counter;
            m_buffer = std::move(other.m_buffer);

            other.m_max_pos = 0;
            other.m_head = 0;
            other.m_tail = 0;
            other.m_overrun_counter = 0;
        }

    };
    }
}