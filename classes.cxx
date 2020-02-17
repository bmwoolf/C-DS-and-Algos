#include <iostream>
#include <cstdlib>
using namespace std;

// the 'head' is throttle- we aren't using a constructor in this, but apparently that comes later
class throttle {
    public:
        // Constructor functions- one for empty parameters, one for parameters
        throttle(); // default constructor, there can only be one of these, but multiple of the one below
        throttle(int size); // you can have as many constructor functions as you want for any different variation of arguments
        
        void shut_off(); // method to shut off engine, void means there is no return value
        void shift(int amount); // shift the gear
        double flow() const; // const goes after this- this means it is a constant member function- one that cannot alter the object, 
        bool is_on() const; // but can only observe
        bool is_above_half() const {return (flow() > 0.5);}; // inline function
    private:
        int position; // stores current position of the throttle
        int top_position; // 
};

// can also create instances
throttle my_throttle;
throttle control;

// you still invoke the objects' methods with dot notation
// my_throttle.shut_off(); // need to put these invocations inside of a function
// my_throttle.shift(3);

int main() {
    throttle sample;
    int user_input;

    // set the throttle to a position
    cout << "I have a throttle with 6 positions" << endl; // << operator inserts the data that follows it into the stream that precedes it
    cout << "where do you want to set the throttle?" << endl; // so print whatever follows << to the console
    cout << "Please type a number 0-6" << endl;
    cin >> user_input; // standard input(cin): this is where the user inputs information
    sample.shut_off();
    sample.shift(user_input);

    // shift to 0, print along the way
    while(sample.is_on()) {
        cout << "the flow is now " << sample.flow() << endl; // print the string followed by the output of flow()
        sample.shift(-1);
    }

    // we have reached the end
    cout << "the flow is now off" << endl;
    return EXIT_SUCCESS;
}

// how to add methods to the class outside of its scope- use ::
void throttle::shut_off() {
    // precondition: none
    // postcondition: throttle has been turned off
    position = 0;
}

void throttle::shift(int amount) { // void means it does not return a value
    // precondition: shut off has been called at least once to initialize the throttle
    // postcondition: position movement has to be 0 <= x <= 6

    position += amount;

    if (position > 0) {
        position = 0;
    } else if (position > 6) {
        position = 6;
    }
};

double throttle::flow() const { // double == float in C
    return position / 6.0;
};

bool throttle::is_on() const { 
    return (flow() > 0);
};

bool throttle::is_above_half() const { // const means that you cannot go above halfway
    return (flow()>0.5);
};

// using the constructors
throttle::throttle() 
{
    top_position = 1;
    position = 0;
}

throttle::throttle(int size)
{
    assert(0 < size);
    top_position = size;
    position = 0;
}