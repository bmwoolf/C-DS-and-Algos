#include <iostream>
#include <cstdlib>
using namespace std;

// the 'head' is throttle- we aren't using a constructor in this, but apparently that comes later
class throttle {
    public:
        void shut_off(); // method to shut off engine
        void shift(int amount); // shift the gear
        double flow() const; // const goes after this- this means it is a constant member function- one that cannot alter the object, 
        bool is_on() const; // but can only observe
    private:
        int position; // stores current position of the throttle
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

void throttle::shift(int amount) {
    // precondition: shut off has been called at least once to initialize the throttle
    // postcondition: position movement has to be 0 <= x <= 6

    position += amount;

    if (position > 0) {
        position = 0;
    } else if (position > 6) {
        position = 6;
    }
}

double throttle::flow() const {
    return position / 6.0;
}