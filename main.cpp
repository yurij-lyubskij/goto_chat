#include "structures.h"
#include "stateMachine.h"


int main()
{

    bool isActive = true;
    Machine chat(isActive);
    while (isActive) {
        chat.listActions();
        chat.handleAction();
    }



    return EXIT_SUCCESS;
}
