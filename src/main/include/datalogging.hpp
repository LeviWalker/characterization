
#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace data
{
    template <int N>
    class State
    {
    private:
        std::vector<double> stateVector;
        void resize()
        {
            if (N == stateVector.size())
                return;
            while (stateVector.size() > N)
                stateVector.pop_back();
            while (stateVector.size() < N)
                stateVector.push_back(0);
        }

    public:
        State(const std::vector<double> &vect) : stateVector{vect} {}

        void set(const std::vector<double> &vect)
        {
            stateVector = vect;
        }

        int getN()
        {
            return N;
        }

        const std::vector<double> &get()
        {
            resize();
            return stateVector;
        }
    };

    template <int N>
    class TimeSignatureLogger
    {
    private:
        std::vector<double> time;
        std::vector<State<N>> states;
        int size;
        void checkSize()
        {
            int tempSize = time.size();
            if (tempSize > this->size)
                this->size = tempSize;
        }

    public:
        TimeSignatureLogger(int size)
        {
            time.reserve(size);
            states.reserve(size);

            this->size = size;
        }

        void log(double currentTime, const std::vector<double> &currentData)
        {
            log(currentTime, State<N>(currentData));
        }

        void log(double currentTime, const State<N> &currentState)
        {
            time.push_back(currentTime);
            states.push_back(currentState);
        }

        void printIndex(int index)
        {
            // if index would cause an error, just return
            if (index >= time.size())
                return;

            std::cout << time[index];
            std::vector<double> temp = states[index].get();
            for (int i = 0; i < N; i++)
            {
                std::cout << ", " << temp[i];
            }

            std::cout << std::endl;
        }

        void printCSV()
        {
            int tempSize = time.size();
            for (int i = 0; i < tempSize; i++)
            {
                printIndex(i);
            }
        }
    };
}