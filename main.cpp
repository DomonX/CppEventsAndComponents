#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class Event {
public:
    string eventType;
    vector<string> path;
};
class Component {
public:
    virtual void handleEvent(Event * event) {
        free(event);
    }
    virtual void serveEvent(Event * event) {
        if(parent == NULL) {
            free(event);
        }
        processEvent(event);
    }
    void processEvent(Event * event) {
        event->path.push_back(componentID);
        parent->serveEvent(event);
    }
    void addChildren(Component * newComponent) {
        newComponent->parent = this;
        children.push_back(newComponent);
    }
    string componentID;
    Component * parent;
    vector<Component *> children;
};

class FirstComponent : public Component {
public:
    void serveEvent(Event * event) override {
        if(event->eventType == "onClick") {
            handleOnClick(event);
            return;
        }
        Component::serveEvent(event);
    }
    void handleOnClick(Event * event) {
        cout << "Click was handled" << endl;
        Component::handleEvent(event);
    }
};

int main() {
    FirstComponent * cmp1 = new FirstComponent();
    FirstComponent * cmp2 = new FirstComponent();
    cmp1->addChildren(cmp2);
    Event * evt1 = new Event();
    evt1->eventType = "onClick";
    cmp2->processEvent(evt1);
    return 0;
}
