// this is provided for any developer that uses the class in classes.cxx

// FILE: throttle.h

// CLASS PROVIDED: throttle (part of the namespace in woolf_2a)

// CONSTRUCTORS for throttle class:
//     throttle()
//     throttle(int size)

// MODIFICATION member functions (they don't have a precondition)
//      void shut_off() - the throttle is turned off with this
//      void shift(int amount) - the throttle position is moved by the input amount

// CONSTANT member functions
//      double flow() - return current flow / maximum flow
//      bool is_on() - return true if flow > 0

// VALUE SEMANTICS - not sure what this means yet

#ifndef woolf_throttle // checks if this has been defined already
#define woolf_throttle

namespace woolf_2a
{
    class throttle
    {
        public:
            // constructors
            throttle();
            throttle(int size);
            // modification member functions 
            void shut_off() { position = 0; };
            void shift(int amount);
            // constant member functions
            double flow() const { return position / double(top_position); } // finding the total flow- divide part by total
            bool is_on() const { return (position > 0);} // in-line doesn't have semi colon that follows

        private:
            int top_position;
            int position;
    };
}

#endif