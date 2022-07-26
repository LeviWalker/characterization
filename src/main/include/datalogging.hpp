
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
        /**
         * Deletes any extraneous data or fills it in with zeros
         * to have a vector of size N.
         */
        void resize()
        {
            if (N == stateVector.size())
                return;

            // the vector has too many values
            while (stateVector.size() > N)
                stateVector.pop_back();
            // the vector has too few values
            while (stateVector.size() < N)
                stateVector.push_back(0);
        }

    public:
        State(const std::vector<double> &vect) : stateVector{vect} {}

        State()
        {
            stateVector.reserve(N);
            for (int i = 0; i < N; i++)
                stateVector.push_back(0);
        }

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
        std::vector<double> times;
        std::vector<State<N>> states;
        unsigned int size;
        /**
         * Sets the class's instance of size to the time vector's size
         * so that it reflects the actual size of the data.
         * Returns false if there might be a problem with the data.
         */
        bool checkSize()
        {
            int tempSize = times.size();
            if (tempSize > this->size)
                this->size = tempSize;

            if (this->size == 0)
                return false;
            else
                return true;
        }

    public:
        TimeSignatureLogger(unsigned int size)
        {
            times.reserve(size);
            states.reserve(size);

            this->size = size;
        }

        void log(double currentTime, double currentValue)
        {
            log(currentTime, {currentValue});
        }

        void log(double currentTime, const std::vector<double> &currentData)
        {
            log(currentTime, State<N>(currentData));
        }

        void log(double currentTime, const State<N> &currentState)
        {
            times.push_back(currentTime);
            states.push_back(currentState);
        }

        void printIndex(unsigned int index)
        {
            // if index would cause an error, just return
            if (index >= times.size())
                return;

            std::cout << times[index];
            std::vector<double> temp = states[index].get();
            for (int i = 0; i < N; i++)
            {
                std::cout << ", " << temp[i];
            }

            std::cout << std::endl;
        }

        void printCSV()
        {
            int tempSize = times.size();
            for (int i = 0; i < tempSize; i++)
                printIndex(i);
        }

        data::State<N> interpolate(double time) {
            return sample(time);
        }

        /**
         * Interpolates a State based on the logged State data
         */
        data::State<N> sample(double time)
        {
            // ensure this->size is the actual size of the data
            if (!checkSize())
                return data::State<N>();

            double lastIndex = size - 1;

            // set up endpoints for interpolation
            if (time < times[0])
                return states[0];
            if (time > times[lastIndex])
                return states[lastIndex];

            double currentTime;
            int firstIndex = 1; // starting at 1 because we'll treat this as the current
            int middleIndex;
            while (firstIndex != lastIndex)
            {
                middleIndex = (firstIndex + lastIndex) / 2;
                currentTime = times[middleIndex];

                if (currentTime < time) firstIndex = middleIndex + 1; // now search top half
                else lastIndex = middleIndex; // now search bottom half
            }

            currentTime = times[firstIndex];
            double previousTime = times[firstIndex - 1];
            std::vector<double> currentState = states[firstIndex].get();
            std::vector<double> previousState = states[firstIndex - 1].get();

            // y = y0 + m(x - x0) where x is time and y is whatever variable we are calculating
            // and where m = (y1 - y0)/(x1 - x0)

            // notice that (x - x0) and (x1 - x0) never change as we iterate through the loop
            // so we calculate (x - x0) / (x1 - x0) for every iteration without redoing the calculation

            // y = y0 + m(x - x0) becomes y = y0 + a(y1 - y0) where a = (x - x0) / (x1 - x0)

            double a = (time - previousTime) / (currentTime - previousTime);

            std::vector<double> stateVector;
            stateVector.reserve(N);

            for (int i = 0; i < N; i++)
                stateVector[i] = previousState[i] + a * (currentState[i] - previousState[i]);
            
            return stateVector; // implicitly convert std::vector<double> to State<N>
        }
    };
}